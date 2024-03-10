
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "board.h"

#include "usb/usb_device.h"

#include "bsp/ads1114.h"
#include "bsp/power.h"
#include "util/_string.h"

#include "nvm.h"
#include "filter.h"
#include "sensor.h"
#include "app_sens_measure.h"

// nvm data
extern s_Nvm g_nvm;
// last float value
extern u_SensorValue g_modbus_value;
float g_last_value[CHANNEL_COUNT][SENS_COUNT];
float g_temp_value[SENS_COUNT];

//state machine
extern s_Sens_Measure g_sens_measure;

#ifdef USE_PPM_WINDOW
//ewma filter;
s_EwmaFilter_t ewmaFilter[CHANNEL_COUNT]; // for ewma filter
#endif

#ifdef USE_KALMAN_FILTER
s_KalmanFilter_t kalmanFilter[CHANNEL_COUNT]; // for kalman filter
#endif

volatile uint16_t g_large_counter;
#ifdef USE_CHECK_CHANNEL_PERIODIC
volatile uint32_t g_sensor_counter;
#endif
volatile uint8_t g_channel_no;
volatile uint8_t g_retry_count;

#ifdef USE_DEBUG_PRINT
extern uint8_t writeBuffer[64];
#endif

void sensMeasure_init()
{
#ifdef USE_PPM_WINDOW
    ewmaFilter[0].hasInit = false;
    ewmaFilter[0].prevValue = 0.0f;
    ewmaFilter[1].hasInit = false;
    ewmaFilter[1].prevValue = 0.0f;

#endif
#ifdef USE_KALMAN_FILTER
    kalmanFilter[0]._current_estimate = 0.0f;
    kalmanFilter[0]._err_estimate = 0.0f;
    kalmanFilter[0]._err_measure = 0.0f;
    kalmanFilter[0]._kalman_gain = 0.0f;
    kalmanFilter[0]._last_estimate = 0.0f;
    kalmanFilter[0]._q_process = 0.0f;

    kalmanFilter[1]._current_estimate = 0.0f;
    kalmanFilter[1]._err_estimate = 0.0f;
    kalmanFilter[1]._err_measure = 0.0f;
    kalmanFilter[1]._kalman_gain = 0.0f;
    kalmanFilter[1]._last_estimate = 0.0f;
    kalmanFilter[1]._q_process = 0.0f;
    //CH1 Gas mV
    Kalman_setMeasurementError(&kalmanFilter[0],1);
    Kalman_setEstimateError(&kalmanFilter[0],1);
    Kalman_setProcessNoise(&kalmanFilter[0],0.001);
    //CH2 Gas mV
    Kalman_setMeasurementError(&kalmanFilter[1],1);
    Kalman_setEstimateError(&kalmanFilter[1],1);
    Kalman_setProcessNoise(&kalmanFilter[1],0.001);
#endif
    sensMeasure_sensor_init();

    g_sens_measure.seq = SENS_INIT;
}

void sensMeasure_sensor_init()
{
    for (uint8_t i = 0 ; i < CHANNEL_COUNT ; i++) {
        g_sens_measure.existChannel[i] = false;
        g_sens_measure.isChecksum[i] = false;
        g_sens_measure.isSensorInit[i] = false;
        g_last_value[i][LV_TEMP] = NO_VALUE;
        g_last_value[i][LV_GAS_VOLT] = NO_VALUE;
        g_last_value[i][LV_GAS_PPM] = NO_VALUE;
    }

    g_sens_measure.seq = SENS_SENSOR_INIT;

    g_channel_no = 0;
    g_large_counter = 0;
#ifdef USE_CHECK_CHANNEL_PERIODIC
    g_sensor_counter = 0;
#endif
    g_retry_count = 0;
}

static bool sensMeasure_temp_read(uint8_t channel)
{
    int16_t raw;

    if (sensor_ADC_read(channel, &raw)) {
        float volt = ADCto_uVoltage(raw, FSR_2p048V);
        g_temp_value[LV_TEMP] = gasSensor_temperature(volt);
        g_temp_value[LV_TEMP] += g_nvm.eeprm[channel].tempOffset;
        return true;
    }
    return false;
}

