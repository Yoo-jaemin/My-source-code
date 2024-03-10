
#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#include "../board.h"

#include "power.h"

void POWER_Init(void)
{
    DC_POWER_TRIS = 1; // DC 5V~30V input check
	USB_POWER_TRIS = 1; // USB input check
    I2C_ACCESS_TRIS = 1; // CC3200 Access input check
    I2C_BUS_TRIS = 1; // DCDC_3V3_OUT - I2C Bus input check
}

POWER_SOURCE POWER_SourceGet(void)
{
    POWER_SOURCE src;
	//pin DC_CHK & USB_CHK
	if (DC_POWER_PORT && USB_POWER_PORT)
        src = POWER_SOURCE_ALL;
    else if (DC_POWER_PORT)
        src = POWER_SOURCE_MAINS;
    else if (USB_POWER_PORT)
        src = POWER_SOURCE_USB;
    else
        src = POWER_SOURCE_NONE;
    return src;
}

void ACCESS_SourceSet(bool set)
{
    if (set) {
        I2C_ACCESS_TRIS = 0; // CC3200 Access pin set output
        __delay_us(50);
        I2C_ACCESS_LAT = 1; // set high
        __delay_ms(10);
    } else {
        I2C_ACCESS_TRIS = 0; // CC3200 Access pin set output
        __delay_us(50);
        I2C_ACCESS_LAT = 0; // set low
        I2C_ACCESS_TRIS = 1; // CC3200 Access input check
        __delay_us(50);
    }
}

bool ACCESS_SourceGet(void)
{
    if (I2C_ACCESS_PORT)
        return true;
    return false;
}

bool I2C_Bus_SourceGet(void)
{
    if (I2C_BUS_PORT)
        return true;
    return false;
}
