#ifndef NVM_H
#define	NVM_H

#include "board.h"

/*
 * EEPROM - 24AA02/24LC02B
  1byte     1byte     1byte     1byte      1byte   1byte      1byte   1byte    1byte   1byte  
.---------.----------.--------.----------.---------.----------.-------.-------.-------.-------.
|supercap | COMP MDEL|ADC gain| LMP GAIN |LMP RLOAD| LMP IntZ | filter| window|temp u |t comp |
.---------.----------.--------.----------.---------.----------.-------'-------'-------'-------'
  4byte     4byte       4bytes       4bytes        4bytes      4bytes        4bytes
.---------.----------.---------------.------------.------------.------------.------------.
| baseline| span uV  |  calib gas |  gas slope |calib baseline | gas offset | temp offset | 
.---------.----------.---------------.------------.------------.------------.------------.
    4bytes       4bytes       10bytes      4byte            2byte
.-----------.------------.-------------.-------------.-------------.
| CAL  TIME | USED TIME  | sensor name | base temp   | check sum   |
.-----------.------------.-------------.-------------.-------------.

 10 byte + 28 byte + 8 byte + 10 byte + 4byte + 2 byte = 62 bytes
 *  
 * The size of float must be 32bit.
 * 
 */

#define EEPROM_ALL_SIZE         62 // 62bytes

#define SENS_NAME_MAX_LENGTH    10

typedef union {
    __pack uint8_t byte[EEPROM_ALL_SIZE];
    __pack struct {
        uint8_t supercap;
        uint8_t sensor_model; /// 1: NH3, 2: H2S
        uint8_t adc_gain; // ads1114 gain amplifier
        uint8_t lmp_gain; // lmp91000 transimpedance gain
        uint8_t lmp_rload; // lmp91000 load resistance
        uint8_t lmp_intZ; // lmp91000 internal zero selection
        uint8_t filter_mode; // block negative ppm value
        uint8_t window_size;
        uint8_t temp_corf;
        uint8_t temp_compensate; // support temperature compensation ppm

        float baseLine_uV; // zero baseline uVolt
        float span_uV; // span uVolt
        float CalibrationGas; // ppm calibration value
        float gas_slope; // sensitivity
        float calib_baseLine; // stored baseline uVolt
        float gasOffset;
        float tempOffset;

        uint32_t caltime;
        uint32_t usedtime;

        __pack uint8_t sensor_name[SENS_NAME_MAX_LENGTH];

        float baseLine_temp; // zero baselne temperature

        uint16_t check_sum;
    };
} u_Eeprom_Nvm;

////////////////////////////////////////////////////////////////////////
/*
 * Internal FLASH - PIC18F26J50
 *   1byte      1byte  
.-------.-------------.
| dummy | sensing_on  |
'-------'-------------'
 * size is 2 bytes
 * 
 *
  1byte     1byte       1byte       1byte     1byte         1byte         4byte    4byte   
.--------.-----------.-----------.----------.--------------.-----------.---------.---------.
| dummy  | 485  on   | is master | ctrl ch  | relay slv id | relay no | ppm max | hold min |
.--------'-----------'-----------'----------.--------------.-----------.---------.---------.
 * size is 14 bytes.

  1byte   1byte    1byte     1byte      4byte      1  1  1  1  1  1  1  1byte
.-------.-------.----------.---------.------------.--.--.--.--.--.--.--.--.
| SWAP  | SLV ID| BAUDRATE | TIMEOUT | BUILD TIME |S |E |R |I |A |L |N |O |
'-------'-------.----------.---------.------------.--.--.--.--.--.--.--.--.
 * size is 16 bytes.
 * 
 * total size is 30 bytes
 */

#define FLASH_ALL_PARAM_SIZE 30

typedef union {
    __pack uint8_t byte[FLASH_ALL_PARAM_SIZE];
    __pack struct {
        uint8_t dummy;
        uint8_t sensing_on; // sensing & 485 on/off on:1, off:0

        uint8_t ctrl_master_mode; // default slave : 0, master : 1
        uint8_t ctrl_channel; // default channel 1 : 0, channel 2 : 1, relay channel
        uint8_t ctrl_slave_id; // default 0x01, for master mode. relay slave id. 
                                // range 0x01 ~ 0x0f, remark: 0x00 --> 0x01
                                // ML-RH8 dip switch
        uint8_t ctrl_relay_no; // default 0, range 0 ~ 7
        float ctrl_ppm_max; // default 15.0, allow range max value
        uint32_t ctrl_holding_min; // default 1min, holding value minute
        
        uint8_t byte_swap; // for only result values
        uint8_t slave_id; // default 54, for slave mode
        uint8_t baudrate;
        uint8_t timeout;
        uint32_t buildtime;
        __pack uint8_t serialNum[8];
    };
} u_Flash_Nvm;
////////////////////////////////////////////////////////////////////////

//typedef enum {
//    NVM_INIT_NONE,
//    NVM_INIT_FLASH,
//    NVM_INIT_EEPRM_CH1,
//    NVM_INIT_EEPRM_CH2
//}e_Nvm_Status;

typedef struct {
    u_Flash_Nvm flash;
    __pack u_Eeprom_Nvm eeprm[CHANNEL_COUNT];
} s_Nvm;

#ifdef	__cplusplus
extern "C" {
#endif

    uint16_t checksum(const uint8_t *data, uint16_t length);

#if 0
    void nvm_all_ff(void);
#endif

    void nvm_init();
    void nvm_clear_channel(uint8_t channel);
    void nvm_clear(void);
    void nvm_clear_all();

    void nvm_sensor_type_channel(uint8_t chno, uint8_t sensor_model);

    bool nvm_write_eeprom_all(uint8_t channel);
    bool nvm_read_eeprom_all(uint8_t channel);

    bool nvm_write_flash_all(u_Flash_Nvm* flash);
    void nvm_read_flash_all(u_Flash_Nvm* flash);

#ifdef	__cplusplus
}
#endif

#endif	/* NVM_H */

