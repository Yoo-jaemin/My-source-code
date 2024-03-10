
#include <stdbool.h>
#include <stdint.h>

#include "board.h"
#include "bsp/lmp91000.h"
#include "bsp/ads1114.h"
#include "bsp/max7323.h"

#include "nvm.h"
#include "app_sens_measure.h"
#include "sensor.h"


extern s_Nvm g_nvm;

static float gasSensor_filter(float gasConcent)
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
    /*
    float retval;
    if (gasConcent < 0.0f && gasConcent >= -0.5f)
        retval = 0.01f;
    else if (gasConcent < -0.5f && gasConcent >= -1.0f)
        retval = 0.02f;
    else if (gasConcent < -1.0f && gasConcent >= -5.0f)
        retval = 0.03f;
    else if (gasConcent < -5.0f && gasConcent >= -10.0f)
        retval = 0.04f;
    else if (gasConcent < -10.0f && gasConcent >= -30.0f)
        retval = 0.05f;
    else if (gasConcent < -30.0f)
        retval = 0.06f;
    else
        retval = gasConcent;
    return retval;
    */
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

void max7323_set_lmp_on(uint8_t channel)
{
    uint8_t wr;  // O7 O6 P5 P4 P3 P2 O1 O0 set low for active low

    for (uint8_t i = 0 ; i < CHANNEL_COUNT ; i++) {
        if (i == channel) wr = 0b00100000;
        else wr = 0b00110000;
        max7323_set_gpio(i, wr);
    }
}

void max7323_set_lmp_off(void)
{
    uint8_t wr[2] = { 0b00110000, 0b00011000 };  // O7 O6 P5 P4 P3 P2 O1 O0 set high for active low

    for (uint8_t i = 0 ; i < CHANNEL_COUNT ; i++) {
        max7323_set_gpio(i, wr[i]);
    }
}

//void sensor_initialize(void)
//{
//    max7323_set_lmp_off();
//}

bool sensor_adc_init(uint8_t channel, bool isTemp)
{
    bool ret;
    if (isTemp) ret = ads1114_SetUp(channel, CONTINUE_CONV, FSR_2p048V, SPS128); // temp
    else        ret = ads1114_SetUp(channel, CONTINUE_CONV, g_nvm.eeprm[channel].adc_gain, SPS128); // gas

    return ret;
}

//static bool sensor_lmp_setup(uint8_t mode)
//{
//    //lmp91000 init
//    if (lmp91000_isReady() == false) {
//       return false;
//    }
//
//    if (lmp91000_unlock() == false) {
//       return false;
//    }
//
//    if (lmp91000_set_Mode(DISABLE, mode) == false) {
//        return false;
//    }
//
//    return true;
//}

bool sensor_lmp_init(uint8_t channel)
{
    max7323_set_lmp_on(channel);

    //lmp91000 init
    if (lmp91000_isReady() == false) {
        max7323_set_lmp_off();
       return false;
    }

    if (lmp91000_unlock() == false) {
        max7323_set_lmp_off();
       return false;
    }

    if (lmp91000_set_GainRLoad(g_nvm.eeprm[channel].lmp_gain, g_nvm.eeprm[channel].lmp_rload) == false) {
        max7323_set_lmp_off();
        return false;
    }

    // INTERNAL: reference voltage = vdd
    // EXTERNAL: reference voltage = 2.5v
    if (lmp91000_set_Reference(EXTERNAL, g_nvm.eeprm[channel].lmp_intZ, NAGATIVE, B0P) == false) {
        max7323_set_lmp_off();
        return false;
    }

    if (lmp91000_set_Mode(DISABLE, STANBY) == false) {
        return false;
    }

    max7323_set_lmp_off();
    return true;
}

bool sensor_init(uint8_t channel)
{
    //g_nvm.eeprm[channel].lmp_gain, g_nvm.eeprm[channel].lmp_rload
    //if (apply >= NONE && apply <= H2S_50)
    if (!(g_nvm.eeprm[channel].sensor_model >= NH3_100 && g_nvm.eeprm[channel].sensor_model <= H2S_50))
        return false;
    return sensor_lmp_init(channel);
}

void sensor_temp_fahrenheit(float* temp)
{
    *temp = (*temp * 1.8f) + 32.0f;
}

bool sensor_ADC_read(uint8_t channel, int16_t* raw_adc)
{
    return ads1114_read(channel, raw_adc);
}

float ADCto_uVoltage(int16_t raw_adc, uint8_t gain)
{
	float uVolt;
    float lsb = FSR_set_LSB(gain);
	uVolt = (float)raw_adc * lsb;
	return uVolt; 
}

#if 1
float compensate_temperature(float temp, float baseLine_temp, uint8_t model)
{
    float cmp_val = 0.0f; // temperature compensation value

    if (model == NH3_100) {
        if (temp >= 25.0f && temp < 30.0f)
            cmp_val = 0.034f * temp - 0.826f;

        else if (temp >= 30.0f && temp < 34.0f) 
            cmp_val = 0.05f * temp - 1.356f;

        else if (temp >= 34.0f && temp < 38.0f)
            cmp_val = 0.095f * temp - 2.892f;

        else if (temp >= 38.0f && temp < 41.0f)
            cmp_val = 0.1f * temp - 3.1f;

        else if (temp >= 41.0f)
            cmp_val = 1.0f;

        else
            cmp_val = 0.0f;  
    } else if (model == H2S_50) {
    
    }

    return cmp_val;
}

