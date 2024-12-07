/*
 * Hello_Embedded_World.c
 *
 * Created: 8/21/2020 5:26:08 PM
 * Author : Roger Younger
 */ 

/***********************************************************************************
*   The application is to use switches (SW0, SW1, SW2, and SW3) to control the
*   respective LEDs (LED0, LED1, LED2, and LED3).  Each time a switch is pressed
*   the LED cycles through three possible states (OFF, ON, and FLASHING).  The LED
*   will change from FLASHING back to OFF with one switch press.
*
*   A sw_state variable for each LED is used to determine the state.  Each time the
*   corresponding switch is pressed, the sw_state advances to the next state.
*   An additional state is used to provide time for the user to release the switch
*   between FLASHING and OFF and automatically advances after a short delay.
*
*   Problems: The use of a delay is inefficient.  The switch can only be read when not in
*   a delay, so the switch needs to be pressed when exiting the flashing loop.  User
*   feedback of the LED switching off is used to let the user know when to release the switch.
************************************************************************************/

#include "peripherals.h"
#include "board.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LEDS.h"
#include "LEDS_CMSIS_IN.h"


int main(void)
{
    // initialize PB3 as an output set to '1' (LED1)
    LED_ctor(&led1, LED1_PORT, LED1_PIN, LED_OFF, ACTIVE_LOW);
    // initialize PE4 as an output set to '1' (LED2)
    LED_ctor(&led2, LED2_PORT, LED2_PIN, LED_OFF, ACTIVE_LOW);
    // initialize PA7 as an output set to '1' (LED3)
    LED_ctor(&led3, LED3_PORT, LED3_PIN, LED_OFF, ACTIVE_LOW);
    while (1) 
    {		
		
        LED_set_value(&led1, LED_ON);
		_delay_ms(1000);
		LED_set_value(&led1, LED_OFF);
		_delay_ms(1000);
		
		
        LED_set_value(&led2, LED_ON);
		_delay_ms(1000);
		LED_set_value(&led2, LED_OFF);
		_delay_ms(1000);
		
	
		LED_set_value(&led3, LED_ON);
		_delay_ms(1000);
		LED_set_value(&led3, LED_OFF);
		_delay_ms(1000);
	
    }
}






