/* 
 * File:   board.h
 * Author: karl
 *
 */

#ifndef BOARD_H
#define	BOARD_H

/* ********************************
*	Application definitions
*
*	RN400T2-TS
******************************** */
#define BOARD_NAME                  "RN400T2-GS"
#define VERSION                     "5v8"
#define CHANNEL_COUNT               2

#define MEASURE_DELAY_COUNT         500 // 5sec for timer interrupt
//#define MEASURE_DELAY_COUNT         3000 // 30sec for timer interrupt
#define SENSOR_INIT_DELAY_COUNT     6000 // 1min for timer interrupt
#define ONE_MINUTE_COUNT            60 // 1min for timer interrupt
#define WARMUP_COUNT                18000 // 3min warm up
#define ONE_HOUR_COUNT              360000 // 1hour for timer interrupt
#define RLY_STATUS_COUNT            1000 // 10sec
#define MASTER_DELAY_COUNT			100 // 1sec for timer interrupt

#define NVM_INIT_RETRY_COUNT        5

#define NO_VALUE                    -999995.0f

// support bootloader app, start address 0x2000
#define SUPPORT_BOOLTLOADER

// for debug print
//#define USE_DEBUG_PRINT

// for 1min eeprom check
//#define USE_CHECK_CHANNEL_PERIODIC

#ifdef USE_DEBUG_PRINT
#undef ONE_MINUTE_COUNT
#define ONE_MINUTE_COUNT            10 // 10sec test
#undef WARMUP_COUNT
#define WARMUP_COUNT                1 // 1sec test
#undef RLY_STATUS_COUNT
#define RLY_STATUS_COUNT            300 // 3sec test
#endif

// sensing & 485 on/off : on:1, off:0
enum {
    SENSING_OFF,
    SENSING_ON
};

// use average mode for ppm
#define USE_PPM_WINDOW
// use kalman filter for adc output(mV)
#define USE_KALMAN_FILTER

// for rs485 uart interrupt mode
#define USE_UART_INTERRUPT

// for modbus
#define MODBUS_RELAY_START_ADDRESS  600 // 600 or 0x0258, ML-RH8 relay register start address 600 ~ 607
#define MODBUS_RELAY_RETRY_COUNT    3

#define MODUBS_SLAVE_FRAME_SIZE     8 // holding register request frame size is 8
#define MODBUS_DEFAULT_SLAVE_ID     54
#define MODBUS_DEFAULT_BAUDRATE     5 //57600
#define MODBUS_DEFAULT_TIMEOUT      0 //100 // 1sec

enum {
    CELSIUS,
    FAHRENHEIT
};

enum { 
    RAW_MODE,
    FIL_MODE
};

enum {
    TEMP_NOT_COMPENSATION,
    TEMP_COMPENSATION
};

enum {
    NONE,
    NH3_100,
    H2S_50,
    EO,
    NH3_1000
};

enum {
    MODBUS_SLAVE_MODE,
    MODBUS_MASTER_MODE
};

/* ********************************
*	PIC18(L)F2xJ50 - USB CHIP
*
*	PORT DESCRIPTION
******************************** */
#define _XTAL_FREQ          48000000

/* *** GPIO ******************** */

// USB POWER CHECK
#define USB_POWER_TRIS      TRISAbits.TRISA0
#define USB_POWER_LAT       LATAbits.LATA0
#define USB_POWER_PORT      PORTAbits.RA0

// DC POWER CHECK
#define DC_POWER_TRIS       TRISAbits.TRISA1
#define DC_POWER_LAT        LATAbits.LATA1
#define DC_POWER_PORT       PORTAbits.RA1

// DCDC_3V3_OUT - I2C Bus check
#define I2C_BUS_TRIS        TRISAbits.TRISA2
#define I2C_BUS_LAT         LATAbits.LATA2
#define I2C_BUS_PORT        PORTAbits.RA2

// I2C dual master (CC3200) check pin
#define I2C_ACCESS_TRIS     TRISAbits.TRISA3
#define I2C_ACCESS_LAT      LATAbits.LATA3
#define I2C_ACCESS_PORT     PORTAbits.RA3

