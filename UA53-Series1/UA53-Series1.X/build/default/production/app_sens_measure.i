
# 1 "app_sens_measure.c"

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

# 4 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18F-J_DFP/1.4.41/xc8\pic\include\__size_t.h"
typedef unsigned size_t;

# 7 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\stdarg.h"
typedef void * va_list[1];

#pragma intrinsic(__va_start)
extern void * __va_start(void);

#pragma intrinsic(__va_arg)
extern void * __va_arg(void *, ...);

# 43 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\stdio.h"
struct __prbuf
{
char * ptr;
void (* func)(char);
};

# 29 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\errno.h"
extern int errno;

# 12 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\conio.h"
extern void init_uart(void);

extern char getch(void);
extern char getche(void);
extern void putch(char);
extern void ungetch(char);

extern __bit kbhit(void);

# 23
extern char * cgets(char *);
extern void cputs(const char *);

# 88 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\stdio.h"
extern int cprintf(char *, ...);
#pragma printf_check(cprintf)



extern int _doprnt(struct __prbuf *, const register char *, register va_list);


# 180
#pragma printf_check(vprintf) const
#pragma printf_check(vsprintf) const

extern char * gets(char *);
extern int puts(const char *);
extern int scanf(const char *, ...) __attribute__((unsupported("scanf() is not supported by this compiler")));
extern int sscanf(const char *, const char *, ...) __attribute__((unsupported("sscanf() is not supported by this compiler")));
extern int vprintf(const char *, va_list) __attribute__((unsupported("vprintf() is not supported by this compiler")));
extern int vsprintf(char *, const char *, va_list) __attribute__((unsupported("vsprintf() is not supported by this compiler")));
extern int vscanf(const char *, va_list ap) __attribute__((unsupported("vscanf() is not supported by this compiler")));
extern int vsscanf(const char *, const char *, va_list) __attribute__((unsupported("vsscanf() is not supported by this compiler")));

#pragma printf_check(printf) const
#pragma printf_check(sprintf) const
extern int sprintf(char *, const char *, ...);
extern int printf(const char *, ...);

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

# 43 "bsp/ads1114.h"
typedef enum {
FSR_6p144V,
FSR_4p096V,
FSR_2p048V,
FSR_1p024V,
FSR_0p512V,
FSR_0p256V
} e_ADC_Gain;


typedef enum {
CONTINUE_CONV,
SINGLE_CONV
} e_ADC_Mode;


typedef enum {
SPS8,
SPS16,
SPS32,
SPS64,
SPS128,
SPS250,
SPS475,
SPS860
} e_ADC_DataRate;



typedef enum {
COMP,
WIN_COMP
} e_Comparator_Mode;


typedef enum {
LO,
HI
} e_Comparator_Pol;


typedef enum {
NONE_LATCH,
LATCH
} e_Comparator_Latch;


typedef enum {
ONE_CONV,
TWO_CONV,
FOUR_CONV,
DISABL
} e_Comparator_Que;

# 101
bool ads1114_read_ready(void);
bool ads1114_SetUp(uint8_t mode, uint8_t pga, uint8_t dataRate);
bool ads1114_read(int16_t* raw_adc);
bool ads1114_Comparator_SetUp(uint8_t mode, uint8_t polar, uint8_t latch, uint8_t que);

# 25 "bsp/lmp91000.h"
typedef enum {
EXTERNAL_REGISTOR,
R2p75K,
R3p5K,
R7K,
R14K,
R35K,
R120K,
R350K
} e_TIA_InternalGain;


typedef enum {
R10,
R33,
R50,
R100
} e_TIA_RLoad;


typedef enum {
INTERNAL,
EXTERNAL
} e_Ref_Voltage;


typedef enum {
S20P,
S50P,
S67P,
BYPASS
} e_InZ_sel;


typedef enum {
NAGATIVE,
POSITIVE
} e_Bias_sign;


typedef enum {
B0P,
B1P,
B2P,
B4P,
B6P,
B8P,
B10P,
B12P,
B14P,
B16P,
B18P,
B20P,
B22P,
B24P
} e_Bias_sel;


typedef enum {
DISABLE,
ENABLE
} e_FET;


