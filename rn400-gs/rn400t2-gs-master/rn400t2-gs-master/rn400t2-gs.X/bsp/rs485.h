
#ifndef _RS485_H
#define	_RS485_H

#ifdef	__cplusplus
extern "C" {
#endif

    void rs485_init(uint32_t baudrate);
    bool rs485_is_writing(void);
    void rs485_writeBytes(const uint8_t* wrptr, const uint8_t len);
    bool rs485_readByte(uint8_t* byte);

#ifdef	__cplusplus
}
#endif

#endif	/* _RS485_H */

