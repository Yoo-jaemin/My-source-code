
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "usb_config.h"
#include "usb/usb_device_cdc.h"

#include "board.h"

#include "util/buffer.h"
#include "util/_string.h"
#include "util/_ftoa.h"
#include "util/_atof.h"
#include "util/_itoa.h"
#include "util/_atoi.h"

#include "bsp/flash.h"
#include "bsp/lmp91000.h"
#include "bsp/ads1114.h"
#include "bsp/power.h"

#include "system.h"
#include "nvm.h"
#include "filter.h"
#include "sensor.h"
#include "app_sens_measure.h"
#include "app_modbus.h"
#include "app_atcommand.h"

#ifdef USE_DEBUG_PRINT
extern float g_value;
#endif

// last float value
extern float g_last_value[CHANNEL_COUNT][SENS_COUNT];
extern u_SensorValue g_modbus_value;

typedef struct {
	e_AtCommand atcommand;
	char szcommand[11];
    e_CommandType type;
} s_Command_type;

const s_Command_type atcommand_type[] = {
#ifdef USE_DEBUG_PRINT
	{ ATCZ, "ATCZ", AT_READAPPLY },
#else
	{ ATCZ, "ATCZ", AT_READONLY },
#endif
	{ ATCD, "ATCD%", AT_READONLY }, // gas ppm, temp
	{ ATCQ, "ATCQ%", AT_READONLY }, // gas uV, gas ppm, temp, zero uV
    { ATCH, "ATCH%", AT_READONLY }, // gas uV, gas ppm, temp, zero uV, slop uV, stored zero uV
    { ATCUV, "ATCUV%", AT_READONLY }, // gas uV, gas ppm
	{ ATCMODEL, "ATCMODEL", AT_READONLY },
    { ATCVER, "ATCVER", AT_READONLY },
    { ATCRST, "ATCRST", AT_APPLYONLY }, // h/w reset
#ifdef SUPPORT_BOOLTLOADER
    { ATCBLRST, "ATCBLRST", AT_APPLYONLY }, // bootloader reset
#endif

    // internal flash
	{ ATCSMODEL, "ATCSMODEL", AT_READAPPLY },
    { ATCFTRST, "ATCFTRST", AT_APPLYONLY }, // factory reset
    { ATCSON, "ATCSON", AT_READAPPLY }, // sensing & 485 on/off : on:1, off:0

    // modbus
	{ ATCISMST, "ATCISMST", AT_READAPPLY }, // modbus is master mode, 0: slave mode, 1: master mode
	{ ATCMODCH, "ATCMODCH", AT_READAPPLY }, // relay channel, channel 1 : 0, channel 2 : 1
	{ ATCMSTID, "ATCMSTID", AT_READAPPLY }, // relay slave id at master mode, default 0x01
	{ ATCRLYNO, "ATCRLYNO", AT_READAPPLY }, // relay no, 1 ~ 8
	{ ATCPPMMAX, "ATCPPMMAX", AT_READAPPLY }, // default 0.0, allow range end value
	{ ATCRLYDLY, "ATCRLYDLY", AT_READAPPLY }, // default 1min, value is minute

	{ ATCMODID, "ATCMODID", AT_READAPPLY }, // modbus slave id
	{ ATCMODBR, "ATCMODBR", AT_READAPPLY }, // modbus baud rate
	{ ATCMODSW, "ATCMODSW", AT_READAPPLY }, // modbus float byte swap - IEEE 754 floating point
	{ ATCMODTO, "ATCMODTO", AT_READAPPLY }, // modbus timeout

    // calibration eeprom
    { ATCCAP, "ATCCAP%", AT_READAPPLY },
    { ATCOFFG, "ATCOFFG%", AT_READAPPLY },
    { ATCOFFT, "ATCOFFT%", AT_READAPPLY },
    { ATCSINM, "ATCSINM%", AT_READAPPLY }, // sensor model 0: NH3, 1: H2S
    { ATCSNAME, "ATCSNAME%", AT_STRAPPLY }, // sensor model 0: NH3, 1: H2S
//    { ATCADCGN, "ATCADCGN%", AT_READAPPLY }, // ads1114 gain amplifier
//    { ATCLMPGN, "ATCLMPGN%", AT_READAPPLY }, // lmp91000 transimpedance gain
//    { ATCLMPRL, "ATCLMPRL%", AT_READAPPLY }, // lmp91000 load resistance
//    { ATCLMPIZ, "ATCLMPIZ%", AT_READAPPLY }, // lmp91000 internal zero selection
    { ATCCAL, "ATCCAL%", AT_READAPPLY }, // zero uV, span uV, cal ppm
    { ATCCZR, "ATCCZR%", AT_APPLYONLY }, // set current uV to zero uV
    { ATCCSP, "ATCCSP%", AT_READAPPLY }, // cal ppm, slop uV, zero uV, span uV

    { ATCMODE, "ATCMODE%", AT_READAPPLY }, // filter on/off
    { ATCTCMP, "ATCTCMP%", AT_READAPPLY }, // temp compensation apply or no apply

    // temperature output mode
    { ATCF, "ATCF%", AT_APPLYONLY },
	{ ATCC, "ATCC%", AT_APPLYONLY },

    // gas ppm window size
    { ATCWIN, "ATCWIN%", AT_READAPPLY },

    //execute datetime
	{ ATCEXTM, "ATCEXTM%", AT_READAPPLY },
    { ATCUSED, "ATCUSED%", AT_READAPPLY },
    { ATCBLDTM, "ATCBLDTM", AT_READONLY }
};

