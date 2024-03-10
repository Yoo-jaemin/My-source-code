/* 
 * File:   app_modbus.h
 * Author: karl
 *
 * Created on February 11, 2019, 4:02 PM
 */

#ifndef APP_MODBUS_H
#define	APP_MODBUS_H

typedef enum {
	MODBUS_INIT,
	MODBUS_READY,
    MODBUS_START,
    MODBUS_TIMEOUT,
	MODBUS_OUTPUT,
    MODBUS_ERRPARSE,
    MODBUS_EXCEPTION,
    MODBUS_END
} e_Modbus_Seq;

typedef enum {
    BAUD_4800,
    BAUD_9600,
    BAUD_14400,
    BAUD_19200,
    BAUD_38400,
    BAUD_57600
} e_Baudrate;

typedef enum {
    TO_ONE_SEC, // 100
    TO_150_MSEC, // 15
    TO_300_MSEC, // 30
    TO_600_MSEC, // 60
    TO_TWO_SEC // 200
} e_Timeout;

typedef enum {
    EV_NORMAL,
    EV_UP
} e_EventType;

typedef enum {
    RLY_NONE,
    RLY_OPEN,
    RLY_SHORT
} e_RelayStatus;

typedef struct {
    uint8_t seq;
    uint8_t timeout; // holding register or read coils or write single coil function
                     // request size is 8

    bool event_flag; // e_EventType change flag
    bool fire_flag; // command change relay status flag
    uint8_t fire_retry; // when command change relay status is failed. retry count
    uint32_t event_timer; // holding value in minute timer
    e_EventType last_event; // last e_EventType
    e_RelayStatus relay_status; // current relay status
    bool isWarmDone; // 3min warmup done flag

} s_Modbus;

#ifdef	__cplusplus
extern "C" {
#endif

    void modbus_init(void);
    void modbus_task(void);
	
	void modbus_set_register(const uint16_t* reg);
	void modbus_set_swap(bool isSwap);

    uint32_t modbus_get_baudrate(uint8_t baud);
    uint8_t modbus_get_timeout(uint8_t to);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_MODBUS_H */

