/*
 * File:   main.c
 *
 * Created on 2022 11/21
 * author: brian Yu 
 */

/** Include *******************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "system.h"
#include "usb/usb.h"
#include "usb/usb_device.h"
#include "usb/usb_device_cdc.h"

#include "board.h"

#include "util/buffer.h"
#include "bsp/leds.h"
#include "bsp/i2c.h"

#include "nvm.h"
#include "app_usb_cdc.h"
#include "app_led_task.h"

#include "sensor.h"
#include "app_sens_measure.h"
#include "app_atcommand.h"
#include "app_sens_calibration.h"
#include "app_linear_regression.h"
#include "app_sens_autoCalibration.h"

s_Queue g_usb_queue;
s_Nvm g_nvm;
u_Flash_Nvm g_flash_temp;
s_Led_Status g_led_status;
s_AtCommand g_atcommand;
s_Sens_Measure g_sens_measure;
s_Sens_Calib g_sens_calib;
//s_Sens_SNR g_sens_snr;
s_Linear_reg g_linear_reg;
s_Auto_calib g_sens_autoCalib;

        
volatile uint32_t g_usedtime_count;
uint8_t g_usb_state;

// bootloader
// Linker Option -> Additional Option -> code offset to 0x2000
#ifdef SUPPORT_BOOLTLOADER
const unsigned int FlashSignatureWord __at(APP_SIGNATURE_ADDRESS) = APP_SIGNATURE_VALUE;
#endif

static void WDT_initialize(void)
{
    WDTCONbits.SWDTEN = 1;      /* enable software controlled watchdog timer*/
//  if(!RCONbits.TO)            /* check for WDT reset occurrence */
//      LCD_String_xy(1,0,"WDT Reset");
}

static void Board_initialize(void)
{
    ANCON0 = 0xFF;          // Default all pins to digital
    ANCON1 = 0xFF;          // Default all pins to digital

    LED_Enable(LED_RED);
    LED_Enable(LED_GREEN);

    g_led_status.seq = LED_INIT;
    g_atcommand.seq = AT_INIT;
    g_sens_measure.seq = SENS_INIT;
    g_nvm.status = NVM_INIT_NONE;

    led_init();
    i2c_init(I2C_100kHz);
    buffer_init(&g_usb_queue); 

    nvm_init();
    sens_ZeroCalib_init();
    sensMeasure_init();
    //sensMeasure_SNR_init(&g_sens_snr);
    atcommand_init();
    Linear_regression_init(&g_linear_reg);
    sens_autoCalib_init();
    g_usb_state = USB_NONE;
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

static void usedtime_task(void)
{
    if (g_led_status.isBlink == true && g_usedtime_count > WARMUP_DELAY_COUNT) {
        g_led_status.isBlink = false;
        g_led_status.seq = LED_ALLOFF;
        //write_command("\r\n**** Warm-up end ****\r\n\r\n");
    }

    if (g_usedtime_count > ONE_HOUR_COUNT) {
        g_usedtime_count = 0;
        memcpy(g_flash_temp.byte, g_nvm.flash.byte, FLASH_ALL_PARAM_SIZE);
        g_nvm.flash.usedtime++;
        if (nvm_write_flash_all(&g_nvm.flash) == false) {
            memcpy(g_nvm.flash.byte, g_flash_temp.byte, FLASH_ALL_PARAM_SIZE);
        }
        if (g_nvm.flash.usedtime >= TWO_YEAR_COUNT) {
            g_led_status.twoYear = true;
        }
    }
}

static void changeUsbState_task(void)
{
    if (USBGetDeviceState() == CONFIGURED_STATE)  g_usb_state = USB_ATTACHED;
    else g_usb_state = USB_DETACHED;
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
            USBDeviceTasks();
        #endif
        app_usb_task();
        changeUsbState_task();
        led_task();
        sens_ZeroCalib_task();
        atcommand_task();
        sensMeasure_task();
        usedtime_task();
        if (g_sens_autoCalib.slpSet_en == ON && g_led_status.isBlink == false) 
            sens_autoCalib_slp_set_task();
        if (g_nvm.flash.auto_Calib == ON && g_led_status.isBlink == false)
            sens_autoCalib_task();
    }//end while
}//end main