typedef enum {
	PARSE_READY,
	PARSE_START,
	PARSE_PARAM,
	PARSE_COMPL
} e_Parsing_Seq;

typedef enum {
    AT_PARSE_NONE,
    AT_PARSE_OK,
    AT_PARSE_ERROR
} e_ParseState;


extern s_Queue g_usb_queue;
extern s_Nvm g_nvm;
extern u_Eeprom_Nvm g_eeprmTemp[CHANNEL_COUNT];

extern s_AtCommand g_atcommand;
extern s_Sens_Measure g_sens_measure;
extern s_Modbus g_modbus;

uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];
static e_ParseState parse_command(const uint8_t *buff, s_AtCommand_status *status);
static void update_command(s_AtCommand_status* status);
static void build_response(const s_AtCommand_status* status);
static void clear_command(void);

bool eeprom_update(uint8_t chno)
{
    bool retval;
    uint8_t wait_count = 0;

//    if (I2C_Bus_SourceGet() == false)
//        return false;

    while (ACCESS_SourceGet()) {
        ClrWdt();
        __delay_ms(100);
        wait_count++;
        if (wait_count >= 15) { // 1.5s
            return false;
        }
    }

    ACCESS_SourceSet(true); // access pin set high

    retval = nvm_write_eeprom_all(chno);

    ACCESS_SourceSet(false); // access pin set low

    return retval;
}

bool eeprom_update_all()
{
    uint8_t wait_count = 0;

//    if (I2C_Bus_SourceGet() == false) {
//        return false;
//    }

    while (ACCESS_SourceGet()) {
        ClrWdt();
        __delay_ms(100);
        wait_count++;
        if (wait_count >= 15) { // 1.5s
            memcpy(g_nvm.eeprm[0].byte, g_eeprmTemp[0].byte, EEPROM_ALL_SIZE); // restore
            memcpy(g_nvm.eeprm[1].byte, g_eeprmTemp[1].byte, EEPROM_ALL_SIZE);  // restore
            return false;
        }
    }

    /*
     * access pin set high
     */
    ACCESS_SourceSet(true); // access pin set high

    if (g_sens_measure.existChannel[0]) {

        if (nvm_write_eeprom_all(0) == false) {

            /*
             * access pin set low
             */
            ACCESS_SourceSet(false); // access pin set low

            memcpy(g_nvm.eeprm[0].byte, g_eeprmTemp[0].byte, EEPROM_ALL_SIZE); // restore
            if (g_sens_measure.existChannel[1]) {
                memcpy(g_nvm.eeprm[1].byte, g_eeprmTemp[1].byte, EEPROM_ALL_SIZE);  // restore
            }

            return false;
        }
        __delay_ms(10);
    }


    if (g_sens_measure.existChannel[1]) {

        if (nvm_write_eeprom_all(1) == false) {

            /*
             * access pin set low
             */
            ACCESS_SourceSet(false); // access pin set low

            memcpy(g_nvm.eeprm[1].byte, g_eeprmTemp[1].byte, EEPROM_ALL_SIZE);  // restore

            return false;
        }
    }

    /*
     * access pin set low
     */
    ACCESS_SourceSet(false); // access pin set low
    
    return true;
}

void atcommand_init(void)
{
    g_atcommand.seq = AT_INIT;
    clear_command();
}

void write_command(const uint8_t *buff)
{
    if(USBUSARTIsTxTrfReady() == true) 
    {
        putUSBUSART((uint8_t*)buff, (uint8_t)_strlen(buff));
    }
}

