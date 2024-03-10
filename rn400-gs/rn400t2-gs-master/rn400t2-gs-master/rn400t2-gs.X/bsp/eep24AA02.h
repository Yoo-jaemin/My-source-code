/* 
 * File:   eeprom.h
 *
 */

#ifndef _EEP24AA02_H
#define	_EEP24AA02_H

/* ********************************
*	PartNumber : 24AA02/24LC02B
*
*	2Kbit Memory = 256Byte
******************************** */
#ifndef EEPROM_I2C_ADDRESS_CH1
#define EEPROM_I2C_ADDRESS_CH1      0xA2
//#define EEPROM_I2C_ADDRESS_CH1      0x51 // 7bit address
#endif
#ifndef EEPROM_I2C_ADDRESS_CH2
#define EEPROM_I2C_ADDRESS_CH2      0xA0
//#define EEPROM_I2C_ADDRESS_CH2      0x50 // 7bit address
#endif

#ifndef EEPROM_TOTAL_SIZE
#define EEPROM_TOTAL_SIZE           256
#endif
#ifndef EEPROM_PAGE_SIZE
#define EEPROM_PAGE_SIZE            8
#endif
#ifndef EEPROM_ACK_POLLING_COUNT
#define EEPROM_ACK_POLLING_COUNT    10
#endif
#ifndef EEPROM_BASE_ADDRESS
#define EEPROM_BASE_ADDRESS         0x00
#endif

#ifdef	__cplusplus
extern "C" {
#endif
    bool eeprom_writePage(const uint8_t channel, const uint8_t mem_addr, const uint8_t* wrptr, const uint8_t len);
    bool eeprom_RandomRead(const uint8_t channel, const uint8_t mem_addr, uint8_t* rdptr, const uint8_t len);
    bool eeprom_SequenceRead(const uint8_t channel, uint8_t* rdptr, const uint8_t len);
#ifdef	__cplusplus
}
#endif

#endif	/* _EEP24AA02_H */
