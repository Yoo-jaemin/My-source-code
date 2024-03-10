
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
    ATCQ, // gas ppm, temp, humi, NULL
    ATCH, // gas uV, gas ppm, temp, zero uV, slop uV, stored zero uV
    ATCUV, // gas uV, gas ppm
    ATCSNR,
    ATCFETS,
    ATCFETO,
            
    ATCMODEL,
            
    ATACSLP,
    ATACZSF,
    ATACZSR,        
    ATACSS,        
            
    ATCSMODEL,  

    ATCC,
    ATCF,

    ATCCAL, // zero uV, nA per ppm
    ATCCZR, 
    ATCCSP, // set nA per ppm

    ATCOFF,
    ATCMODE, // filter on/off
    ATCTCMP, 

    // kalman filter parameter set        
    ATCWIN,
    ATCKMFEM,
    ATCKMFEE,
        
    ATACEN,
    ATACZR,        

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
    bool gas_update;       //gas injection calib result flag
    
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
    
    
#ifdef __cplusplus
}
#endif

#endif // _APP_AT_COMMAND_H_