static bool sensMeasure_gas_read(uint8_t channel)
{
    int16_t raw;

    if (sensor_ADC_read(channel, &raw)) {
        float volt = ADCto_uVoltage(raw, g_nvm.eeprm[channel].adc_gain);
        // kalman filter apply
        #ifdef USE_KALMAN_FILTER
        g_temp_value[LV_GAS_VOLT] = Kalman_updateEstimate(&kalmanFilter[channel], volt);
        #else
        g_temp_value[LV_GAS_VOLT] = volt;
        #endif
#if 1
        float cmp_value = 0.0f;
        if (g_nvm.eeprm[channel].temp_compensate == TEMP_COMPENSATION) {
            cmp_value = compensate_temperature(g_temp_value[LV_TEMP], g_nvm.eeprm[channel].baseLine_temp, g_nvm.eeprm[channel].sensor_model);
        }
        g_temp_value[LV_GAS_PPM] = gasSensor_calib(channel, cmp_value, volt);
#else
        float slope = 1.0f;
        if (g_nvm.eeprm[channel].temp_compensate == TEMP_COMPENSATION) {
            slope = compensate_temperature(g_temp_value[LV_TEMP], g_nvm.eeprm[channel].baseLine_temp, g_nvm.eeprm[channel].sensor_model);
        }
        g_temp_value[LV_GAS_PPM] = gasSensor_calib(channel, slope, volt);
#endif
        return true;
    }
    return false;
}

#ifdef USE_DEBUG_PRINT
uint8_t len = 0;
#endif

