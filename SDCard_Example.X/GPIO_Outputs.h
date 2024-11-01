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
*   GPIO_output_init
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select GPIO pin(s)
*   Output: None
**************************************************************
*   Function: Pin set to be an output by setting that bit in the DDR
*
*   Caution: Does not set the pins to a default value
***************************************************************/


void GPIO_output_ctor(gpio_inst_t * const me, volatile GPIO_t * _port_addr, uint8_t _pin_mask, GPIO_PIN_STATE_t _state);

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

static inline void GPIO_output_toggle_value(gpio_inst_t * const me)
{
    (me->port_addr->GPIO_PORT)^=(me->pin_mask);   
}

// Inline function to initalize a GPIO pin as an output
static inline void GPIO_output_init_2(volatile GPIO_t * addr, uint8_t pinmask) {
    addr -> GPIO_DDR |= pinmask; // set pin direction as output
    addr -> GPIO_PORT |= pinmask; // set PORT to OFF as default
}

// Inline function to set the output value of a GPIO pin
static inline void GPIO_output_set_value_2(volatile GPIO_t * addr, uint8_t pinmask, uint8_t value) {
    if (value) {
        addr -> GPIO_PORT |= pinmask; // set pin to high
    }
    else {
        addr -> GPIO_PORT &= ~pinmask; // set pin to low
    }
}



#endif /* _GPIO_OUTPUTS_H_ */