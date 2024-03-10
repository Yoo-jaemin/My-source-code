
# 1 "app_modbus.c"

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

# 10 "util/_string.h"
unsigned _strcpy(char* dest, const char* source);
void _strncpy(char *_to, const char *_from, int _n);
unsigned _strlen(const char* source);
void _strcat(char* dest, const char* source);

unsigned char _strncmp(const char* src1, const char* src2, int n, int i);
void _strclr(char* dest, int n);

unsigned char _isdigit(const char* src, int n);

# 5 "util/buffer.h"
typedef struct buff_queue
{
uint8_t size;
uint8_t read_pos;
uint8_t write_pos;
uint8_t buffer[64];
} s_Queue;

# 17
void buffer_init(s_Queue* queue);
void buffer_en_queue(s_Queue* queue, uint8_t ch);
uint8_t buffer_de_queue(s_Queue* queue);
bool buffer_de_queue_bool(s_Queue* queue, uint8_t* ch);

# 9 "bsp/rs485.h"
void rs485_init(uint32_t baudrate);
bool rs485_is_writing(void);
void rs485_writeBytes(const uint8_t* wrptr, const uint8_t len);
bool rs485_readByte(uint8_t* byte);

# 49 "lightmodbus/lightmodbus.h"
typedef enum modbusError
{
MODBUS_ERROR_OK = 0,

# 64
MODBUS_ERROR_EXCEPTION = 1,

# 71
MODBUS_ERROR_ALLOC,
MODBUS_ERROR_OTHER,
MODBUS_ERROR_NULLPTR,

# 81
MODBUS_ERROR_PARSE,
MODBUS_ERROR_BUILD,
MODBUS_OK = MODBUS_ERROR_OK,
} ModbusError;

# 91
typedef enum modbusFrameError
{
MODBUS_FERROR_OK = MODBUS_OK,
MODBUS_FERROR_CRC,
MODBUS_FERROR_LENGTH,
MODBUS_FERROR_COUNT,
MODBUS_FERROR_VALUE,
MODBUS_FERROR_RANGE,
MODBUS_FERROR_NOSRC,
MODBUS_FERROR_NOREAD,
MODBUS_FERROR_NOWRITE,
MODBUS_FERROR_NOFUN,
MODBUS_FERROR_BADFUN,
MODBUS_FERROR_NULLFUN,
MODBUS_FERROR_MISM_FUN,
MODBUS_FERROR_MISM_ADDR,
MODBUS_FERROR_MISM_INDEX,
MODBUS_FERROR_MISM_COUNT,
MODBUS_FERROR_MISM_VALUE,
MODBUS_FERROR_MISM_MASK,
MODBUS_FERROR_BROADCAST

} ModbusFrameError;

# 118
typedef enum modbusExceptionCode
{
MODBUS_EXCEP_ILLEGAL_FUNCTION = 1,
MODBUS_EXCEP_ILLEGAL_ADDRESS = 2,
MODBUS_EXCEP_ILLEGAL_VALUE = 3,
MODBUS_EXCEP_SLAVE_FAILURE = 4,
MODBUS_EXCEP_ACK = 5,
MODBUS_EXCEP_NACK = 7
} ModbusExceptionCode;

# 131
typedef enum modbusDataType
{
MODBUS_HOLDING_REGISTER = 1,
MODBUS_INPUT_REGISTER = 2,
MODBUS_COIL = 4,
MODBUS_DISCRETE_INPUT = 8
} ModbusDataType;

# 145
extern uint16_t modbusBitsToBytes( uint16_t n );

# 157
extern uint16_t modbusSwapEndian( uint16_t data );

# 172
extern uint16_t modbusMatchEndian( uint16_t data );

# 183
extern uint8_t modbusMaskRead( const uint8_t *mask, uint16_t maskLength, uint16_t _bit );

# 194
extern uint8_t modbusMaskWrite( uint8_t *mask, uint16_t maskLength, uint16_t _bit, uint8_t value );

# 203
extern uint16_t modbusCRC( const uint8_t *data, uint16_t length );

