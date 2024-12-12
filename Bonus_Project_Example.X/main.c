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
//after 50 - 75 ms, if the switch is still pressed, move to PRESSED.
//If the switch is released before one second has elapsed, then move to P_ACTION. 
//P_ACTION causes the change in the LED state machine from on to off or off to on
//the LED state machine can switch to DEBOUNCE_R to prevent multiple actions from taking place.
//if the switch is, instead, held for one second, move to the HELD state.
//HELD will cause the LED state machine to move to the LED FLASH mode. 
//The LED state machine can change the state to HELD_HOLD to prevent multiple actions based on HELD.
//Once the switch is released, then move to the DEBOUNCE_R state.
//After 25 - 50 ms, if the switch is still released, move to NOT_PRESSSED.
typedef enum {NOT_PRESSED_SM, DEBOUNCE_P, PRESSED_SM, P_ACTION, HELD, HELD_HOLD, DEBOUNCE_R} sw_state_t;

int main(void)
{
    sei();
    led_state_t led_state;
    sw_state_t sw_state;
    sw_state_t temp1;
    sw_state_t temp2;
    sw_state_t temp3;
    //variables to determine with LEDs to switch. 0 to not switch, 1 to switch.
    uint8_t l1 = 0;
    uint8_t l2 = 0;
    uint8_t l3 = 0;
    // initialize PB3 as an output set to '1' (LED1)
    LED_ctor(&led1, LED1_PORT, LED1_PIN, LED_OFF, ACTIVE_LOW);
    // initialize PE4 as an output set to '1' (LED2)
    LED_ctor(&led2, LED2_PORT, LED2_PIN, LED_OFF, ACTIVE_LOW);
    // initialize PA7 as an output set to '1' (LED3)
    LED_ctor(&led3, LED3_PORT, LED3_PIN, LED_OFF, ACTIVE_LOW);
    // initialize switches, not sure why SW_NOT_PRESSED doesn't work/register on my end...
    sw_ctor(&sw1, SW1_PORT, SW1_PIN, SW_NOT_PRESSED, ACTIVE_HIGH);
    sw_ctor(&sw2, SW2_PORT, SW2_PIN, SW_NOT_PRESSED, ACTIVE_HIGH);
    sw_ctor(&sw3, SW3_PORT, SW3_PIN, SW_NOT_PRESSED, ACTIVE_HIGH);

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

    while (1) 
    {		
        //functions needed: LED_set_value(led_inst_t, led_state_t), 
        //LED_get_value (let_inst_t), LED_toggle_value(led_inst_t).
        switch (led_state){
            case LED_OFF_SM:
            {
                //use set value to turn off respective l1, l2, l3 LEDS
            }
            case LED_ON_SM:
            {
                //use set value to turn on respective l1, l2, l3 LEDS
            }
            case FLASH_ON_SM:
            {
                //flash whaever LED is dictated to flash
            }
            case FLASH_OFF_SM:
            {
                //flash is off mode, go back to LED off.
            }
        } //end of switch(led_state)
        
//When the switch is detected as pressed, move to DEBOUNCE_P.
//after 50 - 75 ms, if the switch is still pressed, move to PRESSED.
//If the switch is released before one second has elapsed, then move to P_ACTION. 
//P_ACTION causes the change in the LED state machine from on to off or off to on
//the LED state machine can switch to DEBOUNCE_R to prevent multiple actions from taking place.
//if the switch is, instead, held for one second, move to the HELD state.
//HELD will cause the LED state machine to move to the LED FLASH mode. 
//The LED state machine can change the state to HELD_HOLD to prevent multiple actions based on HELD.
//Once the switch is released, then move to the DEBOUNCE_R state.
//After 25 - 50 ms, if the switch is still released, move to NOT_PRESSSED.
        
        //sw_get_value
        switch(sw_state){
            case NOT_PRESSED_SM:
            {
                temp1 = sw_get_value(&sw1);
                temp2 = sw_get_value(&sw2);
                temp3 = sw_get_value(&sw3);
                if(temp1->_state==SW_PRESSED || temp2->_state==SW_PRESSED || temp3->_state==SW_PRESSED){
                    sw_state = DEBOUNCE_P;
                }
                break;
            }
            case DEBOUNCE_P:
            {
                //Switch 1
                _delay_ms(50); //implement using ISR instead?
                temp1=sw_get_value(&sw1);
                temp2=sw_get_value(&sw2);
                temp3=sw_get_value(&sw3);
                if(temp1->_state==SW_PRESSED){
                    sw_state = PRESSED_SM:
                }
                else{
                    sw_state = NOT_PRESSED_SM;
                }
            }
            case PRESSED_SM:
            {
                //use ISR timer interrupt counting
                //incrementing interrupt count, then check for the conditions after
                //if switch released before 1s, send to P_ACTION
                if(temp1->_state==SW_NOT_PRESSED){
                    sw_state = P_ACTION;
                }
                if(count==100){
                    sw_state = HELD;
                }
            }
            case P_ACTION:
            {
                if (l1==1){
                    LED_toggle_value(&led1);
                    led_state = LED_get_value(&led1);
                    sw_state = DEBOUNCE_R;
                }
            }
            case HELD:
            {
                
            }
            case HELD_HOLD:
            {

            }
            case DEBOUNCE_R:
            {

            }
        } //end of switch(sw_state)
    }
}

//d
//questions for younger: do we need a separate switch and led state variables for each switch and led? How do we count ISR interrupts. 



