// SDCard.c
#include <avr/io.h>
#include <stdint.h>
#include "peripherals.h"
#include "SDCard.h"
#include "SPI.h"

#define CMD0_CHECKSUM (0x95)  // Pre-calculated checksums for CMD0 and CMD8
#define CMD8_CHECKSUM (0x87)
#define CMD0 (0)
#define CMD8 (8)
#define SD_CMD_TIMEOUT (1000) // Timeout value to avoid infinite loops

uint8_t send_command(volatile SPI_t *SPI_addr, uint8_t CMD_value, uint32_t argument) {
    uint8_t error_status = 0;  // Assume no error initially

    // (a) Check if the command is a 6-bit value
    if (CMD_value > 63) {
        error_status = 1;  // Set error flag for illegal command
        return error_status;
    }

    // (b) OR the command with 0x40 to add start and transmission bits
    uint8_t send_value = 0x40 | CMD_value;

    // (c) Send the command byte
    uint8_t rcvd_value = SPI_transfer(SPI_addr, send_value); // The received value is not used in this function
    
    // Not entirely sure if this if statement is right
    if (rcvd_value > 0) return error_status = 2; // Set an error if SPI error occurs and exit early

    // (d) Send the 32-bit argument, MSB first
    for (int8_t index = 0; index < 4; index++) {
        send_value = (uint8_t)(argument>>(24-(index*8)));
        rcvd_value = SPI_transfer(SPI_addr,send_value);
        
        // Not entirely sure if this if statement is right
        if (rcvd_value > 0) return error_status = 3;
    }

    // (e) Send the checksum byte or default end bit value
    uint8_t checksum;
    if (CMD_value == CMD0) {
        checksum = CMD0_CHECKSUM;  // CMD0 checksum
    } else if (CMD_value == CMD8) {
        checksum = CMD8_CHECKSUM;  // CMD8 checksum
    } else {
        checksum = 0x01;  // Default checksum with end bit only, CRC7=0
    }

    rcvd_value = SPI_transfer(SPI_addr, checksum);  // Send checksum byte
    // Not entirely sure if this if statement is right
    if (rcvd_value > 0) return error_status = 3;
    
    return error_status;  // Return final error status
}

uint8_t receive_response (volatile SPI_t *SPI_addr, uint8_t num_bytes, uint8_t rec_array[ ]) {
    uint16_t timeout = 0;
    uint8_t error_status = 0; // assume no initial errors
    uint8_t rcvd_value = 0;
    
    // (1) Wait for the R1 response by repeatedly sending 0xFF
    do {
        rcvd_value = SPI_receive(SPI_addr, 0xFF);
        timeout++;
        
        // Check for timeout
        if (timeout >= SD_CMD_TIMEOUT) {
            return error_status = 1;  // Timeout error
        }
        
    } while ((rcvd_value == 0xFF)&&(timeout != 0));
    
    // Store the R1 response in the array
    rec_array[0] = rcvd_value;
    
    // (2) Read additional bytes if specified
    if(timeout == 0) {
        return error_status = 2;
    } else if((rcvd_value&0xFE) != 0x00) { // 0x00 and 0x01 are good
        *rec_array=rcvd_value; // return the value to see the array
        return error_status = 3;
    } else {
        *rec_array=rcvd_value; // first received value  (R1 resp.)
        if(num_bytes>1) {
            for(int8_t index=1;index<num_bytes;index++) {
                rcvd_value=SPI_receive(SPI_addr, 0xFF);
                *(rec_array+index)=rcvd_value;
            }
        }
    }

    // (3) Send a final 0xFF after receiving the response
    rcvd_value = SPI_transfer(SPI_addr, 0xFF);

    return 0;  // Success
}