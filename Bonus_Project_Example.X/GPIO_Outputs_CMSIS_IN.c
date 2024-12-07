/*
 * GPIO_Outputs.c
 *
 * Created: 6/30/2020 11:32:36 AM
 *  Author: Roger Younger
 */ 

#include "board.h"
#include "GPIO_Outputs_CMSIS_IN.h"

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

void GPIO_output_init_in(volatile GPIO_t * port_addr, uint8_t pin_mask, GPIO_PIN_STATE_b_t state)
{
	// Set or clear PORT register for initial value
    if(GPIO_CLEAR_b==state)
    {
       (port_addr->GPIO_PORT)&=(~pin_mask);    // Clear pin on PORTx to make '0' 
    }
    else
    {
       (port_addr->GPIO_PORT)|=(pin_mask);    // Set pin on PORTx to make '1' 
    }
	(port_addr->GPIO_DDR)|=(pin_mask);    // Set DDRx to make port pin an output
}