# 43 "lightmodbus/parser.h"
typedef union modbusParser
{
uint8_t frame[256];

__pack struct
{
uint8_t address;
uint8_t function;
} _base;

__pack struct
{
uint8_t address;
uint8_t function;
uint8_t code;
uint16_t crc;
} exception;

__pack struct
{
uint8_t address;
uint8_t function;
uint16_t index;
uint16_t count;
uint16_t crc;
} request0102;

__pack struct
{
uint8_t address;
uint8_t function;
uint8_t length;
uint8_t values[250];
uint16_t crc;
} response0102;

__pack struct
{
uint8_t address;
uint8_t function;
uint16_t index;
uint16_t count;
uint16_t crc;
} request0304;

__pack struct
{
uint8_t address;
uint8_t function;
uint8_t length;
uint16_t values[125];
uint16_t crc;
} response0304;


__pack struct
{
uint8_t address;
uint8_t function;
uint16_t index;
uint16_t value;
uint16_t crc;
} request05;

__pack struct
{
uint8_t address;
uint8_t function;
uint16_t index;
uint16_t value;
uint16_t crc;
} response05;

__pack struct
{
uint8_t address;
uint8_t function;
uint16_t index;
uint16_t value;
uint16_t crc;
} request06;

__pack struct
{
uint8_t address;
uint8_t function;
uint16_t index;
uint16_t value;
uint16_t crc;
} response06;

__pack struct
{
uint8_t address;
uint8_t function;
uint16_t index;
uint16_t count;
uint8_t length;
uint8_t values[246];
uint16_t crc;
} request15;

__pack struct
{
uint8_t address;
uint8_t function;
uint16_t index;
uint16_t count;
uint16_t crc;
} response15;

__pack struct
{
uint8_t address;
uint8_t function;
uint16_t index;
uint16_t count;
uint8_t length;
uint16_t values[123];
uint16_t crc;
} request16;

__pack struct
{
uint8_t address;
uint8_t function;
uint16_t index;
uint16_t count;
uint16_t crc;
} response16;

__pack struct
{
uint8_t address;
uint8_t function;
uint16_t index;
uint16_t andmask;
uint16_t ormask;
uint16_t crc;
} request22;

__pack struct
{
uint8_t address;
uint8_t function;
uint16_t index;
uint16_t andmask;
uint16_t ormask;
uint16_t crc;
} response22;
} ModbusParser;

# 71 "lightmodbus/master.h"
typedef struct modbusMaster
{

uint8_t predictedResponseLength;

# 85
struct
{


uint8_t frame[9];

# 96
uint8_t length;
} request;

# 108
struct
{


uint8_t frame[9];

# 119
uint8_t length;
} response;

# 128
struct
{
uint8_t address;
uint16_t index;
uint16_t count;
uint8_t length;
ModbusDataType type;
uint8_t function;


union
{

# 147
uint8_t coils[3];

# 155
uint16_t regs[3 >> 1];
};

# 175
} data;

# 183
struct
{
uint8_t address;
uint8_t function;
ModbusExceptionCode code;
} exception;


ModbusFrameError parseError;


ModbusFrameError buildError;

# 206
} ModbusMaster;

# 47 "lightmodbus/master/mbcoils.h"
extern ModbusError modbusBuildRequest0102( ModbusMaster *status, uint8_t function, uint8_t address, uint16_t index, uint16_t count );

# 62
static inline ModbusError modbusBuildRequest01( ModbusMaster *status, uint8_t address, uint16_t index, uint16_t count )
{ return modbusBuildRequest0102( (status), 1, (address), (index), (count) ); }

# 77
static inline ModbusError modbusBuildRequest02( ModbusMaster *status, uint8_t address, uint16_t index, uint16_t count )
{ return modbusBuildRequest0102( (status), 2, (address), (index), (count) ); }

# 92
extern ModbusError modbusBuildRequest05( ModbusMaster *status, uint8_t address, uint16_t index, uint16_t value );

# 240 "lightmodbus/master.h"
extern ModbusError modbusParseResponse( ModbusMaster *status );

# 247
extern ModbusError modbusMasterInit( ModbusMaster *status );

# 254
extern ModbusError modbusMasterEnd( ModbusMaster *status );

# 6 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\stddef.h"
typedef int ptrdiff_t;

# 45 "lightmodbus/slave.h"
struct modbusSlave;

# 51
typedef struct modbusSlaveUserFunction
{
uint8_t function;

# 60
ModbusError ( *handler )( struct modbusSlave *status, ModbusParser *parser );
} ModbusSlaveUserFunction;

# 73
typedef enum modbusRegisterQuery
{
MODBUS_REGQ_R,
MODBUS_REGQ_W,
MODBUS_REGQ_R_CHECK,
MODBUS_REGQ_W_CHECK
} ModbusRegisterQuery;

# 90
typedef uint16_t ( *ModbusRegisterCallbackFunction )( ModbusRegisterQuery query, ModbusDataType datatype, uint16_t index, uint16_t value, void *ctx );

