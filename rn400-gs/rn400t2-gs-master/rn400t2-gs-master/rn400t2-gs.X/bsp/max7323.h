/*
 * max7323.h
 *
 */

#ifndef _MAX7323_H_
#define _MAX7323_H_

//*****************************************************************************
// Sensor Device details
//*****************************************************************************
#ifndef MAX7323_I2C_ADDRESS_CH1
#define MAX7323_I2C_ADDRESS_CH1     0xDA
//#define MAX7323_I2C_ADDRESS_CH1     0x6D // 7bit address
#endif
#ifndef MAX7323_I2C_ADDRESS_CH2
#define MAX7323_I2C_ADDRESS_CH2     0xD8
//#define MAX7323_I2C_ADDRESS_CH2     0x6C // 7bit address
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    bool max7323_set_gpio(uint8_t chno, uint8_t wb);
    bool max7323_get_gpio(uint8_t chno, uint8_t *rb);
#ifdef __cplusplus
}
#endif

#endif /* _MAX7323_H_ */
