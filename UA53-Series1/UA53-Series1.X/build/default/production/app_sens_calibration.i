
# 1 "app_sens_calibration.c"

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

# 27 "bsp/leds.h"
typedef enum
{
LED_NONE,
LED_RED,
LED_GREEN
} LED;

# 52
void LED_On(LED led);

# 70
void LED_Off(void);

# 88
void LED_Toggle(LED led);

# 106
bool LED_Get(LED led);

# 123
void LED_Enable(LED led);

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

# 5 "app_led_task.h"
typedef enum {
LED_INIT,
LED_READY,
LED_WAIT_OFF,
LED_CALIB,
LED_WARMUP,
LED_COMMAND,
LED_ZEROCAL,
LED_ZEROCAL_END,
LED_FAIL,
LED_ALLOFF,
LED_NOTHING,
} e_Led_Seq;

typedef struct {
uint8_t seq;
uint8_t last_state;

bool isBlink;
bool toggle;
bool twoYear;
} s_Led_Status;

# 33
void led_init(void);
void led_task(void);

# 7 "app_sens_calibration.h"
typedef enum {
CALIB_INIT,
CALIB_WAIT,
CALIB_ZERO
} e_Calib_Seq;

typedef struct {
uint8_t seq;
bool zero_cal;
} s_Sens_Calib;

# 22
void sens_ZeroCalib_init(void);
void sens_ZeroCalib_task(void);

# 21 "app_sens_calibration.c"
extern uint8_t g_usb_state;
extern s_Nvm g_nvm;
extern s_Sens_Calib g_sens_calib;
extern s_Led_Status g_led_status;
extern float g_last_value[LV_HUMI+1];

volatile uint32_t g_calib_count;


static bool sens_ZeroCalibration(void);


void sens_ZeroCalib_init(void)
{
g_sens_calib.seq = CALIB_INIT;
g_sens_calib.zero_cal = 0;
g_calib_count = 0;
}

static bool sens_ZeroCalibration(void)
{
g_nvm.flash.baseLine_uV = g_last_value[LV_GAS_VOLT];
g_nvm.flash.calib_temp = g_last_value[LV_TEMP];
g_sens_calib.zero_cal = nvm_write_flash_all(&g_nvm.flash);
return g_sens_calib.zero_cal;
}

void sens_ZeroCalib_task(void)
{
if ((g_usb_state == USB_DETACHED) && (g_sens_calib.zero_cal == 0)) {
switch (g_sens_calib.seq)
{
case CALIB_INIT:
LED_Off();
LED_On(LED_GREEN);
g_calib_count = 0;
g_sens_calib.seq = CALIB_WAIT;
break;
case CALIB_WAIT:
if (g_calib_count > 18000) {
g_calib_count = 0;
g_sens_calib.seq = CALIB_ZERO;
} break;
case CALIB_ZERO:
if (sens_ZeroCalibration() == 0) g_sens_calib.seq = CALIB_ZERO;
else g_led_status.seq = LED_ZEROCAL_END;
break;
}
} else {
g_calib_count = 0;
return;
}
}
