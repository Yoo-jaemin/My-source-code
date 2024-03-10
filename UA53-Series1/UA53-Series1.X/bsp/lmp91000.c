#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "../board.h"

#include "i2c.h"

#include "lmp91000.h"


bool lmp91000_get_status(uint8_t* preg)
{
    uint8_t wBuff = LMP91000_STATUS_REG;
    uint8_t rBuff;
    
    if (i2c_writeBytes(LMP91000_I2C_ADDRESS, &wBuff, 1, false) == false) {
        return false;
    }

    if (i2c_readBytes(LMP91000_I2C_ADDRESS, &rBuff, 1) == false) {
        return false;
    }

    *preg = rBuff;

    return true;
}

bool lmp91000_get_lock(uint8_t* preg)
{
    uint8_t wBuff = LMP91000_LOCK_REG;
    uint8_t rBuff;
    
    if (i2c_writeBytes(LMP91000_I2C_ADDRESS, &wBuff, 1, false) == false) {
        return false;
    }

    if (i2c_readBytes(LMP91000_I2C_ADDRESS, &rBuff, 1) == false) {
        return false;
    }

    *preg = rBuff;

    return true; 
}

bool lmp91000_get_Tiacn(uint8_t* preg)
{
    uint8_t wBuff = LMP91000_TIACN_REG;
    uint8_t rBuff;
    
    if (i2c_writeBytes(LMP91000_I2C_ADDRESS, &wBuff, 1, false) == false) {
        return false;
    }

    if (i2c_readBytes(LMP91000_I2C_ADDRESS, &rBuff, 1) == false) {
        return false;
    }

    *preg = rBuff;

    return true; 
}

bool lmp91000_get_Refcn(uint8_t* preg)
{
    uint8_t wBuff = LMP91000_REFCN_REG;
    uint8_t rBuff;
    
    if (i2c_writeBytes(LMP91000_I2C_ADDRESS, &wBuff, 1, false) == false) {
        return false;
    }

    if (i2c_readBytes(LMP91000_I2C_ADDRESS, &rBuff, 1) == false) {
        return false;
    }

    *preg = rBuff;

    return true; 
}

bool lmp91000_get_Modecn(uint8_t* preg)
{
    uint8_t wBuff = LMP91000_MODECN_REG;
    uint8_t rBuff;
    
    if (i2c_writeBytes(LMP91000_I2C_ADDRESS, &wBuff, 1, false) == false) {
        return false;
    }

    if (i2c_readBytes(LMP91000_I2C_ADDRESS, &rBuff, 1) == false) {
        return false;
    }

    *preg = rBuff;

    return true; 
}

//=======================================================================================
// enables and disables the writing of the TIACN and the REFCN registers. 
//---------------------------------------------------------------------------------------
// return  true  :   reading mode set (default)
//         false :   error
//---------------------------------------------------------------------------------------
bool lmp91000_lock(void)
{
    uint8_t buff[2];
    buff[0] = LMP91000_LOCK_REG;
    buff[1] = 0x01;

    return i2c_writeBytes(LMP91000_I2C_ADDRESS, buff, 2, true);
}

//=======================================================================================
// enables and disables the writing of the TIACN and the REFCN registers. 
//---------------------------------------------------------------------------------------
// return  true  :   writing mode set
//         false :   error
//---------------------------------------------------------------------------------------
bool lmp91000_unlock(void)
{
    uint8_t buff[2];
    buff[0] = LMP91000_LOCK_REG;
    buff[1] = 0x00;

    return i2c_writeBytes(LMP91000_I2C_ADDRESS, buff, 2, true);
}


//=======================================================================================
// whether or not the device is writing mode
//---------------------------------------------------------------------------------------
// return  true  :   writing mode 
//         false :   reading mode(default) or error 
//---------------------------------------------------------------------------------------
bool lmp91000_isUnLocked(void)
{
    uint8_t rBuff;
    
    if (lmp91000_get_lock(&rBuff) == false)
        return false;
    
    return !(rBuff & 0x01);
}

//=======================================================================================
// whether or not the device is ready
//---------------------------------------------------------------------------------------
// return  true  :   ready 
//         false :   not ready(default)
//---------------------------------------------------------------------------------------
bool lmp91000_isReady(void)
{
    uint8_t rBuff;
    
    if (lmp91000_get_status(&rBuff) == false)
        return false;
    
    return (rBuff & 0x01);
}

//=======================================================================================
// Sets the transimpedance amplifier gain and load registor
//---------------------------------------------------------------------------------------
// param   user gain, load registor
// return  true  :   gain set 
//         false :   error
//---------------------------------------------------------------------------------------
bool lmp91000_set_GainRLoad(uint8_t user_gain, uint8_t RLoad)
{
    uint8_t reg;
    uint8_t buff[2];

    reg = 0x03;                 // default 000:11 (external:100ohm)
    reg &= ~3;                  //clears bits 0-1
    reg |= (user_gain << 2);    //writes to bits 2-4
    reg |= RLoad;

    buff[0] = LMP91000_TIACN_REG;
    buff[1] = reg;

    return i2c_writeBytes(LMP91000_I2C_ADDRESS, buff, 2, true);
}

//=======================================================================================
// Sets the voltage reference source of the LMP91000 to an internal reference or an external reference.
//---------------------------------------------------------------------------------------
// param   internal(default) or external reference
// return  true  :   reference voltage set
//         false :   error
//--------------------------------------------------------------------------------------
bool lmp91000_set_Reference(uint8_t source, uint8_t IntZ, uint8_t sign, uint8_t bias)
{
    uint8_t reg;
    uint8_t buff[2];
  
    reg = 0x20;         // default 0:01:0:0000 (Internal:50%:Negative:0%)
    reg &= ~(3 << 5);   //clears bits 5-6
    reg |= source << 7; //writes to bits 7
    reg |= IntZ << 5;   //writes to bits 5-6
    reg |= sign << 4;   //writes to bits 4
    reg |= bias;        //writes to bits 0-3

    buff[0] = LMP91000_REFCN_REG;
    buff[1] = reg;

    return i2c_writeBytes(LMP91000_I2C_ADDRESS, buff, 2, true);
}

//=======================================================================================
// Shorting FET feature, Mode of Operation selection
//---------------------------------------------------------------------------------------
// param   FET enable or disable
// return  true  :  FET enable
//         false :  error
//--------------------------------------------------------------------------------------
bool lmp91000_set_Mode(uint8_t fet, uint8_t mode)
{
    uint8_t reg;
    uint8_t buff[2];
  
    reg = 0x00;         // default 0:000:000 (DiableFET:000:DeepSleep)
    reg |= fet << 7;    //writes to bits 7
    reg |= mode;        //writes to bits 0-2

    buff[0] = LMP91000_MODECN_REG;
    buff[1] = reg;

    return i2c_writeBytes(LMP91000_I2C_ADDRESS, buff, 2, true);
}
