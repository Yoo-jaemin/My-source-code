
#include <stdbool.h>
#include <stdint.h>
#include <xc.h>

#include "board.h"

#include "bsp/lmp91000.h"
#include "bsp/ads1114.h"
#include "bsp/sht3x.h"

#include "nvm.h"
#include "app_sens_measure.h"
#include "sensor.h"


extern s_Nvm g_nvm;
extern s_Sens_Measure g_sens_measure;
float g_uV_per_ppm;

float gasSensor_lowfilter(float gasConcent)
{
    // modified at 2021-02-15
    float retval;
    if (gasConcent < 0.2 && gasConcent >= 0.0)
        retval = 0.0;					//Added 
    else if (gasConcent < 0 && gasConcent >= -0.5)
        retval = 0.0;					//0.01
    else if (gasConcent < -0.5 && gasConcent >= -1.0)
        retval = 0.02;
    else if (gasConcent < -1.0 && gasConcent >= -5.0)
        retval = 0.03;
    else if (gasConcent < -5.0 && gasConcent >= -10.0)
        retval = 0.04;
    else if (gasConcent < -10.0 && gasConcent >= -30.0)
        retval = 0.05;
    else if (gasConcent < -30.0)
        retval = 0.06;
    else
        retval = gasConcent;
    return retval;
}

static float FSR_set_LSB(uint8_t gain)
{
    if(gain == FSR_6p144V)
        return 187.5f;
    else if(gain == FSR_4p096V)
        return 125.0f;
    else if(gain == FSR_1p024V)
        return 31.25f;
    else if(gain == FSR_0p512V)
        return 15.62f;
    else if(gain == FSR_0p256V)
        return 7.81f;
    // default, FSR_2p048V
    return 62.5f;
}

static bool sensor_adc_init(void)
{
    return ads1114_SetUp(CONTINUE_CONV, ADC_GAIN, SPS128); 
}

static bool sensor_lmp_init(void)
{
    if (lmp91000_isReady() == false)
       return false;

    if (lmp91000_unlock() == false)
       return false;

    if (lmp91000_set_GainRLoad(LMP_GAIN, LMP_RLOAD) == false)
        return false;

    // INTERNAL: reference voltage = vdd
    // EXTERNAL: reference voltage = 2.5v
    if (lmp91000_set_Reference(EXTERNAL, LMP_INTZ, REF_SOURCE, LMP_BIAS) == false)
        return false;

    // gas read mode
    if (lmp91000_set_Mode(DISABLE, AMPEROETRIC_3LEAD) == false)
        return false;

    if (lmp91000_lock() == false)
       return false;

    return true;
}

static bool sensor_sht3x_init(void)
{
    if (sht3x_heaterOff() == false)
        return false;

    __delay_ms(50);

    if (sht3x_clear_status_reg() == false)
        return false;

    __delay_ms(50);

    //start periodic measurement, with low repeatability and 1 measurements per second
    return sht3x_measure_start();
}

bool sensor_init(void)
{
    if (sensor_sht3x_init() == false)
        return false;

    if (sensor_lmp_init() == false)
        return false;

    if (sensor_adc_init() == false)
        return false;
    
    return true;
}

bool sensor_read_temp_humi(float* temp, float* humi)
{
    // get temperature & relative humidity
#if (USE_SHT3X_COMPENSATE)
    return sht3x_measure_nonblock_compensate(temp, humi);
#else
    return sht3x_measure_nonblock_read(temp, humi);
#endif
}

void sensor_temp_fahrenheit(float* temp)
{
    *temp = (*temp * 1.8f) + 32.0f;
}

bool sensor_ADC_read(int16_t* raw_adc)
{
    if (ads1114_read_ready() == false)
        return false;

    return ads1114_read(raw_adc);
}

float ADCto_uVoltage(int16_t raw_adc, uint8_t gain)
{
	float uVolt;
    float lsb = FSR_set_LSB(gain);
	uVolt = (float)raw_adc * lsb; 
	return uVolt; 
}

float compensate_temperature(float temp)
{
    float cmp_val = 0.0f;     
    
#ifdef UA53_CO_1000 
    if (temp >= 28.0f && temp < 34.0f)
        cmp_val = 0.55f * temp -15.06f;
    else if (temp >= 34.0f && temp < 41.0f)
        cmp_val = 0.7f * temp -20.0f;
    else if (temp >= 41.0f)
        cmp_val = 8.0f;
    else
        cmp_val = 0.0f;    
#endif
    return cmp_val;
}

float gasSensor_calib(float cmp_val, float gas_uVolt)
{
    float gas_ppm     = 0.0f;
    float baseline    = g_nvm.flash.baseLine_uV;
    float sensitivity = g_nvm.flash.nA_per_ppm;
    //float uV_per_ppm;
    g_uV_per_ppm = sensitivity * LMP_TIA_GAIN;
    //uV_per_ppm = sensitivity * LMP_TIA_GAIN;
    //gas_ppm = (gas_uVolt - baseline) / uV_per_ppm;
    /* equivalence */
    float nA = ((gas_uVolt + g_nvm.flash.zeroShift_uV) - (baseline + g_nvm.flash.zeroShift_uV)) / LMP_TIA_GAIN;   
    if (sensitivity == 0)   return 0.0f;

    gas_ppm = nA / sensitivity - cmp_val;

    //sprintf(b,"uVolt: %.2f, BL: %.2f, Gain: %.2f, nA: %.2f, ppm: %.2f\r\n", uVolt, baseline, amp_gain, nA, gas_ppm);
    //write_command(b);
    return gas_ppm;
}