# 96
typedef struct modbusSlave
{
uint8_t address;

# 107
ModbusRegisterCallbackFunction registerCallback;

# 114
void *registerCallbackContext;

# 124
uint16_t registerCount;
uint16_t inputRegisterCount;



uint8_t *coils;
uint8_t *discreteInputs;
uint8_t *coilMask;
uint16_t coilMaskLength;

uint16_t coilCount;
uint16_t discreteInputCount;

# 141
ModbusExceptionCode lastException;

# 149
ModbusFrameError parseError;

# 159
ModbusSlaveUserFunction *userFunctions;
uint16_t userFunctionCount;

# 172
struct
{


uint8_t frame[23];

# 183
uint8_t length;
} response;

# 195
struct
{


uint8_t frame[9];

# 206
uint8_t length;
} request;

} ModbusSlave;

# 231
extern ModbusError modbusBuildException( ModbusSlave *status, uint8_t function, ModbusExceptionCode code );

# 258
extern ModbusError modbusParseRequest( ModbusSlave *status );

# 265
extern ModbusError modbusSlaveInit( ModbusSlave *status );

# 272
extern ModbusError modbusSlaveEnd( ModbusSlave *status );

# 293
extern ModbusError modbusBuildExceptionErr( ModbusSlave *status, uint8_t function, ModbusExceptionCode code, ModbusFrameError parseError );

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

# 11 "app_modbus.h"
typedef enum {
MODBUS_INIT,
MODBUS_READY,
MODBUS_START,
MODBUS_TIMEOUT,
MODBUS_OUTPUT,
MODBUS_ERRPARSE,
MODBUS_EXCEPTION,
MODBUS_END
} e_Modbus_Seq;

typedef enum {
BAUD_4800,
BAUD_9600,
BAUD_14400,
BAUD_19200,
BAUD_38400,
BAUD_57600
} e_Baudrate;

typedef enum {
TO_ONE_SEC,
TO_150_MSEC,
TO_300_MSEC,
TO_600_MSEC,
TO_TWO_SEC
} e_Timeout;

typedef enum {
EV_NORMAL,
EV_UP
} e_EventType;

typedef enum {
RLY_NONE,
RLY_OPEN,
RLY_SHORT
} e_RelayStatus;

typedef struct {
uint8_t seq;
uint8_t timeout;


bool event_flag;
bool fire_flag;
uint8_t fire_retry;
uint32_t event_timer;
e_EventType last_event;
e_RelayStatus relay_status;
bool isWarmDone;

} s_Modbus;

# 69
void modbus_init(void);
void modbus_task(void);

void modbus_set_register(const uint16_t* reg);
void modbus_set_swap(bool isSwap);

uint32_t modbus_get_baudrate(uint8_t baud);
uint8_t modbus_get_timeout(uint8_t to);

# 18 "app_modbus.c"
u_SensorValue g_modbus_value;


extern s_Queue g_modbus_queue;

extern s_Nvm g_nvm;

extern s_Modbus g_modbus;

ModbusSlave g_slave;
ModbusMaster g_master;

uint16_t* g_pRegs;
bool g_swap;

volatile uint8_t g_timeout_count;
volatile uint16_t g_relay_sec_count;
volatile uint16_t g_relay_status_count;

# 43
const uint32_t g_baudrate[6] = {
4800, 9600, 14400, 19200, 38400, 57600
};


const uint8_t g_timeout[5] = {
100, 15, 30, 60, 200
};

uint16_t rcallback(ModbusRegisterQuery query, ModbusDataType datatype, uint16_t index, uint16_t value, void *ctx)
{
if(query == MODBUS_REGQ_R_CHECK)
return 1;
if(query == MODBUS_REGQ_R)
{
if(datatype == MODBUS_HOLDING_REGISTER)
{
if (g_swap) {
return modbusSwapEndian(g_pRegs[index]);
} else {
return g_pRegs[index];
}
}
}
return 0;
}

void modbus_set_register(const uint16_t* reg)
{
g_pRegs = (uint16_t*)reg;
}

void modbus_set_swap(bool isSwap)
{
g_swap = isSwap;
}

uint32_t modbus_get_baudrate(uint8_t baud)
{
if (baud > BAUD_57600) baud = BAUD_57600;
return g_baudrate[baud];
}

uint8_t modbus_get_timeout(uint8_t to)
{
if (to > TO_TWO_SEC) to = TO_TWO_SEC;
return g_timeout[to];
}

