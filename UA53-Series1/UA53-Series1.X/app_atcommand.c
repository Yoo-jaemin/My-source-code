
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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
#include "bsp/sht3x.h"

#include "system.h"
#include "nvm.h"
#include "filter.h"
#include "sensor.h"
#include "app_led_task.h"
#include "app_sens_measure.h"
#include "app_atcommand.h"

#include "app_linear_regression.h"
#include "app_sens_autoCalibration.h"
 
extern float g_last_value[SENS_COUNT];
extern float g_temp_value[SENS_COUNT];


typedef struct {
	e_AtCommand atcommand;
	char szcommand[11];
    e_CommandType type;
} s_Command_type;

const s_Command_type atcommand_type[] = {
	{ ATCZ, "ATCZ", AT_READONLY },
	{ ATCD, "ATCD", AT_READONLY }, // gas ppm, temp
	{ ATCQ, "ATCQ", AT_READONLY }, // gas uV, gas ppm, temp, zero uV
    { ATCH, "ATCH", AT_READONLY }, // gas uV, gas ppm, temp, zero uV, slop uV, stored zero uV
    { ATCUV, "ATCUV", AT_READONLY }, // gas uV, gas ppm
    { ATCVER, "ATCVER", AT_READONLY },
    { ATCSNR, "ATCSNR",   AT_READONLY },
    { ATCRST, "ATCRST", AT_APPLYONLY }, // h/w reset
#ifdef SUPPORT_BOOLTLOADER
    { ATCBLRST, "ATCBLRST", AT_APPLYONLY }, // bootloader reset
#endif

	{ ATCMODEL, "ATCMODEL", AT_READONLY },
	{ ATCSMODEL, "ATCSMODEL", AT_APPLYONLY },
    { ATCF, "ATCF", AT_APPLYONLY },
	{ ATCC, "ATCC", AT_APPLYONLY },
    { ATCCAL, "ATCCAL", AT_APPLYONLY }, // zero uV, nA per ppm
    
    { ATCCZR, "ATCCZR", AT_APPLYONLY }, // set current uV to zero uV
    { ATCCSP, "ATCCSP", AT_READAPPLY }, // set span(nA per ppm)
    
    { ATCOFF, "ATCOFF%", AT_READAPPLY },
    { ATCMODE, "ATCMODE", AT_READAPPLY }, // filter on/off
    { ATCTCMP, "ATCTCMP", AT_READAPPLY },  

    { ATCWIN, "ATCWIN", AT_READAPPLY },
    { ATCKMFEM, "ATCKMFEM", AT_READAPPLY },
    { ATCKMFEE, "ATCKMFEE", AT_READAPPLY },
	{ ATCEXTM, "ATCEXTM", AT_READAPPLY },
    { ATCUSED, "ATCUSED", AT_READAPPLY },
    { ATCBLDTM, "ATCBLDTM", AT_READONLY },
    
    // auto calibration command
    { ATACSS, "ATACSS", AT_APPLYONLY},
    { ATACEN, "ATACEN", AT_READAPPLY},
    { ATACZSR, "ATACZSR", AT_READONLY },
    { ATACZR, "ATACZR", AT_READAPPLY },
    { ATACSLP, "ATACSLP", AT_READONLY },
    { ATACZSF, "ATACZSF", AT_READONLY } 
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

extern uint8_t g_usb_state;
extern s_Queue g_usb_queue;
extern s_Nvm g_nvm;
extern s_AtCommand g_atcommand;
extern s_Led_Status g_led_status;
extern s_Sens_Measure g_sens_measure;
extern s_Linear_reg g_linear_reg;
extern s_Auto_calib g_sens_autoCalib;
extern s_KalmanFilter_t kalmanFilter; 
extern float g_uV_per_ppm;

uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];
static e_ParseState parse_command(const uint8_t *buff, s_AtCommand_status *status);
static void update_command(s_AtCommand_status* status);
static void build_response(const s_AtCommand_status* status);
static void clear_command();


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
    if (g_usb_state != USB_ATTACHED) return;
    
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
                        if (g_led_status.isBlink == false && g_sens_autoCalib.led_slpSet == OFF)
                            g_led_status.seq = LED_COMMAND;
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
            if (g_led_status.isBlink == false && g_sens_autoCalib.led_slpSet == OFF)
                g_led_status.seq = LED_WAIT_OFF;
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

