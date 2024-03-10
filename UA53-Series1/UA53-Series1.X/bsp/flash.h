/* 
 * File:   flash.h
 * Author: karl
 *
 */

#ifndef FLASH_H
#define	FLASH_H

typedef union
{
    unsigned long Val;
    __pack unsigned short int w[2];
    __pack unsigned char v[4];
    __pack struct
    {
        unsigned short int LW;
        unsigned short int HW;
    } word;
    __pack struct
    {
        unsigned char LB;
        unsigned char HB;
        unsigned char UB;
        unsigned char MB;
    } byte;
} DWORD_VAL;

#define FLASH_WRITE_BLOCK 	64
#define FLASH_ERASE_BLOCK 	1024

#ifdef	__cplusplus
extern "C" {
#endif

    void flash_readBytes(uint32_t startaddr, uint8_t *flash_array, uint16_t num_bytes);
    bool flash_writeBytes(uint32_t startaddr, uint8_t *flash_array, uint16_t num_bytes);
    void flash_clear(uint32_t startaddr, uint32_t endaddr);

#ifdef	__cplusplus
}
#endif

#endif	/* FLASH_H */

