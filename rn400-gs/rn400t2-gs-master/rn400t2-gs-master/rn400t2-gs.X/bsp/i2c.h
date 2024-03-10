#ifndef _USER_I2C_H_
#define _USER_I2C_H_

typedef enum {
    I2C_100kHz,
    I2C_400kHz
} I2C_SPEED;

typedef enum {
    I2C_ACK,
    I2C_NACK
} I2C_TRANS_CTRL;


#ifdef	__cplusplus
extern "C" {
#endif

    void i2c_init(const I2C_SPEED speed);

    bool i2c_writeData(const uint8_t *wrptr, const uint8_t len, bool isStop);
    bool i2c_writeBytes(const uint8_t address, const uint8_t *wrptr, const uint8_t len, bool isStop);
    bool i2c_writeBytes_to(const uint8_t address, const uint8_t *wraddr, const uint8_t addrlen, const uint8_t *wrptr, const uint8_t len);
    bool i2c_readBytes(const uint8_t address, uint8_t *rdptr, const uint8_t len);
    bool i2c_readBytes_from(const uint8_t address, const uint8_t *wraddr, const uint8_t addrlen, uint8_t *rdptr, const uint8_t len);

#ifdef	__cplusplus
}
#endif

#endif  //_USER_I2C_H_