typedef enum {
SLEEP,
GALVANIC_2LEAD,
STANBY,
AMPEROETRIC_3LEAD,
TEMP_MEASURE_TIAOFF = 6,
TEMP_MEASURE_TIAON = 7
} e_OP_Mode;

# 104
bool lmp91000_lock(void);
bool lmp91000_unlock(void);
bool lmp91000_isUnLocked(void);
bool lmp91000_isReady(void);

bool lmp91000_get_status(uint8_t* preg);
bool lmp91000_get_lock(uint8_t* preg);
bool lmp91000_get_Tiacn(uint8_t* preg);
bool lmp91000_get_Refcn(uint8_t* preg);
bool lmp91000_get_Modecn(uint8_t* preg);

bool lmp91000_set_GainRLoad(uint8_t user_gain, uint8_t RLoad);
bool lmp91000_set_Reference(uint8_t source, uint8_t IntZ, uint8_t sign, uint8_t bias);
bool lmp91000_set_Mode(uint8_t fet, uint8_t mode);

# 79 "bsp/sht3x.h"
bool sht3x_softreset(void);
bool sht3x_measure_start(void);

bool sht3x_art_cmd(void);
bool sht3x_break_cmd(void);

bool sht3x_clear_status_reg(void);
bool sht3x_read_status_reg(uint16_t* status);
bool sht3x_heaterOn(void);
bool sht3x_heaterOff(void);

bool sht3x_write_alert_limits(float humidityHighSet, float temperatureHighSet,
float humidityHighClear, float temperatureHighClear,
float humidityLowClear, float temperatureLowClear,
float humidityLowSet, float temperatureLowSet);

bool sht3x_common_read(int32_t* temp, int32_t* humi);

# 101
bool sht3x_measure_read(float* temp, float* humi);
bool sht3x_measure_nonblock_read(float* temp, float* humi);
bool sht3x_measure_block_read(float* temp, float* humi);

# 6 "nvm.h"
typedef union {
__pack uint8_t byte[72];
__pack struct {
uint8_t filter_mode;
uint8_t window_size;
uint8_t temp_corf;
uint8_t temp_compensate;

float baseLine_uV;
float nA_per_ppm;
float gasOffset;
float tempOffset;
float calib_temp;


float KMf_e_measure;
float KMF_e_estimate;


uint8_t auto_Calib;
uint8_t dummy;
float slope_min;
float slope_max;
float zeroShift_uV;
float zeroRange_ppm;
uint16_t autoCalib_cnt;

uint32_t exectime;
uint32_t usedtime;
uint32_t buildtime;
__pack uint8_t serialNum[8];
};
} u_Flash_Nvm;


typedef enum {
NVM_INIT_NONE,
NVM_INIT_FLASH,
}e_Nvm_Status;

typedef struct {
uint8_t status;
u_Flash_Nvm flash;
} s_Nvm;

# 55
void nvm_init(void);
void nvm_clear(void);
void nvm_clear_all(void);

bool nvm_write_flash_all(u_Flash_Nvm* flash);
void nvm_read_flash_all(u_Flash_Nvm* flash);

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

# 14 "sensor.h"
bool sensor_init(void);

bool sensor_read_temp_humi(float* temp, float* humi);
void sensor_temp_fahrenheit(float* temp);

bool sensor_ADC_read(int16_t* raw_adc);
float ADCto_uVoltage(int16_t raw_adc, uint8_t gain);

float compensate_temperature(float temp);
float gasSensor_calib(float slope, float gas_uVolt);
float gasSensor_lowfilter(float gasConcent);

# 9 "app_sens_measure.h"
enum e_Measure_Seq {
SENS_INIT,
SENS_READY,
SENS_TEMP_MEASURE,
SENS_GAS_MEASURE,
SENS_APPLY,
SENS_WAIT,
SENS_DISPLAY
};

enum e_SensorValue {
LV_GAS_VOLT,
LV_GAS_PPM,
LV_RAW_VALUE,
LV_FILTERD_VALUE,
LV_SNR,
LV_TEMP,
LV_HUMI
};




