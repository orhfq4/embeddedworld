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

/**************************************************************
*   SPI_Master_Init
*   Inputs: SPI object pointer
    unsigned 32-bit integer for the clock frequency
*   Output: an unsigned 8-bit ineger
**************************************************************
*   Function: Initializes the SPI master
*   This function includes error checking, which is as follows:
    s
*   Caution: 
***************************************************************/
uint8_t SPI_Master_Init(volatile SPI_t *SPI_addr, uint32_t clock_freq);

// No Error Checking, return value is received value
/**************************************************************
*   SPI_transmit
*   Inputs: a pointer to an SPI object
    a unsigned 8-bit integer for the data being sent to the SPI
*   Output: None
**************************************************************
*   Function: Transmits a 8-bit integer
*
*   Caution: 
***************************************************************/
void SPI_transmit(volatile SPI_t *SPI_addr, uint8_t send_value);

/**************************************************************
*   
*   Inputs: 
*   Output: 
**************************************************************
*   Function: 
*
*   Caution: 
***************************************************************/
uint8_t SPI_receive(volatile SPI_t *SPI_addr);

/**************************************************************
*   
*   Inputs: 
*   Output: 
**************************************************************
*   Function: 
*
*   Caution: 
***************************************************************/
uint8_t SPI_transfer(volatile SPI_t *SPI_addr, uint8_t send_value);

//**** With Error Checking, return value is error value
/*
uint8_t SPI_transmit(volatile SPI_t *SPI_addr, uint8_t send_value);
uint8_t SPI_receive(volatile SPI_t *SPI_addr, (uint8_t send_value,)# uint8_t *rec_value);
uint8_t SPI_transfer(volatile SPI_t *SPI_addr, uint8_t send_value, uint8_t *rec_value);
*/
// # Indicates an optional value: (uint8_t send_value,)


#endif	/* SPI_H */