// LED
//#define LED_RED_TRIS        TRISBbits.TRISB0
//#define LED_RED_LAT         LATBbits.LATB0
//#define LED_GREEN_TRIS      TRISBbits.TRISB1
//#define LED_GREEN_LAT       LATBbits.LATB1

// I2C1 - 100kHz
#define I2C_SCL_TRIS        TRISBbits.TRISB4
#define I2C_SDA_TRIS        TRISBbits.TRISB5

// USART1
#define UART_TX_TRIS        TRISCbits.TRISC6
#define UART_RX_TRIS        TRISCbits.TRISC7

// Internal FLASH
/*
  1byte   1byte    1byte     1byte      4byte      1  1  1  1  1  1  1  1byte
.-------.-------.----------.---------.------------.--.--.--.--.--.--.--.--.
| SWAP  | SLV ID| BAUDRATE | TIMEOUT | BUILD TIME |S |E |R |I |A |L |N |O |
'-------'-------.----------.---------.------------.--.--.--.--.--.--.--.--.
 * size is 16 bytes.
 */
#define FLASH_BASE_ADDRESS  0xf400 // 62,464 at 61 page

// bootloader
// Linker Option -> Additional Option -> code offset to 0x2000
#ifdef SUPPORT_BOOLTLOADER
#define APP_SIGNATURE_ADDRESS   0x2006  //0x2006 and 0x2007 contains the "signature" WORD, indicating successful erase/program/verify operation
#define APP_SIGNATURE_VALUE     0x600D  //leet "GOOD", implying that the erase/program was a success and the bootloader intentionally programmed the APP_SIGNATURE_ADDRESS with this value
#endif

/* ********************************
*	PartNumber : AZRS3188L
*   
*   A and B TVS : IEC61000-4-2 15kV
*	RS485 Transceiver
******************************** */
#define RS485_REB_TRIS      TRISBbits.TRISB0
#define RS485_DE_TRIS       TRISBbits.TRISB1
#define RS485_REB_LAT       LATBbits.LATB0
#define RS485_REB_PORT      PORTBbits.RB0
#define RS485_DE_LAT        LATBbits.LATB1


/* ********************************
*	PartNumber : 24AA02/24LC02B
*
*	2Kbit Memory = 256Byte
******************************** */
#define EEPROM_I2C_ADDRESS_CH1      0xA2
#define EEPROM_I2C_ADDRESS_CH2      0xA0
//#define EEPROM_I2C_ADDRESS_CH1      0x51 // 7bit address
//#define EEPROM_I2C_ADDRESS_CH2      0x50 // 7bit address

#define EEPROM_TOTAL_SIZE           256
#define EEPROM_PAGE_SIZE            8
#define EEPROM_ACK_POLLING_COUNT    10
#define EEPROM_BASE_ADDRESS         0x00

/* ********************************
*	PartNumber : LMP91000/14WSON
*
*
******************************** */
#define LMP91000_I2C_ADDRESS        0x90
//#define LMP91000_I2C_ADDRESS        0x48 // 7bit address

/* ********************************
*	PartNumber : ADS1114/10X2QFN
*
*
******************************** */
#define ADS1114_I2C_ADDRESS_CH1     0x92 // HIGH
#define ADS1114_I2C_ADDRESS_CH2     0x90 // LOW
//#define ADS1114_I2C_ADDRESS_CH1     0x49 // HIGH 7bit
//#define ADS1114_I2C_ADDRESS_CH2     0x48 // LOW 7bit

/* ********************************
*	PartNumber : MAX7323/16TQFN
*
*
******************************** */
#define MAX7323_I2C_ADDRESS_CH1     0xDA
#define MAX7323_I2C_ADDRESS_CH2     0xD8
//#define MAX7323_I2C_ADDRESS_CH1     0x6D // 7bit address
//#define MAX7323_I2C_ADDRESS_CH2     0x6C // 7bit address

#ifdef	__cplusplus
extern "C" {
#endif

    void write_command(const uint8_t* buff); // output through usb cdc
    uint16_t* get_product_desc(); // get pointer of sd002.string[25]

#ifdef	__cplusplus
}
#endif

#endif	/* BOARD_H */
