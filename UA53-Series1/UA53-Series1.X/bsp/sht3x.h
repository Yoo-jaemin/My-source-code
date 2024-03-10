/* 
 * File:   sht3x.h
 * Author: dekist
 *
 * Created on 2019 4/22 
 */

#ifndef SHT3X_H
#define	SHT3X_H

#ifndef SHT3X_I2C_ADDRESS
//#define SHT3X_I2C_ADDRESS 	0x44 // 7bit address
#define SHT3X_I2C_ADDRESS 	0x88 // 8bit address
#endif

#define SHT3X_SOFT_RESET_MSB            0x30
#define SHT3X_SOFT_RESET_LSB            0xa2

/* polling measurement for block read */
// measurement: polling, low repeatability
#define SHT3X_POLLING_READ_MSB          0x24
#define SHT3X_POLLING_READ_LSB          0x16

/* preiodic measurement for nonblock read*/
// 1mps - low repeatability
#define SHT3X_MEASURE_START_MSB         0x21
#define SHT3X_MEASURE_START_LSB         0x2d

// readout measurements for periodic mode
#define SHT3X_MEASURE_READ_MSB          0xe0
#define SHT3X_MEASURE_READ_LSB          0x00

#define SHT3X_ART_CMD_MSB               0x2b
#define SHT3X_ART_CMD_LSB               0x32

#define SHT3X_BREAK_CMD_MSB             0x30
#define SHT3X_BREAK_CMD_LSB             0x93

#define SHT3X_CLEAR_STATUS_REG_MSB      0x30
#define SHT3X_CLEAR_STATUS_REG_LSB      0x41

#define SHT3X_READ_STATUS_REG_MSB       0xF3
#define SHT3X_READ_STATUS_REG_LSB       0x2D

#define SHT3X_HEATER_ON_MSB             0x30
#define SHT3X_HEATER_ON_LSB             0x6D

#define SHT3X_HEATER_OFF_MSB            0X30
#define SHT3X_HEATER_OFF_LSB            0X66

#define SHT3X_WRITE_LIMIT_MSB           0x61 // write alert limits, high set
#define SHT3X_WRITE_LIMIT_HS_LSB        0x1D // write alert limits, high set
#define SHT3X_WRITE_LIMIT_HC_LSB        0x16 // write alert limits, high clear
#define SHT3X_WRITE_LIMIT_LC_LSB        0x0B // write alert limits, low clear
#define SHT3X_WRITE_LIMIT_LS_LSB        0x00 // write alert limits, low set

// Status-Register
//typedef union {
//  unsigned short u16;
//  struct{
//    unsigned short CrcStatus     : 1; // write data checksum status
//    unsigned short CmdStatus     : 1; // command status
//    unsigned short Reserve0      : 2; // reserved
//    unsigned short ResetDetected : 1; // system reset detected
//    unsigned short Reserve1      : 5; // reserved
//    unsigned short T_Alert       : 1; // temperature tracking alert
//    unsigned short RH_Alert      : 1; // humidity tracking alert
//    unsigned short Reserve2      : 1; // reserved
//    unsigned short HeaterStatus  : 1; // heater status
//    unsigned short Reserve3      : 1; // reserved
//    unsigned short AlertPending  : 1; // alert pending status 
//  } _bit;
//} regStatus;

#ifdef	__cplusplus
extern "C" {
#endif

    bool sht3x_softreset(void);
    bool sht3x_measure_start(void);

    bool sht3x_art_cmd(void);
    bool sht3x_break_cmd(void);

    bool sht3x_clear_status_reg(void);
    bool sht3x_read_status_reg(uint16_t* status);
    bool sht3x_heaterOn(void);
    bool sht3x_heaterOff(void);

    bool sht3x_write_alert_limits(float humidityHighSet,   float temperatureHighSet,
                             float humidityHighClear, float temperatureHighClear,
                             float humidityLowClear,  float temperatureLowClear,
                             float humidityLowSet,    float temperatureLowSet);

    bool sht3x_common_read(int32_t* temp, int32_t* humi);
#if (USE_SHT3X_COMPENSATE)
    bool sht3x_read_compensate(int32_t* temp, int32_t* humi);
    bool sht3x_measure_nonblock_compensate(float* temp, float* humi);
    bool sht3x_measure_block_compensate(float* temp, float* humi);
#else
    bool sht3x_measure_read(float* temp, float* humi);
    bool sht3x_measure_nonblock_read(float* temp, float* humi);
    bool sht3x_measure_block_read(float* temp, float* humi);
#endif // USE_SHT3X_COMPENSATE

#ifdef	__cplusplus
}
#endif

#endif	/* SHT3X_H */

