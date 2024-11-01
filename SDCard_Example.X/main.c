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

#define SPI_CLOCK_FREQ (400000)

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
    uint32_t temp32;
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
    if (SPI_Master_Init(SPI0, SPI_CLOCK_FREQ) != 0) {
        UART_transmit_string(UART1, "SPI Init Error\n\r", 0);
    }
    else {
        UART_transmit_string(UART1, "SPI Init Success!\n\r", 0);
    }
    
    //*** SD Card initialization
	sd_card_init(SPI0);
    
    
    //*** SPI initialization for SD Card communication (25MHHz max)
	
    uint8_t test_data = 0xAA;   // Example byte to test SPI transfer
    uint8_t received_data;
    while (1) 
    {
	UART_transmit_string(UART1, "Entering loop...\n\r", 0); // Checkpoint print

    
    
    received_data = SPI_receive(SPI0);
    
    // Format and transmit the sent and received data to UART
    sprintf(buffer, "Sent: 0x%02X, Received: 0x%02X\n\r", test_data, received_data);
    UART_transmit_string(UART1, buffer, 0); 
    
    _delay_ms(500); // Delay to observe output
        
    test_data++;
		
    }
}