//Helper function to execute some blocking delay.
static void update_command(s_AtCommand_status* status)
{
    uint8_t apply;
    uint8_t chno = ((status->channelno - 1) < 0) ? 0 : status->channelno - 1;

    switch (status->atcommand) 
    {
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

        case ATCSMODEL:
            if (_strlen(status->apply_params) != 8) break;
            if (_isdigit(status->apply_params, 8)) {
                nvm_clear_all();
                for (int i = 0 ; i < 8 ; i++) g_nvm.flash.serialNum[i] = status->apply_params[i];
            }
            break;        
        case ATCMODE: apply = (uint8_t)_atoi(status->apply_params); if (apply >= RAW_MODE && apply <= FIL_MODE) g_nvm.flash.filter_mode = apply; break;
        case ATCTCMP: apply = (uint8_t)_atoi(status->apply_params); if (apply >= TEMP_NOT_COMPENSATION && apply <= TEMP_COMPENSATION) g_nvm.flash.temp_compensate = apply; break;
        case ATCC: g_nvm.flash.temp_corf = CELSIUS; break;
        case ATCF: g_nvm.flash.temp_corf = FAHRENHEIT; break;
        case ATCOFF:
            if (chno == 0) g_nvm.flash.gasOffset = _atof(status->apply_params);
            else g_nvm.flash.tempOffset = _atof(status->apply_params);
            break;                  
        case ATCCAL:
            if (split_param(status->apply_params, status->manual_params, 3, 32) >= 2) {
                g_nvm.flash.baseLine_uV = _atof(status->manual_params[0]); 
                g_nvm.flash.nA_per_ppm = _atof(status->manual_params[1]); 
                g_nvm.flash.calib_temp = g_last_value[LV_TEMP];
            } else
                return;
            break;
        case ATCCSP: g_nvm.flash.nA_per_ppm = _atof(status->apply_params); break;
        case ATCCZR:
            g_nvm.flash.baseLine_uV = g_last_value[LV_GAS_VOLT];
            g_nvm.flash.calib_temp = g_last_value[LV_TEMP];
            break;
        case ATCWIN: 
            apply = (uint8_t)_atoi(status->apply_params); 
            if (apply >= LEVEL_1 && apply <= LEVEL_15) { 
                g_nvm.flash.window_size = apply;
                Set_KamanFilter_Sensitivity(g_nvm.flash.window_size);
            } break;
        case ATCKMFEM: 
            g_nvm.flash.KMf_e_measure = _atof(status->apply_params); 
            Kalman_setMeasurementError(&kalmanFilter, g_nvm.flash.KMf_e_measure);
            break;
        case ATCKMFEE: 
            g_nvm.flash.KMF_e_estimate = _atof(status->apply_params);
            Kalman_setEstimateError(&kalmanFilter, g_nvm.flash.KMF_e_estimate);
            break;    
        case ATCUSED: g_nvm.flash.usedtime = (uint32_t)_atoi(status->apply_params); break;      
        case ATCEXTM: g_nvm.flash.exectime = (uint32_t)_atoi(status->apply_params); break;
        case ATACEN: apply = (uint8_t)_atoi(status->apply_params); if (apply >= OFF && apply <= ON) g_nvm.flash.auto_Calib = apply; break;
        case ATACZR: g_nvm.flash.zeroRange_ppm = _atof(status->apply_params); break;
        case ATACSS: g_sens_autoCalib.slpSet_en = ON; break;
    }
    
    if (status->atcommand >= ATCSMODEL && status->atcommand <= ATCEXTM)
        status->last_update = nvm_write_flash_all(&g_nvm.flash);
}