void sensMeasure_task()
{
    switch (g_sens_measure.seq) 
    {
        case SENS_INIT:
            if (g_large_counter >= 1000) { // 10sec
                g_channel_no = 0;
                g_large_counter = 0;
                g_retry_count = 0;
                g_sens_measure.seq = SENS_EEPRM_INIT;
            }
            break;
        case SENS_EEPRM_INIT:
            if (I2C_Bus_SourceGet() && !ACCESS_SourceGet()) {
                nvm_clear_channel(g_channel_no);
                g_sens_measure.existChannel[g_channel_no] = false;
                g_sens_measure.isChecksum[g_channel_no] = false;
                g_sens_measure.isSensorInit[g_channel_no] = false;
                /*
                 * access pin set high
                 */
                ACCESS_SourceSet(true); // access pin set high
                
                bool ret = nvm_read_eeprom_all(g_channel_no);

                /*
                 * access pin set low
                 */
                ACCESS_SourceSet(false); // access pin set low

                if (ret == true) {
                    g_sens_measure.existChannel[g_channel_no] = true;
                    if (g_nvm.eeprm[g_channel_no].check_sum == checksum(g_nvm.eeprm[g_channel_no].byte, EEPROM_ALL_SIZE-2)) {
                        g_sens_measure.isChecksum[g_channel_no] = true;
#ifdef USE_DEBUG_PRINT
                        len += sprintf(writeBuffer + len, "[%d]SENS_EEPRM_INIT success\r\n", g_channel_no);
#endif
                    }
                    g_retry_count = 0;
                    g_large_counter = 0;
                    g_sens_measure.seq = SENS_EEPRM_INIT_NEXT;
                } else {
                    g_retry_count++;
                    if (g_retry_count >= NVM_INIT_RETRY_COUNT) {
                        g_retry_count = 0;
                        g_large_counter = 0;
                        g_sens_measure.seq = SENS_EEPRM_INIT_NEXT;
                    } else {
                        g_large_counter = 0;
                        g_sens_measure.seq_count = 10; // 100ms
                        g_sens_measure.seq = SENS_WAIT;
                        g_sens_measure.next_seq = SENS_EEPRM_INIT;
                    }
                }
            } else {
                g_large_counter = 0;
                g_sens_measure.seq_count = 10; // 100ms
                g_sens_measure.seq = SENS_WAIT;
                g_sens_measure.next_seq = SENS_EEPRM_INIT;               
            }
            break;
        case SENS_EEPRM_INIT_NEXT:
            g_channel_no++; // skip next cycle
            if (g_channel_no >= CHANNEL_COUNT) {
                g_channel_no = 0;
                g_large_counter = 0;
                g_sens_measure.seq_count = 10; // 100ms
                g_sens_measure.seq = SENS_WAIT;
                g_sens_measure.next_seq = SENS_SENSOR_INIT;

#ifdef USE_DEBUG_PRINT
                write_command(writeBuffer);
                len = 0;
#endif
#ifdef USE_CHECK_CHANNEL_PERIODIC
                g_sensor_counter = 0;
#endif
            } else {
                g_large_counter = 0;
                g_sens_measure.seq_count = 10; // 100ms
                g_sens_measure.seq = SENS_WAIT;
                g_sens_measure.next_seq = SENS_EEPRM_INIT;
            }
            break;
        case SENS_SENSOR_INIT:
            if (I2C_Bus_SourceGet() && !ACCESS_SourceGet()) {

                if (g_sens_measure.existChannel[g_channel_no] == true &&
                        g_sens_measure.isChecksum[g_channel_no] == true) {
                    /*
                     * access pin set high
                     */
                    ACCESS_SourceSet(true); // access pin set high

                    bool ret = sensor_init(g_channel_no);

                    /*
                     * access pin set low
                     */
                    ACCESS_SourceSet(false); // access pin set low

                    if (ret == true) {
                        g_sens_measure.isSensorInit[g_channel_no] = true;
                        g_retry_count = 0;
                        g_large_counter = 0;
                        g_sens_measure.seq = SENS_SENSOR_INIT_NEXT;
#ifdef USE_DEBUG_PRINT
                        len += sprintf(writeBuffer + len, "[%d]SENS_INIT success\r\n", g_channel_no);
#endif
                    } else {
                        g_retry_count++;
                        if (g_retry_count >= NVM_INIT_RETRY_COUNT) {
                            g_retry_count = 0;
                            g_large_counter = 0;
                            g_sens_measure.seq = SENS_SENSOR_INIT_NEXT;
                        } else {
                            g_large_counter = 0;
                            g_sens_measure.seq_count = 10; // 100ms
                            g_sens_measure.seq = SENS_WAIT;
                            g_sens_measure.next_seq = SENS_SENSOR_INIT;
                        }
                    }
                } else {
                    g_retry_count = 0;
                    g_large_counter = 0;
                    g_sens_measure.seq = SENS_SENSOR_INIT_NEXT;
                }
            } else {
                g_large_counter = 0;
                g_sens_measure.seq_count = 10; // 100ms
                g_sens_measure.seq = SENS_WAIT;
                g_sens_measure.next_seq = SENS_SENSOR_INIT;
#ifdef USE_DEBUG_PRINT
                len += sprintf(writeBuffer + len, "[%d]SENS_INIT fail\r\n", g_channel_no);
#endif
            }
            break;
        case SENS_SENSOR_INIT_NEXT:
            g_channel_no++; // skip next cycle
            if (g_channel_no >= CHANNEL_COUNT) {
                g_channel_no = 0;
                g_large_counter = MEASURE_DELAY_COUNT - 10; // 100ms
                g_sens_measure.seq = SENS_READY;

#ifdef USE_DEBUG_PRINT
                write_command(writeBuffer);
                len = 0;
#endif
            } else {
                g_large_counter = 0;
                g_sens_measure.seq_count = 10; // 100ms
                g_sens_measure.seq = SENS_WAIT;
                g_sens_measure.next_seq = SENS_SENSOR_INIT;
            }
            break;
            
        case SENS_READY:
            if (USBGetDeviceState() == CONFIGURED_STATE || g_nvm.flash.sensing_on == SENSING_ON) {
#ifdef USE_CHECK_CHANNEL_PERIODIC
                if (g_sensor_counter >= SENSOR_INIT_DELAY_COUNT) { // 1min
                    g_sensor_counter = 0;
                    g_large_counter = 0;
                    g_channel_no = 0;
                    g_sens_measure.seq = SENS_INIT;
                } else
#endif
                if (g_large_counter >= MEASURE_DELAY_COUNT) { // 5sec
                    g_large_counter = 0;
                    if (g_sens_measure.existChannel[0] && g_sens_measure.isChecksum[0] && g_sens_measure.isSensorInit[0]) {
                        g_channel_no = 0;
                        g_sens_measure.seq = SENS_CHANGE_TEMP;
                    } else {
                        if (g_sens_measure.existChannel[1] && g_sens_measure.isChecksum[1] && g_sens_measure.isSensorInit[1]) {
                            g_channel_no = 1;
                            g_sens_measure.seq = SENS_CHANGE_TEMP;
                        }
                    }
                }
            }
            break;
        case SENS_CHANGE_TEMP:
            if (I2C_Bus_SourceGet() && !ACCESS_SourceGet()) {
                /*
                 * access pin set high
                 */
                ACCESS_SourceSet(true); // access pin set high

                if (g_sens_measure.isChecksum[g_channel_no] && g_sens_measure.isSensorInit[g_channel_no] &&
                        sensor_set_temp_mode(g_channel_no)) {
                    g_large_counter = 0;
                    g_sens_measure.seq_count = 5; // 50ms
                    g_sens_measure.seq = SENS_WAIT;
                    g_sens_measure.next_seq = SENS_TEMP_MEASURE;
#ifdef USE_DEBUG_PRINT
                    len += sprintf(writeBuffer + len, "[%d]SENS_CHANGE_TEMP success\r\n", g_channel_no);
#endif
                } else {
                    /*
                     * access pin set low
                     */
                    ACCESS_SourceSet(false); // access pin set low
#ifdef USE_DEBUG_PRINT
                    len += sprintf(writeBuffer + len, "[%d]SENS_CHANGE_TEMP fail\r\n", g_channel_no);
#endif
                    g_large_counter = 0;
                    g_sens_measure.seq = SENS_NEXT;
                }
            } else {
                g_large_counter = 0;
                g_sens_measure.seq_count = 10; // 100ms
                g_sens_measure.seq = SENS_WAIT;
                g_sens_measure.next_seq = SENS_CHANGE_TEMP;
            }
            break;
        case SENS_TEMP_MEASURE:
            if (sensMeasure_temp_read(g_channel_no)) {
                g_large_counter = 0;
                g_sens_measure.seq_count = 2; // 20ms
                g_sens_measure.seq = SENS_WAIT;
                g_sens_measure.next_seq = SENS_CHANGE_GAS;
            } else {
#ifdef USE_DEBUG_PRINT
                len += sprintf(writeBuffer + len, "[%d]SENS_TEMP_MEASURE2 fail\r\n", g_channel_no);
#endif
                g_large_counter = 0;
                g_sens_measure.seq = SENS_NEXT;
            }

            /*
             * access pin set low
             */
            ACCESS_SourceSet(false); // access pin set low

            break;
        case SENS_CHANGE_GAS:
            if (I2C_Bus_SourceGet() && !ACCESS_SourceGet()) {
                /*
                 * access pin set high
                 */
                ACCESS_SourceSet(true); // access pin set high

                if (g_sens_measure.isChecksum[g_channel_no] && g_sens_measure.isSensorInit[g_channel_no] &&
                    sensor_set_gas_mode(g_channel_no)) {
                    g_large_counter = 0;
                    g_sens_measure.seq_count = 6; // 60ms 7ms := 1/SPS 128
                    g_sens_measure.seq = SENS_WAIT;
                    g_sens_measure.next_seq = SENS_GAS_MEASURE;
                } else {
#ifdef USE_DEBUG_PRINT
                    len += sprintf(writeBuffer + len, "[%d]SENS_CHANGE_GAS fail\r\n", g_channel_no);
#endif
                    g_large_counter = 0;
                    g_sens_measure.seq = SENS_NEXT;
                    /*
                     * access pin set low
                     */
                    ACCESS_SourceSet(false); // access pin set low
                }
            } else {
                g_large_counter = 0;
                g_sens_measure.seq_count = 10; // 100ms
                g_sens_measure.seq = SENS_WAIT;
                g_sens_measure.next_seq = SENS_CHANGE_GAS;
            }
            break;
        case SENS_GAS_MEASURE:
            if (sensMeasure_gas_read(g_channel_no)) {
                g_large_counter = 0;
                g_sens_measure.seq = SENS_APPLY;
            } else {
#ifdef USE_DEBUG_PRINT
                len += sprintf(writeBuffer + len, "[%d]SENS_GAS_MEASURE fail\r\n", g_channel_no);
#endif
                g_large_counter = 0;
                g_sens_measure.seq = SENS_NEXT;
            }

            /*
             * access pin set low
             */
            ACCESS_SourceSet(false); // access pin set low

            break;
        case SENS_APPLY:
            if (g_nvm.eeprm[g_channel_no].sensor_model >= NH3_100 && g_nvm.eeprm[g_channel_no].sensor_model <= H2S_50) {
                g_last_value[g_channel_no][LV_GAS_VOLT] = g_temp_value[LV_GAS_VOLT];
                #ifdef USE_PPM_WINDOW
                g_last_value[g_channel_no][LV_GAS_PPM] = ewmaFilter_get(&ewmaFilter[g_channel_no], g_temp_value[LV_GAS_PPM], g_nvm.eeprm[g_channel_no].window_size);
                g_last_value[g_channel_no][LV_GAS_PPM] += g_nvm.eeprm[g_channel_no].gasOffset;
                #else
                g_last_value[g_channel_no][LV_GAS_PPM] = g_temp_value[LV_GAS_PPM] + g_nvm.eeprm[g_channel_no].gasOffset;
                #endif
                g_modbus_value.float_value[g_channel_no] = g_last_value[g_channel_no][LV_GAS_PPM];
                g_last_value[g_channel_no][LV_TEMP] = g_temp_value[LV_TEMP];
            } else {
                g_last_value[g_channel_no][LV_TEMP] = g_last_value[g_channel_no][LV_GAS_VOLT] = NO_VALUE;
                g_modbus_value.float_value[g_channel_no] = g_last_value[g_channel_no][LV_GAS_PPM] = NO_VALUE;
            }
            g_large_counter = 0;
            g_sens_measure.seq = SENS_NEXT;
            break;
        case SENS_NEXT:
            g_channel_no++; // skip next cycle
            if (g_channel_no >= CHANNEL_COUNT) {
                g_channel_no = 0;
                g_large_counter = 0;
                g_sens_measure.seq = SENS_DISPLAY;
            } else {
                g_large_counter = 0;
                g_sens_measure.seq_count = 2; // 20ms
                g_sens_measure.seq = SENS_WAIT;
                g_sens_measure.next_seq = SENS_CHANGE_TEMP;
            }
            break;
        case SENS_WAIT:
            if (g_large_counter >= g_sens_measure.seq_count) {
                g_large_counter = 0;
                g_sens_measure.seq = g_sens_measure.next_seq;
            }
            break;
        case SENS_DISPLAY:
        {
#ifdef USE_DEBUG_PRINT
            sprintf(writeBuffer + len, "[1][%d][%d]%.2f,%.2f,%.2f\r\n[2][%d][%d]%.2f,%.2f,%.2f\r\n",
                    g_sens_measure.isSensorInit[0],
                    g_nvm.eeprm[0].adc_gain,
                    g_last_value[0][LV_GAS_VOLT], 
                    g_last_value[0][LV_GAS_PPM],
                    g_last_value[0][LV_TEMP],
                    g_sens_measure.isSensorInit[1],
                    g_nvm.eeprm[1].adc_gain,
                    g_last_value[1][LV_GAS_VOLT], 
                    g_last_value[1][LV_GAS_PPM],
                    g_last_value[1][LV_TEMP]
                    );
            write_command(writeBuffer);
            len = 0;
#endif
            g_retry_count = 0;
            g_channel_no = 0;
            g_large_counter = 0;
            g_sens_measure.seq = SENS_READY;
        }
            break;
    }
}
