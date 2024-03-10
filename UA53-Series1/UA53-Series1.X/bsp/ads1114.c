#include <stdint.h>
#include <stdbool.h>

#include "../board.h"

#include "i2c.h"

#include "ads1114.h"

//============================================================
// When reading :
// return   false : Device is currently performing a conversion  or error     
//          true : Device is not currently performing a conversion
//------------------------------------------------------------
bool ads1114_read_ready(void)
{
    uint8_t wbuff = CONFIG_REG;
    uint8_t rbuff[2];
    
    if (i2c_writeBytes(ADS1114_I2C_ADDRESS, &wbuff, 1, true) == false)
        return false;
    
    if (i2c_readBytes(ADS1114_I2C_ADDRESS, rbuff, 2) == false)
        return false;
    
    if (rbuff[0] & 0x80)
        return false;

    return true;
}

bool ads1114_SetUp(uint8_t mode, uint8_t pga, uint8_t dataRate)
{
    uint8_t wraddr = CONFIG_REG;
    uint8_t buff[2];
    
    buff[0] = 0x00 | (pga << 1) | mode; // no effect, MUX 00, pga, mode
    buff[1] = dataRate << 5 | 0b00010011; // DR, COMP_MODE window, POL 0, LAT 0, high-impedence
    
    return i2c_writeBytes_to(ADS1114_I2C_ADDRESS, &wraddr, 1, buff, 2);
}

bool ads1114_read(int16_t* raw_adc)
{
    uint8_t wbuff = CONVERSION_REG;
    uint8_t rbuff[2];

    if (i2c_writeBytes(ADS1114_I2C_ADDRESS, &wbuff, 1, true) == false)
        return false;

    if (i2c_readBytes(ADS1114_I2C_ADDRESS, rbuff, 2) == false)
        return false;

    *raw_adc = ((uint16_t)rbuff[0] << 8) | rbuff[1];
    return true;
}

bool ads1114_Comparator_SetUp(uint8_t mode, uint8_t polar,
                                uint8_t latch, uint8_t que)
{
    uint8_t wbuff = CONFIG_REG;
    uint8_t rbuff[2];

    if(!i2c_writeBytes(ADS1114_I2C_ADDRESS, &wbuff, 1, true))
        return false;

    if(!i2c_readBytes(ADS1114_I2C_ADDRESS, rbuff, 2))
        return false;
    //---------------------------------------------------------
    // Comparator_SetUp
    rbuff[1] |= (mode << 4) | (polar << 3) | (latch << 2) | que;

    return i2c_writeBytes_to(ADS1114_I2C_ADDRESS, &wbuff, 1, rbuff, 2);
}
