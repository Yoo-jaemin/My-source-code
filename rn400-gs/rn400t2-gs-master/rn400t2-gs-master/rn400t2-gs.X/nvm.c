#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <xc.h>

#include "board.h"

#include "bsp/eep24AA02.h"
#include "bsp/flash.h"
#include "bsp/lmp91000.h"
#include "bsp/ads1114.h"

#include "util/_string.h"
#include "util/build_time.h"

#include "app_modbus.h"
#include "filter.h"
#include "nvm.h"

// nvm data
extern s_Nvm g_nvm;

// crc16
uint16_t checksum(const uint8_t *data, uint16_t length)
{
	//Calculate CRC16 checksum using given data and length

	uint16_t crc = 0xFFFF;
	uint16_t i;
	uint8_t j;

	if ( data == NULL ) return 0;

	for ( i = 0; i < length; i++ ) {
		crc ^= (uint16_t) data[i]; //XOR current data byte with crc value

		for ( j = 8; j != 0; j-- ) {
			//For each bit
			//Is least-significant-bit set?
			if ( ( crc & 0x0001 ) != 0 ) {
				crc >>= 1; //Shift to right and xor
				crc ^= 0xA001;
			}
			else
				crc >>= 1;
		}
	}
	//CRC is always little endian
    return crc;
}

#if 0
void nvm_all_ff(void)
{
    for (uint8_t j = 0 ; j < CHANNEL_COUNT ; j++) {
        for (uint8_t i = 0 ; i < EEPROM_ALL_SIZE ; i++) {
            g_nvm.eeprm[j].byte[i] = 0xff;
        }
        nvm_write_eeprom_all(j);
    }
}
#endif

// for eeprom
void nvm_clear_channel(uint8_t channel)
{
    g_nvm.eeprm[channel].supercap = 0;
    g_nvm.eeprm[channel].sensor_model = NONE;
    g_nvm.eeprm[channel].adc_gain = FSR_2p048V;
    g_nvm.eeprm[channel].lmp_gain = EXTERNAL_REGISTOR;
    g_nvm.eeprm[channel].lmp_rload = R100;
    g_nvm.eeprm[channel].lmp_intZ = S50P;
    g_nvm.eeprm[channel].filter_mode = RAW_MODE;
    g_nvm.eeprm[channel].window_size = DEFAULT_FILTER_SIZE;
    g_nvm.eeprm[channel].temp_corf = CELSIUS;
    g_nvm.eeprm[channel].temp_compensate = TEMP_NOT_COMPENSATION;

    g_nvm.eeprm[channel].baseLine_uV = 0.0f;
    g_nvm.eeprm[channel].span_uV = 0.0f;    
    g_nvm.eeprm[channel].calib_baseLine = 0.0f;

    g_nvm.eeprm[channel].baseLine_temp = 0.0f;

    g_nvm.eeprm[channel].CalibrationGas = 0.0f;
    g_nvm.eeprm[channel].gas_slope = 0.0f;

    g_nvm.eeprm[channel].gasOffset = 0.0f;
    g_nvm.eeprm[channel].tempOffset= 0.0f;

    g_nvm.eeprm[channel].caltime = 0;
    g_nvm.eeprm[channel].usedtime = 0;

    _strclr(g_nvm.eeprm[channel].sensor_name, SENS_NAME_MAX_LENGTH);
}

static void nvm_clear_flash(void)
{
    g_nvm.flash.sensing_on = SENSING_OFF; // sensing & 485 on/off default off

    g_nvm.flash.ctrl_master_mode = MODBUS_SLAVE_MODE;
    g_nvm.flash.ctrl_channel = 0; // default channel 1 : 0, channel 2 : 1
    g_nvm.flash.ctrl_slave_id = 0x01; // ML-RH8 dip switch
    g_nvm.flash.ctrl_relay_no = 1; // relay 1
    g_nvm.flash.ctrl_ppm_max = 15.0f;
    g_nvm.flash.ctrl_holding_min = 1; // 1 minute holding delay

    g_nvm.flash.byte_swap = 0; // little endian
    g_nvm.flash.slave_id = MODBUS_DEFAULT_SLAVE_ID; // slave address
    g_nvm.flash.baudrate = MODBUS_DEFAULT_BAUDRATE; // baudrate default 57600
    g_nvm.flash.timeout = 0; // timeout 1sec default 100
    g_nvm.flash.buildtime = (uint32_t)build_time();
}

