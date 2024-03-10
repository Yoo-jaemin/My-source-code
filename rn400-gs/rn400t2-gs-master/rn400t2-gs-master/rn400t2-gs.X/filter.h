/* 
 * File:   filter.h
 * Author: karl
 *
 * Created on 2020 7 16
 */

#ifndef FILTER_H
#define	FILTER_H

#define MAX_FILTER_SIZE     15
#define DEFAULT_FILTER_SIZE 2

typedef struct
{
    bool hasInit;
    float prevValue;

} s_EwmaFilter_t;

#ifdef USE_KALMAN_FILTER
typedef struct
{
	float _err_measure;				//R? , ?? ??? ???? ? 
	float _err_estimate;			//
									//measure_err, est_err could be same value.
	float _q_process;				//usually a small number between 0.001 and 1 - how fast your measurement moves. Recommended 0.01. higher faster

	float _current_estimate;
	float _last_estimate;
	float _kalman_gain;
} s_KalmanFilter_t;

typedef struct
{
   char hasInit;
   s_KalmanFilter_t kalman;
} s_KalmanApp_t;
#endif

#if 0
typedef struct s_MedianNode
{
    int16_t value;                      //sample value
    struct s_MedianNode *nextAge;    //pointer to next oldest value
    struct s_MedianNode *nextValue;  //pointer to next smallest value
    struct s_MedianNode *prevValue;  //pointer to previous smallest value
} s_MedianNode_t;

typedef struct
{
    uint8_t numNodes;          //median node buffer length
    s_MedianNode_t *medianBuffer;    //median node buffer
    s_MedianNode_t *ageHead;         //pointer to oldest value
    s_MedianNode_t *valueHead;       //pointer to smallest value
    s_MedianNode_t *medianHead;      //pointer to median value
} s_MedianFilter_t;
#endif

#ifdef	__cplusplus
extern "C" {
#endif

#if 0
    bool medianFilter_init(s_MedianFilter_t* medianFilter);
    int16_t medianFilter_insert(s_MedianFilter_t* medianFilter, int16_t sample);
#endif

    float ewmaFilter_get(s_EwmaFilter_t* ewmaFilter, float inputValue, uint8_t sensitivity);

#ifdef USE_KALMAN_FILTER
	//Kalman Filter Fuction.
	float Kalman_updateEstimate(s_KalmanFilter_t *pObj,float mea);
	
	void Kalman_setMeasurementError(s_KalmanFilter_t *pObj,float mea_e);
	void Kalman_setEstimateError(s_KalmanFilter_t *pObj,float est_e);
	void Kalman_setProcessNoise(s_KalmanFilter_t *pObj,float q);
	
	float Kalman_getKalmanGain(s_KalmanFilter_t *pObj);
	float Kalman_getEstimateError(s_KalmanFilter_t *pObj);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* FILTER_H */

