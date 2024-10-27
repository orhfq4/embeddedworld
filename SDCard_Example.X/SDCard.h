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




#endif	/* SDCARD_H */

