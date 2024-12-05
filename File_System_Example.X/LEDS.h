/*
 * LEDS.h
 *
 * Created: 6/30/2020 11:42:34 AM
 *  Author: youngerr
 */ 


#ifndef _LEDS_H_
#define _LEDS_H_

#include "GPIO_Outputs.h"


typedef enum {LED_ON=0,LED_OFF} led_state_t;
typedef enum {ACTIVE_LOW=0,ACTIVE_HIGH} led_polarity_t;

typedef struct
{
    gpio_inst_t super;
    led_polarity_t led_polarity;
}led_inst_t;


void LED_ctor(led_inst_t * const me, volatile GPIO_t * _port_addr, 
                                  uint8_t _pin_mask, led_state_t _state,
                                  led_polarity_t _polarity);

void LED_set_value(led_inst_t * const me, led_state_t _state);

led_state_t LED_get_value(led_inst_t * const me);

void LED_toggle_value(led_inst_t * const me);

#endif /* _LEDS_H_ */