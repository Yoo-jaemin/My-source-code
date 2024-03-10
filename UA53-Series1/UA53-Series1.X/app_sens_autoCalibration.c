/*
 * File:   app_sens_autoCalibration.c
 * Author: brian
 *
 * Created on 2022 10/18
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "usb_config.h"

#include "app_sens_autoCalibration.h"
#include "app_linear_regression.h"
#include "app_sens_measure.h"

#include "nvm.h"

#include "board.h"
#include "app_led_task.h"
#include "bsp/leds.h"


/* ******************* Global Variable ******************* */
extern float g_last_value[SENS_COUNT];
extern s_Nvm g_nvm;
extern s_Led_Status g_led_status;
extern s_Linear_reg g_linear_reg;
extern s_Auto_calib g_sens_autoCalib;
extern uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];

volatile uint32_t g_autoCal_cnt;
volatile uint8_t  g_autoCal_cnt2;
volatile uint32_t g_slpSet_cnt; 
volatile uint16_t  g_slpSet_cnt2;


/* ****************** Funtion Prototype ****************** */
static void auto_calib_apply(void);
static void auto_calib_clear(void);
static void sort_uV_slope(float min, float max, float uV_slope);


void sens_autoCalib_init(void)
{ 
    g_sens_autoCalib.Seq_autoCal = AUTO_CALIB_INIT;
    g_sens_autoCalib.Seq_slpSet  = SLOPE_SET_INIT;
    g_autoCal_cnt = 0;
	g_slpSet_cnt = 0;
	
    g_sens_autoCalib.slpSet_en  = OFF;
    g_sens_autoCalib.led_slpSet = OFF;
    
    g_sens_autoCalib.slope_min = 0.0f;
    g_sens_autoCalib.slope_max = 0.0f;  

    g_sens_autoCalib.sumZero_uV = 0.0f;
    g_sens_autoCalib.avgZero_uV = 0.0f;
    
    g_sens_autoCalib.chk_cnt = 0;
    g_sens_autoCalib.sft_ppm = 0.0f;
}

void sens_autoCalib_task(void)
{
    switch (g_sens_autoCalib.Seq_autoCal)
    {
        case AUTO_CALIB_INIT:
            g_autoCal_cnt = 0;
            g_sens_autoCalib.Seq_autoCal = AUTO_CALIB_READY;
            break;
        case AUTO_CALIB_READY:
            if (g_autoCal_cnt >= ONE_MINUTE) { 
                g_autoCal_cnt = 0;
                g_autoCal_cnt2++;
                g_sens_autoCalib.Seq_autoCal = AUTO_CALIB_CHECK;
            } break;
        case AUTO_CALIB_CHECK:
            if (g_linear_reg.slope >= g_nvm.flash.slope_min && 
                g_linear_reg.slope <= g_nvm.flash.slope_max && g_last_value[LV_GAS_PPM] <= g_nvm.flash.zeroRange_ppm) {    
                g_sens_autoCalib.chk_cnt++;
                g_sens_autoCalib.sumZero_uV += g_last_value[LV_GAS_VOLT];    
            }
            if (g_autoCal_cnt2 == ONE_HOUR) { 
                if (g_sens_autoCalib.chk_cnt >= 50/*60*/)   g_sens_autoCalib.Seq_autoCal = AUTO_CALIB;
                else    auto_calib_clear();
            } else {
                g_autoCal_cnt = 0;
                g_sens_autoCalib.Seq_autoCal = AUTO_CALIB_READY;
            } break;
        case AUTO_CALIB:
            auto_calib_apply();
#ifdef USE_DEBUG_PRINT             
            sprintf(writeBuffer, "ppm: %.2f sumZ: %.1f,avgZ: %.1f sftZ: %.1f sftCnt: %d\r\n", g_last_value[LV_GAS_PPM], 
                             g_sens_autoCalib.sumZero_uV, g_sens_autoCalib.avgZero_uV, g_nvm.flash.zeroShift_uV, g_nvm.flash.autoCalib_cnt);
            write_command(writeBuffer);
#endif            
            auto_calib_clear();
            break;
    } // end switch
} // end function

