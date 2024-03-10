
# 1 "lightmodbus/slave/sregs.c"

# 4 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18F-J_DFP/1.4.41/xc8\pic\include\__size_t.h"
typedef unsigned size_t;

# 7 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\stdlib.h"
typedef unsigned short wchar_t;

# 15
typedef struct {
int rem;
int quot;
} div_t;
typedef struct {
unsigned rem;
unsigned quot;
} udiv_t;
typedef struct {
long quot;
long rem;
} ldiv_t;
typedef struct {
unsigned long quot;
unsigned long rem;
} uldiv_t;

# 65
extern double atof(const char *);
extern double strtod(const char *, const char **);
extern int atoi(const char *);
extern unsigned xtoi(const char *);
extern long atol(const char *);

# 73
extern long strtol(const char *, char **, int);

extern int rand(void);
extern void srand(unsigned int);
extern void * calloc(size_t, size_t);
extern div_t div(int numer, int denom);
extern udiv_t udiv(unsigned numer, unsigned denom);
extern ldiv_t ldiv(long numer, long denom);
extern uldiv_t uldiv(unsigned long numer,unsigned long denom);

# 85
extern unsigned long _lrotl(unsigned long value, unsigned int shift);
extern unsigned long _lrotr(unsigned long value, unsigned int shift);
extern unsigned int _rotl(unsigned int value, unsigned int shift);
extern unsigned int _rotr(unsigned int value, unsigned int shift);




extern void * malloc(size_t);
extern void free(void *);
extern void * realloc(void *, size_t);


# 13 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\xc8debug.h"
#pragma intrinsic(__builtin_software_breakpoint)
extern void __builtin_software_breakpoint(void);

# 104 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\stdlib.h"
extern int atexit(void (*)(void));
extern char * getenv(const char *);
extern char ** environ;
extern int system(char *);
extern void qsort(void *, size_t, size_t, int (*)(const void *, const void *));
extern void * bsearch(const void *, void *, size_t, size_t, int(*)(const void *, const void *));
extern int abs(int);
extern long labs(long);

extern char * itoa(char * buf, int val, int base);
extern char * utoa(char * buf, unsigned val, int base);




extern char * ltoa(char * buf, long val, int base);
extern char * ultoa(char * buf, unsigned long val, int base);

extern char * ftoa(float f, int * status);

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

# 49 "lightmodbus/slave/../lightmodbus.h"
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

# 43 "lightmodbus/slave/../parser.h"
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

# 71 "lightmodbus/slave/../master.h"
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

# 47 "lightmodbus/slave/../master/mbcoils.h"
extern ModbusError modbusBuildRequest0102( ModbusMaster *status, uint8_t function, uint8_t address, uint16_t index, uint16_t count );

# 62
static inline ModbusError modbusBuildRequest01( ModbusMaster *status, uint8_t address, uint16_t index, uint16_t count )
{ return modbusBuildRequest0102( (status), 1, (address), (index), (count) ); }

# 77
static inline ModbusError modbusBuildRequest02( ModbusMaster *status, uint8_t address, uint16_t index, uint16_t count )
{ return modbusBuildRequest0102( (status), 2, (address), (index), (count) ); }

# 92
extern ModbusError modbusBuildRequest05( ModbusMaster *status, uint8_t address, uint16_t index, uint16_t value );

# 240 "lightmodbus/slave/../master.h"
extern ModbusError modbusParseResponse( ModbusMaster *status );

# 247
extern ModbusError modbusMasterInit( ModbusMaster *status );

# 254
extern ModbusError modbusMasterEnd( ModbusMaster *status );

# 6 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\stddef.h"
typedef int ptrdiff_t;

# 45 "lightmodbus/slave/../slave.h"
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

# 45 "lightmodbus/slave/sregs.h"
extern ModbusError modbusParseRequest0304( ModbusSlave *status, ModbusParser *parser );

# 28 "lightmodbus/slave/sregs.c"
ModbusError modbusParseRequest0304( ModbusSlave *status, ModbusParser *parser )
{




uint8_t frameLength = 8;
uint8_t i = 0;


if ( status == (0) || parser == (0) ) return MODBUS_ERROR_NULLPTR;
if ( parser->_base.function != 3 && parser->_base.function != 4 )
{
status->parseError = MODBUS_FERROR_BADFUN;
return MODBUS_ERROR_PARSE;
}



if ( parser->_base.address == 0 )
{
status->parseError = MODBUS_FERROR_BROADCAST;
return MODBUS_ERROR_PARSE;
}


if ( status->request.length != frameLength )
{
return modbusBuildExceptionErr( status, parser->_base.function, MODBUS_EXCEP_ILLEGAL_VALUE, MODBUS_FERROR_LENGTH );
}


uint16_t index = modbusMatchEndian( parser->request0304.index );
uint16_t count = modbusMatchEndian( parser->request0304.count );



ModbusDataType datatype = parser->_base.function == 3 ? MODBUS_HOLDING_REGISTER : MODBUS_INPUT_REGISTER;



if ( count == 0 || count > 125 )
{

return modbusBuildExceptionErr( status, parser->_base.function, MODBUS_EXCEP_ILLEGAL_VALUE, MODBUS_FERROR_COUNT );
}



if ( status->registerCallback == (0) )
return modbusBuildExceptionErr( status, parser->_base.function, MODBUS_EXCEP_ILLEGAL_ADDRESS, MODBUS_FERROR_NOSRC );

# 84
if ( index >= ( parser->_base.function == 3 ? status->registerCount : status->inputRegisterCount ) || (uint32_t) index + (uint32_t) count > (uint32_t) ( parser->_base.function == 3 ? status->registerCount : status->inputRegisterCount ) )

# 87
{

return modbusBuildExceptionErr( status, parser->_base.function, MODBUS_EXCEP_ILLEGAL_ADDRESS, MODBUS_FERROR_RANGE );
}



for ( i = 0; i < count; i++ )
if ( status->registerCallback( MODBUS_REGQ_R_CHECK, datatype, index + i, 0, status->registerCallbackContext ) == 0 )
return modbusBuildExceptionErr( status, parser->_base.function, MODBUS_EXCEP_SLAVE_FAILURE, MODBUS_FERROR_NOREAD );



frameLength = 5 + ( count << 1 );

# 106
if ( frameLength > 23 ) return MODBUS_ERROR_ALLOC;


ModbusParser *builder = (ModbusParser *) status->response.frame;


builder->response0304.address = status->address;
builder->response0304.function = parser->request0304.function;
builder->response0304.length = count << 1;



for ( i = 0; i < count; i++ )
builder->response0304.values[i] = modbusMatchEndian( status->registerCallback( MODBUS_REGQ_R, datatype, index + i, 0, status->registerCallbackContext ) );

# 126
builder->response0304.values[count] = modbusCRC( builder->frame, frameLength - 2 );


status->response.length = frameLength;
status->parseError = MODBUS_FERROR_OK;
return MODBUS_ERROR_OK;
}

