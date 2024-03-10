
# 1 "sensor.c"

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

# 46 "bsp/ads1114.h"
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

# 104
bool ads1114_read_ready(uint8_t channel);
bool ads1114_SetUp(uint8_t channel, uint8_t mode, uint8_t pga, uint8_t dataRate);
bool ads1114_read(uint8_t channel, int16_t* raw_adc);
bool ads1114_Comparator_SetUp(uint8_t channel, uint8_t mode, uint8_t pol, uint8_t lat, uint8_t que);

# 25 "bsp/max7323.h"
bool max7323_set_gpio(uint8_t chno, uint8_t wb);
bool max7323_get_gpio(uint8_t chno, uint8_t *rb);

# 31 "nvm.h"
typedef union {
__pack uint8_t byte[62];
__pack struct {
uint8_t supercap;
uint8_t sensor_model;
uint8_t adc_gain;
uint8_t lmp_gain;
uint8_t lmp_rload;
uint8_t lmp_intZ;
uint8_t filter_mode;
uint8_t window_size;
uint8_t temp_corf;
uint8_t temp_compensate;

float baseLine_uV;
float span_uV;
float CalibrationGas;
float gas_slope;
float calib_baseLine;
float gasOffset;
float tempOffset;

uint32_t caltime;
uint32_t usedtime;

__pack uint8_t sensor_name[10];

float baseLine_temp;

uint16_t check_sum;
};
} u_Eeprom_Nvm;

# 91
typedef union {
__pack uint8_t byte[30];
__pack struct {
uint8_t dummy;
uint8_t sensing_on;

uint8_t ctrl_master_mode;
uint8_t ctrl_channel;
uint8_t ctrl_slave_id;


uint8_t ctrl_relay_no;
float ctrl_ppm_max;
uint32_t ctrl_holding_min;

uint8_t byte_swap;
uint8_t slave_id;
uint8_t baudrate;
uint8_t timeout;
uint32_t buildtime;
__pack uint8_t serialNum[8];
};
} u_Flash_Nvm;

# 123
typedef struct {
u_Flash_Nvm flash;
__pack u_Eeprom_Nvm eeprm[2];
} s_Nvm;

# 132
uint16_t checksum(const uint8_t *data, uint16_t length);

# 138
void nvm_init();
void nvm_clear_channel(uint8_t channel);
void nvm_clear(void);
void nvm_clear_all();

void nvm_sensor_type_channel(uint8_t chno, uint8_t sensor_model);

bool nvm_write_eeprom_all(uint8_t channel);
bool nvm_read_eeprom_all(uint8_t channel);

bool nvm_write_flash_all(u_Flash_Nvm* flash);
void nvm_read_flash_all(u_Flash_Nvm* flash);

# 9 "app_sens_measure.h"
enum e_Measure_Seq {
SENS_INIT,
SENS_EEPRM_INIT,
SENS_EEPRM_INIT_NEXT,
SENS_SENSOR_INIT,
SENS_SENSOR_INIT_NEXT,
SENS_READY,
SENS_CHANGE_TEMP,
SENS_TEMP_MEASURE,
SENS_CHANGE_GAS,
SENS_GAS_MEASURE,
SENS_APPLY,
SENS_NEXT,
SENS_WAIT,
SENS_DISPLAY
};

enum e_SensorValue {
LV_GAS_VOLT,
LV_GAS_PPM,
LV_TEMP
};



typedef union {
__pack uint16_t word[(sizeof(float)/sizeof(uint16_t)) * 4];
__pack float float_value[4];
} u_SensorValue;

typedef struct {
uint8_t seq;
uint8_t next_seq;
uint8_t seq_count;

bool existChannel[2];
bool isChecksum[2];
bool isSensorInit[2];

} s_Sens_Measure;

# 55
void sensMeasure_init();
void sensMeasure_sensor_init();
void sensMeasure_task();

# 11 "sensor.h"
bool sensor_init(uint8_t channel);
bool sensor_adc_init(uint8_t channel, bool isTemp);
bool sensor_lmp_init(uint8_t channel);

bool sensor_set_temp_mode(uint8_t channel);
bool sensor_set_gas_mode(uint8_t channel);

void sensor_temp_fahrenheit(float* temp);

bool sensor_ADC_read(uint8_t channel, int16_t* raw_adc);
float ADCto_uVoltage(int16_t raw_adc, uint8_t gain);

float compensate_temperature(float temp, float baseLine_temp, uint8_t model);
float gasSensor_calib(uint8_t channel, float slope, float gas_uVolt);
float gasSensor_temperature(float temp_uVolt);

void max7323_set_lmp_on(uint8_t channel);
void max7323_set_lmp_off(void);

# 15 "sensor.c"
extern s_Nvm g_nvm;

static float gasSensor_filter(float gasConcent)
{

float retval;
if (gasConcent < 0.2 && gasConcent >= 0.0)
retval = 0.0;
else if (gasConcent < 0 && gasConcent >= -0.5)
retval = 0.0;
else if (gasConcent < -0.5 && gasConcent >= -1.0)
retval = 0.02;
else if (gasConcent < -1.0 && gasConcent >= -5.0)
retval = 0.03;
else if (gasConcent < -5.0 && gasConcent >= -10.0)
retval = 0.04;
else if (gasConcent < -10.0 && gasConcent >= -30.0)
retval = 0.05;
else if (gasConcent < -30.0)
retval = 0.06;
else
retval = gasConcent;
return retval;

# 56
}