void atcommand_task(void)
{
	uint8_t ch;

	switch (g_atcommand.seq) {
        case AT_INIT:
            g_atcommand.seq = AT_START;
            break;
        case AT_START:
            ch = buffer_de_queue(&g_usb_queue);
            if (ch) {
                if (ch == '\r' || ch == '\n') {
                    if (g_atcommand.readidx > 2) {
                        g_atcommand.read_cmd[g_atcommand.readidx++] = ch;
                        g_atcommand.readidx = 0;
                        g_atcommand.seq = AT_PARSE;
                    } else {
                        g_atcommand.readidx = 0;
                        _strclr(g_atcommand.read_cmd, sizeof(g_atcommand.read_cmd));
                    }
                } else {
                    if (g_atcommand.readidx >= sizeof(g_atcommand.read_cmd)) g_atcommand.readidx = 0;
                        g_atcommand.read_cmd[g_atcommand.readidx++] = ch;
                }
            }
            break;  
        case AT_PARSE:
            if (parse_command(g_atcommand.read_cmd, &g_atcommand.status) == AT_PARSE_OK)
                g_atcommand.seq = (g_atcommand.status.isApply) ? AT_APPLY : AT_MESSAGE;
            else g_atcommand.seq = AT_END;
            break;
        case AT_APPLY:
            update_command(&g_atcommand.status);
            g_atcommand.seq = AT_MESSAGE;
            break;
        case AT_MESSAGE:
            build_response(&g_atcommand.status);
            g_atcommand.seq = AT_END;
            break;
        case AT_END:
            clear_command();
            g_atcommand.seq = AT_START;
            break;
	}
}

static bool check_param(char param)
{
    if (param == '-' || param == '.' || param == ',' ||
       (param >= '0' && param <= '9'))
        return true;
    return false;
}

static unsigned param_copy(char *src1, const char *src2)
{
    unsigned int i = 0;
    char ch = 0;
	if(!src1 || !src2) return 0;
	do {
        ch = *src2++;
        if (check_param(ch)) {
            *src1++ = ch;
            i++;
        }
    } while(ch);
    return i;
}

static bool atcommand_compare(const char *src1, const char *src2, uint8_t n, uint8_t *channelno)
{
    if(!src1 || !src2 || n<=0) return false;
    while (n--) {
        char ch = *src1;
        if (ch == '%') {
            uint8_t no = *src2 - '0';
            if (no > 0 && no <= CHANNEL_COUNT) {
                *channelno = no;
                ch = *src2;
            } else
                return false;
        }
        if (!(ch == *src2 || ch == (*src2 - 0x20))) // lower case check
//        if (ch != *src2)
            return false;
        src1++;
        src2++;
    }
    return true;
}

static int8_t check_atcommand(const char *cmd, uint8_t *chno)
{
    for (uint8_t i = 0 ; i < sizeof(atcommand_type)/sizeof(s_Command_type) ; i++) {
        if (_strlen(cmd) == _strlen(atcommand_type[i].szcommand)) {
            if (atcommand_compare(atcommand_type[i].szcommand, cmd, _strlen(cmd), chno)) {
                return i;
            }
        }
    }
    return -1;
}

