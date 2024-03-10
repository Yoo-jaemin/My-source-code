 
#ifndef APP_LINEAR_REGRESSION_H
#define	APP_LINEAR_REGRESSION_H


#define DATA_SIZE           60  
#define _DATA_SAMPLES_

#ifdef _DATA_SAMPLES_
    #define DATA_SAMPLES    10
#endif


typedef struct {
    
#ifdef _DATA_SAMPLES_
    float x[DATA_SAMPLES];
    float y[DATA_SAMPLES];
#else
    float x[DATA_SIZE];
    float y[DATA_SIZE];
#endif    
    
    uint8_t position;
    float time_cnt;
    
    float sum_x;
    float sum_x2;
    float sum_y;
    float sum_xy;
    
    float slope;
    float offset;
    
    //float Slope[DATA_POINT];
    //float slope_sum;
    //float slope_avg;
        
} s_Linear_reg;

  
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    
    void Linear_regression_init(s_Linear_reg* p);
    void Linear_regression(s_Linear_reg* p, float uVoltage);

    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	

