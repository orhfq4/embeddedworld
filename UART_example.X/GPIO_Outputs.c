/*
 * GPIO_Outputs.c
 *
 * Created: 6/30/2020 11:32:36 AM
 *  Author: Roger Younger
 */ 

#include "board.h"
#include "GPIO_Outputs.h"


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
void GPIO_output_ctor(gpio_inst_t * const me, volatile GPIO_t * _port_addr, uint8_t _pin_mask, GPIO_PIN_STATE_t _state)
{
    me->port_addr=_port_addr;
    me->pin_mask=_pin_mask;
    // Initialize the GPIO pin
   if(GPIO_CLEAR!=_state)
   {    
      me->port_addr->GPIO_PORT|=_pin_mask;
   }
   else 
   {
      me->port_addr->GPIO_PORT&=~(_pin_mask);
   }   
   me->port_addr->GPIO_DDR|=_pin_mask;

}










