/* 
 * File:   sensor.h
 * Author: brian
 *
 */

#ifndef SENSOR_H
#define	SENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif

    bool sensor_init(void);

    bool sensor_read_temp_humi(float* temp, float* humi);
    void sensor_temp_fahrenheit(float* temp);
    
    bool sensor_ADC_read(int16_t* raw_adc);
    float ADCto_uVoltage(int16_t raw_adc, uint8_t gain);

    float compensate_temperature(float temp);
    float gasSensor_calib(float slope, float gas_uVolt);
    float gasSensor_lowfilter(float gasConcent);

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_H */

