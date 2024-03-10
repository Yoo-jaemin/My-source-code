
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "board.h"

#include "util/_string.h"
#include "util/buffer.h"
#include "bsp/rs485.h"
#include "lightmodbus/lightmodbus.h"

#include "nvm.h"
#include "app_sens_measure.h"
#include "app_modbus.h"

// last float value
u_SensorValue g_modbus_value;

// rs485 modbus buffer
extern s_Queue g_modbus_queue;
// nvm data
extern s_Nvm g_nvm;
// state machine
extern s_Modbus g_modbus;

ModbusSlave g_slave;
ModbusMaster g_master;

uint16_t* g_pRegs;
bool g_swap;

volatile uint8_t g_timeout_count;
volatile uint16_t g_relay_sec_count;
volatile uint16_t g_relay_status_count;

#ifdef USE_DEBUG_PRINT
extern uint8_t writeBuffer[64];
float g_value;
const char hexDigit[] = "0123456789ABCDEF";
#endif

const uint32_t g_baudrate[6] = {
    4800, 9600, 14400, 19200, 38400, 57600
};

// timer interrupt [1sec, 150ms, 300ms, 600ms, 2sec]
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
#ifdef USE_DEBUG_PRINT
    g_value = 10.0f;
#endif
    g_relay_sec_count = 0;
	g_relay_status_count = 0;

    g_modbus.event_flag = false;
    g_modbus.fire_flag = false;
    g_modbus.fire_retry = 0;
    g_modbus.last_event = EV_NORMAL;
    g_modbus.event_timer = 0;
    g_modbus.relay_status = RLY_NONE;
    g_modbus.isWarmDone = false;

    g_slave.address = g_nvm.flash.slave_id;
    g_slave.registerCallback = rcallback;
    g_slave.registerCount = (sizeof(float) * 4) / sizeof(uint16_t);

	modbus_set_register((uint16_t*)g_modbus_value.word); // holding register setting

    modbusSlaveInit(&g_slave);
    modbusMasterInit(&g_master);

    g_swap = g_nvm.flash.byte_swap;

    g_timeout_count = 0;
    g_modbus.timeout = modbus_get_timeout(g_nvm.flash.timeout);

    rs485_init(modbus_get_baudrate(g_nvm.flash.baudrate));
}

// modbus master mode. write single coil (0x05) function. change relay status
static bool modbus_relay_ouput(const uint8_t relay_idx, const bool on)
{
    g_modbus.relay_status = RLY_NONE;
    uint16_t data = (on == true)?0xff00:0x0000;
    uint8_t idx = ((relay_idx - 1) < 0)?0:(relay_idx - 1); // 1 ~ 8 to 0 ~ 7
    ModbusError err = modbusBuildRequest05(&g_master, g_nvm.flash.ctrl_slave_id,
            MODBUS_RELAY_START_ADDRESS + idx, data);
    if (err != MODBUS_OK) {
        return false;
    }

#ifdef USE_DEBUG_PRINT
    sprintf(writeBuffer, "[%d]fire\r\n", on);
    write_command(writeBuffer);
#endif
    rs485_writeBytes(g_master.request.frame, g_master.request.length);
    return true;
}

// modbus master mode. read coils (0x01) function. relay status
static bool modbus_relay_status(void)
{
    g_modbus.relay_status = RLY_NONE;
    ModbusError err = modbusBuildRequest01(&g_master, g_nvm.flash.ctrl_slave_id,
            MODBUS_RELAY_START_ADDRESS, 0x0008);
    if (err != MODBUS_OK) {
        return false;
    }

#ifdef USE_DEBUG_PRINT
    sprintf(writeBuffer, "status\r\n");
    write_command(writeBuffer);
#endif
    rs485_writeBytes(g_master.request.frame, g_master.request.length);
    return true;
}

// modbus master mode. check threshold.
static e_EventType modbus_check_threshold(const float ppm)
{
    float max = g_nvm.flash.ctrl_ppm_max;

    e_EventType type = EV_NORMAL;
    if (ppm > max) {
        type = EV_UP;
    }
    return type;
}

// modbus master mode. check change event status and check holding value.
static void modbus_check_event(const e_EventType type)
{
    if (g_modbus.last_event != type) {
        g_modbus.last_event = type;
        g_modbus.event_flag = true;
        g_modbus.event_timer = 0;
    }
    if (g_modbus.event_flag) {
        g_modbus.event_timer++;
#ifdef USE_DEBUG_PRINT
        sprintf(writeBuffer, "'%d','%d'\r\n", type, g_modbus.event_timer);
        write_command(writeBuffer);
#endif
        if (g_modbus.event_timer >= g_nvm.flash.ctrl_holding_min * ONE_MINUTE_COUNT) {
            g_modbus.event_timer = 0;
            g_modbus.event_flag = false;
             g_modbus.fire_flag = true;
        }
    }
}

// modbus master mode. fire event to slave.
static void modbus_fire_event(void)
{
    modbus_relay_ouput(g_nvm.flash.ctrl_relay_no, (g_modbus.last_event==EV_UP)?true:false);
}

