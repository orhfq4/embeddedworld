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
#include "File_System.h"
#include "TWI.h"
#include "STA013_Config.h"
#include "Play_Song.h"
#include <avr/interrupt.h>

const char SD_Header[28] PROGMEM = {"SD Initialization Program\n\r\0"};
const char LSI_Prompt[16] PROGMEM = {"Enter block #: "};
const char Complete[9] PROGMEM = {"  OK!\n\r\0"};
const char High_Cap[15] PROGMEM = {"High Capacity\0"};
const char Stnd_Cap[19] PROGMEM = {"Standard Capacity\0"};

#define DATA_REQ (1<<6)
#define MP3_timeout_ms (12)
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
    TWI_master_init(TWI1,50000);
    STA013_Init();
    mount_drive(buffer1_g);
    FS_values_t * drive;
    drive=export_drive_values();
    
    
    /*************** Simple Embedded OS Initialization***********************/
    // Enable pull-up resistor on DATA_REQ pin
     //Pull_Up_Enable(PC, DATA_REQ);
    GPIO_input_set_pullup(PC, PU_ENABLED);    
   
    // Initialize input on DATA_REQ pin
    //Input_Init(PC, DATA_REQ);
    GPIO_input_ctor(&sta013_data_req, PC, DATA_REQ, PU_ENABLED);
    
    // Initialize global variables
    uint32_t cluster_g = begin_cluster; //unsure what begin_cluster is? Or how to find it?
    uint32_t sector_g = first_sector(begin_cluster); // Are these initialized as globals? (In main?))
    uint32_t num_sectors_g = 0;

    // Read the first two sectors into the global buffers
    read_sector((sector_g + num_sectors_g), drive->BytesPerSec, buffer1_g);
    num_sectors_g++;
    uint32_t index1_g = 0;
    read_sector((sector_g + num_sectors_g), drive->BytesPerSec, buffer2_g);
    num_sectors_g++;
    
    uint32_t index2_g = 0;

    // Initialize the state variable
    play_state_g=Data_Send_1;
    // I use this variable to exit playing the song.
    // It must be declared as volatile, since it is changed in the ISR
    volatile uint8_t play_status_g=1;
    // Set up Timer 2 to cause the interrupt
    //Timer2_Interrupt_Init(MP3_timeout_ms); // Do we have to make a timer init?
    sEOS_Init(MP3_timeout_ms);
    // Set the global interrupt enable
    sei();
    // Sleep mode is optional
    /*
    set_sleep_mode(SLEEP_MODE_IDLE);
    while(play_status_g!=0) // Plays until play_status_g==0
    {
    sleep_mode(); //Go to Sleep
    }
    */
    // Clear the global interrupt enable (and stop timer 2) to end
    cli();
    /*************** Simple Embedded OS Initialization above***********************/
    
    uint32_t curr_directory;
    curr_directory=drive->FirstRootDirSec;
    while (1) 
    {
		/*copy_string_to_buffer(LSI_Prompt,buffer,0);
		UART_transmit_string(print_port,buffer,0);
		temp32=long_serial_input(print_port);
		sprintf(buffer," %lu \n\r",temp32);
		UART_transmit_string(print_port,buffer,0);
		SD_type=Return_SD_Card_Type();
		temp32=(temp32<<SD_type);
		LED_set_value(&led0, LED_ON);
        read_sector(temp32, 512, buffer1_g);
		LED_set_value(&led0, LED_OFF);
		print_memory(buffer1_g,512);*/  
        uint16_t num_entries;
        uint32_t cluster_num;
        num_entries=print_directory(curr_directory,buffer1_g);
        copy_string_to_buffer(LSI_Prompt,buffer,0);
		UART_transmit_string(print_port,buffer,0);
		temp32=long_serial_input(print_port);
		if(temp32<=num_entries)
        {
            cluster_num=read_dir_entry(curr_directory,temp32,buffer1_g);
            if((cluster_num&(1UL<<28))!=0)
            {
               curr_directory=first_sector(cluster_num&0x0FFFFFFF);
            }
            else
            {
                open_file(cluster_num,buffer1_g);
                play_song(cluster_num);
            } 
        }
        
        
	
    }
}






