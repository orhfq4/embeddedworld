/*
 * LEDS.c
 *
 * Created: 6/30/2020 11:32:36 AM
 *  Author: Roger Younger
 */ 

#include "board.h"
#include "GPIO_Outputs.h"
#include "LEDS.h"

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
                                  led_polarity_t _polarity)
{
    GPIO_output_ctor(&me->super, _port_addr, _pin_mask, (_state^_polarity));
    me->led_polarity=_polarity;
}

/**************************************************************
*   GPIO_output_ctor
*   Inputs: pointer to a GPIO port struct,
            pointer to a GPIO Instance Object,
*           pin_mask to select GPIO pin(s)
            GPIO_PIN_STATE variable indicating the state of the constructor - GPIO_PIN_STATE-t originates from an output of another function.
*   Output: None
**************************************************************
*   Function: GPIO instance object constructor, builds a GPIO object.
*
*   Caution: 
***************************************************************/
void LED_set_value(led_inst_t * const me, led_state_t _state)
{
        GPIO_output_set_value(&me->super,((_state)^(me->led_polarity)));
}

/**************************************************************
*   GPIO_output_ctor
*   Inputs: pointer to a GPIO port struct,
            pointer to a GPIO Instance Object,
*           pin_mask to select GPIO pin(s)
            GPIO_PIN_STATE variable indicating the state of the constructor - GPIO_PIN_STATE-t originates from an output of another function.
*   Output: None
**************************************************************
*   Function: GPIO instance object constructor, builds a GPIO object.
*
*   Caution: 
***************************************************************/
led_state_t LED_get_value(led_inst_t * const me)
{
    uint8_t temp8;
    led_state_t return_val=LED_OFF;
    temp8=GPIO_output_get_value(&me->super);
    temp8^=me->led_polarity;
    if(2>temp8)
    {
        return_val=(led_state_t)temp8;
    }
    return return_val;
}

/**************************************************************
*   GPIO_output_ctor
*   Inputs: pointer to a GPIO port struct,
            pointer to a GPIO Instance Object,
*           pin_mask to select GPIO pin(s)
            GPIO_PIN_STATE variable indicating the state of the constructor - GPIO_PIN_STATE-t originates from an output of another function.
*   Output: None
**************************************************************
*   Function: GPIO instance object constructor, builds a GPIO object.
*
*   Caution: 
***************************************************************/
void LED_toggle_value(led_inst_t * const me)
{
    GPIO_output_toggle_value(&me->super);
}