static void auto_calib_apply(void)
{
    g_sens_autoCalib.avgZero_uV   = g_sens_autoCalib.sumZero_uV / g_sens_autoCalib.chk_cnt; 
    g_nvm.flash.zeroShift_uV      = (g_sens_autoCalib.avgZero_uV - g_nvm.flash.baseLine_uV);
    g_nvm.flash.autoCalib_cnt++;
    nvm_write_flash_all(&g_nvm.flash);
}

static void auto_calib_clear(void)
{
    g_autoCal_cnt = 0;
    g_autoCal_cnt2 = 0;
    g_sens_autoCalib.chk_cnt = 0;
    g_sens_autoCalib.sumZero_uV = 0.0f;
    g_sens_autoCalib.avgZero_uV = 0.0f;
    g_sens_autoCalib.Seq_autoCal = AUTO_CALIB_READY;
}

void sens_autoCalib_slp_set_task(void)
{
    switch (g_sens_autoCalib.Seq_slpSet)
    {
        case SLOPE_SET_INIT:
            g_slpSet_cnt = 0;
            g_sens_autoCalib.led_slpSet = ON;
            g_sens_autoCalib.Seq_slpSet = SLOPE_SET_LED;
            break;
        case SLOPE_SET_LED:
            if (g_slpSet_cnt >= FIVE_HUN_mS) {
                g_slpSet_cnt = 0;
                g_led_status.seq = LED_ZEROCAL;
                g_led_status.last_state = LED_NOTHING;
                g_sens_autoCalib.Seq_slpSet = SLOPE_SET_READY;
            } break;
        case SLOPE_SET_READY:
            if (g_slpSet_cnt >= ONE_SECOND) {
                g_slpSet_cnt2++;
                g_sens_autoCalib.Seq_slpSet = SLOPE_SAVE;
            } break;
        case SLOPE_SAVE:
            sort_uV_slope(g_sens_autoCalib.slope_min, g_sens_autoCalib.slope_max, g_linear_reg.slope);
            if (g_slpSet_cnt2 >= TEN_MINUTES)     
                g_sens_autoCalib.Seq_slpSet = SLOPE_SET; 
            else {   
                g_slpSet_cnt = 0;
                g_sens_autoCalib.Seq_slpSet = SLOPE_SET_READY;
            } break;
        case SLOPE_SET:
            g_nvm.flash.slope_min = g_sens_autoCalib.slope_min;
            g_nvm.flash.slope_max = g_sens_autoCalib.slope_max;
            if (nvm_write_flash_all(&g_nvm.flash)) {  
                g_led_status.seq = LED_ZEROCAL_END;
                write_command("ATACSS\r\n");
            } g_sens_autoCalib.Seq_slpSet = SLOPE_SET_END;
            break;
        case SLOPE_SET_END:
            g_slpSet_cnt2 = 0;
            g_sens_autoCalib.slpSet_en = OFF;
            g_sens_autoCalib.Seq_slpSet  = SLOPE_SET_INIT;
            break;
    } // end switch
} // end function

static void sort_uV_slope(float min, float max, float uV_slope)
{
    float Min, Mid, Max, Temp;
    Min = min;
    Mid = uV_slope;
    Max = max;        
    
    if (Min >= Mid) {
        Temp = Mid;
        Mid  = Min;
        Min  = Temp;
	}
	if (Mid >= Max) {
		Temp = Max;
		Max  = Mid;
		Mid  = Temp;	
	}
	if (Min >= Mid) {
		Temp = Mid;
		Mid  = Min;
		Min  = Temp;
	}
    g_sens_autoCalib.slope_min = Min;
    g_sens_autoCalib.slope_max = Max;
}