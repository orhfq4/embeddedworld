#ifndef _TWI_H
#define _TWI_H

#include "board.h"




#define no_errors (0)
#define BUS_BUSY_ERROR (0x81)
#define NACK_ERROR (0x82)
#define TWI_CLOCK_ERROR (0x87)

// ------ Public function prototypes -------------------------------

/***********************************************************************
DESC:    Sets the Prescale and Clock Rate Generator for the two wire interface
INPUT: Base Address of the TWI peripheral to use.
       Desired SCL clock frequency.      
RETURNS: Error status to indicate if clock was set or not
CAUTION: 
          
************************************************************************/
uint8_t TWI_master_init(volatile TWI_t *TWI_addr, uint32_t I2C_FREQ);


/***********************************************************************
DESC:    Uses the TWI peripheral to transmit the device address
         internal address and data contained in an array
INPUTS: Base address of the TWI peripheral to use
        The device address and internal address of where to start writing data
        The internal address size allows for more flexibility in bus devices
        The number of bytes to send and an array of those bytes
RETURNS: Error status
CAUTION: 
          
************************************************************************/
uint8_t TWI_master_transmit(volatile TWI_t *TWI_addr, uint8_t device_addr, 
                             uint32_t internal_addr, uint8_t int_addr_bytes, 
                             uint8_t num_bytes, uint8_t *send_array);


/***********************************************************************
DESC:    Uses the TWI peripheral to transmit the device address
         internal address from which data should be received
         The values that are received are stored in an array
INPUTS: Base address of the TWI peripheral to use
        The device address and internal address of where to start writing data
        The internal address size allows for more flexibility in bus devices
        The number of bytes to send and an array of those bytes
RETURNS: Error status, received values in an array
CAUTION: 
          
************************************************************************/
uint8_t TWI_master_receive(volatile TWI_t *TWI_addr, uint8_t device_addr, 
                            uint32_t internal_addr, uint8_t int_addr_bytes, 
                            uint8_t num_bytes, uint8_t *rec_array);





#endif