// modbus master mode. slave's response to update fire flags and current relay status.
static void modbus_master_response_parse(void)
{
    uint8_t idx = ((g_nvm.flash.ctrl_relay_no - 1) < 0)?0:(g_nvm.flash.ctrl_relay_no - 1);
    switch (g_master.data.function) {
    // releay status function. Read Coils function
    case 0x01:
        if (g_modbus.fire_flag == false && g_modbus.event_flag == false) {
            if ((g_master.data.coils[0] >> idx) & 0x01) { // RLY_SHORT
                if (g_modbus.last_event == EV_NORMAL && g_modbus.relay_status != RLY_OPEN) {
                    modbus_fire_event();
                }
            } else { // RLY_OPEN
                if (g_modbus.last_event == EV_UP && g_modbus.relay_status != RLY_SHORT) {
                    modbus_fire_event();
                }
            }
        }
        break;
    // relay on/off function. Write Single Coil function
    case 0x05:
        if (g_modbus.last_event == EV_NORMAL) {
            if (g_master.data.coils[0] == 0) {
                g_modbus.relay_status = RLY_OPEN;
                g_modbus.fire_flag = false;
                g_modbus.fire_retry = 0;
            }
        }
        else if (g_modbus.last_event == EV_UP) {
            if (g_master.data.coils[0] != 0) {
                g_modbus.relay_status = RLY_SHORT;
                g_modbus.fire_flag = false;
                g_modbus.fire_retry = 0;
            }
        }
        break;
    } 
}

static void modbus_master_relay_status_task(void)
{
    if (g_relay_status_count >= RLY_STATUS_COUNT) { // 10sec
        g_relay_status_count = 0;
        if (g_modbus.fire_flag == false && g_modbus.event_flag == false) {
            modbus_relay_status();
        }
    }
}

// modbus master mode. 1sec task, last specific sensor's value check threshold and fire event.
static void modbus_master_relay_control_task(void)
{
    float ppm;
    if (g_relay_sec_count >= MASTER_DELAY_COUNT) { // 1sec
        g_relay_sec_count = 0;
    #ifdef USE_DEBUG_PRINT
        ppm = g_value;
    #else
        ppm = g_modbus_value.float_value[g_nvm.flash.ctrl_channel];
    #endif
        modbus_check_event(modbus_check_threshold(ppm));

        if (g_modbus.fire_flag) {
            if (g_modbus.fire_retry >= MODBUS_RELAY_RETRY_COUNT) {
                g_modbus.fire_flag = false;
                g_modbus.fire_retry = 0;
                return;
            }
            modbus_fire_event();
            g_modbus.fire_retry++;
        }
    }
}

// modbus master mode. waiting slave's response and check master's request.
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
                        // parse ok
                        case MODBUS_OK:
                            g_modbus.seq = MODBUS_OUTPUT;
                            break;
                        // slave error exception
                        case MODBUS_ERROR_EXCEPTION:
                        case MODBUS_ERROR_PARSE:
                        case MODBUS_ERROR_BUILD:
                            g_modbus.seq = MODBUS_EXCEPTION;
                            break;
                        // Memory problem
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
#ifdef USE_DEBUG_PRINT
            uint8_t i;
            writeBuffer[0] = hexDigit[g_master.data.length];
            for (i = 0 ; i < g_master.data.length ; i++) {
                writeBuffer[1 + i] = hexDigit[g_master.data.coils[i]];
            }
            writeBuffer[1 + i] = '\n';
            writeBuffer[2 + i] = 0;
            write_command(writeBuffer);
#endif
            modbus_master_response_parse();
            g_modbus.seq = MODBUS_END;
        }
            break;
        case MODBUS_EXCEPTION:
#ifdef USE_DEBUG_PRINT
            writeBuffer[0] = hexDigit[g_master.parseError];
            writeBuffer[1] = hexDigit[g_master.buildError];
            writeBuffer[2] = hexDigit[g_master.exception.code];
            writeBuffer[3] = hexDigit[g_master.exception.address];
            writeBuffer[4] = hexDigit[g_master.exception.function];
            writeBuffer[5] = '\n';
            writeBuffer[6] = 0;
            write_command(writeBuffer);
#endif
            g_modbus.seq = MODBUS_END;
            break;
        case MODBUS_END:
            modbusMasterEnd(&g_master);
            g_timeout_count = 0;
            g_modbus.seq = MODBUS_READY;
            break;
    }  
}

// modbus slave mode. waiting master's request and response to master.
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
                if (g_slave.request.length >= MODUBS_SLAVE_FRAME_SIZE) {
                    switch (modbusParseRequest(&g_slave)) {
                        // parse ok & build response ok
                        case MODBUS_OK:
                            g_modbus.seq = MODBUS_OUTPUT;
                            break;
                        // error exception
                        case MODBUS_ERROR_EXCEPTION:
                        case MODBUS_ERROR_PARSE:
                        case MODBUS_ERROR_BUILD:
                            g_modbus.seq = MODBUS_EXCEPTION;
                            break;
                        // Memory problem
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
#ifdef USE_DEBUG_PRINT
            writeBuffer[0] = hexDigit[g_slave.parseError];
            writeBuffer[1] = hexDigit[g_slave.lastException];
            writeBuffer[2] = hexDigit[g_slave.request.length];
            writeBuffer[3] = '\n';
            writeBuffer[4] = 0;
            write_command(writeBuffer);
#endif
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
                if (g_relay_sec_count >= WARMUP_COUNT) {
                    g_relay_sec_count = 0;
                    g_modbus.isWarmDone = true;
                }
            }
            modbus_master_relay_status_task();
        } else {
            modbus_slave_task();
        }
    }
}