float gasSensor_calib(uint8_t channel, float cmp_val, float gas_uVolt)
{
    float gas_ppm;

    float span = g_nvm.eeprm[channel].span_uV;
    float baseline = g_nvm.eeprm[channel].baseLine_uV;
    float CalibrationGas = g_nvm.eeprm[channel].CalibrationGas;

    if ((span - baseline) == 0.0f || span <= baseline )
        return 0.0f;
    
    gas_ppm = ((CalibrationGas * gas_uVolt) / (span - baseline) - (CalibrationGas * baseline) / (span - baseline)) - cmp_val;

    if(g_nvm.eeprm[channel].filter_mode == FIL_MODE) //filterd atcd
    {
         gas_ppm = gasSensor_filter(gas_ppm); 
    }

    return gas_ppm;
}

#else
float compensate_temperature(float temp, float baseLine_temp, uint8_t model)
{
    float slope = 1.0f;

    if (model == NH3_100) {
        float temp_slope = 0.0f;
        if (baseLine_temp >= -10.0f && baseLine_temp < 10.0f)
            temp_slope = 0.03f * baseLine_temp + 0.7f;
        else if (baseLine_temp >= 10.0f && baseLine_temp < 20.0f)
            temp_slope = -0.0025f * baseLine_temp + 1.02525f;
        else if (baseLine_temp >= 20.0f && baseLine_temp < 40.0f)
            temp_slope = -0.011f * baseLine_temp + 1.19525f;    
        
        float difference = 0.98f - temp_slope;   //f(20) = 0.98 

        if (temp >= -10.0f && temp < 10.0f)
            slope = 0.03f * temp + 0.7f + difference;
        else if (temp >= 10.0f && temp < 20.0f)
            slope = -0.0025f * temp + 1.02525f + difference;
        else if (temp >= 20.0f && temp < 40.0f)
            slope = -0.011f * temp + 1.19525f + difference;

    } else if (model == H2S_50) {
        float temp_slope = 0.0f;
        if (baseLine_temp >= -10.0f && baseLine_temp < 20.0f)
            temp_slope = 0.004f * baseLine_temp + 0.92f;
        else if (baseLine_temp >= 20.0f && baseLine_temp < 40.0f)
            temp_slope = 0.002f * baseLine_temp + 0.96f;

        float difference = 1.0f - temp_slope; //f(20) = 1.0

        if (temp >= -10.0f && temp < 20.0f)
            slope = 0.004f * temp + 0.92f + difference;
        else if (temp >= 20.0f && temp < 40.0f)
            slope = 0.002f * temp + 0.96f + difference;
    }

    if (slope == 0.0f) slope = 1.0f;

    return (1/slope);
}

float gasSensor_calib(uint8_t channel, float slope, float gas_uVolt)
{
    float gas_ppm;

    float span = g_nvm.eeprm[channel].span_uV;
    float baseline = g_nvm.eeprm[channel].baseLine_uV;
    float CalibrationGas = g_nvm.eeprm[channel].CalibrationGas;

    if (span == 0.0f || baseline == 0.0f || CalibrationGas == 0.0f || span <= baseline)
    {
        return 0.0f;
    }

    gas_ppm = (CalibrationGas * gas_uVolt) / (span - baseline)*slope - (CalibrationGas * baseline) / (span - baseline);

    if(g_nvm.eeprm[channel].filter_mode == FIL_MODE) //filterd atcd
    {
         gas_ppm = gasSensor_filter(gas_ppm); 
    }

    return gas_ppm;
}
#endif

/* ******************** 
*    0°C  -> 1560 mV
*    50°C -> 1154 mV
*    
*    -10 -> internal_min = 5.32
*     40 -> internal_max = 40.41
*     etemp= 1.42 * itemp -17.57;
********************  */
float gasSensor_temperature(float temp_uVolt)
{
    float temp = -0.12f * (temp_uVolt/1000.0f + 500.0f) + 187.2f;
    return temp;
}

bool sensor_set_temp_mode(uint8_t channel)
{
    max7323_set_lmp_on(channel);

    if (lmp91000_set_Mode(DISABLE, TEMP_MEASURE_TIAON) == false) {
        max7323_set_lmp_off();
        return false;
    }

    max7323_set_lmp_off();
    
    if (sensor_adc_init(channel, true) == false)
        return false;

    return true;
}

bool sensor_set_gas_mode(uint8_t channel)
{
    max7323_set_lmp_on(channel);

    if (lmp91000_set_Mode(DISABLE, AMPEROETRIC_3LEAD) == false) {
        max7323_set_lmp_off();
        return false;
    }

    max7323_set_lmp_off();

    if (sensor_adc_init(channel, false) == false)
        return false;

    return true;
}