static void build_response(const s_AtCommand_status* status)
{
    uint8_t i;
    uint8_t chno = ((status->channelno - 1) < 0) ? 0 : status->channelno - 1;
    uint8_t len = _strcpy(&writeBuffer[0], status->szcommand);
    writeBuffer[len++] = ' ';
    
    if (status->atcommand >= ATCSMODEL && status->atcommand <= ATCEXTM)
        nvm_read_flash_all(&g_nvm.flash);

	switch (status->atcommand)
    {
        case ATCZ: writeBuffer[len++] = 'O'; writeBuffer[len++] = 'K'; break;
        case ATCVER: len += _strcpy(&writeBuffer[len], BOARD_NAME"_"VERSION); break;
        case ATCUV:
        {
            for (i = 0 ; i < 2 ; i++) {
                len += _ftoa(g_last_value[i], &writeBuffer[len]);
                if (i != (2 - 1)) writeBuffer[len++] = ',';
            }
        } break;
        case ATCSNR: len += _ftoa(g_last_value[LV_SNR], &writeBuffer[len]); break;
        case ATCD:
        {
            if (g_sens_measure.isInitDone) {
                if(g_nvm.flash.nA_per_ppm == 0.0f || g_led_status.isBlink)
                    len += _strcpy(&writeBuffer[len], "----");
                else 
                    len += _ftoa(g_last_value[LV_GAS_PPM], &writeBuffer[len]);
                writeBuffer[len++] = ',';
                float temp = g_last_value[LV_TEMP];
                if (g_nvm.flash.temp_corf == FAHRENHEIT)
                    sensor_temp_fahrenheit(&temp);
                len += _ftoa(temp, &writeBuffer[len]);
            } else 
                len += _strcpy(&writeBuffer[len], "----,----");
        } break;
        case ATCQ:
        {
            if (g_sens_measure.isInitDone) { 
                len += _ftoa(g_last_value[LV_GAS_PPM], &writeBuffer[len]);
                writeBuffer[len++] = ',';
                float temp = g_last_value[LV_TEMP];
                if (g_nvm.flash.temp_corf == FAHRENHEIT)
                    sensor_temp_fahrenheit(&temp);
                len += _ftoa(temp, &writeBuffer[len]);
                writeBuffer[len++] = ',';
                len += _ftoa(g_last_value[LV_HUMI], &writeBuffer[len]);
                writeBuffer[len++] = ',';
                len += _strcpy(&writeBuffer[len], "----");
            } else
                len += _strcpy(&writeBuffer[len], "----,----,----,----");
        } break;
        case ATCH: // [uVolt,ppm,temperature,baseLine_uV,nA_per_ppm,----]
        {
            if (g_sens_measure.isInitDone) {
                len += _ftoa(g_last_value[LV_GAS_VOLT] , &writeBuffer[len]);  writeBuffer[len++] = ','; 
                if(g_nvm.flash.nA_per_ppm == 0.0f || g_led_status.isBlink)
                    len += _strcpy(&writeBuffer[len], "----");
                else 
                    len += _ftoa(g_last_value[LV_GAS_PPM], &writeBuffer[len]);
                writeBuffer[len++] = ',';
                float temp = g_last_value[LV_TEMP];
                if (g_nvm.flash.temp_corf == FAHRENHEIT)
                    sensor_temp_fahrenheit(&temp);
                len += _ftoa(temp, &writeBuffer[len]);
                writeBuffer[len++] = ',';
                len += _ftoa(g_nvm.flash.baseLine_uV, &writeBuffer[len]);  writeBuffer[len++] = ',';
                len += _ftoa(g_nvm.flash.nA_per_ppm, &writeBuffer[len]);  writeBuffer[len++] = ',';
                len += _strcpy(&writeBuffer[len], "----");
            } else 
                len += _strcpy(&writeBuffer[len], "----,----,----,----,----,----");           
        } break;
        case ATCMODE: len += _itoa(g_nvm.flash.filter_mode, &writeBuffer[len]); break;
        case ATCTCMP: len += _itoa(g_nvm.flash.temp_compensate, &writeBuffer[len]); break;
        case ATCC: case ATCF:
            if (status->last_update) { writeBuffer[len++] = 'O'; writeBuffer[len++] = 'K'; }
            else { writeBuffer[len++] = 'F'; writeBuffer[len++] = 'A'; writeBuffer[len++] = 'I'; writeBuffer[len++] = 'L'; }
        break;
        case ATCCAL: 
            len += _ftoa(g_nvm.flash.baseLine_uV, &writeBuffer[len]);    writeBuffer[len++] = ',';
            len += _ftoa(g_nvm.flash.nA_per_ppm, &writeBuffer[len]);
        break;
        case ATCSMODEL: len--;  // remove ' '
        case ATCMODEL: for (int i = 0 ; i < 8 ; i++) writeBuffer[len++] = g_nvm.flash.serialNum[i]; break;
        case ATCCZR:  len += _ftoa(g_nvm.flash.baseLine_uV, &writeBuffer[len]); break;  
        case ATCCSP: 
            len += _ftoa(g_nvm.flash.baseLine_uV, &writeBuffer[len]);    writeBuffer[len++] = ',';
            len += _ftoa(g_nvm.flash.nA_per_ppm, &writeBuffer[len]);     writeBuffer[len++] = ',';
            len += _ftoa(g_nvm.flash.calib_temp, &writeBuffer[len]);
        break;
        case ATCOFF:
            if (chno == 0) len += _ftoa(g_nvm.flash.gasOffset, &writeBuffer[len]); 
            else len += _ftoa(g_nvm.flash.tempOffset, &writeBuffer[len]);
            break;
        case ATCWIN: len += _itoa(g_nvm.flash.window_size, &writeBuffer[len]); break;
        case ATCKMFEM: len += _ftoa(g_nvm.flash.KMf_e_measure, &writeBuffer[len]);  break;
        case ATCKMFEE: len += _ftoa(g_nvm.flash.KMF_e_estimate, &writeBuffer[len]); break;
        case ATCEXTM: len += _itoa(g_nvm.flash.exectime, &writeBuffer[len]);   break;    
        case ATCUSED: len += _itoa(g_nvm.flash.usedtime, &writeBuffer[len]);   break;    
        case ATCBLDTM: len += _itoa(g_nvm.flash.buildtime, &writeBuffer[len]); break;
        case ATACEN: len += _itoa(g_nvm.flash.auto_Calib, &writeBuffer[len]);  break;
        case ATACZR: len += _ftoa(g_nvm.flash.zeroRange_ppm, &writeBuffer[len]); break;
        case ATACSS: { writeBuffer[len++] = 'O'; writeBuffer[len++] = 'K'; }   break;
        case ATACZSR: len += _ftoa(g_nvm.flash.slope_min, &writeBuffer[len]); writeBuffer[len++] = ',';
                      len += _ftoa(g_nvm.flash.slope_max, &writeBuffer[len]);  break;
        case ATACSLP: len += _ftoa(g_linear_reg.slope, &writeBuffer[len]);     break;
        case ATACZSF:
        {   
            if (g_nvm.flash.zeroShift_uV == 0.0f) g_sens_autoCalib.sft_ppm = 0.0f;
            else g_sens_autoCalib.sft_ppm = g_nvm.flash.zeroShift_uV / g_uV_per_ppm;
            len += _ftoa(g_nvm.flash.zeroShift_uV, &writeBuffer[len]); writeBuffer[len++] = ',';  
            len += _ftoa(g_sens_autoCalib.sft_ppm, &writeBuffer[len]); writeBuffer[len++] = ',';  
            len += _itoa(g_nvm.flash.autoCalib_cnt, &writeBuffer[len]);
        } break;
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