static e_ParseState parse_command(const uint8_t *buff, s_AtCommand_status *status)
{
	e_Parsing_Seq seq = PARSE_READY;

	char cmd[11] = {0};
	char param[32] = {0};
	uint8_t cmdidx = 0, paramidx = 0;

	e_ParseState retval = AT_PARSE_NONE;

    char ch = 0;
	do
	{
		ch = *buff;
		switch (seq) {
            case PARSE_READY:
                if (ch == 'A' || ch == 'T' || ch == 'a' || ch == 't') {
                    cmd[cmdidx++] = ch;
                    if (cmdidx > 1) {
                        if ((cmd[0] == 'A' || cmd[0] == 'a') &&
                            (cmd[1] == 'T' || cmd[1] == 't')) {
                            seq = PARSE_START;
                        } else retval = AT_PARSE_ERROR;
                    }
                }
                break;
            case PARSE_START:
                if (ch == ' ') {
                    seq = PARSE_PARAM;
                    paramidx = 0;
                } else //ATCSMODEL
                if (cmdidx > 8 &&
                    (cmd[0] == 'A' || cmd[0] == 'a') && (cmd[1] == 'T' || cmd[1] == 't') && (cmd[2] == 'C' || cmd[2] == 'c') &&
                    (cmd[3] == 'S' || cmd[3] == 's') && (cmd[4] == 'M' || cmd[4] == 'm') && (cmd[5] == 'O' || cmd[5] == 'o') &&
                    (cmd[6] == 'D' || cmd[6] == 'd') && (cmd[7] == 'E' || cmd[7] == 'e') && (cmd[8] == 'L' || cmd[8] == 'l')) 
                {
                    seq = PARSE_PARAM;
                    paramidx = 0;
                    param[paramidx++] = ch;
                } else
                if (ch == '\r' || ch == '\n') {
                    seq = PARSE_COMPL;
                } else {
                    if (cmdidx >= sizeof(cmd)) cmdidx = 0;
                    cmd[cmdidx++] = ch;
                }
                break;
            case PARSE_PARAM:
                if (ch == '\r' || ch == '\n') {
                    seq = PARSE_COMPL;
                } else {
                    if (paramidx >= sizeof(param)) paramidx = 0;
                    param[paramidx++] = ch;
                }
                break; 
            case PARSE_COMPL:
            {
                uint8_t chno = 0;
                int8_t idx = check_atcommand(cmd, &chno);
                if (idx >= 0) {
                    status->channelno = chno;
                    status->atcommand = atcommand_type[idx].atcommand;
                    status->type = atcommand_type[idx].type;
                    _strcpy(status->szcommand, cmd);
                    switch (status->type) {
                        case AT_READONLY: status->isApply = false; break;
                        case AT_APPLYONLY: param_copy(status->apply_params, param); status->isApply = true; break;
                        case AT_READAPPLY: status->isApply = (param_copy(status->apply_params, param) > 0) ? true : false; break;
                        case AT_STRAPPLY: status->isApply = (_strcpy(status->apply_params, param) > 0) ? true : false; break;
                    }
                    return AT_PARSE_OK;
                } else
                    return AT_PARSE_ERROR;
            }
                break;
		}
        if (ch) buff++;
	} while(ch);

	return retval;
}

static uint8_t split_param(char* src, char* params, uint8_t m, uint8_t n)
{
    if(!src || !params) return 0;
    uint8_t len = _strlen(src);
    uint8_t i = 0, cnt = 0;
    while (len--) {
        char ch = *src;
        if (ch == ',') {
            if (cnt >= m) return 0;
            *((params + (n * cnt++)) + i++) = '\0';
            i = 0;
        } else {
            *((params + (n * cnt)) + i++) = ch;
            if (i >= n) return 0;
        }
        src++;
    }
    *((params + (n * cnt)) + i++) = '\0';
    return cnt+1;
}

