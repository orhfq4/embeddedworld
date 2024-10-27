/* 
 * File:   SPI.h
 * Author: owenhancock
 *
 * Created on October 26, 2024, 9:03 PM
 */

#ifndef SPI_H
#define	SPI_H

#include <stdint.h>
#include "peripherals.h"
#include "board.h"

// Defined constants for CPOL and CPHA values
#define CPOL_bit (0) // Set CPOL bit as needed
#define CPHA_bit (0) // Set CPHA bit as needed

// Function prototype for SPI initialization
uint8_t SPI_Master_Init(volatile SPI_t *SPI_addr, uint32_t clock_freq);

// No Error Checking, return value is received value

void SPI_transmit(volatile SPI_t *SPI_addr, uint8_t send_value);
uint8_t SPI_receive(volatile SPI_t *SPI_addr);
uint8_t SPI_transfer(volatile SPI_t *SPI_addr, uint8_t send_value);

//**** With Error Checking, return value is error value
/*
uint8_t SPI_transmit(volatile SPI_t *SPI_addr, uint8_t send_value);
uint8_t SPI_receive(volatile SPI_t *SPI_addr, (uint8_t send_value,)# uint8_t *rec_value);
uint8_t SPI_transfer(volatile SPI_t *SPI_addr, uint8_t send_value, uint8_t *rec_value);
*/
// # Indicates an optional value: (uint8_t send_value,)


#endif	/* SPI_H */

