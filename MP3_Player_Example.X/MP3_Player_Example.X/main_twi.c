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
#include "SPI.h"
#include "SDCard.h"
#include "OLED.h"
#include "Long_Serial_In.h"
#include "TWI.h"
#include "STA013_Config.h"
#include <avr/pgmspace.h>
#include <stdio.h>

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
    uint8_t twi_read[10];
    uint32_t temp_c, temp_f;
	// Initialize the LED outputs
    LED_ctor(&led0, LED0_PORT, LED0_PIN, LED_OFF, ACTIVE_LOW);
    LED_ctor(&led1, LED1_PORT, LED1_PIN, LED_OFF, ACTIVE_LOW);
    LED_ctor(&led2, LED2_PORT, LED2_PIN, LED_OFF, ACTIVE_LOW);
    LED_ctor(&led3, LED3_PORT, LED3_PIN, LED_OFF, ACTIVE_LOW);
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
    
    TWI_master_init(TWI1,50000UL);
    
    STA013_Init();
    
    
    while (1) 
    {
		input=TWI_master_receive(TWI1,TEMP_SENSOR_ADDR,0x00,1,2,twi_read);
        temp_c=(((uint32_t)twi_read[0])<<8)+(uint32_t)twi_read[1];
        temp_f=((temp_c*461)>>8)+8320;
        temp_f=temp_f>>8;
        sprintf(buffer,"Temp=%u\n\r",(uint8_t)temp_f);
        OLED_clear_line(OLED_SPI_Port,OLED_LINE_2);
        OLED_set_line (OLED_SPI_Port,OLED_LINE_2);
        OLED_transmit_string(OLED_SPI_Port,buffer,0);
        copy_string_to_buffer(LSI_Prompt,buffer,0);
		UART_transmit_string(print_port,buffer,0);
		temp32=long_serial_input(print_port);
		sprintf(buffer," %lu \n\r",temp32);
		UART_transmit_string(print_port,buffer,0);
		SD_type=Return_SD_Card_Type();
		temp32=(temp32<<SD_type);
		LED_set_value(&led0, LED_ON);
		SPI_CS_set_value(&sd_cs, CS_ACTIVE);
		Send_Command(CMD17,temp32);
		Read_Block(512,buffer1_g);
		LED_set_value(&led0, LED_OFF);
		SPI_CS_set_value(&sd_cs, CS_INACTIVE);
		print_memory(buffer1_g,512);  
        
        
	
    }
}






