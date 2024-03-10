
#ifndef SENSOR_H
#define	SENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif

//    void sensor_initialize(void);

    bool sensor_init(uint8_t channel);
    bool sensor_adc_init(uint8_t channel, bool isTemp);
    bool sensor_lmp_init(uint8_t channel);

    bool sensor_set_temp_mode(uint8_t channel);
    bool sensor_set_gas_mode(uint8_t channel);
    
    void sensor_temp_fahrenheit(float* temp);
    
    bool sensor_ADC_read(uint8_t channel, int16_t* raw_adc);
    float ADCto_uVoltage(int16_t raw_adc, uint8_t gain);

    float compensate_temperature(float temp, float baseLine_temp, uint8_t model);
    float gasSensor_calib(uint8_t channel, float slope, float gas_uVolt);
    float gasSensor_temperature(float temp_uVolt);

    void max7323_set_lmp_on(uint8_t channel);
    void max7323_set_lmp_off(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_H */

