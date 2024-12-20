/*
 * GPIO_Outputs.h
 *
 * Created: 6/30/2020 11:42:34 AM
 *  Author: youngerr
 */ 


#ifndef _GPIO_OUTPUTS_H_
#define _GPIO_OUTPUTS_H_

#include "board.h"

typedef enum {GPIO_CLEAR=0,GPIO_SET} GPIO_PIN_STATE_t;

typedef struct
{
    volatile GPIO_t * port_addr;
    uint8_t pin_mask;
}gpio_inst_t;
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
void GPIO_output_ctor(gpio_inst_t * const me, volatile GPIO_t * _port_addr, uint8_t _pin_mask, GPIO_PIN_STATE_t _state);

/**************************************************************
*   GPIO_output_set_value
*   Inputs: pointer to a GPIO Instance Object,
*           GPIO_PIN_STATE variable indicating the state of the constructor - GPIO_PIN_STATE-t originates from an output of another function
*   Output: None
**************************************************************
*   Function: Sets the value of the GPIO PORT register.
*
*   Caution: 
***************************************************************/
static inline void GPIO_output_set_value(gpio_inst_t * const me, GPIO_PIN_STATE_t _state)
{
    if(GPIO_CLEAR==_state)
    {
       (me->port_addr->GPIO_PORT)&=(~(me->pin_mask));    // Clear pin on PORTx to make '0' 
    }
    else
    {
       (me->port_addr->GPIO_PORT)|=(me->pin_mask);    // Set pin on PORTx to make '1' 
    }
}

/**************************************************************
*   GPIO_PIN_STATE_t
*   Inputs: GPIO instance object
*   Output: Outputs a GPIO_PIN_STATE_t variable which reads the value of the GPIO object's PIN
**************************************************************
*   Function: Reads the PIN register of the GPIO object called by the function.
*
*   Caution: 
***************************************************************/
static inline GPIO_PIN_STATE_t GPIO_output_get_value(gpio_inst_t * const me)
{
    uint8_t temp8;
    GPIO_PIN_STATE_t return_value=GPIO_CLEAR;
    temp8=(me->port_addr->GPIO_PIN)&(me->pin_mask);
    if(0!=temp8)
    {
        return_value=GPIO_SET;
    }
    return return_value;
}

/**************************************************************
*   GPIO_output_ctor
*   Inputs: GPIO instance object
*   Output: None
**************************************************************
*   Function: Toggles the PORT register of the GPIO object.
*
*   Caution: 
***************************************************************/
static inline void GPIO_output_toggle_value(gpio_inst_t * const me)
{
    (me->port_addr->GPIO_PORT)^=(me->pin_mask);   
}



#endif /* _GPIO_OUTPUTS_H_ */