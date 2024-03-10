#include <stdbool.h>
#include <stdint.h>
#include <xc.h>

#include "../board.h"

#include "i2c.h"

#include "sht3x.h"

static unsigned char crc8(unsigned char* data, unsigned char len)
{
    unsigned char crc = 0xff;
    unsigned char i;
    unsigned char j;

    //calculates 8-Bit checksum with given polynomial
    for (i = 0; i < len; ++i)
    {
        crc ^= (data[i]);
        for (j = 8; j > 0; --j)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc = (crc << 1);
        }
    }
    return crc;
}

static bool check_crc8(unsigned char* data, unsigned char nbrOfBytes, unsigned char checksum)
{
    unsigned char crc;
    // calculates 8-Bit checksum
    crc = crc8(data, nbrOfBytes);

    // verify checksum
    if(crc != checksum) return false;  //checksum error

    return true;
}

bool sht3x_softreset(void)
{
    uint8_t cmd[2];
    cmd[0] = SHT3X_SOFT_RESET_MSB;
    cmd[1] = SHT3X_SOFT_RESET_LSB;
    return i2c_writeBytes(SHT3X_I2C_ADDRESS, cmd, 2, true);
}

bool sht3x_measure_start(void)
{
    uint8_t cmd[2];
    cmd[0] = SHT3X_MEASURE_START_MSB;
    cmd[1] = SHT3X_MEASURE_START_LSB;
    return i2c_writeBytes(SHT3X_I2C_ADDRESS, cmd, 2, true);
}

bool sht3x_common_read(int32_t* temp, int32_t* humi)
{
    uint8_t buff[6];
    if (i2c_readBytes(SHT3X_I2C_ADDRESS, buff, 6) == false)
        return false;

    if(check_crc8(&buff[0], 2, buff[2]) == false)  
        return false;
    if(check_crc8(&buff[3], 2, buff[5]) == false)  
        return false; 
    
    *temp = (int32_t)((int32_t)buff[0] << 8 | (buff[1] & 0xff));
    *humi = (int32_t)((int32_t)buff[3] << 8 | (buff[4] & 0xff));

    return true;
}

#if (USE_SHT3X_COMPENSATE)
/* Definition of global constants and variables */
static const int32_t c2[29] = {73727, 85210, 152199, 1610612736, 63573, 100811, -226492416, 271852, 113553, 180066,
                                38809, 73728, 1879048192, 47431, 75213, -264241152, 119270, -37734, 22937600, -23592960,
                                90498, 161644, -1610612736, 67519, 107068, -786432, 11726618, 18927601, 65536};
static const int16_t c1[20] = {1000, 25000, 500, 21727, -256, 16210, 25706, -21125, -15761, -24993,
                                -5386, 18432, 23076, -5136, -9173, -3831, -6076, -1309, 6554, 16384};
static const int8_t c0[6] = {19, 14, 5, 1, 8, 6};
static int64_t v[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0};
static int32_t t1[2] = {0, 0};
static uint8_t t0[8] = {54, 130, 0, 0, 0, 0, 0, 0};

