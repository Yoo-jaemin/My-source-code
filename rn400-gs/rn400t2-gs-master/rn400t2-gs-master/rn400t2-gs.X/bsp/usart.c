
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "../board.h"

#include "usart.h"

void usart_init(uint32_t baudrate)
{
    UART_TX_TRIS = 0;			// TX output
    UART_RX_TRIS = 1;           // RX input

    TXSTA1 = 0b10100010;       	// TX enable BRGH=0 - async mode, low speed
    RCSTA1 = 0b10010000;       	// Single Character RX
    BAUDCON1 = 0b00000000;     	// BRG16 = 0

#ifdef USE_UART_INTERRUPT
    RCONbits.IPEN = 1;          //enable Interrupt priority levels	
	IPR1bits.RC1IP= 0;          // EUSART Receive Interrupt Priority 0 = Low priority
    PIE1bits.RC1IE= 1;          // 1 = Enables the EUSART receive interrupt
#endif

    uint32_t b = (CLOCK_FREQ / (64 * baudrate)) - 1;
    SPBRG1 = b;
}

bool usart_tx_empty(void)
{
    if (TXSTA1bits.TRMT)
        return true;
    return false;
}

void usart_putc(uint8_t c)
{
    while (!usart_tx_empty())
        ;
    TXREG = c;
}

bool usart_rx_ready(void)
{
    if (PIR1bits.RC1IF)
        return true;
    return false;
}

uint8_t usart_getc(void)
{
    uint8_t c = 0;

    if(RCSTA1bits.OERR == 1)
    {
        RCSTA1bits.CREN = 0;    // continuous receive enable
        c = RCREG1;             // read new data into variable
        RCSTA1bits.CREN = 1;
    }
    else
    {
        c = RCREG1;
    }
    return c;
}

void usart_writeBytes(const uint8_t* wrptr, const uint8_t len)
{
    for (uint8_t i = 0 ; i < len ; i++) {
        usart_putc(wrptr[i]);
    }
}

bool usart_readByte(uint8_t* byte)
{
    if (usart_rx_ready()) {
        *byte = usart_getc();
        return true;
    }
    return false;
}