void modbus_init(void)
{

# 97
g_relay_sec_count = 0;
g_relay_status_count = 0;

g_modbus.event_flag = 0;
g_modbus.fire_flag = 0;
g_modbus.fire_retry = 0;
g_modbus.last_event = EV_NORMAL;
g_modbus.event_timer = 0;
g_modbus.relay_status = RLY_NONE;
g_modbus.isWarmDone = 0;

g_slave.address = g_nvm.flash.slave_id;
g_slave.registerCallback = rcallback;
g_slave.registerCount = (sizeof(float) * 4) / sizeof(uint16_t);

modbus_set_register((uint16_t*)g_modbus_value.word);

modbusSlaveInit(&g_slave);
modbusMasterInit(&g_master);

g_swap = g_nvm.flash.byte_swap;

g_timeout_count = 0;
g_modbus.timeout = modbus_get_timeout(g_nvm.flash.timeout);

rs485_init(modbus_get_baudrate(g_nvm.flash.baudrate));
}


static bool modbus_relay_ouput(const uint8_t relay_idx, const bool on)
{
g_modbus.relay_status = RLY_NONE;
uint16_t data = (on == 1)?0xff00:0x0000;
uint8_t idx = ((relay_idx - 1) < 0)?0:(relay_idx - 1);
ModbusError err = modbusBuildRequest05(&g_master, g_nvm.flash.ctrl_slave_id,
600 + idx, data);
if (err != MODBUS_OK) {
return 0;
}

# 141
rs485_writeBytes(g_master.request.frame, g_master.request.length);
return 1;
}


static bool modbus_relay_status(void)
{
g_modbus.relay_status = RLY_NONE;
ModbusError err = modbusBuildRequest01(&g_master, g_nvm.flash.ctrl_slave_id,
600, 0x0008);
if (err != MODBUS_OK) {
return 0;
}

# 159
rs485_writeBytes(g_master.request.frame, g_master.request.length);
return 1;
}


static e_EventType modbus_check_threshold(const float ppm)
{
float max = g_nvm.flash.ctrl_ppm_max;

e_EventType type = EV_NORMAL;
if (ppm > max) {
type = EV_UP;
}
return type;
}


static void modbus_check_event(const e_EventType type)
{
if (g_modbus.last_event != type) {
g_modbus.last_event = type;
g_modbus.event_flag = 1;
g_modbus.event_timer = 0;
}
if (g_modbus.event_flag) {
g_modbus.event_timer++;

# 189
if (g_modbus.event_timer >= g_nvm.flash.ctrl_holding_min * 60) {
g_modbus.event_timer = 0;
g_modbus.event_flag = 0;
g_modbus.fire_flag = 1;
}
}
}


static void modbus_fire_event(void)
{
modbus_relay_ouput(g_nvm.flash.ctrl_relay_no, (g_modbus.last_event==EV_UP)?1:0);
}


static void modbus_master_response_parse(void)
{
uint8_t idx = ((g_nvm.flash.ctrl_relay_no - 1) < 0)?0:(g_nvm.flash.ctrl_relay_no - 1);
switch (g_master.data.function) {

case 0x01:
if (g_modbus.fire_flag == 0 && g_modbus.event_flag == 0) {
if ((g_master.data.coils[0] >> idx) & 0x01) {
if (g_modbus.last_event == EV_NORMAL && g_modbus.relay_status != RLY_OPEN) {
modbus_fire_event();
}
} else {
if (g_modbus.last_event == EV_UP && g_modbus.relay_status != RLY_SHORT) {
modbus_fire_event();
}
}
}
break;

case 0x05:
if (g_modbus.last_event == EV_NORMAL) {
if (g_master.data.coils[0] == 0) {
g_modbus.relay_status = RLY_OPEN;
g_modbus.fire_flag = 0;
g_modbus.fire_retry = 0;
}
}
else if (g_modbus.last_event == EV_UP) {
if (g_master.data.coils[0] != 0) {
g_modbus.relay_status = RLY_SHORT;
g_modbus.fire_flag = 0;
g_modbus.fire_retry = 0;
}
}
break;
}
}

static void modbus_master_relay_status_task(void)
{
if (g_relay_status_count >= 1000) {
g_relay_status_count = 0;
if (g_modbus.fire_flag == 0 && g_modbus.event_flag == 0) {
modbus_relay_status();
}
}
}


static void modbus_master_relay_control_task(void)
{
float ppm;
if (g_relay_sec_count >= 100) {
g_relay_sec_count = 0;



ppm = g_modbus_value.float_value[g_nvm.flash.ctrl_channel];

modbus_check_event(modbus_check_threshold(ppm));

if (g_modbus.fire_flag) {
if (g_modbus.fire_retry >= 3) {
g_modbus.fire_flag = 0;
g_modbus.fire_retry = 0;
return;
}
modbus_fire_event();
g_modbus.fire_retry++;
}
}
}


