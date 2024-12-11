/*
 * GPIO_Inputs.c
 *
 * Created: 6/30/2020 11:32:36 AM
 *  Author: Roger Younger
 */ 

#include "peripherals.h"
#include "GPIO_Inputs.h"

/**************************************************************
*   GPIO_input_init
*   Inputs: pointer to a GPIO port struct, 
*           pin_mask to select a GPIO pin,
*           pullup set to PU_ENABLE or PU_DISABLE 
*   Output: None
**************************************************************
*   Function: Pin set to be an input by clearing that bit in the DDR
*             Pull-up enabled by setting that bit in the PORT reg.
*
*   Caution: Must use the defined constants PU_ENABLE, PU_DISABLE
***************************************************************/
void GPIO_input_ctor(input_inst_t * const me, volatile GPIO_t * _port_addr, uint8_t _pin_mask, PU_STATE_t _pu_state)
{
    me->port_addr=_port_addr;
    me->pin_mask=_pin_mask;
    // Initialize the GPIO pin
   if(PU_ENABLED==_pu_state)
   {    
      me->port_addr->GPIO_PORT|=_pin_mask;
   }
   else 
   {
      me->port_addr->GPIO_PORT&=~(_pin_mask);
   }   
   me->port_addr->GPIO_DDR&=~(_pin_mask);

}

void GPIO_input_set_pullup(input_inst_t * const me, PU_STATE_t _pu_state)
{
    if(PU_DISABLED==_pu_state)
    {
       (me->port_addr->GPIO_PORT)&=(~(me->pin_mask));    // Clear pin on PORTx to make '0' 
    }
    else
    {
       (me->port_addr->GPIO_PORT)|=(me->pin_mask);    // Set pin on PORTx to make '1' 
    }
}

/**************************************************************
*   GPIO_read_input
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select a GPIO pin
*   Output: State of input pin (0 or 1)
**************************************************************
*   Function: Checks the value of an input pin and returns that value   
*
*   Caution: Intended to work with only one pin, output is 0 or 1
*            Will work with multiple pins, but all must be 0 to get output=0  
***************************************************************/


