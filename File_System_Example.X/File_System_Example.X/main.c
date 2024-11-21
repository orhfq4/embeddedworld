/*
 * SD Card Solution
 *
 * Created: 8/21/2020 5:26:08 PM
 * Author : Roger Younger
 */ 

/***********************************************************************************
*   Initializes the SPI to 400KHz, then initializes the SD Card,
*   and then sets the SPI to 10KHz (the max freq. in this system is 8MHz).
*   Once the SD Card is initialized, block can be read by entering the 
*   block number and the print memory function prints the block contents. 
*
*   The OLED display also uses the SPI.  It is initialized for use.
*   The OLED is a graphical display (128x32 pixels).  It is used as a four-line
*   display (LINE0 to LINE3) that can display ASCII strings.  The file
*   OLED char map converts ACII to bit patterns for display.  The OLED print
*   function prints a NULL terminated string or a specified numbers of
*   characters from a string.  
*
*   
************************************************************************************/

#include "peripherals.h"
#include "board.h"
#include <util/delay.h>
#include "LEDS.h"
#include "UART.h"
#include "UART_Print.h"
#include "print_memory.h"
#include "SPI.h"
#include "SDCard.h"
#include "SPI_CS.h"
#include "Long_Serial_In.h"
#include <avr/pgmspace.h>
#include <stdio.h>
#include "OLED.h"
#include "Read_Sector.h"
#include "Drive_Values.h"
#include "Directory_Functions.h"
//#include "File_System.h"

const char SD_Header[28] PROGMEM = {"SD Initialization Program\n\r\0"};
const char LSI_Prompt[16] PROGMEM = {"Enter block #: "};
const char Complete[9] PROGMEM = {"  OK!\n\r\0"};
const char High_Cap[15] PROGMEM = {"High Capacity\0"};
const char Stnd_Cap[19] PROGMEM = {"Standard Capacity\0"};

uint8_t buffer1_g[512];
uint8_t buffer2_g[512];


int main(void)
{
    uint8_t input,status,SD_type;
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
    
    
	//*** SPI initialization for SD Card
	status=SPI_master_init(SPI0,400000UL);
    _delay_ms(1000);
	if(status!=no_errors)
	{
		LED_set_value(&led1, LED_ON);
        while(1);
	}
    OLED_init(OLED_SPI_Port);
	OLED_set_line (OLED_SPI_Port,OLED_LINE_0);
	copy_string_to_buffer(SD_Header,buffer,0);
	OLED_transmit_string(OLED_SPI_Port,buffer,7);
	status=SD_Card_Init();
	if(status!=no_errors)
	{
		LED_set_value(&led2, LED_ON);
        while(1);
		
	}
	SPI_master_init(SPI0,10000000UL);
    
    copy_string_to_buffer(Complete,buffer,0);
	OLED_transmit_string(OLED_SPI_Port,buffer,0);
    
    
    OLED_clear_line(OLED_SPI_Port,OLED_LINE_1);
    OLED_set_line (OLED_SPI_Port,OLED_LINE_1);
    SD_type=Return_SD_Card_Type();
    if(SD_type==Standard_Capacity)
    {    
	   copy_string_to_buffer(Stnd_Cap,buffer,0);
	   OLED_transmit_string(OLED_SPI_Port,buffer,0);
    }
    else
    {    
	   copy_string_to_buffer(High_Cap,buffer,0);
	   OLED_transmit_string(OLED_SPI_Port,buffer,0);
    }
    
    
    while (1) 
    {
		copy_string_to_buffer(LSI_Prompt,buffer,0);
		UART_transmit_string(print_port,buffer,0);
		temp32=long_serial_input(print_port);
		sprintf(buffer," %lu \n\r",temp32);
		UART_transmit_string(print_port,buffer,0);
		SD_type=Return_SD_Card_Type();
		temp32=(temp32<<SD_type);
		LED_set_value(&led0, LED_ON);
        
        //*** This is for testing read_sector when implemented ****
        read_sector(temp32, 512, buffer1_g);
        
        
		LED_set_value(&led0, LED_OFF);
		print_memory(buffer1_g,512);  
        
        
        
	
    }
}





