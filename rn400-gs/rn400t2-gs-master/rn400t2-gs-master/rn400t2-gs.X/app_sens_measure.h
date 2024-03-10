/* 
 * File:   app_sens_measure.h
 *
 */

#ifndef APP_SENS_MEASURE_H
#define	APP_SENS_MEASURE_H

enum e_Measure_Seq {
    SENS_INIT,
    SENS_EEPRM_INIT,
    SENS_EEPRM_INIT_NEXT,
    SENS_SENSOR_INIT,
    SENS_SENSOR_INIT_NEXT,
	SENS_READY,
    SENS_CHANGE_TEMP,
    SENS_TEMP_MEASURE,
    SENS_CHANGE_GAS,
    SENS_GAS_MEASURE,
    SENS_APPLY,
    SENS_NEXT,
    SENS_WAIT,
    SENS_DISPLAY
};

enum e_SensorValue {
    LV_GAS_VOLT,
    LV_GAS_PPM,
    LV_TEMP
};

#define SENS_COUNT LV_TEMP+1

typedef union {
    __pack uint16_t word[(sizeof(float)/sizeof(uint16_t)) * 4];
    __pack float float_value[4];
} u_SensorValue;

typedef struct {
    uint8_t seq;
    uint8_t next_seq;
    uint8_t seq_count;

    bool existChannel[CHANNEL_COUNT];
    bool isChecksum[CHANNEL_COUNT];
    bool isSensorInit[CHANNEL_COUNT];

} s_Sens_Measure;


#ifdef	__cplusplus
extern "C" {
#endif
    
    void sensMeasure_init();
    void sensMeasure_sensor_init();
    void sensMeasure_task();

#ifdef	__cplusplus
}
#endif

#endif	/* APP_SENS_MEASURE_H */

