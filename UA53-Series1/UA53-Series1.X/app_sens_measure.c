
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "math.h"

#include "board.h"

#include "bsp/ads1114.h"
#include "bsp/lmp91000.h"
#include "bsp/sht3x.h"

#include "nvm.h"
#include "filter.h"
#include "sensor.h"
#include "app_sens_measure.h"
#include "window.h"
#include "app_linear_regression.h"
#include "app_sens_autoCalibration.h"

extern s_Sens_Measure g_sens_measure;
extern s_Nvm g_nvm;
//extern s_Sens_SNR g_sens_snr;
extern s_Linear_reg g_linear_reg;
extern s_Auto_calib g_sens_autoCalib;
extern volatile uint16_t g_slpSet_cnt2; 
extern volatile uint8_t  g_autoCal_cnt2;

float g_last_value[SENS_COUNT];
float g_temp_value[SENS_COUNT];

volatile uint32_t g_large_counter;
volatile uint16_t gCnt;

#ifdef USE_KALMAN_FILTER
s_KalmanFilter_t kalmanFilter;
//s_KalmanFilter_t KMfilter_raw_value;
#endif

#ifdef USE_DEBUG_PRINT
extern uint8_t writeBuffer[64];
#endif

void sensMeasure_init(void)
{
    g_large_counter = 0;
    g_sens_measure.seq = SENS_INIT;
    g_sens_measure.isInitDone = false;
    g_sens_measure.isGasSensor_Success = false;
    g_sens_measure.isTemp_Success = false;

#ifdef USE_KALMAN_FILTER
    kalmanFilter._current_estimate = 0.0f;
    kalmanFilter._err_estimate = 0.0f;
    kalmanFilter._err_measure = 0.0f;
    kalmanFilter._kalman_gain = 0.0f;
    kalmanFilter._last_estimate = 0.0f;
    kalmanFilter._q_process = 0.0f;
    Kalman_setMeasurementError(&kalmanFilter, g_nvm.flash.KMf_e_measure);
    Kalman_setEstimateError(&kalmanFilter, g_nvm.flash.KMF_e_estimate); 
    Set_KamanFilter_Sensitivity(g_nvm.flash.window_size);
  
//    KMfilter_raw_value._current_estimate = 0.0f;
//    KMfilter_raw_value._err_estimate = 0.0f;
//    KMfilter_raw_value._err_measure = 0.0f;
//    KMfilter_raw_value._kalman_gain = 0.0f;
//    KMfilter_raw_value._last_estimate = 0.0f;
//    KMfilter_raw_value._q_process = 0.0f; 
//    Kalman_setMeasurementError(&KMfilter_raw_value,1);
//    Kalman_setEstimateError(&KMfilter_raw_value,1); 
//    Kalman_setProcessNoise(&KMfilter_raw_value,0.0001);
#endif
}

static bool sensMeasure_temp_read()
{
    float temp, humi;

    if (g_sens_measure.isInitDone == false)
        return false;

    if (sensor_read_temp_humi(&temp, &humi)) {
        g_temp_value[LV_TEMP] = temp;
        g_temp_value[LV_TEMP] += g_nvm.flash.tempOffset;
        g_temp_value[LV_HUMI] = humi;
        return true;
    }
    return false;
}

static bool sensMeasure_gas_read()
{
    int16_t raw;

    if (g_sens_measure.isInitDone == false)
        return false;

    if (sensor_ADC_read(&raw)) {
        float volt = ADCto_uVoltage(raw, ADC_GAIN);
        g_temp_value[LV_GAS_VOLT] = Kalman_updateEstimate(&kalmanFilter, volt); 
        
        //volt = window_moving_average_recursion(volt, WINDOW_SIZE);        
        /* SNR */
        //g_last_value[LV_SNR] = sensMeasure_SNR(&g_sens_snr, g_last_value[LV_RAW_VALUE], g_last_value[LV_FILTERD_VALUE]);
        
#if (defined UA53_SO2_50 || defined UA53_O3_20)    
        g_temp_value[LV_GAS_VOLT] = g_temp_value[LV_GAS_VOLT] * 2.0f;
#endif               
        float cmp_val = 0.0f;
        if (g_nvm.flash.temp_compensate == TEMP_COMPENSATION) 
            cmp_val = compensate_temperature(g_temp_value[LV_TEMP]);
        
        g_temp_value[LV_GAS_PPM] = gasSensor_calib(cmp_val, g_temp_value[LV_GAS_VOLT]);
        
        if(g_nvm.flash.filter_mode == FIL_MODE) 
            g_temp_value[LV_GAS_PPM] = gasSensor_lowfilter(g_temp_value[LV_GAS_PPM]); 
        
        return true;
    }
    return false;
}

