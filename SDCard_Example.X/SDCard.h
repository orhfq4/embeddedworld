/* 
 * File:   SDCard.h
 * Author: owenhancock
 *
 * Created on October 26, 2024, 9:03 PM
 */

#ifndef SDCARD_H
#define	SDCARD_H

// Function prototype for the send command
uint8_t send_command (volatile SPI_t *SPI_addr, uint8_t CMD_value,uint32_t argument);

// Function prototype for the receive command
uint8_t receive_response (volatile SPI_t *SPI_addr, uint8_t num_bytes,uint8_t rec_array[ ]);

// Pre:
// Post:
// Desc:
uint8_t sd_card_init(volatile SPI_t *SPIaddr);

// Function prototype for read block
uint8_t read_block (volatile SPI_t *SPI_addr, uint8_t array[ ],uint16_t number_of_bytes);

#endif	/* SDCARD_H */

