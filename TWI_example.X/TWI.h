/* 
 * File:   TWI.h
 * Author: owenhancock
 *
 * Created on November 8, 2024, 11:14 AM
 */

// Verifying

#ifndef TWI_H
#define	TWI_H

#include "board.h"
/*
 
 * Need to add in the following 3 functions:
 * TWI_master_init()
 * TWI_master_transmit()
 * TWI_master_receive()
 
 */

// TWI_master_init prototype
// Sets the clock rate for the TWI
uint8_t TWI_master_init(volatile TWI_t *TWI_addr, uint32_t I2C_freq);

// TWI_master_receive prototype
// Reads values to a slave device
uint8_t TWI_master_receive(volatile TWI_t *TWI_addr, uint8_t slave_addr, 
        uint16_t num_bytes, uint8_t * rec_array);

// TWI_master_receive prototype with bonus implementation (includes internal address size and the address)
// uint8_t TWI_master_receive(volatile TWI_t *TWI_addr, uint8_t device_addr, 
    // uint32_t int_addr, uint8_t int_addr_sz, uint16_t num_bytes, uint8_t * array_name);

// TWI_master_transmit prototype
// Writes values to a slave device
uint8_t TWI_master_transmit(volatile TWI_t *TWI_addr, uint8_t slave_addr, 
        uint16_t num_bytes, uint8_t *array);

// TWI_master_transmit prototype with bonus implementation (includes internal address size and the address)
// uint8_t TWI_master_transmit(volatile TWI_t *TWI_addr, 
        // int32_t internal_addr, uint8_t int_addr_size,
        // int8_t slave_addr, uint16_t num_bytes, uint8_t *array);

#endif	/* TWI_H */

