/*
 * GPIO_Outputs.h
 *
 * Created: 6/30/2020 11:42:34 AM
 *  Author: youngerr
 */ 


#ifndef _GPIO_OUTPUTS_IN_H_
#define _GPIO_OUTPUTS_IN_H_

#include "board.h"

typedef enum {GPIO_CLEAR_b=0,GPIO_SET_b} GPIO_PIN_STATE_b_t;

/**************************************************************
*   GPIO_output_init
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select GPIO pin(s)
*           initial state of the GPIO pin GPIO_CLEAR_b, or GPIO_SET_b
*   Output: None
**************************************************************
*   Function: Pin set to be an output by setting that bit in the DDR
*
*   Caution: Odd naming due to multiple versions of similar functions
***************************************************************/

void GPIO_output_init_in(volatile GPIO_t * port_addr, uint8_t pin_mask, GPIO_PIN_STATE_b_t state);


/**************************************************************
*   GPIO_output_set_value
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select GPIO pin(s)
*           state of the GPIO pin GPIO_CLEAR_b, or GPIO_SET_b
*   Output: None
**************************************************************
*   Function: Sets or clears a GPIO pin based on input value
*   Caution: Can change any PORT reg. bit, not just outputs
***************************************************************/
static inline void GPIO_output_set_value_in(volatile GPIO_t * port_addr, uint8_t pin_mask, GPIO_PIN_STATE_b_t state)
{
    if(GPIO_CLEAR_b==state)
    {
       (port_addr->GPIO_PORT)&=(~pin_mask);    // Clear pin on PORTx to make '0' 
    }
    else
    {
       (port_addr->GPIO_PORT)|=(pin_mask);    // Set pin on PORTx to make '1' 
    }
}


/**************************************************************
*   GPIO_output_get_value
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select GPIO pin(s)
*   Output: state of GPIO pin, GPIO_SET_b or GPIO_CLEAR_b 
**************************************************************
*   Function: Reads a GPIO pin and returns GPIO_SET_b or GPIO_CLEAR_b
*   Caution: Expects to read only one GPIO pin, but no restriction on pin mask
***************************************************************/
static inline GPIO_PIN_STATE_b_t GPIO_output_get_value_in(volatile GPIO_t * port_addr, uint8_t pin_mask)
{
    uint8_t temp8;
    GPIO_PIN_STATE_b_t return_value=GPIO_CLEAR_b;
    temp8=(port_addr->GPIO_PORT)&(pin_mask);
    if(0!=temp8)
    {
        return_value=GPIO_SET_b;
    }
    return return_value;
}

/**************************************************************
*   GPIO_output_toggle_in
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select GPIO pin(s)
*   Output: None
**************************************************************
*   Function: Changes the state of a GPIO pin
*   Caution: Can change any PORT reg. bit, not just outputs
***************************************************************/
static inline void GPIO_output_toggle_in(volatile GPIO_t * port_addr, uint8_t pin_mask)
{
    (port_addr->GPIO_PORT)^=(pin_mask);   
}


#endif /* _GPIO_OUTPUTS_IN_H_ */