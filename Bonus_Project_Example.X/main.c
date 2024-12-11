/*
 * Hello_Embedded_World.c
 *
 * Created: 8/21/2020 5:26:08 PM
 * Author : Roger Younger
 * Group: Jacob Byers, Owen Hancock, Joshua Perkins
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

//initializing state machine and variables

//Pressing switch should move the LED's state to move between on and off.
//Holding the switch for one second should cause the LED to change to one of the FLASH states
//The move between flash states is based on time and is up to us to decide on how much time. 
//Intended that the user will press and hold the switch for one second, and the LED will start flashing
//When the switch is released when it done being held, the LED will continue to flash.
//Pressing the switch will cause the LED to move from FLASH mode back to the ON or OFF state.
typedef enum {LED_OFF_SM, LED_ON_SM, FLASH_ON_SM, FLASH_OFF_SM} led_state_t;

//When the switch is detected as pressed, move to debounce_p.
//after 50 - 75 ms, if the switch is still pressed, move to pressed.
//If the switch is released before one second has elapsed, then move to P_ACTION. 
//P_ACTION causes the change in the LED state machine from on to off or off to on
//the LED state machine can switch to DEBOUNCE_R to prevent multiple actions from taking place.
//if the switch is, instead, held for one second, move to the HELD state.
//HELD will cause the LED state machine to move to the LED FLASH mode. 
//The LED state machine can change the state to HELD_HOLD to prevent multiple actions based on HELD.
//Once the switch is released, then move to the DEBOUNCE_R state.
//After 25 - 50 ms, if the switch is still released, move to NOT_PRESSSED.
typedef enum {NOT_PRESSED, DEBOUNCE_P, PRESSED, P_ACTION, HELD, HELD_HOLD, DEBOUNCE_R} sw_state_t;

int main(void)
{
    sei();
    
    // initialize PB3 as an output set to '1' (LED1)
    LED_ctor(&led1, LED1_PORT, LED1_PIN, LED_OFF, ACTIVE_LOW);
    // initialize PE4 as an output set to '1' (LED2)
    LED_ctor(&led2, LED2_PORT, LED2_PIN, LED_OFF, ACTIVE_LOW);
    // initialize PA7 as an output set to '1' (LED3)
    LED_ctor(&led3, LED3_PORT, LED3_PIN, LED_OFF, ACTIVE_LOW);
    // initialize switches, not sure why SW_NOT_PRESSED doesn't work/register on my end...
    sw_ctor(&sw1, SW1_PORT, SW1_PIN, SW_NOT_PRESSED, ACTIVE_HIGH);
    sw_ctor(&sw2, SW2_PORT, SW2_PIN, SW_NOT_PRESSED, ACTIVE_HIGH);
    sw_ctor(&sw3, );

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