bool sht3x_read_compensate(int32_t* temp, int32_t* humi)
{
    if (sht3x_common_read(&t1[0], &t1[1]) == false)
        return false;

    if (i2c_writeBytes(SHT3X_I2C_ADDRESS, t0, 2, true) == false)
        return false;

    __delay_us(500);

    if (i2c_readBytes(SHT3X_I2C_ADDRESS, &t0[2], 6) == false)
        return false;

    uint8_t i, j, k;
    v[1]=(int64_t)((((uint32_t)t0[2])<<24)|(((uint32_t)t0[3])<<16)|(((uint32_t)t0[5])<<8)|((uint32_t)t0[6]));
    v[2]=(int64_t)t1[0]; v[3]=(int64_t)t1[1];
    if(v[0]==0) {
        v[0]=c0[3];
        v[6]=((c2[0])>>c0[2]);
        v[10]=((c1[7]*v[4])>>c0[0])+((c2[17]*v[5])>>c0[0])+((c1[8]*v[8])>>c0[0])+((c1[9]*v[9])>>c0[0])+((c2[18]*v[2])>>c0[0])+((c1[10])>>c0[2])+((c2[19])>>c0[2]);
        v[11]=((c2[20]*v[4])>>c0[0])+((c2[21]*v[5])>>c0[0])+((c2[22]*v[7])>>c0[0])+((c2[23]*v[8])>>c0[0])+((c2[24]*v[9])>>c0[0])+((c1[11]*v[1])>>c0[0])+((c1[12])>>c0[2])+((c2[25])>>c0[2]);
        v[12]=((c1[13]*v[4])>>c0[0])+((c1[14]*v[5])>>c0[0])+((c1[15]*v[8])>>c0[0])+((c1[16]*v[9])>>c0[0])+((c2[26]*v[2])>>c0[0])+((c1[17])>>c0[2])+((c2[27])>>c0[2]);
        v[13]=c1[18]; for(i=0;i<c0[4];i++) {v[13]=v[13]+v[13]-((((v[13]*v[13])>>c0[0])*v[12])>>c0[1]);}
        v[14]=c1[19]+((v[11]*v[13])>>(c0[0]+c0[4])); for(j=0;j<c0[4];j++) {v[14]=((v[14]*v[14])>>c0[1]);} v[14]=((v[14]*v[3])>>c0[1]); if(v[14]>c2[28]) v[14]=c2[28];
    } else {
        int64_t vp[15]; for(k=0;k<15;k++) {vp[k]=v[k];}
        v[4]=((c2[1]*vp[4])>>c0[0])+((c2[2]*vp[5])>>c0[0])+((c2[3]*vp[6])>>c0[0])+((c2[4]*vp[8])>>c0[0])+((c2[5]*vp[9])>>c0[0])+((c1[3])>>c0[2])+((c2[6])>>c0[2]);
        v[5]=((c2[2]*vp[4])>>c0[0])+((c2[7]*vp[5])>>c0[0])+((c2[3]*vp[6])>>c0[0])+((c2[8]*vp[8])>>c0[0])+((c2[9]*vp[9])>>c0[0])+((c2[10])>>c0[2])+((c2[6])>>c0[2]);
        v[6]=((c0[4]*vp[7])>>c0[0])+((c2[11])>>c0[2]);
        v[7]=((c0[5]*v[1])>>c0[0])+((c1[4])>>c0[2]);
        v[8]=((c2[4]*vp[4])>>c0[0])+((c2[8]*vp[5])>>c0[0])+((c2[12]*vp[6])>>c0[0])+((c2[13]*vp[8])>>c0[0])+((c2[14]*vp[9])>>c0[0])+((c1[5])>>c0[2])+((c2[15])>>c0[2]);
        v[9]=((c2[5]*vp[4])>>c0[0])+((c2[9]*vp[5])>>c0[0])+((c2[12]*vp[6])>>c0[0])+((c2[14]*vp[8])>>c0[0])+((c2[16]*vp[9])>>c0[0])+((c1[6])>>c0[2])+((c2[15])>>c0[2]);
        v[10]=((c1[7]*v[4])>>c0[0])+((c2[17]*v[5])>>c0[0])+((c1[8]*v[8])>>c0[0])+((c1[9]*v[9])>>c0[0])+((c2[18]*v[2])>>c0[0])+((c1[10])>>c0[2])+((c2[19])>>c0[2]);
        v[11]=((c2[20]*v[4])>>c0[0])+((c2[21]*v[5])>>c0[0])+((c2[22]*v[7])>>c0[0])+((c2[23]*v[8])>>c0[0])+((c2[24]*v[9])>>c0[0])+((c1[11]*v[1])>>c0[0])+((c1[12])>>c0[2])+((c2[25])>>c0[2]);
        v[12]=((c1[13]*v[4])>>c0[0])+((c1[14]*v[5])>>c0[0])+((c1[15]*v[8])>>c0[0])+((c1[16]*v[9])>>c0[0])+((c2[26]*v[2])>>c0[0])+((c1[17])>>c0[2])+((c2[27])>>c0[2]);
        v[13]=c1[18]; for(i=0;i<c0[4];i++) {v[13]=v[13]+v[13]-((((v[13]*v[13])>>c0[0])*v[12])>>c0[1]);}
        v[14]=c1[19]+((v[11]*v[13])>>(c0[0]+c0[4])); for(j=0;j<c0[4];j++) {v[14]=((v[14]*v[14])>>c0[1]);} v[14]=((v[14]*v[3])>>c0[1]); if(v[14]>c2[28]) v[14]=c2[28];
    }
    *temp = (int32_t)((c1[0]*v[10])>>c0[1]);
    *humi = (int32_t)((c1[1]*v[14])>>c0[1]);

    return true;
}

bool sht3x_measure_nonblock_compensate(float* temp, float* humi)
{
    uint8_t cmd[2];
    cmd[0] = SHT3X_MEASURE_READ_MSB;
    cmd[1] = SHT3X_MEASURE_READ_LSB;

    if (i2c_writeBytes(SHT3X_I2C_ADDRESS, cmd, 2, false) == false)
        return false;

    if (sht3x_measure_read(temp, humi) == false)
        return false;

    *temp = (float)(raw_temp / 1000.0f);
    *humi = (float)(raw_humi / 1000.0f);

    return true;
}

