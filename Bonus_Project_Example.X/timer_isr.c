
//*** Define timer interrupt service routine
#include "peripherals.h"
#include <avr/interrupt.h>

#define INTERVAL (10)

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

extern uint16_t time_g;
led_state_t led_state1;
sw_state_t sw_state1;
led_state_t led_state2;
sw_state_t sw_state2;
led_state_t led_state3;
sw_state_t sw_state3;
sw_state_t sw_temp;
led_state_t led_temp;

ISR(TIMER2_COMPA_vect)
{
   // Increment time variable for scheduler
   time_g = 0;
    time_g+=INTERVAL;  
   
}

