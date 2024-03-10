/* 
 * File:   board.h
 *
 */

#ifndef BOARD_H
#define	BOARD_H

/* ********************************
*	Application definitions
******************************** */

//#define UA53_CO_1000
//#define UA53_NO2_10 
#define UA53_O3_20

#ifdef UA53_CO_1000             
#define BOARD_NAME              "UA53-CO"
#define ADC_GAIN                FSR_1p024V
#define LMP_GAIN                R350K
#define LMP_RLOAD               R10
#define LMP_TIA_GAIN            350.0f
#define LMP_BIAS                B0P
#define REF_SOURCE              NAGATIVE              
#define WARMUP_DELAY_COUNT      18000
#define KMF_e_measure           60.0f
#define ZERO_RANGE              2.0f

#elif defined UA53_NO2_10
#define BOARD_NAME              "UA53-NO2"
#define ADC_GAIN                FSR_0p256V
#define LMP_GAIN                EXTERNAL_REGISTOR           // R350K 
#define LMP_RLOAD               R10
#define LMP_TIA_GAIN            1000.0f                     // 350.0f 
#define LMP_BIAS                B0P                         // BIAS -25mV    B1P
#define REF_SOURCE              NAGATIVE   
#define WARMUP_DELAY_COUNT      18000                       // 50min  300000
#define KMF_e_measure           50.0f
#define ZERO_RANGE              1.0f

#elif defined UA53_O3_20
#define BOARD_NAME          "UA53-O3"
#define ADC_GAIN            FSR_0p256V
#define LMP_GAIN            R350K
#define LMP_RLOAD           R10
#define LMP_TIA_GAIN        350.0f
#define LMP_BIAS            B0P
#define REF_SOURCE          NAGATIVE 
#define WARMUP_DELAY_COUNT  18000       
#define KMF_e_measure       50.0f
#define ZERO_RANGE          1.0f

#endif

#define LMP_INTZ                S20P

#define VERSION                 "6v1"
#define CHANNEL_COUNT           2

#define MEASURE_DELAY_COUNT     100    // 1sec 
#define ONE_SEC_COUNT           100
#define ONE_HOUR_COUNT          360000            
#define TWO_YEAR_COUNT          17520  


// support bootloader app, start address 0x2000
#define SUPPORT_BOOLTLOADER

#define USE_KALMAN_FILTER
//#define USE_DEBUG_PRINT


enum {
    CELSIUS,
    FAHRENHEIT
};

enum { 
    RAW_MODE, // ATCD Raw
    FIL_MODE  // ATCD
};

enum {
    TEMP_NOT_COMPENSATION,
    TEMP_COMPENSATION
};

enum {
    USB_NONE,
    USB_DETACHED,
    USB_ATTACHED
};

enum {
    OFF,
    ON
};

/* ********************************
*	PIC18(L)F2xJ50 - USB CHIP
*
*	PORT DESCRIPTION
******************************** */
#define _XTAL_FREQ          48000000

// LED
#define LED_RED_LAT         LATBbits.LATB0
#define LED_RED_TRIS        TRISBbits.TRISB0  
#define LED_GREEN_LAT       LATBbits.LATB1
#define LED_GREEN_TRIS      TRISBbits.TRISB1

// I2C1 - 100kHz
#define I2C_SCL_TRIS        TRISBbits.TRISB4
#define I2C_SDA_TRIS        TRISBbits.TRISB5

// USART1
#define UART_TX_TRIS        TRISCbits.TRISC6
#define UART_RX_TRIS        TRISCbits.TRISC7

// lmp91000
#define LMP91000_MENB_LAT   LATBbits.LATB3
#define LMP91000_MENB_TRIS  TRISBbits.TRISB3  

// Internal FLASH
//#define FLASH_BASE_ADDRESS  0x7800 // 30,720
// 0xf000 ~ 0xfe00 [61,440 ~ 65,024]
#define FLASH_BASE_ADDRESS  0xf400 // 62,464 at 61 page for nvm

// bootloader
// Linker Option -> Additional Option -> code offset to 0x2000
#ifdef SUPPORT_BOOLTLOADER
#define APP_SIGNATURE_ADDRESS   0x2006  //0x2006 and 0x2007 contains the "signature" WORD, indicating successful erase/program/verify operation
#define APP_SIGNATURE_VALUE     0x600D  //leet "GOOD", implying that the erase/program was a success and the bootloader intentionally programmed the APP_SIGNATURE_ADDRESS with this value
#endif

/* ********************************
*	ADS1114: ADC
*   LMP91000: OPAMP
******************************** */
#define ADS1114_I2C_ADDRESS     0x92
#define LMP91000_I2C_ADDRESS    0x90

/* ********************************
*   SHT31: SENSIRION TEMP & HUMI SENSOR  
******************************** */
#define USE_SHT3X_COMPENSATE            0

//#define SHT3X_I2C_ADDRESS 	0x44 // 7bit address
#define SHT3X_I2C_ADDRESS 	0x88 // 8bit address


#ifdef	__cplusplus
extern "C" {
#endif

    void write_command(const uint8_t* buff); // output through usb cdc
    uint16_t* get_product_desc();            // get pointer of sd002.string[25]

#ifdef	__cplusplus
}
#endif

#endif	/* BOARD_H */
