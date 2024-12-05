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



uint8_t buffer1_g[512];
uint8_t buffer2_g[512];


int main(void)
{
    uint8_t status,SD_type;
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
    
    
    
    //******************** (for testing read_value functions) ****************
    
    // Example array for testing (little-endian representation)
    uint8_t data[] = {
        0x01, 0x02, 0x03, 0x04, // 32-bit value = 0x04030201
        0x05, 0x06,             // 16-bit value = 0x0605
        0x07                    // 8-bit value = 0x07
    };

    // Read and print 8-bit, 16-bit, and 32-bit values
    uint8_t val8 = read_value_8(6, data); // Offset 6: 8-bit value
    uint16_t val16 = read_value_16(4, data); // Offset 4: 16-bit value
    uint32_t val32 = read_value_32(0, data); // Offset 0: 32-bit value

    // Print values
    //printf("8-bit value: %u (0x%X)\n", val8, val8);
    //printf("16-bit value: %u (0x%X)\n", val16, val16);
    //printf("32-bit value: %lu (0x%lX)\n", val32, val32);
    
    //******************** Calling the mount drive function (Question 8) *****************
    //Comment out for debugging:
        //What to pass for array? Not used in function?    
    FS_values_t* drive = export_drive_values();    
    uint8_t error_flag = mount_drive(drive, buffer1_g);
    /*
    // ASK TO SEE IF WE USE THIS, IN OTHER LOOP?
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
        
        //This is for testing read_sector when implemented ****
        read_sector(temp32, 512, buffer1_g);
        
        
		LED_set_value(&led0, LED_OFF);
		print_memory(buffer1_g,512);  
        
        
        
	
    }
    */
    
    
    //******************(Question 9) Super Loop **************************************
    uint16_t  directoryEntries = 0;
    uint32_t  userInput = 0;
    uint8_t error_status = 0x00;
    
    error_flag = 0;
    if (error_flag == 0){ // Check to see if mount drive returned an error
        while(1){      
            uint8_t repeat = 1; // Variable to repeat loop to get to a file
            
            do{
                  //*************** Part A ***********************************
                // Call print directory function with the current direct variable
                uint32_t SecNum = drive->FirstDataSec;
                directoryEntries = print_directory(16384, buffer2_g); // USING BUFFER 1 NOW :D
                //Prompt user for entry number

                uint8_t error_check = 0;
                do{
                   copy_string_to_buffer(EnterNum,buffer,0);
                   UART_transmit_string(print_port,buffer,0);
                   temp32=long_serial_input(print_port); // Waiting for input
                   sprintf(buffer," %lu \n\r",temp32);
                   UART_transmit_string(print_port,buffer,0); // Printing the input
                   // Error check to see if entered number is too large
                   if (temp32 > directoryEntries){ // Entry is too large!
                       copy_string_to_buffer(entryFeedback,buffer,0);
                       UART_transmit_string(print_port,buffer,0);
                   }
                   else{
                       error_check = 1; // User entry is correct size, exit loop :D
                       userInput = temp32;
                   }
                }while(error_check == 0);
                // Then use as input parameter to read_directory function
                uint32_t returnCluster = 0;
                SecNum = drive->FirstRootDirSec;
                returnCluster = read_dir_entry(SecNum, userInput, buffer1_g);
                returnCluster &= 0xF0000000; // Keeping the upper four bits :D
                 // Bit 28 = 1 means directory, Bit #28 = 0 means file,
                if(returnCluster & (1UL << 31)){ //  Check bit 31 for error 1 = no error
                    if(returnCluster & (1UL << 28)){ // Check Bit 28 for directory of file
                        // Bit 28 == 1, must be directory
                        repeat = 1;
                    }
                    else{ // Bit 28 == 0, must be a file
                        repeat = 0;
                    }
                }
                else{  //There is an error :(
                    error_status = 1; //  Throw an error to exit loop
                }  
            }while((repeat == 1) && (error_status == 0x00));

            uint32_t InputCluster = read_dir_entry(drive->FirstRootDirSec, userInput, buffer1_g);
            //open_file(drive, InputCluster, buffer1_g);
        }
    }
    else{
        // Error with the mount drive function
        copy_string_to_buffer("Mount drive failed",buffer,0);
        UART_transmit_string(print_port,buffer,0);
    }
    
    return 0;
}