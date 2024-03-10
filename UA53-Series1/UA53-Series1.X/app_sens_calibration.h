 
#ifndef APP_SENS_CALIBRATION_H
#define	APP_SENS_CALIBRATION_H

#define ZERO_CALIB_TIME 18000 //3mins 

typedef enum {
    CALIB_INIT,
    CALIB_WAIT,
    CALIB_ZERO      
} e_Calib_Seq;

typedef struct {
    uint8_t seq;
    bool zero_cal;
} s_Sens_Calib;

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    void sens_ZeroCalib_init(void);
    void sens_ZeroCalib_task(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	

