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

/**************************************************************
*   LED_ctor
*   Inputs: pointer to a GPIO object
*           LED instance object
            an 8-bit value to set the pin mask
            led_state_t variable to set the state of the LED object
            let_polarity_t variable to set the polarity of the LED object
*   Output: None
**************************************************************
*   Function: Creates a LED object
*
*   Caution: 
***************************************************************/
void LED_ctor(led_inst_t * const me, volatile GPIO_t * _port_addr, 
                                  uint8_t _pin_mask, led_state_t _state,
                                  led_polarity_t _polarity);

/**************************************************************
*   LED_set_value
*   Inputs: LED instance object
            a led_state_t variable to set the state of the LED
*   Output: None
**************************************************************
*   Function: Sets the value of the LED state
*
*   Caution: 
***************************************************************/
void LED_set_value(led_inst_t * const me, led_state_t _state);

/**************************************************************
*   LED_get_value
*   Inputs: LED instance object
*   Output: a led_state_t variable with the value of the LED's state
**************************************************************
*   Function: Gets the value of the LED's state
*
*   Caution: 
***************************************************************/
led_state_t LED_get_value(led_inst_t * const me);

/**************************************************************
*   LED_toggle_value
*   Inputs: LED instance object
*   Output: None
**************************************************************
*   Function: Toggles the value of the LED state
*
*   Caution: 
***************************************************************/
void LED_toggle_value(led_inst_t * const me);





#endif /* _LEDS_H_ */