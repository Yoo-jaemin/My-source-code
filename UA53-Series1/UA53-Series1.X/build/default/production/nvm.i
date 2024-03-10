
# 1 "nvm.c"

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

# 18 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\assert.h"
extern void _fassert(int, const char *, const char *);


# 24
#pragma intrinsic(__builtin_software_breakpoint)
extern void __builtin_software_breakpoint(void);

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

# 10 "bsp/flash.h"
typedef union
{
unsigned long Val;
__pack unsigned short int w[2];
__pack unsigned char v[4];
__pack struct
{
unsigned short int LW;
unsigned short int HW;
} word;
__pack struct
{
unsigned char LB;
unsigned char HB;
unsigned char UB;
unsigned char MB;
} byte;
} DWORD_VAL;

# 36
void flash_readBytes(uint32_t startaddr, uint8_t *flash_array, uint16_t num_bytes);
bool flash_writeBytes(uint32_t startaddr, uint8_t *flash_array, uint16_t num_bytes);
void flash_clear(uint32_t startaddr, uint32_t endaddr);

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

# 4 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18F-J_DFP/1.4.41/xc8\pic\include\__size_t.h"
typedef unsigned size_t;

# 8 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\time.h"
typedef long time_t;
struct tm {
int tm_sec;
int tm_min;
int tm_hour;
int tm_mday;
int tm_mon;
int tm_year;
int tm_wday;
int tm_yday;
int tm_isdst;
};

# 25
extern int time_zone;

# 30
extern time_t time(time_t *);
extern int stime(time_t *);

# 47
extern char * asctime(const struct tm *) ;
extern char * ctime(const time_t *) ;
extern struct tm * gmtime(const time_t *) ;
extern struct tm * localtime(const time_t *) ;
extern size_t strftime(char *, size_t, const char *, const struct tm *) ;
extern time_t mktime(struct tm *);

# 79 "util/build_time.h"
time_t build_time(void);

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

# 18 "nvm.c"
extern s_Nvm g_nvm;

static void nvm_clear_flash(void)
{
g_nvm.flash.filter_mode = RAW_MODE;
g_nvm.flash.window_size = LEVEL_14;
g_nvm.flash.temp_corf = CELSIUS;
g_nvm.flash.temp_compensate = TEMP_NOT_COMPENSATION;

g_nvm.flash.baseLine_uV = 0.0f;
g_nvm.flash.nA_per_ppm = 0.0f;
g_nvm.flash.gasOffset = 0.0f;
g_nvm.flash.tempOffset= 0.0f;
g_nvm.flash.calib_temp = 0.0f;

g_nvm.flash.KMf_e_measure = 50.0f;
g_nvm.flash.KMF_e_estimate = 1.0f;

g_nvm.flash.auto_Calib = OFF;
g_nvm.flash.dummy = 0;
g_nvm.flash.slope_min = 0.0f;
g_nvm.flash.slope_max = 0.0f;
g_nvm.flash.zeroShift_uV = 0.0f;
g_nvm.flash.autoCalib_cnt = 0;
g_nvm.flash.zeroRange_ppm = 1.0f;

g_nvm.flash.exectime = 0;
g_nvm.flash.usedtime = 0;
g_nvm.flash.buildtime = (uint32_t)build_time();
}

void nvm_clear(void)
{
nvm_clear_flash();
}

void nvm_clear_all(void)
{
uint8_t i;
nvm_clear();
for (i = 0 ; i < 8 ; i++) g_nvm.flash.serialNum[i] = 0xff;
}

static bool nvm_serialno_check(const uint8_t* sno)
{
uint8_t i;
for (i = 0 ; i < 8 ; i++) {
if (sno[i] == 0xff || sno[i] == 0x00)
return 0;
}
return 1;
}

void nvm_init(void)
{
uint8_t i;

nvm_read_flash_all(&g_nvm.flash);
g_nvm.status = NVM_INIT_FLASH;

if (nvm_serialno_check(g_nvm.flash.serialNum))
{
uint16_t* pdesc = get_product_desc();
for (i = 0 ; i < 8 ; i++) {
pdesc[i + 11] = g_nvm.flash.serialNum[i];
}
}
else
{
nvm_clear();

if (nvm_write_flash_all(&g_nvm.flash) == 0)
return;
g_nvm.status = NVM_INIT_FLASH;
}
}


bool nvm_write_flash_all(u_Flash_Nvm* flash)
{
flash_clear(0xf400, (0xf400 + 72));
return flash_writeBytes(0xf400, flash->byte, 72);
}

void nvm_read_flash_all(u_Flash_Nvm* flash)
{
flash_readBytes(0xf400, flash->byte, 72);
}
