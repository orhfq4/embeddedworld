/* 
 * File:   SDCard.h
 * Author: owenhancock
 *
 * Created on October 26, 2024, 9:03 PM
 */

#ifndef SDCARD_H
#define	SDCARD_H

/**************************************************************
*   send_command
*   Inputs: SPI Object
    an unsigned 8-bit integer value for the value of the command
    an unsigned 32-bit integer value for the value of the argument/what is being sent
*   Output: an unsigned 8-bit integer
**************************************************************
*   Function: Sends a command to the SPI
*
*   Caution: 
***************************************************************/
uint8_t send_command (volatile SPI_t *SPI_addr, uint8_t CMD_value,uint32_t argument);

/**************************************************************
*   receive_response
*   Inputs: SPI object
    unsigned 8-bit integer for t he number of bytes received
    an array of unsigned 8-bit integers 
*   Output: an unsigned 8-bit integer
**************************************************************
*   Function: receives data from the SPI.
*
*   Caution: 
***************************************************************/
uint8_t receive_response (volatile SPI_t *SPI_addr, uint8_t num_bytes,uint8_t rec_array[ ]);

/**************************************************************
*   sd_card_init
*   Inputs: SPI object
*   Output: unsigned 8-bit integer
**************************************************************
*   Function: Initializes the SD card.
*
*   Caution: make sure to call this function after you have initialized the init_SD_CS function.
***************************************************************/
uint8_t sd_card_init(volatile SPI_t *SPIaddr);

/**************************************************************
*   init_SD_CS
*   Inputs: SPIO object
    unsigned 8-bit integer for the pin value
*   Output: none
**************************************************************
*   Function: initializes the chipset of the SD card
*
*   Caution: 
***************************************************************/
void init_SD_CS(volatile GPIO_t *port, uint8_t pin);

/**************************************************************
*   SD_CS_Active
*   Inputs: None
*   Output: None
**************************************************************
*   Function: Toggles the chipset of the SD card to active
*
*   Caution: 
***************************************************************/
void SD_CS_active();

/**************************************************************
*   SD_CS_inactive
*   Inputs: None
*   Output: None
**************************************************************
*   Function: Toggles the chipset of the SD card to inactive
*
*   Caution: 
***************************************************************/
void SD_CS_inactive();

/**************************************************************
*   init_SCK
*   Inputs: GPIO object
    unsigned 8-bit value for the pin value
*   Output: None
**************************************************************
*   Function: initializes the SCK
*
*   Caution: 
***************************************************************/
void init_SCK(volatile GPIO_t *port, uint8_t pin);

/**************************************************************
*   SCK_low
*   Inputs: None
*   Output: None
**************************************************************
*   Function: Sets the SCK pin to low (0).
*
*   Caution: 
***************************************************************/
void SCK_low();

/**************************************************************
*   read_block
*   Inputs: SPI object
    array of unsigned 8-bit integers
    unsigned 16-bit integer for number of bytes
*   Output: an unsigned 8-bit integer
**************************************************************
*   Function: Reads the block and returns the value of the block to the SPI.
*
*   Caution: 
***************************************************************/
uint8_t read_block (volatile SPI_t *SPI_addr, uint8_t array[ ],uint16_t number_of_bytes);

#endif	/* SDCARD_H */