typedef struct {
uint8_t seq;
uint8_t next_seq;
uint8_t seq_count;

bool isInitDone;
bool isGasSensor_Success;
bool isTemp_Success;

} s_Sens_Measure;

typedef struct {
float rawData_buffer[30];
float fltData_buffer[30];

float rawData_sum;
float fltData_sum;

float rawData_sqrSum;
float fltData_sqrSum;

float rawData_avg;
float fltData_avg;

float rawData_RMS;
float fltData_RMS;

float SNRv;
float SNRdB;

} s_Sens_SNR;

# 68
void sensMeasure_init();
void sensMeasure_task();


void sensMeasure_SNR_init(s_Sens_SNR* pSNR);
float sensMeasure_SNR(s_Sens_SNR* pSNR, float rawData, float filData);

# 12 "window.h"
float window_moving_average_recursion(float uV, uint8_t window_size);

# 14 "app_linear_regression.h"
typedef struct {


float x[10];
float y[10];

# 24
uint8_t position;
float time_cnt;

float sum_x;
float sum_x2;
float sum_y;
float sum_xy;

float slope;
float offset;

# 39
} s_Linear_reg;

# 47
void Linear_regression_init(s_Linear_reg* p);
void Linear_regression(s_Linear_reg* p, float uVoltage);

# 15 "app_sens_autoCalibration.h"
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

# 53
void sens_autoCalib_init(void);
void sens_autoCalib_task(void);
void sens_autoCalib_slp_set_task(void);

# 22 "app_sens_measure.c"
extern s_Sens_Measure g_sens_measure;
extern s_Nvm g_nvm;

extern s_Linear_reg g_linear_reg;
extern s_Auto_calib g_sens_autoCalib;
extern volatile uint16_t g_slpSet_cnt2;
extern volatile uint8_t g_autoCal_cnt2;

float g_last_value[LV_HUMI+1];
float g_temp_value[LV_HUMI+1];

volatile uint32_t g_large_counter;
volatile uint16_t gCnt;


s_KalmanFilter_t kalmanFilter;

# 45
void sensMeasure_init(void)
{
g_large_counter = 0;
g_sens_measure.seq = SENS_INIT;
g_sens_measure.isInitDone = 0;
g_sens_measure.isGasSensor_Success = 0;
g_sens_measure.isTemp_Success = 0;


kalmanFilter._current_estimate = 0.0f;
kalmanFilter._err_estimate = 0.0f;
kalmanFilter._err_measure = 0.0f;
kalmanFilter._kalman_gain = 0.0f;
kalmanFilter._last_estimate = 0.0f;
kalmanFilter._q_process = 0.0f;
Kalman_setMeasurementError(&kalmanFilter, g_nvm.flash.KMf_e_measure);
Kalman_setEstimateError(&kalmanFilter, g_nvm.flash.KMF_e_estimate);
Set_KamanFilter_Sensitivity(g_nvm.flash.window_size);

# 74
}

static bool sensMeasure_temp_read()
{
float temp, humi;

if (g_sens_measure.isInitDone == 0)
return 0;

if (sensor_read_temp_humi(&temp, &humi)) {
g_temp_value[LV_TEMP] = temp;
g_temp_value[LV_TEMP] += g_nvm.flash.tempOffset;
g_temp_value[LV_HUMI] = humi;
return 1;
}
return 0;
}

static bool sensMeasure_gas_read()
{
int16_t raw;

if (g_sens_measure.isInitDone == 0)
return 0;

if (sensor_ADC_read(&raw)) {
float volt = ADCto_uVoltage(raw, FSR_0p256V);
g_temp_value[LV_GAS_VOLT] = Kalman_updateEstimate(&kalmanFilter, volt);

# 108
g_temp_value[LV_GAS_VOLT] = g_temp_value[LV_GAS_VOLT] * 2.0f;

float cmp_val = 0.0f;
if (g_nvm.flash.temp_compensate == TEMP_COMPENSATION)
cmp_val = compensate_temperature(g_temp_value[LV_TEMP]);

g_temp_value[LV_GAS_PPM] = gasSensor_calib(cmp_val, g_temp_value[LV_GAS_VOLT]);

if(g_nvm.flash.filter_mode == FIL_MODE)
g_temp_value[LV_GAS_PPM] = gasSensor_lowfilter(g_temp_value[LV_GAS_PPM]);

return 1;
}
return 0;
}

