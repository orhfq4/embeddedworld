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
#define SD_CS_PORT (PB)       // (&PINB)
#define SD_CS_PIN (1<<4)      

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
        rcvd_value = SPI_receive(SPI_addr);
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
                rcvd_value=SPI_receive(SPI_addr);
                *(rec_array+index)=rcvd_value;
            }
        }
    }

    // (3) Send a final 0xFF after receiving the response
    rcvd_value = SPI_transfer(SPI_addr, 0xFF);

    return 0;  // Success
}

void SD_CS_active(volatile uint8_t *port, uint8_t pin) { // maybe this is right?
    gpio_inst_t CS_PIN;
    GPIO_output_ctor(&CS_PIN, port, pin, 1);
}

void SD_CS_inactive(volatile uint8_t *port, uint8_t pin) { // maybe this is right?
    gpio_inst_t CS_PIN;
    GPIO_output_ctor(&CS_PIN, port, pin, 0);
}

uint8_t sd_card_init(volatile SPI_t *SPI_addr){
    uint16_t timeout = 0;
    uint8_t error_status = 0; 
    uint8_t rcvd_value = 0;
    uint32_t argument = 0x00000000;
    uint8_t rec_array[0];
    uint8_t num_bytes = 0;
    
    //************************************************************************
    
    // CMD0:
    
    //Set /CS = 1
    SD_CS_active(SD_CS_PORT, SD_CS_PIN);

    //TODO: Send 74 clock cycles on SCK

    //************************************************************************
    
    // CMD8:
    //check for errors
    if(error_status == 0){
        //Set /CS = 1
        SD_CS_active(SD_CS_PORT, SD_CS_PIN);
        // Send CMD0
        argument = 0x000001AA; // argument for CMD8
        error_status = send_command(SPI_addr, CMD8, argument);
        // RxC Response
        if(error_status == 0) {
            num_bytes = 5; // RxC response 3 Bytes R1 + 0x000001AA, 0x01
            error_status = receive_response(SPI_addr, num_bytes, rec_array);
        }
        //Set /CS = 0
        SD_CS_inactive(SD_CS_PORT, SD_CS_PIN);
        // Check the response (could print the response if necessary)
        if ((rec_array[0]==0x01)&&(error_status==0)) {
            if(rec_array[3]==0x01&&(error_status==0)) {
                if(rec_array[3]==0x01&&(rec_array[4]==0xAA)) {
                    argument = 0x40000000; //High Capacity support ACMD41 Argument
                }
                else {
                    error_status = 1; // incompatible voltage
                }
            }
            else if (rec_array[0]==0x05) {
                error_status = 0; // if supporting older cards
                argument = 0x00000000; // No High Capacity Support
                // SD_Card_Type_g = Standard_Capacity;
            }
            else {
                error_status = 2; // Flag if received response is neither for HCS or /HCS
            }
        }
    
    /* Steps to Initialization function:
     * CMD0 command: (Power on the SD card and wait for completion)
     * CMD0 w/ CS = 0
     * CS Active
     * Send Command
     * RxC Response
     * CS inactive
     * Analyze Response
     * 
     * CMD8 Command: (Check for v1 compatibility or v2 compatibility then analyze appropriately)
     * if(error_status == no_errors){
     * CS active
     * send command (8,0x000001AA, 0x87)
     * RxC response 3 Bytes R1 + 0x000001AA, 0x01
     * CS inactive
     * Analyze:
     * if (R1==0x05){
     * Assume standard capacity card
     * if (R1==0x01){
     * if(voltage==0x01, check_byte==0xAA){
     * error_status = no_errors
     * else{
     * error_status = error

     * CMD58 (For handling v1 cards)
     * if (error_status == no_errors){
     * CS Active
     * Send Command (58, 0x00000000, 0x01)
     * RxC Response 5 Bytes R1 + OCR (4 Bytes) 0x01 (check voltage)
     * CS Inactive
     * Analyze:
     * if(R1==0x01){
     * if(OCR Voltage OK){
     * error_status == no_errors
     * else{
     * error_status = error
     * 
     * ACMD41 (Application specific command to check for SDHC or SDXC
     */
    
    }
}