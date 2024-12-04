/* 
 * File:   Read_Values.h
 * Author: Younger
 *
 * Created on November 18, 2024, 9:29 PM
 */

#ifndef READ_VALUES_H
#define	READ_VALUES_H

#include "peripherals.h"

/***********************************************************************
*   read_value_8
DESC:    Reads an 8-bit value from an array at the specified offset.
INPUT:   uint16_t offset - The offset in the array to read from.
         uint8_t array[] - The array containing the data.
RETURNS: uint8_t - The 8-bit value at the given offset.
************************************************************************/

uint8_t read_value_8(uint16_t offset, uint8_t array[]);

/***********************************************************************
*   read_value_16
DESC:    Reads a 16-bit value from an array at the specified offset, considering byte order.
INPUT:   uint16_t offset - The offset in the array to read from.
         uint8_t array[] - The array containing the data.
RETURNS: uint16_t - The 16-bit value at the given offset.
************************************************************************/

uint16_t read_value_16(uint16_t offset, uint8_t array[]);

/***********************************************************************
*   read_value_32
DESC:    Reads a 32-bit value from an array at the specified offset, considering byte order.
INPUT:   uint16_t offset - The offset in the array to read from.
         uint8_t array[] - The array containing the data.
RETURNS: uint32_t - The 32-bit value at the given offset.
************************************************************************/

uint32_t read_value_32(uint16_t offset, uint8_t array[]);


#endif	/* READ_VALUES_H */