void sensMeasure_task(void)
{
switch (g_sens_measure.seq)
{
case SENS_INIT:
if (sensor_init()) {
g_sens_measure.isInitDone = 1;
g_large_counter = 0;
g_sens_measure.seq = SENS_READY;
} else {
g_large_counter = 0;
g_sens_measure.seq_count = 30;
g_sens_measure.seq = SENS_WAIT;
g_sens_measure.next_seq = SENS_INIT;
} break;
case SENS_READY:
if (g_large_counter >= 100) {

if (gCnt == 3600) gCnt = 1;
else gCnt++;

g_large_counter = 0;
g_sens_measure.seq = SENS_TEMP_MEASURE;
} break;
case SENS_TEMP_MEASURE:
g_sens_measure.isTemp_Success = sensMeasure_temp_read();
g_large_counter = 0;
g_sens_measure.seq_count = 2;
g_sens_measure.seq = SENS_WAIT;
g_sens_measure.next_seq = SENS_GAS_MEASURE;
break;
case SENS_GAS_MEASURE:
g_sens_measure.isGasSensor_Success = sensMeasure_gas_read();
g_large_counter = 0;
g_sens_measure.seq = SENS_APPLY;
break;
case SENS_APPLY:
if (g_sens_measure.isGasSensor_Success) {
g_last_value[LV_GAS_VOLT] = g_temp_value[LV_GAS_VOLT];

Linear_regression(&g_linear_reg, g_last_value[LV_GAS_VOLT]);




g_last_value[LV_GAS_PPM] = g_temp_value[LV_GAS_PPM];

g_last_value[LV_GAS_PPM] = g_last_value[LV_GAS_PPM] + g_nvm.flash.gasOffset;;
}
if (g_sens_measure.isTemp_Success) {
g_last_value[LV_TEMP] = g_temp_value[LV_TEMP];
g_last_value[LV_HUMI] = g_temp_value[LV_HUMI];
}
g_large_counter = 0;
g_sens_measure.seq = SENS_DISPLAY;
break;
case SENS_WAIT:
if (g_large_counter > g_sens_measure.seq_count) {
g_large_counter = 0;
g_sens_measure.seq = g_sens_measure.next_seq;
} break;
case SENS_DISPLAY:
{

# 201
g_large_counter = 0;
g_sens_measure.seq = SENS_READY;
} break;
}
}

# 215
void sensMeasure_SNR_init(s_Sens_SNR* pSNR)
{
for (uint8_t i = 0; i < 30; i++) {
pSNR->rawData_buffer[i] = 0.0f;
pSNR->fltData_buffer[i] = 0.0f;
}
pSNR->rawData_RMS = 0.0f;
pSNR->rawData_RMS = 0.0f;
}

float sensMeasure_SNR(s_Sens_SNR* pSNR, float rawData, float filData)
{
uint8_t idx;
pSNR->rawData_sum = 0.0f;
pSNR->fltData_sum = 0.0f;


float RawData = rawData/1000;
float FilData = filData/1000;


for (idx = 0; idx < 30 -1; idx++) {
pSNR->rawData_buffer[idx] = pSNR->rawData_buffer[idx +1];
pSNR->fltData_buffer[idx] = pSNR->fltData_buffer[idx +1];
}
pSNR->rawData_buffer[30 -1] = RawData;
pSNR->fltData_buffer[30 -1] = FilData;


for (idx = 0; idx < 30; idx++) {
pSNR->rawData_sum += pSNR->rawData_buffer[idx];
pSNR->fltData_sum += pSNR->fltData_buffer[idx];


}


pSNR->rawData_avg = pSNR->rawData_sum / 30;
pSNR->fltData_avg = pSNR->fltData_sum / 30;

# 260
pSNR->SNRv = pSNR->fltData_avg / pSNR->rawData_avg;
pSNR->SNRdB = 10.0f * log10(pSNR->SNRv);


return pSNR->SNRdB;
}
