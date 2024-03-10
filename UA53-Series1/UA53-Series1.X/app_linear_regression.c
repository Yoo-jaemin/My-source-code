/*
 * File:   app_linear_regression.c
 * Author: brian
 *
 * Created on 2022 10/11
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <math.h>

#include "app_linear_regression.h"


static float slope_average(s_Linear_reg* p, float slope);

volatile uint8_t g_time_cnt;


void Linear_regression_init(s_Linear_reg* p)
{
    uint8_t index;
    
#ifdef _DATA_SAMPLES_    
    for (index = 0; index < DATA_SAMPLES; index++) { 
        p->x[index] = 0.0f;
        p->y[index] = 0.0f;
    }
#else
    for (index = 0; index < DATA_SIZE; index++) { 
        p->x[index] = 0.0f;
        p->y[index] = 0.0f;
    }
#endif     
    
    p->position = 0;
    p->time_cnt = 0.0f;
    
    p->sum_x = 0.0f;
    p->sum_y = 0.0f;
    p->sum_x2 = 0.0f;
    p->sum_xy = 0.0f;
    p->slope = 0.0f;
    p->offset = 0.0f;    
}

/* **************************************************
 *  Linear regression: least Square Method
 *
 *  Real-time voltage prediction
 *  x-Axis: time
 *  y-Axis: uVoltage 
 ************************************************** */
#ifdef _DATA_SAMPLES_ 

void Linear_regression(s_Linear_reg* p, float uVoltage)
{
    uint8_t index;
    float slp;
    
    p->sum_x = 0.0f;
    p->sum_y = 0.0f;
    p->sum_x2 = 0.0f;
    p->sum_xy = 0.0f;
    
    /* time, voltage store */
    if (p->time_cnt != DATA_SIZE) {     // buffer isn't full
        p->time_cnt = p->time_cnt + 1.0f; 
        if ( fmod(p->time_cnt, (float)(DATA_SIZE/DATA_SAMPLES)) == 0.0f ) {
            p->x[p->position] = p->time_cnt;         
            p->y[p->position] = uVoltage;
            p->position++;
        }
    } else {
        g_time_cnt++;
        if (g_time_cnt == DATA_SIZE/DATA_SAMPLES) {
            g_time_cnt = 0;
            for (index = 0; index < DATA_SAMPLES -1; index++) {
                p->x[index] = (p->x[index +1] - (float)(DATA_SIZE/DATA_SAMPLES));
                p->y[index] = p->y[index +1];        
            }
            p->x[DATA_SAMPLES -1] = (float)DATA_SIZE;
            p->y[DATA_SAMPLES -1] = uVoltage;
        }
    }
                
    /* data sum */
    for (index = 0; index < DATA_SAMPLES; index++) {
        p->sum_x  += p->x[index]; 
        p->sum_y  += p->y[index];
        p->sum_x2 += p->x[index] * p->x[index];
        p->sum_xy += p->x[index] * p->y[index];
    }
    
    /* calculating slope and offset */
    p->slope = (DATA_SAMPLES*p->sum_xy - p->sum_x*p->sum_y) / (DATA_SAMPLES*p->sum_x2 - p->sum_x*p->sum_x);
    p->offset = (p->sum_y - p->slope*p->sum_x) / DATA_SAMPLES;        
} // end function

#else

void Linear_regression(s_Linear_reg* p, float uVoltage)    // fitting y= ax+b
{
    uint8_t index;
    float slp;
    
    p->sum_x = 0.0f;
    p->sum_y = 0.0f;
    p->sum_x2 = 0.0f;
    p->sum_xy = 0.0f;
    
    /* time, voltage store */
    if (p->time_cnt != DATA_SIZE) {     // buffer isn't full
        p->time_cnt = p->time_cnt + 1.0f; 
        p->x[p->position] = p->time_cnt;         
        p->y[p->position] = uVoltage;
        p->position++;
    } else {
        for (index = 0; index < DATA_SIZE -1; index++) {
            p->x[index] = p->x[index +1] - 1.0f;
            p->y[index] = p->y[index +1];
        }   
        p->x[DATA_SIZE -1] = (float)DATA_SIZE; 
        p->y[DATA_SIZE -1] = uVoltage;
    }
       
    /* data sum */
    for (index = 0; index < DATA_SIZE; index++) {
        p->sum_x  += p->x[index]; 
        p->sum_y  += p->y[index];
        p->sum_x2 += p->x[index] * p->x[index];
        p->sum_xy += p->x[index] * p->y[index];
    }
    
    /* calculating slope and offset */
    p->slope = (DATA_SIZE*p->sum_xy - p->sum_x*p->sum_y) / (DATA_SIZE*p->sum_x2 - p->sum_x*p->sum_x);
    p->offset = (p->sum_y - p->slope*p->sum_x) / DATA_SIZE;
}

#endif



#if 0

static float slope_average(s_Linear_reg* p, float slope)
{
    uint8_t idx;
    p->slope_sum = 0.0f;
    
    /* slope store */
    for (idx = 0; idx < DATA_SAMPLES -1; idx++)
        p->Slope[idx] = p->Slope[idx +1];
    p->Slope[DATA_SAMPLES -1] = slope;
    
    /* slope sum */
    for (idx = 0; idx < DATA_SAMPLES; idx++)
        p->slope_sum += p->Slope[idx];
    
    return p->slope_sum / DATA_SAMPLES;
}

#endif




