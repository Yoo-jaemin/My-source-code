
# 1 "bsp/ads1114.c"

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

# 51 "bsp/../board.h"
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

# 4 "bsp/i2c.h"
typedef enum {
I2C_100kHz,
I2C_400kHz
} I2C_SPEED;

typedef enum {
I2C_ACK,
I2C_NACK
} I2C_TRANS_CTRL;

# 19
void i2c_init(const I2C_SPEED speed);

bool i2c_writeData(const uint8_t *wrptr, const uint8_t len, bool isStop);
bool i2c_writeBytes(const uint8_t address, const uint8_t *wrptr, const uint8_t len, bool isStop);
bool i2c_writeBytes_to(const uint8_t address, const uint8_t *wraddr, const uint8_t addrlen, const uint8_t *wrptr, const uint8_t len);
bool i2c_readBytes(const uint8_t address, uint8_t *rdptr, const uint8_t len);
bool i2c_readBytes_from(const uint8_t address, const uint8_t *wraddr, const uint8_t addrlen, uint8_t *rdptr, const uint8_t len);

# 27 "bsp/power.h"
typedef enum
{
POWER_SOURCE_NONE,
POWER_SOURCE_USB,
POWER_SOURCE_MAINS,
POWER_SOURCE_ALL
} POWER_SOURCE;

# 39
void POWER_Init(void);
POWER_SOURCE POWER_SourceGet(void);
void ACCESS_SourceSet(bool set);
bool ACCESS_SourceGet(void);
bool I2C_Bus_SourceGet(void);

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

# 10 "bsp/ads1114.c"
static uint8_t ads1114_address[2] = { 0x92, 0x90 };

# 17
bool ads1114_read_ready(uint8_t channel)
{
uint8_t wbuff = 0x01;
uint8_t rbuff[2];

if (i2c_writeBytes(ads1114_address[channel], &wbuff, 1, 1) == 0)
return 0;

if (i2c_readBytes(ads1114_address[channel], rbuff, 2) == 0)
return 0;

if ((rbuff[0] & 0x80) != 0x80)
return 0;
return 1;
}

bool ads1114_SetUp(uint8_t channel, uint8_t mode, uint8_t pga, uint8_t dataRate)
{
uint8_t wraddr = 0x01;
uint8_t buff[2];

buff[0] = 0x80 | (pga << 1) | mode;
buff[1] = dataRate << 5 | 0b00010011;

return i2c_writeBytes_to(ads1114_address[channel], &wraddr, 1, buff, 2);
}

bool ads1114_read(uint8_t channel, int16_t* raw_adc)
{
uint8_t wbuff = 0x00;
uint8_t rbuff[2];

if (i2c_writeBytes(ads1114_address[channel], &wbuff, 1, 1) == 0)
return 0;

if (i2c_readBytes(ads1114_address[channel], rbuff, 2) == 0)
return 0;

*raw_adc = ((uint16_t)rbuff[0] << 8) | rbuff[1];
return 1;
}

bool ads1114_Comparator_SetUp(uint8_t channel, uint8_t mode, uint8_t polar,
uint8_t latch, uint8_t que)
{
uint8_t wbuff = 0x01;
uint8_t rbuff[2];

if(!i2c_writeBytes(ads1114_address[channel], &wbuff, 1, 1))
return 0;

if(!i2c_readBytes(ads1114_address[channel], rbuff, 2))
return 0;


rbuff[1] |= (mode << 4) | (polar << 3) | (latch << 2) | que;

return i2c_writeBytes_to(ads1114_address[channel], &wbuff, 1, rbuff, 2);
}
