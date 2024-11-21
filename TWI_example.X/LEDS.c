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



void LED_ctor(led_inst_t * const me, volatile GPIO_t * _port_addr, 
                                  uint8_t _pin_mask, led_state_t _state,
                                  led_polarity_t _polarity)
{
    GPIO_output_ctor(&me->super, _port_addr, _pin_mask, (_state^_polarity));
    me->led_polarity=_polarity;
}

void LED_set_value(led_inst_t * const me, led_state_t _state)
{
        GPIO_output_set_value(&me->super,((_state)^(me->led_polarity)));
}

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

void LED_toggle_value(led_inst_t * const me)
{
    GPIO_output_toggle_value(&me->super);
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
