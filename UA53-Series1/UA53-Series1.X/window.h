
#ifndef WINDOW_H
#define	WINDOW_H

#define WINDOW_SIZE     12


#ifdef	__cplusplus
extern "C" {
#endif

    float window_moving_average_recursion(float uV, uint8_t window_size);
    
    
#ifdef	__cplusplus
}
#endif

#endif	

