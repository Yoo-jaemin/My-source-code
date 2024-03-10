
# 1 "filter.c"

# 15 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\stdbool.h"
typedef unsigned char bool;

# 13 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\stdint.h"
typedef signed char int8_t;

# 20
typedef signed int int16_t;

# 28
typedef __int24 int24_t;

# 36
typedef signed long int int32_t;

# 52
typedef unsigned char uint8_t;

# 58
typedef unsigned int uint16_t;

# 65
typedef __uint24 uint24_t;

# 72
typedef unsigned long int uint32_t;

# 88
typedef signed char int_least8_t;

# 96
typedef signed int int_least16_t;

# 109
typedef __int24 int_least24_t;

# 118
typedef signed long int int_least32_t;

# 136
typedef unsigned char uint_least8_t;

# 143
typedef unsigned int uint_least16_t;

# 154
typedef __uint24 uint_least24_t;

# 162
typedef unsigned long int uint_least32_t;

# 181
typedef signed char int_fast8_t;

# 188
typedef signed int int_fast16_t;

# 200
typedef __int24 int_fast24_t;

# 208
typedef signed long int int_fast32_t;

# 224
typedef unsigned char uint_fast8_t;

# 230
typedef unsigned int uint_fast16_t;

# 240
typedef __uint24 uint_fast24_t;

# 247
typedef unsigned long int uint_fast32_t;

# 268
typedef int32_t intmax_t;

# 282
typedef uint32_t uintmax_t;

# 289
typedef int16_t intptr_t;




typedef uint16_t uintptr_t;

# 30 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\math.h"
extern double fabs(double);
extern double floor(double);
extern double ceil(double);
extern double modf(double, double *);
extern double sqrt(double);
extern double atof(const char *);
extern double sin(double) ;
extern double cos(double) ;
extern double tan(double) ;
extern double asin(double) ;
extern double acos(double) ;
extern double atan(double);
extern double atan2(double, double) ;
extern double log(double);
extern double log10(double);
extern double pow(double, double) ;
extern double exp(double) ;
extern double sinh(double) ;
extern double cosh(double) ;
extern double tanh(double);
extern double eval_poly(double, const double *, int);
extern double frexp(double, int *);
extern double ldexp(double, int);
extern double fmod(double, double);
extern double trunc(double);
extern double round(double);

# 73 "board.h"
enum {
CELSIUS,
FAHRENHEIT
};

enum {
RAW_MODE,
FIL_MODE
};

enum {
TEMP_NOT_COMPENSATION,
TEMP_COMPENSATION
};

enum {
USB_NONE,
USB_DETACHED,
USB_ATTACHED
};

enum {
OFF,
ON
};

# 156
void write_command(const uint8_t* buff);
uint16_t* get_product_desc();

# 16 "filter.h"
typedef struct
{
float _err_measure;
float _err_estimate;

float _q_process;

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

# 56
float Kalman_updateEstimate(s_KalmanFilter_t *pObj,float mea);

void Kalman_setMeasurementError(s_KalmanFilter_t *pObj,float mea_e);
void Kalman_setEstimateError(s_KalmanFilter_t *pObj,float est_e);
void Kalman_setProcessNoise(s_KalmanFilter_t *pObj,float q);

float Kalman_getKalmanGain(s_KalmanFilter_t *pObj);
float Kalman_getEstimateError(s_KalmanFilter_t *pObj);

void Set_KamanFilter_Sensitivity(e_KalmaFilter_sensitivity e_level);

# 13 "filter.c"
s_KalmanFilter_t kalmanFilter;
e_KalmaFilter_sensitivity e_level;
float g_sensitivity;

static float kalman_q_factor[15] = {
0.99f, 0.8f, 0.6f, 0.5f, 0.3f, 0.1f, 0.05f, 0.01f, 0.005f,0.001f,
0.0005f, 0.0001f, 0.00005f, 0.00001f, 0.000001f};


float Kalman_updateEstimate(s_KalmanFilter_t *pObj,float mea)
{

pObj->_kalman_gain = pObj->_err_estimate/(pObj->_err_estimate + pObj->_err_measure);

pObj->_current_estimate = pObj->_last_estimate + pObj->_kalman_gain * (mea - pObj->_last_estimate);

pObj->_err_estimate = (1.0 - pObj->_kalman_gain)*pObj->_err_estimate +
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
case LEVEL_1 : g_sensitivity = 1.0; break;
case LEVEL_2 : g_sensitivity = 0.9; break;
case LEVEL_3 : g_sensitivity = 0.8; break;
case LEVEL_4 : g_sensitivity = 0.7; break;
case LEVEL_5 : g_sensitivity = 0.6; break;
case LEVEL_6 : g_sensitivity = 0.5; break;
case LEVEL_7 : g_sensitivity = 0.4; break;
case LEVEL_8 : g_sensitivity = 0.35; break;
case LEVEL_9 : g_sensitivity = 0.3; break;
case LEVEL_10 : g_sensitivity = 0.25; break;
case LEVEL_11 : g_sensitivity = 0.2; break;
case LEVEL_12 : g_sensitivity = 0.1; break;
case LEVEL_13 : g_sensitivity = 0.01; break;
case LEVEL_14 : g_sensitivity = 0.001; break;
case LEVEL_15 : g_sensitivity = 0.0001; break;
default: g_sensitivity = 0.1; break;
}
Kalman_setProcessNoise(&kalmanFilter,g_sensitivity);
}

