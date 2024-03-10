
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "board.h"
#include "bsp/flash.h"

#include "bsp/lmp91000.h"
#include "bsp/ads1114.h"

#include "util/build_time.h"

#include "filter.h"
#include "nvm.h"


extern s_Nvm g_nvm;

static void nvm_clear_flash(void)
{
    g_nvm.flash.filter_mode = RAW_MODE;
    g_nvm.flash.window_size = LEVEL_14;  
    g_nvm.flash.temp_corf = CELSIUS;
    g_nvm.flash.temp_compensate = TEMP_NOT_COMPENSATION;
    
    g_nvm.flash.baseLine_uV = 0.0f;
    g_nvm.flash.nA_per_ppm = 0.0f;   
    g_nvm.flash.gasOffset = 0.0f;
    g_nvm.flash.tempOffset= 0.0f;
    g_nvm.flash.calib_temp = 0.0f;
    
    g_nvm.flash.KMf_e_measure = KMF_e_measure;
    g_nvm.flash.KMF_e_estimate = 1.0f;
   
    g_nvm.flash.auto_Calib = OFF;
    g_nvm.flash.dummy = 0;
    g_nvm.flash.slope_min = 0.0f;
    g_nvm.flash.slope_max = 0.0f;
    g_nvm.flash.zeroShift_uV = 0.0f;
    g_nvm.flash.autoCalib_cnt = 0;
    g_nvm.flash.zeroRange_ppm = ZERO_RANGE;

    g_nvm.flash.exectime = 0;
    g_nvm.flash.usedtime = 0;
    g_nvm.flash.buildtime = (uint32_t)build_time();
}

void nvm_clear(void)
{
    nvm_clear_flash();
}

void nvm_clear_all(void)
{
    uint8_t i;
    nvm_clear();
    for (i = 0 ; i < 8 ; i++) g_nvm.flash.serialNum[i] = 0xff;
}

static bool nvm_serialno_check(const uint8_t* sno)
{
    uint8_t i;
    for (i = 0 ; i < 8 ; i++) {
        if (sno[i] == 0xff || sno[i] == 0x00)
            return false;
    }
    return true;
}

void nvm_init(void)
{
    uint8_t i;

    nvm_read_flash_all(&g_nvm.flash);
    g_nvm.status = NVM_INIT_FLASH;

    if (nvm_serialno_check(g_nvm.flash.serialNum)) 
    {
        uint16_t* pdesc = get_product_desc();
        for (i = 0 ; i < 8 ; i++) {
            pdesc[i + 11] = g_nvm.flash.serialNum[i];
        }
    } 
    else 
    {
        nvm_clear();

        if (nvm_write_flash_all(&g_nvm.flash) == false)
            return;
        g_nvm.status = NVM_INIT_FLASH;   
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
bool nvm_write_flash_all(u_Flash_Nvm* flash)
{
    flash_clear(FLASH_BASE_ADDRESS, (FLASH_BASE_ADDRESS + FLASH_ALL_PARAM_SIZE));
    return flash_writeBytes(FLASH_BASE_ADDRESS, flash->byte, FLASH_ALL_PARAM_SIZE);
}

void nvm_read_flash_all(u_Flash_Nvm* flash)
{
    flash_readBytes(FLASH_BASE_ADDRESS, flash->byte, FLASH_ALL_PARAM_SIZE);
}
