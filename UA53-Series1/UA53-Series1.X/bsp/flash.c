
#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#include "flash.h"

void flash_readBytes(uint32_t startaddr, uint8_t *flash_array, uint16_t num_bytes)
{
    DWORD_VAL flash_addr;
    DWORD_VAL tblptr_save;

    flash_addr.Val = startaddr;
    // save the current tblptr
    tblptr_save.byte.UB = TBLPTRU;
    tblptr_save.byte.HB = TBLPTRH;
    tblptr_save.byte.LB = TBLPTRL;

    TBLPTRU = flash_addr.byte.UB; //Load the address to Address pointer registers
    TBLPTRH = flash_addr.byte.HB;	
    TBLPTRL	= flash_addr.byte.LB;

    while(num_bytes--)
    {
        //*********** Table read sequence ******************************
        asm("TBLRDPOSTINC");
        *flash_array++ = TABLAT;
    }	
    // restore the tblptr
    TBLPTRU = tblptr_save.byte.UB;
    TBLPTRH = tblptr_save.byte.HB;	
    TBLPTRL	= tblptr_save.byte.LB;
}

bool flash_writeBytes(uint32_t startaddr, uint8_t *flash_array, uint16_t num_bytes)
{
    bool retval = true;
    unsigned char write_byte=0,flag=0;
    DWORD_VAL flash_addr;

    flash_addr.Val = startaddr;

    startaddr /= FLASH_WRITE_BLOCK ;	//Allign the starting address block
    startaddr *= FLASH_WRITE_BLOCK ;
    startaddr += FLASH_WRITE_BLOCK ;

    write_byte = startaddr - flash_addr.Val;

    while(num_bytes)
    {
        TBLPTRU = flash_addr.byte.UB;	//Load the address to Address pointer registers
        TBLPTRH = flash_addr.byte.HB;	
        TBLPTRL	= flash_addr.byte.LB;

        while(write_byte--)
        {
            TABLAT = *flash_array++;
            asm("TBLWTPOSTINC");
            if(--num_bytes==0)	break;
        }

        TBLPTRU = flash_addr.byte.UB;	//Load the address to Address pointer registers
        TBLPTRH = flash_addr.byte.HB;	
        TBLPTRL	= flash_addr.byte.LB;
        //*********** Flash write sequence ***********************************
        EECON1bits.WREN = 1;
        if(INTCONbits.GIE)
        {
            INTCONbits.GIE = 0;
            flag=1;
        }		  
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR =1;
        EECON1bits.WREN = 0 ; 
        if(flag)
        {
            INTCONbits.GIE = 1;	
            flag=0;
		}
        write_byte = FLASH_WRITE_BLOCK;
        flash_addr.Val = flash_addr.Val + FLASH_WRITE_BLOCK;	//increment to one block of 64 bytes

        if (EECON1bits.WRERR == 1)
            retval = false;
    }
    return retval;
}

void flash_clear(uint32_t startaddr, uint32_t endaddr)
{
    unsigned char flag=0;
    DWORD_VAL flash_addr;

    flash_addr.Val = startaddr;

    while(flash_addr.Val<endaddr)
    {
        TBLPTRU = flash_addr.byte.UB;						//Load the address to Address pointer registers
        TBLPTRH = flash_addr.byte.HB;	
        TBLPTRL	= flash_addr.byte.LB;
        //*********Flash Erase sequence*****************
        EECON1bits.WREN = 1;
        EECON1bits.FREE = 1;
        if(INTCONbits.GIE)
        {
            INTCONbits.GIE = 0;
            flag=1;
        }
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR = 1;
        if(flag)
            INTCONbits.GIE = 1;

        flash_addr.Val = flash_addr.Val + FLASH_ERASE_BLOCK;
    }
}