static void update_command(s_AtCommand_status* status)
{
    uint8_t apply;
    uint8_t chno = ((status->channelno - 1) < 0) ? 0 : status->channelno - 1;

    // after eeprom read
    if (g_sens_measure.seq < SENS_READY)
        return;

    if (status->isApply) {
        if ((status->atcommand >= ATCOFFG && status->atcommand <= ATCEXTM)) {
            memcpy(g_eeprmTemp[chno].byte, g_nvm.eeprm[chno].byte, EEPROM_ALL_SIZE); // backup eeprom
        }
        if (status->atcommand == ATCFTRST) {
            if (g_sens_measure.existChannel[0]) {
                memcpy(g_eeprmTemp[0].byte, g_nvm.eeprm[0].byte, EEPROM_ALL_SIZE); // backup eeprom
            }
            if (g_sens_measure.existChannel[1]) {
                memcpy(g_eeprmTemp[1].byte, g_nvm.eeprm[1].byte, EEPROM_ALL_SIZE); // backup eeprom
            }
        }
    }

    switch (status->atcommand) 
    {
#ifdef USE_DEBUG_PRINT
        case ATCZ:
            g_value = _atof(status->apply_params);
            break;
#endif
        // h/w reset
        case ATCRST:
            ResetDeviceCleanly();
            return;
        // HID mode reset
#ifdef SUPPORT_BOOLTLOADER
        case ATCBLRST:
            ResetBootloaderCleanly();
            return;
#endif

        // internal flash
        case ATCSMODEL : if (_strlen(status->apply_params) != 8) break;
            if (_isdigit(status->apply_params, 8)) for (uint8_t i = 0 ; i < 8 ; i++) g_nvm.flash.serialNum[i] = status->apply_params[i]; break;

        // factory reset;
        case ATCFTRST: nvm_clear(); break;

        // sensing & 485 on/off
        case ATCSON: apply = (uint8_t)_atoi(status->apply_params); if (apply >= SENSING_OFF && apply <= SENSING_ON) g_nvm.flash.sensing_on = apply; break;

        // modbus
        case ATCISMST: apply = (uint8_t)_atoi(status->apply_params); if (apply >= MODBUS_SLAVE_MODE && apply <= MODBUS_MASTER_MODE) g_nvm.flash.ctrl_master_mode = apply; break;
        case ATCMODCH: apply = (uint8_t)_atoi(status->apply_params); if (apply >= 0 && apply <= (CHANNEL_COUNT-1)) g_nvm.flash.ctrl_channel = apply; break;
        case ATCMSTID: apply = (uint8_t)_atoi(status->apply_params); if (apply >= 0x01 && apply <= 0x0f) g_nvm.flash.ctrl_slave_id = apply; break;
        case ATCRLYNO: apply = (uint8_t)_atoi(status->apply_params); if (apply >= 1 && apply <= 8) g_nvm.flash.ctrl_relay_no = apply; break;
        case ATCPPMMAX: if (_atof(status->apply_params) > 0.0f) g_nvm.flash.ctrl_ppm_max = _atof(status->apply_params); break;
        case ATCRLYDLY: if ((uint32_t)_atoi(status->apply_params) >= 1) g_nvm.flash.ctrl_holding_min = (uint32_t)_atoi(status->apply_params); break;

        case ATCMODSW: apply = (uint8_t)_atoi(status->apply_params); if (apply >= 0 && apply <= 1) g_nvm.flash.byte_swap = apply; break;
        case ATCMODID: apply = (uint8_t)_atoi(status->apply_params); if (apply > 0) g_nvm.flash.slave_id = apply; break;
        case ATCMODBR: apply = (uint8_t)_atoi(status->apply_params); if (apply >= BAUD_4800 && apply <= BAUD_57600) g_nvm.flash.baudrate = apply; break;
        case ATCMODTO: apply = (uint8_t)_atoi(status->apply_params); if (apply >= TO_ONE_SEC && apply <= TO_TWO_SEC) g_nvm.flash.timeout = apply; break;

        // external eeprom
        case ATCCAP: apply = (uint8_t)_atoi(status->apply_params); if (apply >= 0 && apply <= 1) g_nvm.eeprm[chno].supercap = apply; break;
        case ATCMODE: apply = (uint8_t)_atoi(status->apply_params); if (apply >= 0 && apply <= 1) g_nvm.eeprm[chno].filter_mode = apply; break;
        case ATCTCMP: apply = (uint8_t)_atoi(status->apply_params); if (apply >= 0 && apply <= 1) g_nvm.eeprm[chno].temp_compensate = apply; break;
        case ATCC: g_nvm.eeprm[chno].temp_corf = CELSIUS; break;
        case ATCF: g_nvm.eeprm[chno].temp_corf = FAHRENHEIT; break;
        case ATCOFFG: g_nvm.eeprm[chno].gasOffset = _atof(status->apply_params); break;
        case ATCOFFT: g_nvm.eeprm[chno].tempOffset = _atof(status->apply_params); break;
        case ATCSINM: apply = (uint8_t)_atoi(status->apply_params); if (apply >= NONE && apply <= H2S_50) nvm_sensor_type_channel(chno, apply); break;
        case ATCSNAME:
            if (_strlen(status->apply_params) < SENS_NAME_MAX_LENGTH)
                _strcpy(g_nvm.eeprm[chno].sensor_name, status->apply_params);
            else
                g_nvm.eeprm[chno].sensor_name[SENS_NAME_MAX_LENGTH-1] = '\0';
            break;
        case ATCCAL:
            if (split_param(status->apply_params, status->manual_params, 3, 32) >= 3) {
                if ((_atof(status->manual_params[1]) - _atof(status->manual_params[0])) != 0.0f) {
                    g_nvm.eeprm[chno].baseLine_uV = _atof(status->manual_params[0]); 
                    g_nvm.eeprm[chno].span_uV = _atof(status->manual_params[1]); 
                    g_nvm.eeprm[chno].CalibrationGas = _atof(status->manual_params[2]);
                    g_nvm.eeprm[chno].baseLine_temp = g_last_value[chno][LV_TEMP];
                    if ((g_nvm.eeprm[chno].span_uV - g_nvm.eeprm[chno].baseLine_uV) != 0.0f) {
                        g_nvm.eeprm[chno].gas_slope = ((g_nvm.eeprm[chno].span_uV - g_nvm.eeprm[chno].baseLine_uV) / g_nvm.eeprm[chno].CalibrationGas);
                    }
                }
            }
            break;
        case ATCCSP:
            if ((g_last_value[chno][LV_GAS_VOLT] - g_nvm.eeprm[chno].baseLine_uV) != 0.0f) {
                g_nvm.eeprm[chno].CalibrationGas = _atof(status->apply_params);
                g_nvm.eeprm[chno].span_uV = g_last_value[chno][LV_GAS_VOLT];
                if ((g_nvm.eeprm[chno].span_uV - g_nvm.eeprm[chno].baseLine_uV) != 0.0f) {
                    g_nvm.eeprm[chno].gas_slope = ((g_nvm.eeprm[chno].span_uV - g_nvm.eeprm[chno].baseLine_uV) / g_nvm.eeprm[chno].CalibrationGas);
                }
            }
            break;
        case ATCCZR:
            if ((g_nvm.eeprm[chno].span_uV - g_last_value[chno][LV_GAS_VOLT]) != 0.0f) {
                g_nvm.eeprm[chno].baseLine_uV = g_last_value[chno][LV_GAS_VOLT];
                g_nvm.eeprm[chno].baseLine_temp = g_last_value[chno][LV_TEMP];
                if ((g_nvm.eeprm[chno].span_uV - g_nvm.eeprm[chno].baseLine_uV) != 0.0f) {
                    g_nvm.eeprm[chno].gas_slope = ((g_nvm.eeprm[chno].span_uV - g_nvm.eeprm[chno].baseLine_uV) / g_nvm.eeprm[chno].CalibrationGas);
                }
            }
            break;
        case ATCWIN: apply = (uint8_t)_atoi(status->apply_params); if (apply >= 1 && apply <= MAX_FILTER_SIZE) g_nvm.eeprm[chno].window_size = apply; break;
        case ATCUSED: g_nvm.eeprm[chno].usedtime = (uint32_t)_atoi(status->apply_params); break;      
        case ATCEXTM: 
            g_nvm.eeprm[chno].caltime = (uint32_t)_atoi(status->apply_params); 
            g_nvm.eeprm[chno].calib_baseLine = g_nvm.eeprm[chno].baseLine_uV;
            g_nvm.eeprm[chno].usedtime = 0;
            break;
	}
    
    if (status->isApply) {
        if (status->atcommand >= ATCSMODEL && status->atcommand <= ATCMODTO) {
            status->last_update = nvm_write_flash_all(&g_nvm.flash);
        }

        if (status->atcommand == ATCFTRST) {
            status->last_update = eeprom_update_all();
        }

        if (status->atcommand >= ATCOFFG && status->atcommand <= ATCEXTM) {
            status->last_update = eeprom_update(chno);
        }
    }
}