bool sht3x_measure_block_compensate(float* temp, float* humi)
{
    int32_t raw_temp, raw_humi;
    uint8_t cmd[2];
    cmd[0] = SHT3X_POLLING_READ_MSB;
    cmd[1] = SHT3X_POLLING_READ_LSB;

    if (i2c_writeBytes(SHT3X_I2C_ADDRESS, cmd, 2, true) == false)
        return false;

    __delay_us(15000);

    if (sht3x_read_compensate(&raw_temp, &raw_humi) == false)
        return false;

    *temp = (float)(raw_temp / 1000.0f);
    *humi = (float)(raw_humi / 1000.0f);

    return true; 
}

#else

bool sht3x_measure_read(float* temp, float* humi)
{
    int32_t raw_temp, raw_humi;
    if (sht3x_common_read(&raw_temp, &raw_humi) == false)
        return false;

    /**
     * formulas for conversion of the sensor signals, optimized for fixed point algebra:
     * Temperature       = 175 * S_T / 2^16 - 45
     * Relative Humidity = 100 * S_RH / 2^16
     */
#if 1
    raw_temp = ((21875 * raw_temp) >> 13) - 45000;
    raw_humi = ((12500 * raw_humi) >> 13);

    *temp = (float)(raw_temp / 1000.0f);
    *humi = (float)(raw_humi / 1000.0f);
#else
    *temp = (175.0f * ((float)raw_temp / 65535.0f)) - 45.0f;
    *humi = (100.0f * ((float)raw_humi / 65535.0f));
#endif

    return true; 
}

bool sht3x_measure_nonblock_read(float* temp, float* humi)
{
    uint8_t cmd[2];
    cmd[0] = SHT3X_MEASURE_READ_MSB;
    cmd[1] = SHT3X_MEASURE_READ_LSB;

    if (i2c_writeBytes(SHT3X_I2C_ADDRESS, cmd, 2, false) == false)
        return false;

    if (sht3x_measure_read(temp, humi) == false)
        return false;

    return true;
}

bool sht3x_measure_block_read(float* temp, float* humi)
{
    uint8_t cmd[2];
    cmd[0] = SHT3X_POLLING_READ_MSB;
    cmd[1] = SHT3X_POLLING_READ_LSB;

    if (i2c_writeBytes(SHT3X_I2C_ADDRESS, cmd, 2, true) == false)
        return false;

    __delay_us(15000);

    if (sht3x_measure_read(temp, humi) == false)
        return false;

    return true;
}
#endif // USE_SHT3X_COMPENSATE

bool sht3x_art_cmd(void)
{
    uint8_t cmd[2];
    cmd[0] = SHT3X_ART_CMD_MSB;
    cmd[1] = SHT3X_ART_CMD_LSB;
    return i2c_writeBytes(SHT3X_I2C_ADDRESS, cmd, 2, true);
}

bool sht3x_break_cmd(void)
{
    uint8_t cmd[2];
    cmd[0] = SHT3X_BREAK_CMD_MSB;
    cmd[1] = SHT3X_BREAK_CMD_LSB;
    return i2c_writeBytes(SHT3X_I2C_ADDRESS, cmd, 2, true);
}

bool sht3x_clear_status_reg(void)
{
    uint8_t cmd[2];
    cmd[0] = SHT3X_CLEAR_STATUS_REG_MSB;
    cmd[1] = SHT3X_CLEAR_STATUS_REG_LSB;
    return i2c_writeBytes(SHT3X_I2C_ADDRESS, cmd, 2, true);
}

