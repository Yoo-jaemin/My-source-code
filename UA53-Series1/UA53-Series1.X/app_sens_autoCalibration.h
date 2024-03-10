
  
#ifndef APP_SENS_AUTOCALIB_H
#define	APP_SENS_AUTOCALIB_H

#include <stdint.h>

#define FIVE_HUN_mS 50
#define ONE_SECOND  100
#define ONE_MINUTE  6000 
#define TEN_MINUTES 500 
#define ONE_HOUR    60


typedef enum {
    AUTO_CALIB_INIT,
    AUTO_CALIB_READY,
    AUTO_CALIB_CHECK,        
    AUTO_CALIB        
} e_AutoCalib;

typedef enum {
    SLOPE_SET_INIT,
    SLOPE_SET_LED,        
    SLOPE_SET_READY,
    SLOPE_SAVE,
    SLOPE_SET,
    SLOPE_SET_END
} e_AutoCalib_slp;

typedef struct {
    uint8_t Seq_autoCal; 
    uint8_t Seq_slpSet;
    uint8_t slpSet_en;
    uint8_t led_slpSet;
   
    float slope_min;
    float slope_max;
    
    volatile uint8_t chk_cnt;
    float sumZero_uV;
    float avgZero_uV;
    
    float sft_ppm;
    
} s_Auto_calib;


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

   void sens_autoCalib_init(void); 
   void sens_autoCalib_task(void);
   void sens_autoCalib_slp_set_task(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	

