
#ifndef APP_LED_TASK_H
#define	APP_LED_TASK_H

typedef enum {
    LED_INIT,
    LED_READY,
	LED_WAIT_OFF,
    LED_CALIB,
    LED_WARMUP,
    LED_COMMAND,
    LED_ZEROCAL,
    LED_ZEROCAL_END,
    LED_FAIL,
    LED_ALLOFF,
    LED_NOTHING,
} e_Led_Seq;

typedef struct {
    uint8_t seq;
    uint8_t last_state;

    bool isBlink;
    bool toggle;
    bool twoYear;
} s_Led_Status;

#ifdef	__cplusplus
extern "C" {
#endif


    void led_init(void);
    void led_task(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_LED_TASK_H */