static void modbus_master_task(void)
{
uint8_t byte;

switch (g_modbus.seq) {
case MODBUS_INIT:
modbus_init();
g_timeout_count = 0;
g_modbus.seq = MODBUS_READY;
break;
case MODBUS_READY:
if (buffer_de_queue_bool(&g_modbus_queue, &byte)) {
g_timeout_count = 0;
if (byte == g_nvm.flash.ctrl_slave_id && g_master.predictedResponseLength > 0) {
g_master.response.length = 0;
g_master.response.frame[g_master.response.length++] = byte;
g_modbus.seq = MODBUS_START;
}
}
break;
case MODBUS_START:
if (buffer_de_queue_bool(&g_modbus_queue, &byte)) {
g_timeout_count = 0;
g_master.response.frame[g_master.response.length++] = byte;
if (g_master.response.length >= g_master.predictedResponseLength) {
switch (modbusParseResponse(&g_master)) {

case MODBUS_OK:
g_modbus.seq = MODBUS_OUTPUT;
break;

case MODBUS_ERROR_EXCEPTION:
case MODBUS_ERROR_PARSE:
case MODBUS_ERROR_BUILD:
g_modbus.seq = MODBUS_EXCEPTION;
break;

case MODBUS_ERROR_ALLOC:
case MODBUS_ERROR_OTHER:
case MODBUS_ERROR_NULLPTR:
g_modbus.seq = MODBUS_END;
break;
}
}
} else {
if (g_timeout_count > g_modbus.timeout) {
g_modbus.seq = MODBUS_TIMEOUT;
}
}
break;
case MODBUS_TIMEOUT:
g_modbus.seq = MODBUS_END;
break;
case MODBUS_OUTPUT:
{

# 343
modbus_master_response_parse();
g_modbus.seq = MODBUS_END;
}
break;
case MODBUS_EXCEPTION:

# 358
g_modbus.seq = MODBUS_END;
break;
case MODBUS_END:
modbusMasterEnd(&g_master);
g_timeout_count = 0;
g_modbus.seq = MODBUS_READY;
break;
}
}


static void modbus_slave_task(void)
{
uint8_t byte;

switch (g_modbus.seq) {
case MODBUS_INIT:
modbus_init();
g_timeout_count = 0;
g_modbus.seq = MODBUS_READY;
break;
case MODBUS_READY:
if (buffer_de_queue_bool(&g_modbus_queue, &byte)) {
g_timeout_count = 0;
if (byte == g_slave.address) {
g_slave.request.length = 0;
g_slave.request.frame[g_slave.request.length++] = byte;
g_modbus.seq = MODBUS_START;
}
}
break;
case MODBUS_START:
if (buffer_de_queue_bool(&g_modbus_queue, &byte)) {
g_timeout_count = 0;
g_slave.request.frame[g_slave.request.length++] = byte;
if (g_slave.request.length >= 8) {
switch (modbusParseRequest(&g_slave)) {

case MODBUS_OK:
g_modbus.seq = MODBUS_OUTPUT;
break;

case MODBUS_ERROR_EXCEPTION:
case MODBUS_ERROR_PARSE:
case MODBUS_ERROR_BUILD:
g_modbus.seq = MODBUS_EXCEPTION;
break;

case MODBUS_ERROR_ALLOC:
case MODBUS_ERROR_OTHER:
case MODBUS_ERROR_NULLPTR:
g_modbus.seq = MODBUS_END;
break;
}
}
} else {
if (g_timeout_count > g_modbus.timeout) {
g_modbus.seq = MODBUS_TIMEOUT;
}
}
break;
case MODBUS_TIMEOUT:
g_modbus.seq = MODBUS_END;
break;
case MODBUS_OUTPUT:
rs485_writeBytes(g_slave.response.frame, g_slave.response.length);
g_modbus.seq = MODBUS_END;
break;
case MODBUS_EXCEPTION:

# 435
g_modbus.seq = MODBUS_END;
break;
case MODBUS_END:
modbusSlaveEnd(&g_slave);
g_timeout_count = 0;
g_modbus.seq = MODBUS_READY;
break;
}
}

void modbus_task(void)
{
if (g_nvm.flash.sensing_on == SENSING_ON) {
if (g_nvm.flash.ctrl_master_mode == MODBUS_MASTER_MODE) {
modbus_master_task();
if (g_modbus.isWarmDone) {
modbus_master_relay_control_task();
} else {
if (g_relay_sec_count >= 18000) {
g_relay_sec_count = 0;
g_modbus.isWarmDone = 1;
}
}
modbus_master_relay_status_task();
} else {
modbus_slave_task();
}
}
}