void sensMeasure_task(void)
{
    switch (g_sens_measure.seq) 
    {
        case SENS_INIT:
            if (sensor_init()) {
                g_sens_measure.isInitDone = true;
                g_large_counter = 0;
                g_sens_measure.seq = SENS_READY;
            } else {
                g_large_counter = 0;
                g_sens_measure.seq_count = 30; // 300ms
                g_sens_measure.seq = SENS_WAIT;
                g_sens_measure.next_seq = SENS_INIT;                      
            } break;
        case SENS_READY:   
            if (g_large_counter >= MEASURE_DELAY_COUNT) { // 1sec
                
                if (gCnt == 3600) gCnt = 1;
                else gCnt++;
                
                g_large_counter = 0;
                g_sens_measure.seq = SENS_TEMP_MEASURE; 
            } break;
        case SENS_TEMP_MEASURE:
            g_sens_measure.isTemp_Success = sensMeasure_temp_read();
            g_large_counter = 0;
            g_sens_measure.seq_count = 2; 
            g_sens_measure.seq = SENS_WAIT;
            g_sens_measure.next_seq = SENS_GAS_MEASURE;
            break;
        case SENS_GAS_MEASURE:
            g_sens_measure.isGasSensor_Success = sensMeasure_gas_read();
            g_large_counter = 0;
            g_sens_measure.seq = SENS_APPLY;
            break;
        case SENS_APPLY:
            if (g_sens_measure.isGasSensor_Success) {
                g_last_value[LV_GAS_VOLT] = g_temp_value[LV_GAS_VOLT];
                // regression: gas uV  
                Linear_regression(&g_linear_reg, g_last_value[LV_GAS_VOLT]);
                
//#ifdef USE_KALMAN_FILTER
//                g_last_value[LV_GAS_PPM] = Kalman_updateEstimate(&kalmanFilter, g_temp_value[LV_GAS_PPM]); 
//#else                
                g_last_value[LV_GAS_PPM] = g_temp_value[LV_GAS_PPM];
//#endif                 
                g_last_value[LV_GAS_PPM] = g_last_value[LV_GAS_PPM] + g_nvm.flash.gasOffset;; 
            }
            if (g_sens_measure.isTemp_Success) {
                g_last_value[LV_TEMP] = g_temp_value[LV_TEMP];
                g_last_value[LV_HUMI] = g_temp_value[LV_HUMI];
            }
            g_large_counter = 0;
            g_sens_measure.seq = SENS_DISPLAY;
            break;
        case SENS_WAIT:
            if (g_large_counter > g_sens_measure.seq_count) {
                g_large_counter = 0;
                g_sens_measure.seq = g_sens_measure.next_seq;
            } break;
        case SENS_DISPLAY:
        {
#ifdef USE_DEBUG_PRINT
            //sprintf(writeBuffer, "Raw: %.0f, Flt: %.0f, rAvg: %.2f, fAvg: %.2f, snr: %.2f\r\n",
            //        g_last_value[LV_RAW_VALUE], g_last_value[LV_FILTERD_VALUE], g_sens_snr.rawData_avg, g_sens_snr.fltData_avg, g_last_value[LV_SNR]);
            //sprintf(writeBuffer, "Raw: %.1f, Flt: %.1f, rRMS: %.1f, fRMS: %.1f, snr: %.2f\r\n",
            //        g_last_value[LV_RAW_VALUE], g_last_value[LV_FILTERD_VALUE], g_sens_snr.rawData_RMS, g_sens_snr.fltData_RMS, g_last_value[LV_SNR]);
            if (g_nvm.flash.auto_Calib && g_sens_autoCalib.Seq_autoCal != AUTO_CALIB) {
                sprintf(writeBuffer,"s: %.1f uV: %.1f,sumZ: %.1f cnt: %d,Ccnt: %d,chk: %d\r\n", g_linear_reg.slope, g_last_value[LV_GAS_VOLT], 
                                                                    g_sens_autoCalib.sumZero_uV, gCnt, g_autoCal_cnt2, g_sens_autoCalib.chk_cnt);
            } else {
                sprintf(writeBuffer,"s: %.1f\tm: %.1f,M: %.1f\t%.1f cnt: %d,Scnt: %d\r\n", g_linear_reg.slope, g_sens_autoCalib.slope_min,
                                                                    g_sens_autoCalib.slope_max, g_last_value[LV_GAS_VOLT], gCnt, g_slpSet_cnt2);
            }                
            write_command(writeBuffer);
#endif
            g_large_counter = 0;
            g_sens_measure.seq = SENS_READY;
        } break;
    }// end switch
}// end function