void nvm_clear()
{
    nvm_clear_flash();

    nvm_clear_channel(0);
    nvm_clear_channel(1);
}

void nvm_clear_all()
{
    uint8_t i;
    nvm_clear();
    for (i = 0 ; i < 8 ; i++) g_nvm.flash.serialNum[i] = 0xff;
}

void nvm_sensor_type_channel(uint8_t chno, uint8_t sensor_model)
{
    if (sensor_model == NH3_100) { // NH3
        g_nvm.eeprm[chno].sensor_model = NH3_100;
        g_nvm.eeprm[chno].adc_gain = FSR_0p512V; // v2.7
        g_nvm.eeprm[chno].lmp_gain = R35K;
        g_nvm.eeprm[chno].lmp_rload = R100;
        g_nvm.eeprm[chno].lmp_intZ = S20P;
        _strcpy(g_nvm.eeprm[chno].sensor_name, "NH3-100");
    } else if (sensor_model == H2S_50) { // H2S
        g_nvm.eeprm[chno].sensor_model = H2S_50;
        g_nvm.eeprm[chno].adc_gain = FSR_0p512V;
        g_nvm.eeprm[chno].lmp_gain = R2p75K; // R7K; 7k --> 2.75k 2021-04-01
        g_nvm.eeprm[chno].lmp_rload = R100;
        g_nvm.eeprm[chno].lmp_intZ = S20P;
        _strcpy(g_nvm.eeprm[chno].sensor_name, "H2S-50");
    } else if (sensor_model == EO) { // EO
        g_nvm.eeprm[chno].sensor_model = EO;
        g_nvm.eeprm[chno].adc_gain = FSR_0p256V;
        g_nvm.eeprm[chno].lmp_gain = R14K;
        g_nvm.eeprm[chno].lmp_rload = R100;
        g_nvm.eeprm[chno].lmp_intZ = S20P;
        _strcpy(g_nvm.eeprm[chno].sensor_name, "EO");
    } else if (sensor_model == NH3_1000) { // NH3-1000
        g_nvm.eeprm[chno].sensor_model = NH3_1000;
        g_nvm.eeprm[chno].adc_gain = FSR_0p256V;
        g_nvm.eeprm[chno].lmp_gain = R14K;
        g_nvm.eeprm[chno].lmp_rload = R100;
        g_nvm.eeprm[chno].lmp_intZ = S20P;
        _strcpy(g_nvm.eeprm[chno].sensor_name, "NH3-1000");
    } else {
        g_nvm.eeprm[chno].sensor_model = NONE;
        _strclr(g_nvm.eeprm[chno].sensor_name, SENS_NAME_MAX_LENGTH);
    }
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

static bool nvm_flash_check(void)
{
    if (!(g_nvm.flash.baudrate >= BAUD_4800 && g_nvm.flash.baudrate <= BAUD_57600)) return false;
    else if (!(g_nvm.flash.ctrl_master_mode >= MODBUS_SLAVE_MODE && g_nvm.flash.ctrl_master_mode <= MODBUS_MASTER_MODE)) return false;
    else if (!(g_nvm.flash.ctrl_channel >= 0 && g_nvm.flash.ctrl_channel <= (CHANNEL_COUNT-1))) return false;
    else if (!(g_nvm.flash.ctrl_slave_id >= 0x01 && g_nvm.flash.ctrl_slave_id <= 0x0f)) return false;
    else if (!(g_nvm.flash.ctrl_relay_no >= 1 && g_nvm.flash.ctrl_relay_no <= 8)) return false;
    else if (!(g_nvm.flash.timeout >= TO_ONE_SEC && g_nvm.flash.timeout <= TO_TWO_SEC)) return false;
    else if (!(g_nvm.flash.byte_swap >= 0 && g_nvm.flash.byte_swap <= 1)) return false;
    else if (g_nvm.flash.buildtime == 0) return false;
    return true;
}

#if 0
void nvm_init(void)
{
    nvm_read_flash_all(&g_nvm.flash);

    if (nvm_serialno_check(g_nvm.flash.serialNum)) {
        uint16_t* pdesc = get_product_desc();
        for (uint8_t i = 0 ; i < 8 ; i++)
        {
            pdesc[i + 11] = g_nvm.flash.serialNum[i];
        }
    } else {
        nvm_clear_all();
        if (nvm_write_flash_all(&g_nvm.flash) == false)
            return;
    }
}
#else
void nvm_init(void)
{
    uint8_t i;

    // nvm flash read
    nvm_read_flash_all(&g_nvm.flash);

    // usb descriptor setup
    uint16_t* pdesc = get_product_desc();
    for (i = 0 ; i < 8 ; i++)
    {
        pdesc[i + 11] = g_nvm.flash.serialNum[i];
    }

    if (nvm_flash_check() == false) {
        nvm_clear_flash();
        nvm_write_flash_all(&g_nvm.flash);
    }
}
#endif

bool nvm_write_eeprom_all(uint8_t channel)
{
    g_nvm.eeprm[channel].check_sum = checksum(g_nvm.eeprm[channel].byte, EEPROM_ALL_SIZE-2);
    
    uint8_t size = (EEPROM_ALL_SIZE / EEPROM_PAGE_SIZE);
    for (uint8_t i = 0 ; i < size ; i++) {
        if (eeprom_writePage(channel, EEPROM_BASE_ADDRESS + (i * EEPROM_PAGE_SIZE), &g_nvm.eeprm[channel].byte[(i * EEPROM_PAGE_SIZE)], EEPROM_PAGE_SIZE) == false)
            return false;
        __delay_ms(10);
    }
    uint8_t left = EEPROM_ALL_SIZE - (size * EEPROM_PAGE_SIZE);
    if (left > 0) {
        if (eeprom_writePage(channel, EEPROM_BASE_ADDRESS + (size * EEPROM_PAGE_SIZE), &g_nvm.eeprm[channel].byte[(size * EEPROM_PAGE_SIZE)], left) == false)
            return false;
        __delay_ms(10);
    }
    return true;
}

#if 1
bool nvm_read_eeprom_all(uint8_t channel)
{
    return eeprom_RandomRead(channel, EEPROM_BASE_ADDRESS, g_nvm.eeprm[channel].byte, EEPROM_ALL_SIZE);
}
#else
bool nvm_read_eeprom_all(uint8_t channel)
{
    if (eeprom_RandomRead(channel, EEPROM_BASE_ADDRESS, g_nvm.eeprm[channel].byte, EEPROM_ALL_SIZE)) {
        if (eeprm->check_sum == checksum(g_nvm.eeprm[channel].byte, EEPROM_ALL_SIZE-2))
            return true;
    }
    return false;
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////
/*bool nvm_write_flash_all(u_Flash_Nvm* flash)
{
    uint8_t block[FLASH_WRITE_BLOCK] = {0xff};
    assert(!(FLASH_ALL_PARAM_SIZE > FLASH_WRITE_BLOCK));
    for (uint8_t i = 0 ; i < FLASH_ALL_PARAM_SIZE ; i++) block[i] = flash->byte[i];
    flash_clear(FLASH_BASE_ADDRESS, FLASH_BASE_ADDRESS + FLASH_WRITE_BLOCK);
    return flash_writeBytes(FLASH_BASE_ADDRESS, block, FLASH_WRITE_BLOCK);
}*/
bool nvm_write_flash_all(u_Flash_Nvm* flash)
{
    flash_clear(FLASH_BASE_ADDRESS, (FLASH_BASE_ADDRESS + FLASH_ALL_PARAM_SIZE));
    return flash_writeBytes(FLASH_BASE_ADDRESS, flash->byte, FLASH_ALL_PARAM_SIZE);
}

void nvm_read_flash_all(u_Flash_Nvm* flash)
{
    flash_readBytes(FLASH_BASE_ADDRESS, flash->byte, FLASH_ALL_PARAM_SIZE);
}
