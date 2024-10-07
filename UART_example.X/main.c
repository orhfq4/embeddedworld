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
#include "LEDS.h"
#include "UART.h"
#include "UART_Print.h"
#include "print_memory.h"
#include <avr/pgmspace.h>
#include <stdio.h>

const char string_name[15] PROGMEM = "Hello World!\n\r"; // uses copy_string_to_buffer to translate Flash to SRAM
const char members[] = "Alice, Bob, Charlie, David, Eve"; // 32 characters including commas and spaces to test print_memory function

int main(void)
{
	// Initialize the LED outputs
    LED_ctor(&led0, LED0_PORT, LED0_PIN, LED_OFF, ACTIVE_LOW);
    
    // Initialize the UART
    UART_Init(UART1, 9600);
    
    // Import the print buffer
    char *print_buffer;
    print_buffer = export_print_buffer();
    
    // transmitting string using sprintf
    sprintf(print_buffer, "Hello UART World!");
    UART_transmit_string(UART1, print_buffer, sizeof(print_buffer) - 1);
    
    // transmitting string using copy_string_to_buffer
    // Copy string from Flash to SRAM and print
    copy_string_to_buffer(string_name, print_buffer, 15); // to ensure that the string is copied from FLASH to SRAM
    UART_transmit_string(UART1, print_buffer, sizeof(print_buffer) - 1);
    
    // Call print_memory to print the string (length is 32)
    print_memory((uint8_t *)members, sizeof(members));  // Cast to uint8_t pointer and pass size
    
    while (1) 
    {
        // Blink LED0
		LED_set_value(&led0, LED_ON);
		_delay_ms(50);
		LED_set_value(&led0, LED_OFF);
		_delay_ms(450);
        
        // Transmit the character 'U'
        UART_Transmit(UART1, 0x55);  // ASCII character 'U' (0x55)

        // Add a delay of 0.5 to 1 second
        _delay_ms(500);  // Adjust the delay as needed
	
    }
}
