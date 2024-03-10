
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "../board.h"

#include "i2c.h"
#include "power.h"
#include "max7323.h"

static uint8_t max7323_address[2] = { MAX7323_I2C_ADDRESS_CH1, MAX7323_I2C_ADDRESS_CH2 };

bool max7323_set_gpio(uint8_t chno, uint8_t wb)
{
    uint8_t b = wb;

    if (i2c_writeBytes(max7323_address[chno], &b, 1, true) == false)
        return false;
    
    return true;
}

bool max7323_get_gpio(uint8_t chno, uint8_t *rb)
{
    uint8_t b;

    if (i2c_readBytes(max7323_address[chno], &b, 1) == false)
        return false;

    *rb = b;

    return true;
}