static uint8_t display_sensor_value(const bool ishex, const uint8_t chno, const uint8_t strlen)
{
    uint8_t len = strlen;

    if (g_sens_measure.isSensorInit[chno] == true)
    {
        if (g_last_value[chno][LV_GAS_VOLT] == NO_VALUE)
            len += _strcpy(&writeBuffer[len], "----");
        else
            len += _ftoa(g_last_value[chno][LV_GAS_VOLT] , &writeBuffer[len]);
        writeBuffer[len++] = ',';
        if((g_nvm.eeprm[chno].span_uV - g_nvm.eeprm[chno].baseLine_uV) == 0.0f ||
                g_nvm.eeprm[chno].CalibrationGas == 0.0f || g_last_value[chno][LV_GAS_PPM] == NO_VALUE)
            len += _strcpy(&writeBuffer[len], "----");
        else 
            len += _ftoa(g_last_value[chno][LV_GAS_PPM], &writeBuffer[len]);
        writeBuffer[len++] = ',';
        if(g_last_value[chno][LV_TEMP] == NO_VALUE) {
            len += _strcpy(&writeBuffer[len], "----");
        } else {
            float temp = g_last_value[chno][LV_TEMP];
            if (g_nvm.eeprm[chno].temp_corf == FAHRENHEIT)
                sensor_temp_fahrenheit(&temp);
            len += _ftoa(temp, &writeBuffer[len]);
        }
    }
    else
    {
        len += _strcpy(&writeBuffer[len], "----,----,----"); 
    }
    writeBuffer[len++] = ',';
    len += _ftoa(g_nvm.eeprm[chno].baseLine_uV, &writeBuffer[len]);       writeBuffer[len++] = ',';
    len += sprintf (&writeBuffer[len], "%.2f", g_nvm.eeprm[chno].gas_slope);

    if (ishex) {
        writeBuffer[len++] = ',';
        len += _ftoa(g_nvm.eeprm[chno].calib_baseLine, &writeBuffer[len]);
    }

    return len;
}

