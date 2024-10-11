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
*   Inputs: LED instance object from the LED struct,
            GPIO Object from the GPIO struct,
            pin mask to set the value of the pin mask of the GPIO object,
            led_state_t variable that orginates from the LED_get_value function which reads the PIN register of the LED,
            Polarity variable to determine either active high or active low for the LED
*   Output: None
**************************************************************
*   Function: LED instance object constructor, builds a LED object.
*
*   Caution: Make sure your inputting the correct value for the polarity value.
***************************************************************/
void LED_ctor(led_inst_t * const me, volatile GPIO_t * _port_addr, 
                                  uint8_t _pin_mask, led_state_t _state,
                                  led_polarity_t _polarity);

/**************************************************************
*   LED_set_value
*   Inputs: LED instance object,
            led_state_t variable that orginates from the LED_get_value function which reads the PIN register of the LED
*   Output: None
**************************************************************
*   Function: Sets the value of the LED PORT register
*
*   Caution: 
***************************************************************/
void LED_set_value(led_inst_t * const me, led_state_t _state);

/**************************************************************
*   LED_get_value
*   Inputs: LED instance object
*   Output: Outputs the PIN register value of the LED object
**************************************************************
*   Function: Gets the value of the PIN register of the LED object
*
*   Caution: 
***************************************************************/
led_state_t LED_get_value(led_inst_t * const me);

/**************************************************************
*   GPIO_output_ctor
*   Inputs: LED instance object
*   Output: None
**************************************************************
*   Function: Toggles the value of the LED instance object from off to on or on to off.
*
*   Caution: 
***************************************************************/
void LED_toggle_value(led_inst_t * const me);





#endif /* _LEDS_H_ */