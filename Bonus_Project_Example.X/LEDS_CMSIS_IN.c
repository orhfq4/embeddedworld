/*
 * LEDS.c
 *
 * Created: 6/30/2020 11:32:36 AM
 *  Author: Roger Younger
 */ 

#include "board.h"
#include "GPIO_Outputs_CMSIS_IN.h"
#include "LEDS_CMSIS_IN.h"

/**************************************************************
*   LEDS_init
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select GPIO pin(s)
*           active selects when LED is on(active), ACTIVE_HIGH or ACTIVE_LOW
*   Output: None
**************************************************************
*   Function: Switches the LED off (inactive)
*             Enables the GPIO pin(s) as output(s)
*   Caution: Must use the defined constants: ACTIVE_HIGH or ACTIVE_LOW
***************************************************************/

void LEDS_init_in(volatile GPIO_t * port_addr, uint8_t pin_mask, led_state_b_t state, led_polarity_b_t polarity)
{
	//Set Port Pin to be an output with initial value '1'
	GPIO_output_init_in(port_addr,pin_mask,(state^polarity));
}

/*******************************************************************************
*    This section uses conditional execution to select the correct function
*    based on the defined constants ACTIVE_LOW or ACTIVE_HIGH
********************************************************************************/

/******* Comment out the other definitions of LEDS_on and LEDS_off to use these ****/

/**************************************************************
*   LEDS_on
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select GPIO pin(s)
*           active selects when LED is on(active), ACTIVE_HIGH or ACTIVE_LOW
*   Output: None
**************************************************************
*   Function: Switches the selected LEDs on (active)
*          
*   Caution: Must use the defined constants: ACTIVE_HIGH or ACTIVE_LOW
*            Alternative version below eliminates the if for faster execution
***************************************************************/

__attribute__((optimize("O0"))) void LED_set_state_in(volatile GPIO_t * port_addr, uint8_t pin_mask, led_state_b_t state, led_polarity_b_t polarity)
{	
		GPIO_output_set_value_in(port_addr,pin_mask,(state^polarity)); 
}

/**************************************************************
*   LEDS_off
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select GPIO pin(s)
*           active selects when LED is on(active), ACTIVE_HIGH or ACTIVE_LOW
*   Output: None
**************************************************************
*   Function: Switches the selected LEDs off (inactive)
*
*   Caution: Must use the defined constants: ACTIVE_HIGH or ACTIVE_LOW
*            Alternative version below eliminates the if for faster execution
***************************************************************/

led_state_b_t LED_get_state_in(volatile GPIO_t * port_addr, uint8_t pin_mask, led_polarity_b_t polarity)
{
	uint8_t temp8;
    led_state_b_t return_value=LED_OFF_b;
    temp8=(uint8_t)GPIO_output_get_value_in(port_addr,pin_mask);
    if(0!=(temp8^(uint8_t)polarity))
    {
        return_value=LED_ON_b;
    }
    return return_value;
}


void LED_toggle_in(volatile GPIO_t * port_addr, uint8_t pin_mask)
{
    GPIO_output_toggle_in(port_addr,pin_mask);
}

/*******************************************************************************
*    This section uses conditional compilation to select the correct function 
*    based on the defined constant LED_ACTIVE_LOW or LED_ACTIVE_HIGH          
********************************************************************************/

/******* Comment out the previous definitions of LEDS_on and LEDS_off to use these ****/

//#define LED_ACTIVE_LOW     // uncomment the correct LED ACTIVE STATE 
  ////#define LED_ACTIVE_HIGH   
///**************************************************************
//*   LEDS_on
//*   Inputs: pointer to a GPIO port struct,
//*           pin_mask to select GPIO pin(s)
//*           active selects when LED is on(active), ACTIVE_HIGH or ACTIVE_LOW
//*   Output: None
//**************************************************************
//*   Function: Switches the selected LEDs on (active)
//*
//*   Caution: Must use the defined constants: ACTIVE_HIGH or ACTIVE_LOW
//*            Alternative version below eliminates the if for faster execution
//***************************************************************/
//
//void LEDS_on(volatile GPIO_t * port_addr, uint8_t pin_mask, uint8_t active)
//{
//#ifdef LED_ACTIVE_LOW
		//GPIO_output_clear(port_addr,pin_mask);
//#else // LED_ACTIVE_HIGH
		//GPIO_output_set(port_addr,pin_mask);
//#endif
//}
//
///**************************************************************
//*   LEDS_off
//*   Inputs: pointer to a GPIO port struct,
//*           pin_mask to select GPIO pin(s)
//*           active selects when LED is on(active), ACTIVE_HIGH or ACTIVE_LOW
//*   Output: None
//**************************************************************
//*   Function: Switches the selected LEDs off (inactive)
//*
//*   Caution: Must use the defined constants: ACTIVE_HIGH or ACTIVE_LOW
//*            Alternative version below eliminates the if for faster execution
//***************************************************************/
//
//void LEDS_off(volatile GPIO_t * port_addr, uint8_t pin_mask, uint8_t active)
//{
//#ifdef LED_ACTIVE_LOW
     //GPIO_output_set(port_addr,pin_mask);
//#else // LED_ACTIVE_HIGH
     //GPIO_output_clear(port_addr,pin_mask);
//#endif
//}
