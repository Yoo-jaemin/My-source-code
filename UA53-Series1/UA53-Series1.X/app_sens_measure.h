/* 
 * File:   app_sens_measure.h
 *
 */

#ifndef APP_SENS_MEASURE_H
#define	APP_SENS_MEASURE_H

enum e_Measure_Seq {
    SENS_INIT,
	SENS_READY,
    SENS_TEMP_MEASURE,
    SENS_GAS_MEASURE,
    SENS_APPLY,
    SENS_WAIT,
    SENS_DISPLAY
};

enum e_SensorValue {
    LV_GAS_VOLT,
    LV_GAS_PPM,
    LV_RAW_VALUE,
    LV_FILTERD_VALUE,
    LV_SNR,
    LV_TEMP,
    LV_HUMI
};

#define SENS_COUNT LV_HUMI+1
#define SIZE    30

typedef struct {
    uint8_t seq;
    uint8_t next_seq;
    uint8_t seq_count;

    bool isInitDone;
    bool isGasSensor_Success; 
    bool isTemp_Success;
    
} s_Sens_Measure;

typedef struct {
    float rawData_buffer[SIZE];
    float fltData_buffer[SIZE];
    
    float rawData_sum;
    float fltData_sum;
    
    float rawData_sqrSum;
    float fltData_sqrSum;
    
    float rawData_avg;
    float fltData_avg;
    
    float rawData_RMS;
    float fltData_RMS;
    
    float SNRv;
    float SNRdB;
    
} s_Sens_SNR;

#ifdef	__cplusplus
extern "C" {
#endif
    
    void sensMeasure_init();
    void sensMeasure_task();

    // 2022-10-06
    void sensMeasure_SNR_init(s_Sens_SNR* pSNR);
    float sensMeasure_SNR(s_Sens_SNR* pSNR, float rawData, float filData);
    
#ifdef	__cplusplus
}
#endif

#endif	/* APP_SENS_MEASURE_H */