/* ************************************************************************
 * 
 *      2022-10-06
 *      Signal to noise (SNR) 
 *                         
 * ************************************************************************ */ 
void sensMeasure_SNR_init(s_Sens_SNR* pSNR)
{
    for (uint8_t i = 0; i < SIZE; i++) {
        pSNR->rawData_buffer[i] = 0.0f;
        pSNR->fltData_buffer[i] = 0.0f;
    }
    pSNR->rawData_RMS = 0.0f;
    pSNR->rawData_RMS = 0.0f;      
}

float sensMeasure_SNR(s_Sens_SNR* pSNR, float rawData, float filData)
{
    uint8_t idx;
    pSNR->rawData_sum = 0.0f;
    pSNR->fltData_sum = 0.0f;
    //pSNR->rawData_sqrSum = 0.0f;
    //pSNR->fltData_sqrSum = 0.0f;
    float RawData = rawData/1000;   // mV  
    float FilData = filData/1000;
    
    /* data store */
    for (idx = 0; idx < SIZE -1; idx++) {
        pSNR->rawData_buffer[idx] = pSNR->rawData_buffer[idx +1];
        pSNR->fltData_buffer[idx] = pSNR->fltData_buffer[idx +1];
    }
    pSNR->rawData_buffer[SIZE -1] = RawData;    //RawData*RawData;     
    pSNR->fltData_buffer[SIZE -1] = FilData;    //FilData*FilData;           
    
    /* data sum */
    for (idx = 0; idx < SIZE; idx++) {
        pSNR->rawData_sum += pSNR->rawData_buffer[idx];
        pSNR->fltData_sum += pSNR->fltData_buffer[idx];       
        //pSNR->rawData_sqrSum += pSNR->rawData_buffer[idx];
        //pSNR->fltData_sqrSum += pSNR->fltData_buffer[idx];
    }
    
    /* data avg */
    pSNR->rawData_avg = pSNR->rawData_sum / SIZE;
    pSNR->fltData_avg = pSNR->fltData_sum / SIZE;
            
    /* RMS (Root Mean square) */
    //pSNR->rawData_RMS = sqrt(pSNR->rawData_sqrSum / SIZE);
    //pSNR->fltData_RMS = sqrt(pSNR->fltData_sqrSum / SIZE);
        
    /* SNR: [dB] */
    pSNR->SNRv =  pSNR->fltData_avg / pSNR->rawData_avg;
    pSNR->SNRdB = 10.0f * log10(pSNR->SNRv);
    //pSNR->SNRv = pSNR->fltData_RMS / pSNR->rawData_RMS;       
    //pSNR->SNRdB = 20.0f * log10(pSNR->SNRv);
    return pSNR->SNRdB;
}
