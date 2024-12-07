/*
 * LEDS.h
 *
 * Created: 6/30/2020 11:42:34 AM
 *  Author: youngerr
 */ 


#ifndef _LEDS_IN_H_
#define _LEDS_IN_H_

#include "GPIO_Outputs_CMSIS_IN.h"


typedef enum {LED_ON_b=0,LED_OFF_b} led_state_b_t;
typedef enum {ACTIVE_LOW_b=0,ACTIVE_HIGH_b} led_polarity_b_t;




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

void LEDS_init_in(volatile GPIO_t * port_addr, uint8_t pin_mask, led_state_b_t state, led_polarity_b_t polarity);

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
***************************************************************/
__attribute__((optimize("O0"))) void LED_set_state_in(volatile GPIO_t * port_addr, uint8_t pin_mask, led_state_b_t state, led_polarity_b_t polarity);

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
***************************************************************/
led_state_b_t LED_get_state_in(volatile GPIO_t * port_addr, uint8_t pin_mask, led_polarity_b_t polarity);

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
***************************************************************/
void LED_toggle_in(volatile GPIO_t * port_addr, uint8_t pin_mask);



#endif /* _LEDS_IN_H_ */