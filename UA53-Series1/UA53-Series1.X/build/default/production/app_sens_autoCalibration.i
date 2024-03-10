
# 1 "app_sens_autoCalibration.c"

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

# 15 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\stdbool.h"
typedef unsigned char bool;

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

# 26 "app_sens_autoCalibration.c"
extern float g_last_value[LV_HUMI+1];
extern s_Nvm g_nvm;
extern s_Led_Status g_led_status;
extern s_Linear_reg g_linear_reg;
extern s_Auto_calib g_sens_autoCalib;
extern uint8_t writeBuffer[64];

volatile uint32_t g_autoCal_cnt;
volatile uint8_t g_autoCal_cnt2;
volatile uint32_t g_slpSet_cnt;
volatile uint16_t g_slpSet_cnt2;



static void auto_calib_apply(void);
static void auto_calib_clear(void);
static void sort_uV_slope(float min, float max, float uV_slope);


void sens_autoCalib_init(void)
{
g_sens_autoCalib.Seq_autoCal = AUTO_CALIB_INIT;
g_sens_autoCalib.Seq_slpSet = SLOPE_SET_INIT;
g_autoCal_cnt = 0;
g_slpSet_cnt = 0;

g_sens_autoCalib.slpSet_en = OFF;
g_sens_autoCalib.led_slpSet = OFF;

g_sens_autoCalib.slope_min = 0.0f;
g_sens_autoCalib.slope_max = 0.0f;

g_sens_autoCalib.sumZero_uV = 0.0f;
g_sens_autoCalib.avgZero_uV = 0.0f;

g_sens_autoCalib.chk_cnt = 0;
g_sens_autoCalib.sft_ppm = 0.0f;
}

void sens_autoCalib_task(void)
{
switch (g_sens_autoCalib.Seq_autoCal)
{
case AUTO_CALIB_INIT:
g_autoCal_cnt = 0;
g_sens_autoCalib.Seq_autoCal = AUTO_CALIB_READY;
break;
case AUTO_CALIB_READY:
if (g_autoCal_cnt >= 6000) {
g_autoCal_cnt = 0;
g_autoCal_cnt2++;
g_sens_autoCalib.Seq_autoCal = AUTO_CALIB_CHECK;
} break;
case AUTO_CALIB_CHECK:
if (g_linear_reg.slope >= g_nvm.flash.slope_min &&
g_linear_reg.slope <= g_nvm.flash.slope_max && g_last_value[LV_GAS_PPM] <= g_nvm.flash.zeroRange_ppm) {
g_sens_autoCalib.chk_cnt++;
g_sens_autoCalib.sumZero_uV += g_last_value[LV_GAS_VOLT];
}
if (g_autoCal_cnt2 == 60) {
if (g_sens_autoCalib.chk_cnt >= 50 ) g_sens_autoCalib.Seq_autoCal = AUTO_CALIB;
else auto_calib_clear();
} else {
g_autoCal_cnt = 0;
g_sens_autoCalib.Seq_autoCal = AUTO_CALIB_READY;
} break;
case AUTO_CALIB:
auto_calib_apply();

# 99
auto_calib_clear();
break;
}
}

static void auto_calib_apply(void)
{
g_sens_autoCalib.avgZero_uV = g_sens_autoCalib.sumZero_uV / g_sens_autoCalib.chk_cnt;
g_nvm.flash.zeroShift_uV = (g_sens_autoCalib.avgZero_uV - g_nvm.flash.baseLine_uV);
g_nvm.flash.autoCalib_cnt++;
nvm_write_flash_all(&g_nvm.flash);
}

static void auto_calib_clear(void)
{
g_autoCal_cnt = 0;
g_autoCal_cnt2 = 0;
g_sens_autoCalib.chk_cnt = 0;
g_sens_autoCalib.sumZero_uV = 0.0f;
g_sens_autoCalib.avgZero_uV = 0.0f;
g_sens_autoCalib.Seq_autoCal = AUTO_CALIB_READY;
}

void sens_autoCalib_slp_set_task(void)
{
switch (g_sens_autoCalib.Seq_slpSet)
{
case SLOPE_SET_INIT:
g_slpSet_cnt = 0;
g_sens_autoCalib.led_slpSet = ON;
g_sens_autoCalib.Seq_slpSet = SLOPE_SET_LED;
break;
case SLOPE_SET_LED:
if (g_slpSet_cnt >= 50) {
g_slpSet_cnt = 0;
g_led_status.seq = LED_ZEROCAL;
g_led_status.last_state = LED_NOTHING;
g_sens_autoCalib.Seq_slpSet = SLOPE_SET_READY;
} break;
case SLOPE_SET_READY:
if (g_slpSet_cnt >= 100) {
g_slpSet_cnt2++;
g_sens_autoCalib.Seq_slpSet = SLOPE_SAVE;
} break;
case SLOPE_SAVE:
sort_uV_slope(g_sens_autoCalib.slope_min, g_sens_autoCalib.slope_max, g_linear_reg.slope);
if (g_slpSet_cnt2 >= 500)
g_sens_autoCalib.Seq_slpSet = SLOPE_SET;
else {
g_slpSet_cnt = 0;
g_sens_autoCalib.Seq_slpSet = SLOPE_SET_READY;
} break;
case SLOPE_SET:
g_nvm.flash.slope_min = g_sens_autoCalib.slope_min;
g_nvm.flash.slope_max = g_sens_autoCalib.slope_max;
if (nvm_write_flash_all(&g_nvm.flash)) {
g_led_status.seq = LED_ZEROCAL_END;
write_command("ATACSS\r\n");
} g_sens_autoCalib.Seq_slpSet = SLOPE_SET_END;
break;
case SLOPE_SET_END:
g_slpSet_cnt2 = 0;
g_sens_autoCalib.slpSet_en = OFF;
g_sens_autoCalib.Seq_slpSet = SLOPE_SET_INIT;
break;
}
}

static void sort_uV_slope(float min, float max, float uV_slope)
{
float Min, Mid, Max, Temp;
Min = min;
Mid = uV_slope;
Max = max;

if (Min >= Mid) {
Temp = Mid;
Mid = Min;
Min = Temp;
}
if (Mid >= Max) {
Temp = Max;
Max = Mid;
Mid = Temp;
}
if (Min >= Mid) {
Temp = Mid;
Mid = Min;
Min = Temp;
}
g_sens_autoCalib.slope_min = Min;
g_sens_autoCalib.slope_max = Max;
}
