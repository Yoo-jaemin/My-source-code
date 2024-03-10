
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

# 51 "board.h"
enum {
SENSING_OFF,
SENSING_ON
};

# 73
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
NONE,
NH3_100,
H2S_50,
EO,
NH3_1000
};

enum {
MODBUS_SLAVE_MODE,
MODBUS_MASTER_MODE
};

# 221
void write_command(const uint8_t* buff);
uint16_t* get_product_desc();

# 14 "filter.h"
typedef struct
{
bool hasInit;
float prevValue;

} s_EwmaFilter_t;


typedef struct
{
float _err_measure;
float _err_estimate;

float _q_process;

float _current_estimate;
float _last_estimate;
float _kalman_gain;
} s_KalmanFilter_t;

typedef struct
{
char hasInit;
s_KalmanFilter_t kalman;
} s_KalmanApp_t;

# 69
float ewmaFilter_get(s_EwmaFilter_t* ewmaFilter, float inputValue, uint8_t sensitivity);



float Kalman_updateEstimate(s_KalmanFilter_t *pObj,float mea);

void Kalman_setMeasurementError(s_KalmanFilter_t *pObj,float mea_e);
void Kalman_setEstimateError(s_KalmanFilter_t *pObj,float est_e);
void Kalman_setProcessNoise(s_KalmanFilter_t *pObj,float q);

float Kalman_getKalmanGain(s_KalmanFilter_t *pObj);
float Kalman_getEstimateError(s_KalmanFilter_t *pObj);

# 22 "filter.c"
float ewmaFilter_get(s_EwmaFilter_t* ewmaFilter, float inputValue, uint8_t sensitivity)
{
float retval, alpha;
static float filter_alpha[15] = {
1.0f, 0.9f, 0.85f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f, 0.25f,
0.2f, 0.15f, 0.1f, 0.05f, 0.02f
};

if (ewmaFilter->hasInit == 0) {
ewmaFilter->prevValue = inputValue;
ewmaFilter->hasInit = 1;
return inputValue;
}

uint8_t idx = sensitivity - 1;
if (idx < 0) idx = 0;
if (idx > 14) idx = 14;
alpha = filter_alpha[idx];

retval = ((1 - alpha) * ewmaFilter->prevValue) + (alpha * inputValue);

ewmaFilter->prevValue = retval;

return retval;
}

# 53
static float kalman_q_factor[15] = {
0.99f, 0.8f, 0.6f, 0.5f, 0.3f, 0.1f, 0.05f, 0.01f, 0.005f,0.001f,
0.0005f, 0.0001f, 0.00005f, 0.00001f, 0.000001f};

# 144
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

void Kalman_setProcessNoise(s_KalmanFilter_t *pObj,float q)
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

