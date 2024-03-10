/* 
 * File:   lmp91000.h
 * 
 */

#ifndef LMP91000_H
#define	LMP91000_H

/* Device address */
#ifndef LMP91000_I2C_ADDRESS
#define LMP91000_I2C_ADDRESS    0x90
//#define LMP91000_I2C_ADDRESS        0x48 // 7bit address
#endif

/* Register address */
#define LMP91000_STATUS_REG     0x00    // Read only status register 
#define LMP91000_LOCK_REG       0x01    // Protection Register 
#define LMP91000_TIACN_REG      0x10;   // TIA Control Register 
#define LMP91000_REFCN_REG      0x11;   // Reference Control Register 
#define LMP91000_MODECN_REG     0x12;   // Mode Control Register 



/* transimpedance gain */
typedef enum {
    EXTERNAL_REGISTOR, //default
    R2p75K,
    R3p5K,
    R7K,
    R14K,
    R35K,
    R120K,
    R350K
} e_TIA_InternalGain;

/* low pass filter */
typedef enum {
    R10,
    R33,
    R50,
    R100  //default
} e_TIA_RLoad;

/* Reference voltage source selection */
typedef enum {
   INTERNAL,  //default
   EXTERNAL        
} e_Ref_Voltage;

/* internal zero selection(Percentage of the source reference) */
typedef enum {
    S20P,  //20%
    S50P,  //50%   default
    S67P,  //67%
    BYPASS 
} e_InZ_sel;

/* Selection of the Bias polarity */
typedef enum {
    NAGATIVE, //default
    POSITIVE
} e_Bias_sign;

/* BIAS selection (Percentage of the source reference) */
typedef enum {
    B0P, // 0%  default
    B1P,
    B2P,
    B4P,
    B6P,
    B8P,
    B10P,
    B12P,
    B14P,
    B16P,
    B18P,
    B20P,
    B22P,
    B24P            
} e_Bias_sel;

/* Shorting FET */
typedef enum {
    DISABLE, //default
    ENABLE
} e_FET;

/* Mode of Operation selection */
typedef enum {
    SLEEP, //default
    GALVANIC_2LEAD,
    STANBY,
    AMPEROETRIC_3LEAD,
    TEMP_MEASURE_TIAOFF = 6,
    TEMP_MEASURE_TIAON = 7    //VOUT Pin     
} e_OP_Mode;



#ifdef	__cplusplus
extern "C" {
#endif

    bool lmp91000_lock(void);
    bool lmp91000_unlock(void);
    bool lmp91000_isUnLocked(void);
    bool lmp91000_isReady(void);

    bool lmp91000_get_status(uint8_t* preg);
    bool lmp91000_get_lock(uint8_t* preg);
    bool lmp91000_get_Tiacn(uint8_t* preg);
    bool lmp91000_get_Refcn(uint8_t* preg);
    bool lmp91000_get_Modecn(uint8_t* preg);

    bool lmp91000_set_GainRLoad(uint8_t user_gain, uint8_t RLoad);
    bool lmp91000_set_Reference(uint8_t source, uint8_t IntZ, uint8_t sign, uint8_t bias);
    bool lmp91000_set_Mode(uint8_t fet, uint8_t mode);
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* LMP91000_H */

