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
uint8_t SPI_Master_Init(volatile uint8_t *SPI_addr, uint32_t clock_freq);

#endif	/* SPI_H */

