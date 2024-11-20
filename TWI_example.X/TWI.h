/* 
 * File:   TWI.h
 * Author: owenhancock
 *
 * Created on November 8, 2024, 11:14 AM
 */

#ifndef TWI_H
#define	TWI_H

#include "board.h"

/**************************************************************
*   TWI_master_init
*   Inputs: TWI instance object - TWI_addr
    an unsigned 32-bit integer for the I2C clock rate - I2C_freq
*   Output: an unsigned 8-bit integer for the clock rate of the TWI
**************************************************************
*   Function: Sets the clock rate for the TWI
*
*   Caution: 
***************************************************************/
uint8_t TWI_master_init(volatile TWI_t *TWI_addr, uint32_t I2C_freq);

/**************************************************************
*   TWI_master_receive
*   Inputs: TWI instance object - TWI_addr
    an unsigned 8-bit integer for the address of the slave - slave_addr
    an unsigned 16-bit integer for the number of bytes read - num_bytes
    an unsigned 8-bit integer for the address of the receive array - rec_array
*   Output: an unsigned 8-bit integer of the received byte
**************************************************************
*   Function: reads values to the slave device
*
*   Caution: 
***************************************************************/
uint8_t TWI_master_receive(volatile TWI_t *TWI_addr, uint8_t slave_addr, 
        uint16_t num_bytes, uint8_t * rec_array);

// TWI_master_receive prototype with bonus implementation (includes internal address size and the address)
uint8_t TWI_master_receive(volatile TWI_t *TWI_addr, uint8_t device_addr, 
    uint32_t int_addr, uint8_t int_addr_sz, uint16_t num_bytes, uint8_t * array_name);

/**************************************************************
*   TWI_master_transmit
*   Inputs: TWI instance object - TWI_addr
    an unsigned 8-bit integer for the address of the slave - slave_addr
    an unsigned 16-bit integer for the number of bytes read - num_bytes
    an unsigned 8-bit integer for the array tranmitted - array
*   Output: an unsigned 8-bit integer for the error
**************************************************************
*   Function: writes values to the slave device
*
*   Caution: 
***************************************************************/
uint8_t TWI_master_transmit(volatile TWI_t *TWI_addr, uint8_t slave_addr, 
        uint16_t num_bytes, uint8_t *array);

// TWI_master_transmit prototype with bonus implementation (includes internal address size and the address)
uint8_t TWI_master_transmit(volatile TWI_t *TWI_addr, int32_t internal_addr, 
        uint8_t int_addr_size, int8_t slave_addr, uint16_t num_bytes, uint8_t *array);

#endif	/* TWI_H */

