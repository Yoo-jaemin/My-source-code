
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "../board.h"

#include "usart.h"
#include "rs485.h"

#define RS485_RX_MODE()     RS485_DE_LAT = 0;RS485_REB_LAT = 0
#define RS485_TX_MODE()     RS485_DE_LAT = 1;RS485_REB_LAT = 1

void rs485_init(uint32_t baudrate)
{
    RS485_REB_TRIS = 0;           // REB output
    RS485_DE_TRIS = 0;            // DE output

    usart_init(baudrate);

    RS485_RX_MODE();
}

bool rs485_is_writing(void)
{
    if (RS485_REB_PORT)
        return true;
    return false;
}

void rs485_writeBytes(const uint8_t* wrptr, const uint8_t len)
{
    RS485_TX_MODE();
    __delay_ms(2);
    usart_writeBytes(wrptr, len);
    __delay_ms(2);
    RS485_RX_MODE();
}

bool rs485_readByte(uint8_t* byte)
{
    if (usart_rx_ready()) {
        *byte = usart_getc();
        return true;
    }
    return false;
}

