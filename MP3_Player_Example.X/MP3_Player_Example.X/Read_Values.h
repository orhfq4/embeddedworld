/* 
 * File:   Read_Values.h
 * Author: Younger
 *
 * Created on November 18, 2024, 9:29 PM
 */

#ifndef READ_VALUES_H
#define	READ_VALUES_H

#include "peripherals.h"

uint8_t read_value_8(uint16_t offset, uint8_t array[]);
uint16_t read_value_16(uint16_t offset, uint8_t array[]);
uint32_t read_value_32(uint16_t offset, uint8_t array[]);


#endif	/* READ_VALUES_H */

