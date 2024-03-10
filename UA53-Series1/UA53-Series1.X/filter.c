
#include <stdbool.h>
#include <stdint.h>
#include <math.h> // for fabs

#include "board.h"

#include "filter.h"


#ifdef USE_KALMAN_FILTER

s_KalmanFilter_t kalmanFilter; 
e_KalmaFilter_sensitivity e_level;
float g_sensitivity;

static float kalman_q_factor[MAX_FILTER_SIZE] = {
        0.99f, 0.8f, 0.6f, 0.5f, 0.3f, 0.1f, 0.05f, 0.01f, 0.005f,0.001f, 
        0.0005f, 0.0001f, 0.00005f, 0.00001f, 0.000001f};


	float Kalman_updateEstimate(s_KalmanFilter_t *pObj,float mea)
	{

		pObj->_kalman_gain = pObj->_err_estimate/(pObj->_err_estimate + pObj->_err_measure);
		
		pObj->_current_estimate = pObj->_last_estimate + pObj->_kalman_gain * (mea - pObj->_last_estimate);
		
		pObj->_err_estimate =  (1.0 - pObj->_kalman_gain)*pObj->_err_estimate + 
			fabs(pObj->_last_estimate-pObj->_current_estimate)*pObj->_q_process;
		
		pObj->_last_estimate=pObj->_current_estimate;
		
		return pObj->_current_estimate;
	}

	void Kalman_setMeasurementError(s_KalmanFilter_t *pObj,float mea_e)
	{
		pObj->_err_measure=mea_e;
	}
	void Kalman_setEstimateError(s_KalmanFilter_t *pObj,float est_e)
	{
		pObj->_err_estimate=est_e;
	}

	void Kalman_setProcessNoise(s_KalmanFilter_t *pObj, float q)
	{
		pObj->_q_process=q;
	}

	float Kalman_getKalmanGain(s_KalmanFilter_t *pObj)
	{
		return pObj->_kalman_gain;

	}
	float Kalman_getEstimateError(s_KalmanFilter_t *pObj)
	{
		  return pObj->_err_estimate;
	}
    
    void Set_KamanFilter_Sensitivity(e_KalmaFilter_sensitivity e_level)
    {
        switch (e_level)
        {
            case LEVEL_1 : g_sensitivity = 1.0;	    break; //high speed 
            case LEVEL_2 : g_sensitivity = 0.9;	    break;	
            case LEVEL_3 : g_sensitivity = 0.8;	    break;	
            case LEVEL_4 : g_sensitivity = 0.7;	    break;	
            case LEVEL_5 : g_sensitivity = 0.6;	    break;	
            case LEVEL_6 : g_sensitivity = 0.5;	    break;
            case LEVEL_7 : g_sensitivity = 0.4;	    break;
            case LEVEL_8 : g_sensitivity = 0.35;	break;
            case LEVEL_9 : g_sensitivity = 0.3;	    break;
            case LEVEL_10 : g_sensitivity = 0.25;	break;
            case LEVEL_11 : g_sensitivity = 0.2;	break;
            case LEVEL_12 : g_sensitivity = 0.1;	break;
            case LEVEL_13 : g_sensitivity = 0.01;	break;
            case LEVEL_14 : g_sensitivity = 0.001;	break;
            case LEVEL_15 : g_sensitivity = 0.0001;	break; //low speed
            default: g_sensitivity = 0.1;          break;
        }
        Kalman_setProcessNoise(&kalmanFilter,g_sensitivity); 
    }
    
#endif //kalman

