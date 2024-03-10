
#include <stdbool.h>
#include <stdint.h>

#include "board.h"

#include "bsp/leds.h"
#include "usb/usb_device.h"

#include "nvm.h"
#include "app_led_task.h"

#define LED_OFF_DELAY_COUNT 10 // 100ms
#define LED_OFF_LONG_DELAY_COUNT 50 // 500ms

//state machine
extern s_Led_Status g_led_status;

extern s_Nvm g_nvm;

volatile uint32_t g_led_counter;

static void led_warmup(void)
{
    if (g_led_counter > LED_OFF_LONG_DELAY_COUNT) {
        LED_Off();
        LED_On((g_led_status.toggle==true)?LED_RED:LED_GREEN);
        g_led_status.toggle = (g_led_status.toggle)?false:true;
        g_led_counter = 0;
    }
}

static void led_zerocal_end(void)
{
    if (g_led_counter > LED_OFF_DELAY_COUNT) {
        g_led_counter = 0;
        if (g_led_status.toggle == true) {
            LED_Off();
            g_led_status.toggle = false;
        } else {
            LED_On(LED_GREEN);
            g_led_status.toggle = true;
        }
    }
}

static void led_fail(void)
{
    if (g_led_counter > LED_OFF_DELAY_COUNT) {
        g_led_counter = 0;
        if (g_led_status.toggle == true) {
            LED_Off();
            g_led_status.toggle = false;
        } else {
            LED_On(LED_RED);
            g_led_status.toggle = true;
        }
    }
}

void led_init(void)
{
    g_led_status.seq = LED_INIT;
    g_led_status.last_state = LED_INIT;
    g_led_status.isBlink = false;
    g_led_status.toggle = false;
    g_led_status.twoYear = false;
    if (g_nvm.flash.usedtime >= TWO_YEAR_COUNT) {
        g_led_status.twoYear = true;
    }

    LED_Off();
    LED_On(LED_RED); // default red on. usb disconnected

    g_led_counter = 0;
}

void led_task(void)
{
    switch (g_led_status.seq) {
        case LED_INIT:
            g_led_counter = 0;
            g_led_status.toggle = false;
            g_led_status.seq = LED_READY;
            break;
        case LED_READY:
            if (USBGetDeviceState() == CONFIGURED_STATE) {
                g_led_counter = 0;
                g_led_status.seq = LED_WAIT_OFF;
                g_led_status.isBlink = true;
                g_led_status.last_state = LED_WARMUP;
            }
            break;
        case LED_WAIT_OFF:
            if (g_led_counter > LED_OFF_DELAY_COUNT) {
                g_led_counter = 0;
                g_led_status.seq = LED_ALLOFF;
            }
            break;
        case LED_WARMUP:
            g_led_counter = 0;
            g_led_status.last_state = LED_WARMUP;
            g_led_status.seq = LED_NOTHING;
            break;
        case LED_COMMAND:
            LED_Off();
            LED_On((g_led_status.twoYear==true)?LED_RED:LED_GREEN);
            g_led_counter = 0;
            g_led_status.seq = LED_NOTHING;
            break;
        case LED_ZEROCAL:
            LED_Off();
            LED_On(LED_GREEN);
            g_led_counter = 0;
            g_led_status.seq = LED_NOTHING;
            break;
        case LED_ZEROCAL_END:
            g_led_counter = 0;
            g_led_status.last_state = LED_ZEROCAL_END;
            g_led_status.seq = LED_NOTHING;
            break;
        case LED_FAIL:
            g_led_counter = 0;
            g_led_status.last_state = LED_FAIL;
            g_led_status.seq = LED_NOTHING;
            break;
        case LED_ALLOFF:
            LED_Off();
            g_led_counter = 0;
            g_led_status.seq = LED_NOTHING;
            break;
        case LED_NOTHING:
            switch (g_led_status.last_state) {
                case LED_WARMUP: if (g_led_status.isBlink) led_warmup(); break;
                case LED_ZEROCAL_END: led_zerocal_end(); break;
                case LED_FAIL: led_fail(); break;
                default: break;
            }
            break;
    }
}
