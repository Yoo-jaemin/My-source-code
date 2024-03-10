/*
 * File:   main.c
 * Author: karl
 *
*/

/** INCLUDES *******************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "system.h"
#include "usb/usb.h"
#include "usb/usb_device.h"
#include "usb/usb_device_cdc.h"

#include "board.h"

#include "util/buffer.h"

#include "bsp/i2c.h"
#include "bsp/usart.h"
#include "bsp/rs485.h"
#include "bsp/power.h"
#include "bsp/max7323.h"

#include "nvm.h"
#include "app_usb_cdc.h"
#include "app_sens_measure.h"
#include "app_modbus.h"
#include "app_atcommand.h"

// usb buffer
s_Queue g_usb_queue;

// rs485 modbus buffer
s_Queue g_modbus_queue;

// nvm data
s_Nvm g_nvm;
u_Eeprom_Nvm g_eeprmTemp[CHANNEL_COUNT];

// state machine
s_AtCommand g_atcommand;
s_Sens_Measure g_sens_measure;
s_Modbus g_modbus;

volatile uint32_t g_usedtime_count;

// bootloader
#ifdef SUPPORT_BOOLTLOADER
// Linker Option -> Additional Option -> code offset to 0x2000
const unsigned int FlashSignatureWord __at(APP_SIGNATURE_ADDRESS) = APP_SIGNATURE_VALUE;
#endif

static void WDT_initialize(void)
{
    WDTCONbits.SWDTEN = 1;      /* enable software controlled watchdog timer*/
//    if(!RCONbits.TO)            /* check for WDT reset occurrence */
//        LCD_String_xy(1,0,"WDT Reset");
}

static void Board_initialize(void)
{
    ANCON0 = 0xFF;  // Default all pins to digital
    ANCON1 = 0xFF;  // Default all pins to digital
    POWER_Init(); // gpio pin setting

    // state initialize
    g_atcommand.seq = AT_INIT;
    g_sens_measure.seq = SENS_INIT;
    g_modbus.seq = MODBUS_INIT;

    i2c_init(I2C_100kHz); // I2C set Master & 100kHz mode

    buffer_init(&g_usb_queue); // usb queue buffer initialize
    buffer_init(&g_modbus_queue); // modbus queue buffer initialize

    // check serialno after read nvm
    nvm_init();
    // initialize sensor app
    sensMeasure_init();
    // initialize atcommand app
    atcommand_init();
    // initialize modbus app
    modbus_init();
}

static void InitTimer(void)
{
	/* 48MHz / 4  */
	T0CONbits.T08BIT = 1;	// Timer0 8-Bit/16-Bit Control bit (1 = Timer0 is configured as an 8-bit timer/counter, 0 = Timer0 is configured as a 16-bit timer/counter)
	T0CONbits.T0CS = 0;		// Timer0 Clock Source Select bit (1 = Transition on T0CKI pin, 0 = Internal instruction cycle clock (CLKO))
	T0CONbits.T0PS0 = 1;	// Timer0 Prescaler Select bits(111 = 1:256 Prescale value)
	T0CONbits.T0PS1 = 0;
	T0CONbits.T0PS2 = 1;
	T0CONbits.PSA = 0;	// Timer0 Prescaler Assignment bit (1 = TImer0 prescaler is NOT assigned. Timer0 clock input bypasses prescaler. / 0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output)

	TMR0L = 0;
	T0CONbits.TMR0ON = 1;	// Timer0 On/Off Control bit(1 = Enables Timer0, 0 = Stops Timer0)

	/* Enable Global Interrupt */
	RCONbits.IPEN = 1; 	// Interrupt Priority Enable bit (1 = Enable priority levels on interrupts /0 = Disable priority levels on interrupts (PIC16CXXX Compatibility mode)) 
	INTCONbits.GIE = 1; // Global Interrupt Enable bit (When IPEN = 1: 1 = Enables all high-priority interrupts / 0 = Disables all interrupts)
	INTCONbits.PEIE = 1;// Peripheral Interrupt Enable bit (When IPEN = 1: 1 = Enables all low-priority peripheral interrupts / 0 = Disables all low-priority peripheral interrupts

	/* Enable TIMER0 Interrupt */
	INTCONbits.TMR0IE = 1; 	// TMR0 Overflow Interrupt Enable bit(1 = Enables the TMR0 overflow interrupt / 0 = Disables the TMR0 overflow interrupt)
	INTCON2bits.TMR0IP = 1; // TMR0 Overflow Interrupt Priority bit(1 = High priority / 0 = Low priority)
}

#ifdef USE_UART_INTERRUPT
__interrupt(low_priority) void rs485_read_task(void)
#else
static void rs485_read_task(void)
#endif
{
    uint8_t byte;
    if (rs485_readByte(&byte)) {
        if (g_nvm.flash.sensing_on == SENSING_ON) {
            buffer_en_queue(&g_modbus_queue, byte);
        }
    }
}

static void usedtime_task(void)
{
    if (g_usedtime_count > ONE_HOUR_COUNT) {
        g_usedtime_count = 0;
        if (g_sens_measure.existChannel[0]) {
            memcpy(g_eeprmTemp[0].byte, g_nvm.eeprm[0].byte, EEPROM_ALL_SIZE); // backup eeprom
            g_nvm.eeprm[0].usedtime++;
        }

        if (g_sens_measure.existChannel[1]) {
            memcpy(g_eeprmTemp[1].byte, g_nvm.eeprm[1].byte, EEPROM_ALL_SIZE); // backup eeprom
            g_nvm.eeprm[1].usedtime++;
        }

        eeprom_update_all();
    }
}

void main(void)
{
    Board_initialize();

    SYSTEM_Initialize(SYSTEM_STATE_USB_START);
    USBDeviceInit();
    USBDeviceAttach();

    InitTimer();
    WDT_initialize();

    while(1)
    {
        ClrWdt();
        #if defined(USB_POLLING)
            // Interrupt or polling method.  If using polling, must call
            // this function periodically.  This function will take care
            // of processing and responding to SETUP transactions
            // (such as during the enumeration process when you first
            // plug in).  USB hosts require that USB devices should accept
            // and process SETUP packets in a timely fashion.  Therefore,
            // when using polling, this function should be called
            // regularly (such as once every 1.8ms or faster** [see
            // inline code comments in usb_device.c for explanation when
            // "or faster" applies])  In most cases, the USBDeviceTasks()
            // function does not take very long to execute (ex: <100
            // instruction cycles) before it returns.
            // get current I2C power state
            USBDeviceTasks();
        #endif

        //Application specific tasks
        app_usb_task();
#ifndef USE_UART_INTERRUPT
        rs485_read_task();
#endif
        sensMeasure_task();
        modbus_task();
        atcommand_task();
        usedtime_task();

    }
}