static float FSR_set_LSB(uint8_t gain)
{
if(gain == FSR_6p144V)
return 187.5f;
else if(gain == FSR_4p096V)
return 125.0f;
else if(gain == FSR_1p024V)
return 31.25f;
else if(gain == FSR_0p512V)
return 15.62f;
else if(gain == FSR_0p256V)
return 7.81f;

return 62.5f;
}

void max7323_set_lmp_on(uint8_t channel)
{
uint8_t wr;

for (uint8_t i = 0 ; i < 2 ; i++) {
if (i == channel) wr = 0b00100000;
else wr = 0b00110000;
max7323_set_gpio(i, wr);
}
}

void max7323_set_lmp_off(void)
{
uint8_t wr[2] = { 0b00110000, 0b00011000 };

for (uint8_t i = 0 ; i < 2 ; i++) {
max7323_set_gpio(i, wr[i]);
}
}

# 99
bool sensor_adc_init(uint8_t channel, bool isTemp)
{
bool ret;
if (isTemp) ret = ads1114_SetUp(channel, CONTINUE_CONV, FSR_2p048V, SPS128);
else ret = ads1114_SetUp(channel, CONTINUE_CONV, g_nvm.eeprm[channel].adc_gain, SPS128);

return ret;
}

# 126
bool sensor_lmp_init(uint8_t channel)
{
max7323_set_lmp_on(channel);


if (lmp91000_isReady() == 0) {
max7323_set_lmp_off();
return 0;
}

if (lmp91000_unlock() == 0) {
max7323_set_lmp_off();
return 0;
}

if (lmp91000_set_GainRLoad(g_nvm.eeprm[channel].lmp_gain, g_nvm.eeprm[channel].lmp_rload) == 0) {
max7323_set_lmp_off();
return 0;
}



if (lmp91000_set_Reference(EXTERNAL, g_nvm.eeprm[channel].lmp_intZ, NAGATIVE, B0P) == 0) {
max7323_set_lmp_off();
return 0;
}

if (lmp91000_set_Mode(DISABLE, STANBY) == 0) {
return 0;
}

max7323_set_lmp_off();
return 1;
}

bool sensor_init(uint8_t channel)
{


if (!(g_nvm.eeprm[channel].sensor_model >= NH3_100 && g_nvm.eeprm[channel].sensor_model <= H2S_50))
return 0;
return sensor_lmp_init(channel);
}

void sensor_temp_fahrenheit(float* temp)
{
*temp = (*temp * 1.8f) + 32.0f;
}

bool sensor_ADC_read(uint8_t channel, int16_t* raw_adc)
{
return ads1114_read(channel, raw_adc);
}

float ADCto_uVoltage(int16_t raw_adc, uint8_t gain)
{
float uVolt;
float lsb = FSR_set_LSB(gain);
uVolt = (float)raw_adc * lsb;
return uVolt;
}


float compensate_temperature(float temp, float baseLine_temp, uint8_t model)
{
float cmp_val = 0.0f;

if (model == NH3_100) {
if (temp >= 25.0f && temp < 30.0f)
cmp_val = 0.034f * temp - 0.826f;

else if (temp >= 30.0f && temp < 34.0f)
cmp_val = 0.05f * temp - 1.356f;

else if (temp >= 34.0f && temp < 38.0f)
cmp_val = 0.095f * temp - 2.892f;

else if (temp >= 38.0f && temp < 41.0f)
cmp_val = 0.1f * temp - 3.1f;

else if (temp >= 41.0f)
cmp_val = 1.0f;

else
cmp_val = 0.0f;
} else if (model == H2S_50) {

}

return cmp_val;
}

float gasSensor_calib(uint8_t channel, float cmp_val, float gas_uVolt)
{
float gas_ppm;

float span = g_nvm.eeprm[channel].span_uV;
float baseline = g_nvm.eeprm[channel].baseLine_uV;
float CalibrationGas = g_nvm.eeprm[channel].CalibrationGas;

if ((span - baseline) == 0.0f || span <= baseline )
return 0.0f;

gas_ppm = ((CalibrationGas * gas_uVolt) / (span - baseline) - (CalibrationGas * baseline) / (span - baseline)) - cmp_val;

if(g_nvm.eeprm[channel].filter_mode == FIL_MODE)
{
gas_ppm = gasSensor_filter(gas_ppm);
}

return gas_ppm;
}

# 314
float gasSensor_temperature(float temp_uVolt)
{
float temp = -0.12f * (temp_uVolt/1000.0f + 500.0f) + 187.2f;
return temp;
}

bool sensor_set_temp_mode(uint8_t channel)
{
max7323_set_lmp_on(channel);

if (lmp91000_set_Mode(DISABLE, TEMP_MEASURE_TIAON) == 0) {
max7323_set_lmp_off();
return 0;
}

max7323_set_lmp_off();

if (sensor_adc_init(channel, 1) == 0)
return 0;

return 1;
}

bool sensor_set_gas_mode(uint8_t channel)
{
max7323_set_lmp_on(channel);

if (lmp91000_set_Mode(DISABLE, AMPEROETRIC_3LEAD) == 0) {
max7323_set_lmp_off();
return 0;
}

max7323_set_lmp_off();

if (sensor_adc_init(channel, 0) == 0)
return 0;

return 1;
}
