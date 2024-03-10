/* 
 * File:   filter.h
 * Author: karl
 *
 * Created on 2020 7 16
 */

#ifndef FILTER_H
#define	FILTER_H

#define MAX_FILTER_SIZE     15


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


typedef enum {
    LEVEL_1 = 1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4,
	LEVEL_5,
	LEVEL_6,
	LEVEL_7,
	LEVEL_8,
	LEVEL_9,
	LEVEL_10,
	LEVEL_11,
	LEVEL_12,
	LEVEL_13,
    LEVEL_14,
    LEVEL_15
} e_KalmaFilter_sensitivity;

#endif

#ifdef	__cplusplus
extern "C" {
#endif


#ifdef USE_KALMAN_FILTER
	//Kalman Filter Fuction.
	float Kalman_updateEstimate(s_KalmanFilter_t *pObj,float mea);
	
	void Kalman_setMeasurementError(s_KalmanFilter_t *pObj,float mea_e);
	void Kalman_setEstimateError(s_KalmanFilter_t *pObj,float est_e);
	void Kalman_setProcessNoise(s_KalmanFilter_t *pObj,float q);
	
	float Kalman_getKalmanGain(s_KalmanFilter_t *pObj);
	float Kalman_getEstimateError(s_KalmanFilter_t *pObj);

    void Set_KamanFilter_Sensitivity(e_KalmaFilter_sensitivity e_level);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* FILTER_H */

