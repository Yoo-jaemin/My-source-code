
#include <stdbool.h>
#include <stdint.h>

#include "window.h"


float gMv_Window_buff[WINDOW_SIZE] = {0.0f, };

float window_moving_average_recursion(float uV, uint8_t window_size)
{
    uint8_t idx;
    static float avg = 0.0f;
    
    avg = avg + (uV - gMv_Window_buff[0]) / window_size;
    
    for(idx = 0; idx < window_size-1; idx++)
        gMv_Window_buff[idx] = gMv_Window_buff[idx+1];    
    gMv_Window_buff[idx] = uV;
    
    return avg;
}
