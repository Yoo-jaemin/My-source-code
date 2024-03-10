/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************/

#ifndef USART_H
#define USART_H

#define CLOCK_FREQ _XTAL_FREQ

#ifdef	__cplusplus
extern "C" {
#endif

    void usart_init(uint32_t baudrate);
    bool usart_tx_empty(void);
    void usart_putc(uint8_t);
    bool usart_rx_ready(void);
    uint8_t usart_getc(void);

    void usart_writeBytes(const uint8_t* wrptr, const uint8_t len);
    bool usart_readByte(uint8_t* byte);
    bool usart_readChar(char* ch);

    #ifndef USE_UART_INTERRUPT
    void uart_getBuffer(void);
    #endif
#ifdef	__cplusplus
}
#endif

#endif //USART_H
