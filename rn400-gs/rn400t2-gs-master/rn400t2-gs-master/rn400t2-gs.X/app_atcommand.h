
#ifndef _APP_AT_COMMAND_H_
#define _APP_AT_COMMAND_H_

typedef enum {
    ATNONE,
	ATCZ,
    ATCVER,
    ATCRST, // h/w reset
#ifdef SUPPORT_BOOLTLOADER
    ATCBLRST, // bootloader reset
#endif

    ATCD, // gas ppm, temp
    ATCQ, // gas uV, gas ppm, temp, zero uV
    ATCH, // gas uV, gas ppm, temp, zero uV, slop uV, stored zero uV
    ATCUV, // gas uV, gas ppm
    ATCMODEL,

    ATCSMODEL, // serial number apply
    ATCFTRST, // factory reset
    ATCSON, // sensing & 485 on/off : on:1, off:0

    // modbus
    ATCISMST, // modbus is master mode, 0: slave mode, 1: master mode
    ATCMODCH, // relay channel, channel 1 : 0, channel 2 : 1
    ATCMSTID, // relay slave id at master mode, default 0x01
    ATCRLYNO, // relay no, 1 ~ 8
    ATCPPMMAX, // default 15.0, allow range max value
    ATCRLYDLY, // default 1min, value is minute

    ATCMODID, // modbus slave id
    ATCMODBR, // modbus baud rate
    ATCMODSW, // modbus float byte swap. default little endian
    ATCMODTO, // modbus timeout

    // eeprom
    ATCOFFG,
    ATCOFFT,
    ATCCAP, // GS use supercap
    ATCSINM, // sensor model 0: NH3, 1: H2S
    ATCSNAME, // sensor name
//    ATCADCGN, // ads1114 gain amplifier
//    ATCLMPGN, // lmp91000 transimpedance gain
//    ATCLMPRL, // lmp91000 load resistance
//    ATCLMPIZ, // lmp91000 internal zero selection
    ATCCAL, // zero uV, span uV, cal ppm
    ATCCZR, // set current uV to zero uV
    ATCCSP, // cal ppm, slop uV, zero uV, span uV

    ATCMODE, // filter on/off
    ATCTCMP, // temp compensation apply or no apply

    ATCC, // temp output mode
    ATCF, // temp output mode

    ATCWIN, // gas window size

    //execute datetime
    ATCUSED,
    ATCEXTM,
    ATCBLDTM
} e_AtCommand;

typedef enum {
    AT_READONLY,
    AT_APPLYONLY,
    AT_READAPPLY,
    AT_STRAPPLY
} e_CommandType;

typedef enum {
    AT_INIT,
    AT_START,
    AT_PARSE,
    AT_APPLY,
    AT_MESSAGE,
    AT_END
} e_CommandSeq;

typedef struct {
    uint8_t channelno; 
    bool last_update;      //write result flag
    
    e_AtCommand atcommand; //atcommand enumeration value
    char szcommand[11]; 

    bool isApply;          //write flag
    char apply_params[32]; //command parameter buffer
    char manual_params[4][32]; //command multi parameter buffer
    
    e_CommandType type; 
} s_AtCommand_status;


typedef struct {
    e_CommandSeq seq;   //atcommand state

    char read_cmd[64];  //read buffer
    uint8_t readidx;    

    s_AtCommand_status status; //atcommand result
    
} s_AtCommand;


#ifdef __cplusplus
extern "C" {
#endif

    void atcommand_init(void);
    void atcommand_task(void);
    bool eeprom_update(uint8_t chno);
    bool eeprom_update_all();
    
#ifdef __cplusplus
}
#endif

#endif // _APP_AT_COMMAND_H_
