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
#include "Read_Values.h"
#include "Drive_Values.h"
#include "Directory_Functions.h"
#include "File_System.h"

const char SD_Header[28] PROGMEM = {"SD Initialization Program\n\r\0"};
const char LSI_Prompt[16] PROGMEM = {"Enter block #: "};
const char Complete[9] PROGMEM = {"  OK!\n\r\0"};
const char High_Cap[15] PROGMEM = {"High Capacity\0"};
const char Stnd_Cap[19] PROGMEM = {"Standard Capacity\0"};
const char EnterNum[29] PROGMEM = {"Enter desired entry number\n\r\0"};
const char entryFeedback[18] PROGMEM = {"Entry too large\n\r\0"};
const char error_message[13] PROGMEM = {"error. Goodbye :)\n\r\0"};



uint8_t buffer1_g[512];
//uint8_t buffer2_g[512];


int main(void)
{
    uint8_t status,SD_type;
    uint32_t temp32 = 0;
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

    
    //******************** Calling the mount drive function (Question 8) *****************
    //Comment out for debugging:  
    FS_values_t* drive = export_drive_values();    
    uint8_t error_flag = mount_drive(drive, buffer1_g);
    
    //******************(Question 9) Super Loop **************************************
    uint16_t  directoryEntries = 0;
    uint32_t  userInput = 0;
    uint8_t error_status = 0x00;
    uint32_t curr_dir;
    error_flag = 0;
    curr_dir = drive->FirstDataSec;
    if (error_flag == 0){ // Check to see if mount drive returned an error
        while(error_status == 0){      
            uint8_t repeat = 1; // Variable to repeat loop to get to a file
            do{
                  //*************** Part A ***********************************
                // Call print directory function with the current direct variable
                directoryEntries = print_directory(curr_dir, buffer1_g); // USING BUFFER 1 NOW :D
                //Prompt user for entry number
                uint8_t error_check = 0;
                do{
                   copy_string_to_buffer(EnterNum,buffer,0);
                   UART_transmit_string(print_port,buffer,0);
                   temp32=long_serial_input(print_port); // Waiting for input
                   // Error check to see if entered number is too large
                   if (temp32 > directoryEntries){ // Entry is too large!
                       copy_string_to_buffer(entryFeedback,buffer,0);
                       UART_transmit_string(print_port,buffer,0);
                   }
                   else{
                       error_check = 1; // User entry is correct size, exit loop :D
                       userInput = temp32; // for clarity
                   }
                }while(error_check == 0);
                // Then use as input parameter to read_directory function
                uint32_t returnCluster = 0;
                
                returnCluster = read_dir_entry(curr_dir, userInput, buffer1_g);
                
               
                                
                if((returnCluster & (1UL << 31)) == 0){ //
                    if(returnCluster & (1UL << 28)){ // Check Bit 28 for directory of file
                        // Bit 28 == 1, must be directory
                        repeat = 1;
                        returnCluster &= 0x0FFFFFFF;
                        curr_dir = First_Sector(drive, returnCluster); // needs to be set to a variable
 
                        // Needs to actually enter the subdirectory ****************
                    }
                    else{ // Bit 28 == 0, must be a file
                        repeat = 0; 
                        
                        // Exits loop to read file
                        
                    }
                }
                else{  //There is an error :(
                    error_status = 1; //  Throw an error to exit loop
                    copy_string_to_buffer(error_message,buffer,0);
                    UART_transmit_string(print_port,buffer,0);
                }  
            }while((repeat == 1) && (error_status == 0x00));
            
            if(error_status == 0x00){
                uint32_t InputCluster = read_dir_entry(curr_dir, userInput, buffer1_g);
                open_file(drive, InputCluster, buffer1_g); // This is fine :)
                
            }
            else{
                // error Bit 31 signals error
            }
        }
    }
    else{
        // Error with the mount drive function
        copy_string_to_buffer("Mount drive failed",buffer,0);
        UART_transmit_string(print_port,buffer,0);
    }
    
    return 0;
}