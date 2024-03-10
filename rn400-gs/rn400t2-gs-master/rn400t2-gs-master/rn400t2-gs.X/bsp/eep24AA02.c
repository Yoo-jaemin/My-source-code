
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "../board.h"

#include "i2c.h"
#include "power.h"
#include "eep24AA02.h"

static uint8_t eeprom_address[2] = { EEPROM_I2C_ADDRESS_CH1, EEPROM_I2C_ADDRESS_CH2 };

bool eeprom_writePage(const uint8_t channel, const uint8_t mem_addr, const uint8_t* wrptr, const uint8_t len)
{
    if (len > EEPROM_PAGE_SIZE) return false;
    unsigned cnt = EEPROM_ACK_POLLING_COUNT;
    while (cnt--) {
        if (i2c_writeBytes_to(eeprom_address[channel], &mem_addr, 1, wrptr, len))
            return true;
        __delay_ms(10);
    }
    return false;
}

bool eeprom_RandomRead(const uint8_t channel, const uint8_t mem_addr, uint8_t* rdptr, const uint8_t len)
{
    return i2c_readBytes_from(eeprom_address[channel], &mem_addr, 1, rdptr, len);
}

bool eeprom_SequenceRead(const uint8_t channel, uint8_t* rdptr, const uint8_t len)
{
    return i2c_readBytes(eeprom_address[channel], rdptr, len);
}
