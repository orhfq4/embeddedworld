/*
 * Hello_Embedded_World.c
 *
 * Created: 8/21/2020 5:26:08 PM
 * Author : Roger Younger
 */ 

/******************************************************************************
*   This application blinks the LEDs (LED0, LED1, LED2, and LED3) on and then
*   off to demonstrate the execution time of various methods of GPIO control.
*
*******************************************************************************/

#include "peripherals.h"
#include "board.h"
#include <util/delay.h>



int main(void)
{
	// initialize PC7 as an output set to '1' (LED0) (off)
    PORTC|=LED0_PIN;
    DDRC|=LED0_PIN;
    // initialize PB3 as an output set to '1' (LED1) (off)
    PORTB|=LED1_PIN;
    DDRB|=LED1_PIN;
    // initialize PE4 as an output set to '1' (LED2) (off)
    PORTE|=LED2_PIN;
    DDRE|=LED2_PIN;
    // initialize PA7 as an output set to '1' (LED3) (off)
    PORTA|=LED3_PIN;
    DDRA|=LED3_PIN;
    
    while (1) 
    {
		// Blink LED0
        PORTC&=(~LED0_PIN);
		_delay_ms(1000);
        PORTC|=LED0_PIN;
		_delay_ms(1000);
		
		
	    // Blink LED1
        PORTB&=(~LED1_PIN);
		_delay_ms(1000);
        PORTB|=LED1_PIN;
		_delay_ms(1000);
		
		// Blink LED2
		PORTE&=(~LED2_PIN);
		_delay_ms(1000);
        PORTE|=LED2_PIN;
		_delay_ms(1000);
        
        // Blink LED3
		PORTA&=(~LED3_PIN);
		_delay_ms(1000);
        PORTA|=LED3_PIN;
		_delay_ms(1000);
	
    }
}






