/* 
 * File:   ads1114.h
 * 
 */

#ifndef ADS1114_H
#define	ADS1114_H

//============================================================================================================================
// The ADS1114 reset on power-up and set all the bits in the Config register 
// to the respective default settings.
//---------------------------------------------------------------------------------------------------------------------------
// power-down state is the default state for the ADS1114 when power is first applied.
// Although powered down, the devices still respond to commands.
//---------------------------------------------------------------------------------------------------------------------------
// The ADS1114 remain in this power-down state until a 1 is written to the operational status (OS) bit in the Config register. 
// When the OS bit is asserted, the device powers up in approximately 25 us, resets the OS bit to 0, 
// and starts a single conversion. When conversion data are ready for retrieval, the device powers down again
//============================================================================================================================

/* Device address */
#ifndef ADS1114_I2C_ADDRESS_CH1
#define ADS1114_I2C_ADDRESS_CH1    0x92 // HIGH
//#define ADS1114_I2C_ADDRESS_CH1     0x49 // HIGH 7bit
#endif
#ifndef ADS1114_I2C_ADDRESS_CH2
#define ADS1114_I2C_ADDRESS_CH2    0x90 // LOW
//#define ADS1114_I2C_ADDRESS_CH2     0x48 // LOW 7bit
#endif

/* Register address */
#define CONVERSION_REG  0x00
#define CONFIG_REG      0x01
#define LO_THRESH_REG   0x10
#define HI_THRESH_REG   0x11

/*  FSR: +-0.256 -> 0.512V   LSB: 7.81uV  */
/*  FSR: +-0.512 -> 1.024V   LSB: 15.62uV */
/*  FSR: +-2.048 -> 4.096V   LSB: 62.5uV  */ 
/*  FSR: +-4.096 -> 8.192V   LSB: 125uV   */
// resolution -> FSR/2^16
// #define ADS1114_LSB   7.81  


/* gain amplifier */
typedef enum {
    FSR_6p144V,
    FSR_4p096V,
    FSR_2p048V, //default
    FSR_1p024V,
    FSR_0p512V,
    FSR_0p256V            
} e_ADC_Gain;

/* Device operating mode */
typedef enum {
    CONTINUE_CONV,
    SINGLE_CONV    //default
} e_ADC_Mode;

/* Data rate */
typedef enum {      //Conversion Time: 1/SPS
    SPS8,           //SPS: Sample Per Second
    SPS16,
    SPS32,
    SPS64,
    SPS128, //default
    SPS250,
    SPS475,
    SPS860            
} e_ADC_DataRate;

//=============================================================================
/* Comparator mode */
typedef enum {
    COMP,   //default
    WIN_COMP
} e_Comparator_Mode;

/* Comparator polarity */
typedef enum {
    LO,   //default
    HI
} e_Comparator_Pol;

/* Latching comparator */
typedef enum {
    NONE_LATCH, //default
    LATCH
} e_Comparator_Latch;

/* Comparator queue and disable */
typedef enum {
    ONE_CONV,
    TWO_CONV,
    FOUR_CONV,
    DISABL   //default, Disable comparator and set ALERT/RDY pin to high-impedance
} e_Comparator_Que;

#ifdef	__cplusplus
extern "C" {
#endif

    bool ads1114_read_ready(uint8_t channel);
    bool ads1114_SetUp(uint8_t channel, uint8_t mode, uint8_t pga, uint8_t dataRate);
    bool ads1114_read(uint8_t channel, int16_t* raw_adc);
    bool ads1114_Comparator_SetUp(uint8_t channel, uint8_t mode, uint8_t pol, uint8_t lat, uint8_t que);

    
#ifdef	__cplusplus
}
#endif

#endif	/* ADS1114_H */