static void build_response(const s_AtCommand_status* status)
{
    uint8_t i;
    uint8_t chno = ((status->channelno - 1) < 0) ? 0 : status->channelno - 1;
    uint8_t len = _strcpy(&writeBuffer[0], status->szcommand);
    writeBuffer[len++] = ' ';

    // after eeprom read
    if (g_sens_measure.seq < SENS_READY) {
        write_command("INITIALIZING...\r\n"); //Initializing
        return;
    }

    if (status->isApply) {
		if (status->atcommand >= ATCSMODEL && status->atcommand <= ATCMODTO)
			nvm_read_flash_all(&g_nvm.flash);

        if (status->atcommand >= ATCOFFG && status->atcommand <= ATCEXTM) {
            if (status->last_update == false) memcpy(g_nvm.eeprm[chno].byte, g_eeprmTemp[chno].byte, EEPROM_ALL_SIZE); // restore temp
        }
    }

	switch (status->atcommand)
    {
        case ATCZ:
#ifdef USE_DEBUG_PRINT
            len += _ftoa(g_value, &writeBuffer[len]); break;
#else
            writeBuffer[len++] = 'O'; writeBuffer[len++] = 'K'; break;
#endif
        case ATCVER: len += _strcpy(&writeBuffer[len], BOARD_NAME"_"VERSION); break;
        case ATCUV:
            for (i = 0 ; i < CHANNEL_COUNT ; i++) {
                if (g_last_value[chno][i] == NO_VALUE)
                    len += _strcpy(&writeBuffer[len], "----");
                else
                    len += _ftoa(g_last_value[chno][i], &writeBuffer[len]);
                if (i != (CHANNEL_COUNT - 1)) writeBuffer[len++] = ',';
            }
            break;
        case ATCD:
            if (g_sens_measure.isSensorInit[chno] == true) {
                if((g_nvm.eeprm[chno].span_uV - g_nvm.eeprm[chno].baseLine_uV) == 0.0f || 
                        g_nvm.eeprm[chno].CalibrationGas == 0.0f || g_last_value[chno][LV_GAS_PPM] == NO_VALUE)
                    len += _strcpy(&writeBuffer[len], "----");
                else 
                    len += _ftoa(g_last_value[chno][LV_GAS_PPM], &writeBuffer[len]);
                writeBuffer[len++] = ',';
                if(g_last_value[chno][LV_TEMP] == NO_VALUE)
                    len += _strcpy(&writeBuffer[len], "----");
                else {
                    float temp = g_last_value[chno][LV_TEMP];
                    if (g_nvm.eeprm[chno].temp_corf == FAHRENHEIT)
                        sensor_temp_fahrenheit(&temp);
                    len += _ftoa(temp, &writeBuffer[len]);
                }
            }
            else
            {
                len += _strcpy(&writeBuffer[len], "----,----");
            }
            break;
        case ATCQ:
            len = display_sensor_value(false, chno, len);
            break;
        case ATCH :
            len = display_sensor_value(true, chno, len);
            break;

        // internal flash
        case ATCSMODEL: len--; // remove ' '
        case ATCMODEL: for (i = 0 ; i < 8 ; i++) writeBuffer[len++] = g_nvm.flash.serialNum[i]; break;

        // factory reset
        case ATCFTRST:
            if (status->last_update) {
                writeBuffer[len++] = 'O'; writeBuffer[len++] = 'K';
            }
            else {  writeBuffer[len++] = 'F'; writeBuffer[len++] = 'A'; writeBuffer[len++] = 'I'; writeBuffer[len++] = 'L'; }
            sensMeasure_sensor_init();
            break;

        // modbus
        case ATCSON: len += _itoa(g_nvm.flash.sensing_on, &writeBuffer[len]);
            if (status->last_update) g_modbus.seq = MODBUS_INIT; break;
        case ATCISMST: len += _itoa(g_nvm.flash.ctrl_master_mode, &writeBuffer[len]);
            if (status->last_update) g_modbus.seq = MODBUS_INIT; break;
        case ATCMODCH: len += _itoa(g_nvm.flash.ctrl_channel, &writeBuffer[len]); break;
        case ATCMSTID: len += _itoa(g_nvm.flash.ctrl_slave_id, &writeBuffer[len]); break;
        case ATCRLYNO: len += _itoa(g_nvm.flash.ctrl_relay_no, &writeBuffer[len]); break;
        case ATCPPMMAX: len += _ftoa(g_nvm.flash.ctrl_ppm_max, &writeBuffer[len]); break;
        case ATCRLYDLY: len += _itoa(g_nvm.flash.ctrl_holding_min, &writeBuffer[len]);
            break;

        case ATCMODSW: len += _itoa(g_nvm.flash.byte_swap, &writeBuffer[len]);
            if (status->last_update) modbus_set_swap((bool)g_nvm.flash.byte_swap); break;
        case ATCMODID: len += _itoa(g_nvm.flash.slave_id, &writeBuffer[len]); 
            if (status->last_update) g_modbus.seq = MODBUS_INIT; break;
        case ATCMODBR: len += _itoa(g_nvm.flash.baudrate, &writeBuffer[len]);
            if (status->last_update) g_modbus.seq = MODBUS_INIT; break;
        case ATCMODTO: len += _itoa(g_nvm.flash.timeout, &writeBuffer[len]);
            if (status->last_update) g_modbus.timeout = modbus_get_timeout(g_nvm.flash.timeout); break;

        // external eeprom
        case ATCCAP: len += _itoa(g_nvm.eeprm[chno].supercap, &writeBuffer[len]); break;
        case ATCSINM: len += _itoa(g_nvm.eeprm[chno].sensor_model, &writeBuffer[len]);
            if (status->last_update) sensMeasure_sensor_init(); break;
        case ATCSNAME: g_nvm.eeprm[chno].sensor_name[SENS_NAME_MAX_LENGTH-1] = '\0'; len += _strcpy(&writeBuffer[len], g_nvm.eeprm[chno].sensor_name); break;
        case ATCMODE: len += _itoa(g_nvm.eeprm[chno].filter_mode, &writeBuffer[len]); break;
        case ATCTCMP: len += _itoa(g_nvm.eeprm[chno].temp_compensate, &writeBuffer[len]); break;
        case ATCC: case ATCF:
            if (status->last_update) { writeBuffer[len++] = 'O'; writeBuffer[len++] = 'K'; }
            else { writeBuffer[len++] = 'F'; writeBuffer[len++] = 'A'; writeBuffer[len++] = 'I'; writeBuffer[len++] = 'L'; }
        break;
        case ATCCAL: 
            len += _ftoa(g_nvm.eeprm[chno].baseLine_uV, &writeBuffer[len]); writeBuffer[len++] = ',';
            len += _ftoa(g_nvm.eeprm[chno].span_uV, &writeBuffer[len]); writeBuffer[len++] = ',';
            len += _ftoa(g_nvm.eeprm[chno].CalibrationGas, &writeBuffer[len]);
        break;
        case ATCCZR:  len += _ftoa(g_nvm.eeprm[chno].baseLine_uV, &writeBuffer[len]); break;  
        case ATCCSP: 
            len += _ftoa(g_nvm.eeprm[chno].CalibrationGas, &writeBuffer[len]); writeBuffer[len++] = ',';
            len += sprintf(&writeBuffer[len], "%.2f", g_nvm.eeprm[chno].gas_slope); writeBuffer[len++] = ',';
            len += _ftoa(g_nvm.eeprm[chno].baseLine_uV, &writeBuffer[len]); writeBuffer[len++] = ',';
            len += _ftoa(g_nvm.eeprm[chno].span_uV, &writeBuffer[len]); writeBuffer[len++] = ',';
            len += _ftoa(g_nvm.eeprm[chno].baseLine_temp, &writeBuffer[len]);
        break;
        case ATCOFFG: len += _ftoa(g_nvm.eeprm[chno].gasOffset, &writeBuffer[len]); break;
        case ATCOFFT: len += _ftoa(g_nvm.eeprm[chno].tempOffset, &writeBuffer[len]); break;
        case ATCWIN: len += _itoa(g_nvm.eeprm[chno].window_size, &writeBuffer[len]); break;
        case ATCEXTM: len += _itoa(g_nvm.eeprm[chno].caltime, &writeBuffer[len]); break;    
        case ATCUSED: len += _itoa(g_nvm.eeprm[chno].usedtime, &writeBuffer[len]); break;    
        case ATCBLDTM: len += _itoa(g_nvm.flash.buildtime, &writeBuffer[len]); break;
	}
    writeBuffer[len++] = '\r'; writeBuffer[len++] = '\n'; writeBuffer[len++] = '\0';
    write_command(writeBuffer);
}

static void clear_command(void)
{
    g_atcommand.readidx = 0;
	g_atcommand.status.channelno = 0;
    g_atcommand.status.last_update = false;
	g_atcommand.status.atcommand = ATNONE;
	g_atcommand.status.isApply = false;
    g_atcommand.status.type = AT_READONLY;

    _strclr(g_atcommand.read_cmd, sizeof(g_atcommand.read_cmd));
    _strclr(g_atcommand.status.szcommand, sizeof(g_atcommand.status.szcommand));
	_strclr(g_atcommand.status.apply_params, sizeof(g_atcommand.status.apply_params));

    _strclr(writeBuffer, CDC_DATA_IN_EP_SIZE);
}