bool sht3x_read_status_reg(uint16_t* status)
{
    uint8_t buff[3];
    uint8_t cmd[2];
    cmd[0] = SHT3X_READ_STATUS_REG_MSB;
    cmd[1] = SHT3X_READ_STATUS_REG_LSB;

    if (i2c_readBytes_from(SHT3X_I2C_ADDRESS, cmd, 2, buff, 3) == false)
        return false;
    
    if(check_crc8(&buff[0], 2, buff[2]) == false)  
        return false;
    
    *status = ((uint16_t)buff[0] << 8) | buff[1];
    
     return true; 
}

 bool sht3x_heaterOn(void)
 {
    uint8_t cmd[2];
    cmd[0] = SHT3X_HEATER_ON_MSB;
    cmd[1] = SHT3X_HEATER_ON_LSB;
    return i2c_writeBytes(SHT3X_I2C_ADDRESS, cmd, 2, true);
}
    
 bool sht3x_heaterOff(void)
 {
    uint8_t cmd[2];
    cmd[0] = SHT3X_HEATER_OFF_MSB;
    cmd[1] = SHT3X_HEATER_OFF_LSB;
    return i2c_writeBytes(SHT3X_I2C_ADDRESS, cmd, 2, true);
 }
 
 static uint16_t calc_raw_temperature(float temp)
 {
     return (uint16_t)((temp + 45.0f) / 175.0f * 65535.0f);
 }
 
 static uint16_t calc_raw_humidity(float humi)
 {
     return (uint16_t)(humi / 100.0f * 65535.0f);
 }
 
 bool sht3x_write_alert_limits(float humidityHighSet,   float temperatureHighSet,
                             float humidityHighClear, float temperatureHighClear,
                             float humidityLowClear,  float temperatureLowClear,
                             float humidityLowSet,    float temperatureLowSet)
{
    uint16_t raw_humi, raw_temp, raw;
    uint8_t buff[3];
    uint8_t cmd[2];

    // humidityHighSet, temperatureHighSet
    if((humidityHighSet < 0.0f) || (humidityHighSet > 100.0f)
    || (temperatureHighSet < -45.0f) || (temperatureHighSet > 130.0f))
    {
        return false;
    }
    cmd[0] = SHT3X_WRITE_LIMIT_MSB;
    cmd[1] = SHT3X_WRITE_LIMIT_HS_LSB;

    raw_humi = calc_raw_humidity(humidityHighSet);
    raw_temp = calc_raw_temperature(temperatureHighSet);

    raw = (raw_humi & 0xFE00) | ((raw_temp >> 7) & 0x001FF);

    buff[0] = (uint8_t)(raw >> 8 & 0xff);
    buff[1] = (uint8_t)(raw & 0xff);
    buff[2] = crc8(buff, 2);
    
    if (i2c_writeBytes_to(SHT3X_I2C_ADDRESS, cmd, 2, buff, 3) == false)
        return false;

    // humidityHighClear, temperatureHighClear
    if((humidityHighClear < 0.0f) || (humidityHighClear > 100.0f)
    || (temperatureHighClear < -45.0f) || (temperatureHighClear > 130.0f))
    {
        return false;
    }
    cmd[0] = SHT3X_WRITE_LIMIT_MSB;
    cmd[1] = SHT3X_WRITE_LIMIT_HC_LSB;

    raw_humi = calc_raw_humidity(humidityHighClear);
    raw_temp = calc_raw_temperature(temperatureHighClear);

    raw = (raw_humi & 0xFE00) | ((raw_temp >> 7) & 0x001FF);

    buff[0] = (uint8_t)(raw >> 8 & 0xff);
    buff[1] = (uint8_t)(raw & 0xff);
    buff[2] = crc8(buff, 2);
    
    if (i2c_writeBytes_to(SHT3X_I2C_ADDRESS, cmd, 2, buff, 3) == false)
        return false;

    // humidityLowClear, temperatureLowClear
    if((humidityLowClear < 0.0f) || (humidityLowClear > 100.0f)
    || (temperatureLowClear < -45.0f) || (temperatureLowClear > 130.0f))
    {
        return false;
    }
    cmd[0] = SHT3X_WRITE_LIMIT_MSB;
    cmd[1] = SHT3X_WRITE_LIMIT_LC_LSB;

    raw_humi = calc_raw_humidity(humidityLowClear);
    raw_temp = calc_raw_temperature(temperatureLowClear);

    raw = (raw_humi & 0xFE00) | ((raw_temp >> 7) & 0x001FF);

    buff[0] = (uint8_t)(raw >> 8 & 0xff);
    buff[1] = (uint8_t)(raw & 0xff);
    buff[2] = crc8(buff, 2);
    
    if (i2c_writeBytes_to(SHT3X_I2C_ADDRESS, cmd, 2, buff, 3) == false)
        return false;

    // humidityLowSet, temperatureLowSet
    if((humidityLowSet < 0.0f) || (humidityLowSet > 100.0f)
    || (temperatureLowSet < -45.0f) || (temperatureLowSet > 130.0f))
    {
        return false;
    }
    cmd[0] = SHT3X_WRITE_LIMIT_MSB;
    cmd[1] = SHT3X_WRITE_LIMIT_LS_LSB;

    raw_humi = calc_raw_humidity(humidityLowSet);
    raw_temp = calc_raw_temperature(temperatureLowSet);

    raw = (raw_humi & 0xFE00) | ((raw_temp >> 7) & 0x001FF);

    buff[0] = (uint8_t)(raw >> 8 & 0xff);
    buff[1] = (uint8_t)(raw & 0xff);
    buff[2] = crc8(buff, 2);
    
    if (i2c_writeBytes_to(SHT3X_I2C_ADDRESS, cmd, 2, buff, 3) == false)
        return false;

    return true;
}
