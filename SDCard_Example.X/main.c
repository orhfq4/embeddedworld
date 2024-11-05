/*
 * SD Card Example.c
 *
 * Created: 8/21/2020 5:26:08 PM
 * Author : Roger Younger
 */ 

/***********************************************************************************
*   This application initializes LEDs, UART1, and SPI0.  The SPI is used to
*   initialize and communicate with an SD Card.  The user can enter a block
*  mnumber of the SD Card and the contents will be printed using UART1. 
*
************************************************************************************/

// (7)

#include "peripherals.h"
#include "board.h"
#include <util/delay.h>
#include "LEDS.h"
#include "UART.h"
#include "UART_Print.h"
#include "print_memory.h"
#include "Long_Serial_In.h"
#include "SPI.h"
#include "SDCard.h"
#include <avr/pgmspace.h>
#include <stdio.h>

#define SPI_CLOCK_FREQ_400KHz (400000)
#define SPI_CLOCK_FREQ_4MHz (4000000)
#define SD_CS_port (PB)
#define SD_CS_pin (1<<4)

const char SD_Header[28] PROGMEM = {"SD Initialization Program\n\r\0"};
const char LSI_Prompt[16] PROGMEM = {"Enter block #: "};
const char Complete[9] PROGMEM = {"  OK!\n\r\0"};
const char High_Cap[15] PROGMEM = {"High Capacity\0"};
const char Stnd_Cap[19] PROGMEM = {"Standard Capacity\0"};

uint8_t buffer1_g[512];
uint8_t buffer2_g[512];


int main(void)
{
    //uint8_t input,status,SD_type;
    uint32_t block_number;
    char *buffer;
    
	// Initialize the LED outputs
    LED_ctor(&led0, LED0_PORT, LED0_PIN, LED_OFF, ACTIVE_LOW);
   
    UART_init(UART1,9600);
    
    buffer=export_print_buffer();
    
    
    copy_string_to_buffer(SD_Header,buffer,0);
    UART_transmit_string(UART1,buffer,0);
    
    LED_set_value(&led0, LED_ON);
	_delay_ms(200);
	LED_set_value(&led0, LED_OFF);
    
    
	//*** SPI initialization for SD Card initialization (400KHz max)
    if (SPI_Master_Init(SPI0, SPI_CLOCK_FREQ_400KHz) != 0) {
        UART_transmit_string(UART1, "SPI Init Error (400KHz)\n\r", 0);
        LED_set_value(&led0, LED_ON);  // Light LED to indicate error
    }
    else {
        UART_transmit_string(UART1, "SPI Init Success! (400KHz)\n\r", 0);
    }
    
    //*** SD Card initialization
	sd_card_init(SPI0);
    UART_transmit_string(UART1, "SD CARD INIT COMPLETE\n\r", 0);
    
    
    //*** SPI initialization for SD Card communication (4MHHz max)
	if (SPI_Master_Init(SPI0, SPI_CLOCK_FREQ_4MHz) != 0) {
        UART_transmit_string(UART1, "SPI Init Error (4MHz)\n\r", 0);
        LED_set_value(&led0, LED_ON);  // Light LED to indicate error
    }
    else {
        UART_transmit_string(UART1, "SPI Init Success! (4MHz)\n\r", 0);
    }
    
        
    while (1)
    {
        
        UART_transmit_string(UART1, "Entering While loop in main...\n\r", 0); // Checkpoint print
        // Prompt user for a block number
        copy_string_to_buffer(LSI_Prompt, buffer,0);
        UART_transmit_string(UART1, buffer, 0);
        block_number = long_serial_input(UART1);  // Get block number from user
        adjust_block_number(block_number); // Send CMD16
        SD_CS_inactive(); // set /CS to 0
        send_command(SPI0, 17, block_number); // send CMD17 to read the block
        
        // Read 512 bytes from the block into buffer1_g
        if (read_block(SPI0, buffer1_g, 512) == 0) {
            // Block read successfully, print the block contents
            print_memory(buffer1_g, 512);
        } else {
            // Error in reading the block, print error message
            UART_transmit_string(UART1, "Error reading block\n\r", 0);
        }
        
        SD_CS_active(); // set /CS to 1
    
        _delay_ms(500); // Delay to observe output
        
		
    }
}






