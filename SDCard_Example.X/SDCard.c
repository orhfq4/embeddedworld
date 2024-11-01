// SDCard.c
#include <avr/io.h>
#include <stdint.h>
#include "peripherals.h"
#include "SDCard.h"
#include "SPI.h"
#include "UART_Print.h"

#define SD_CS_port (PB)
#define SD_CS_pin (1<<4)
#define SD_CS_pin_clear (0<<4)
#define SCK_PORT_SD (PB)
#define SCK_PIN_SD (1<<7)
#define CMD0_CHECKSUM (0x95)  // Pre-calculated checksums for CMD0 and CMD8
#define CMD8_CHECKSUM (0x87)
#define CMD0 (0)
#define CMD8 (8)
#define SD_CMD_TIMEOUT (1000) // Timeout value to avoid infinite loops
#define CMD0_error (7) //arbitrarily chosen
#define CMD8_error (8) // arb chosen 
#define illegal_command (9)
#define CMD58_error (10)
#define normal (0x00)

uint8_t send_command(volatile SPI_t *SPI_addr, uint8_t CMD_value, uint32_t argument) {
    uint8_t error_status = 0;  // Assume no error initially

    // (a) Check if the command is a 6-bit value
    if (error_status==normal) {
        if (CMD_value > 63) {
            error_status = 1;  // Set error flag for illegal command
        }
    }

    // (b) OR the command with 0x40 to add start and transmission bits
    uint8_t send_value = 0x40 | CMD_value;

    // (c) Send the command byte
    uint8_t rcvd_value = SPI_transfer(SPI_addr, send_value); // The received value is not used in this function
    
    if (error_status==normal) {
        if (rcvd_value > 0) {
            error_status = 2; // Set an error if SPI error occurs and exit early
        }
    }

    // (d) Send the 32-bit argument, MSB first
    for (int8_t index = 0; index < 4; index++) {
        send_value = (uint8_t)(argument>>(24-(index*8)));
        rcvd_value = SPI_transfer(SPI_addr,send_value);
        
        if (error_status==normal) {
            if (rcvd_value > 0) {
                error_status = 3;
            }
        }
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
    if (error_status==normal) {
        if (rcvd_value > 0){
            error_status = 3;
        }
    }
    
    return error_status;  // Return final error status
}

uint8_t receive_response (volatile SPI_t *SPI_addr, uint8_t num_bytes, uint8_t rec_array[]) {
    uint16_t timeout = 0;
    uint8_t error_status = 0; // assume no initial errors
    uint8_t rcvd_value = 0;
    
    // (1) Wait for the R1 response by repeatedly sending 0xFF
    do {
        rcvd_value = SPI_receive(SPI_addr);
        timeout++;
        
        // Check for timeout
        if (error_status==normal) {
            if (timeout >= SD_CMD_TIMEOUT) {
                error_status = 1;  // Timeout error
            }
        }
        
    } while ((rcvd_value == 0xFF)&&(timeout != 0));
    
    // Store the R1 response in the array
    rec_array[0] = rcvd_value;
    
    // (2) Read additional bytes if specified
    if (error_status==normal){
        if(timeout == 0) {
            error_status = 2;
        }
        else if((rcvd_value&0xFE) != 0x00) { // 0x00 and 0x01 are good
        *rec_array=rcvd_value; // return the value to see the array
        error_status = 3;
    } else {
        *rec_array=rcvd_value; // first received value  (R1 resp.)
        if(num_bytes>1) {
            for(int8_t index=1;index<num_bytes;index++) {
                rcvd_value=SPI_receive(SPI_addr);
                *(rec_array+index)=rcvd_value;
            }
        }
    }
    }

    // (3) Send a final 0xFF after receiving the response
    rcvd_value = SPI_transfer(SPI_addr, 0xFF);

    return error_status;  // Success
}

uint8_t sd_card_init(volatile SPI_t *SPI_addr){
    uint16_t timeout = 0;
    uint8_t error_status = normal; 
    uint8_t rcvd_value = 0;
    uint8_t R1_bytes = 1;
    uint8_t OCR_bytes = 5;
    uint8_t ACMD41_arg = 0x40000000;

    uint8_t R1;
    uint8_t host_supply_v;
    uint8_t operating_v;
    uint32_t argument_0 = 0x00000000;
    uint32_t argument_8 = 0x000001AA;
    uint8_t rec_array[5];
    
    UART_transmit_string(UART1, "Entering SD_CARD INIT \n\r", 0);
    GPIO_output_init_2(SD_CS_port, SD_CS_pin); // Creates PB4 for the /CS, initial value set to 1

    GPIO_output_init_2(SCK_PORT_SD, SCK_PIN_SD); //Creates PB7 which acts as the SCK. Initial value of 0.

    //10 SPI_transfers of 0xFF
    for(uint8_t i = 0; i<10; i++){
        UART_transmit_string(UART1, "Running For Loop \n\r", 0);
        uint8_t send_value = 0xFF; 
        rcvd_value = SPI_transfer(SPI_addr,send_value);
    }
    
    /****************************CMD0*********************************/
    if(error_status==normal){
        UART_transmit_string(UART1, "Sending CMD0 \n\r", 0);
        //Clear the /CS bit (PB4) to start the communication
        GPIO_output_set_value_2(SD_CS_port, SD_CS_pin, 0);
        // Send CMD0 with argument 0x00;
        send_command(SPI_addr, 0x00, argument_0);
        //Receive response and check R1
        receive_response (SPI_addr, R1_bytes, rec_array);
        R1 = rec_array[0];
        //Set /CS = 1, stop transmission
        GPIO_output_set_value_2(SD_CS_port, SD_CS_pin, 1);
        if(R1!=0x01){
            error_status = CMD0_error;
            UART_transmit_string(UART1, "CMD0: R1 is not equal to 0x01 \n\r", 0);
        }
    }
    /*****************************************************************/
    
    /****************************CMD8*********************************/
    if(error_status==normal){
        UART_transmit_string(UART1, "Sending CMD8 \n\r", 0);
        //Clear the /CS bit (PB4) to start the communication
        GPIO_output_set_value(SD_CS_port, SD_CS_pin_clear);
        // Send CMD8 with argument 0x000001AA;
        send_command(SPI_addr, 0x08, argument_8);
        //Receive response and check R1
        receive_response (SPI_addr, OCR_bytes, rec_array);
        R1 = rec_array[0];
        host_supply_v = rec_array[3]; // Read host supply voltage
        //Set /CS = 1, stop transmission
        GPIO_output_set_value(SD_CS_port, SD_CS_pin);
        
        if(R1!=0x01){
            error_status = CMD8_error;
            UART_transmit_string(UART1, "CMD8: R1 is not equal to 0x01 \n\r", 0);
        }
        if(R1 == 0x05){
            error_status = illegal_command; // Checks for illigal command
            ACMD41_arg = 0x00;
        }
        if(host_supply_v != 0x01){ //check to see if supply is correct
            error_status = CMD8_error;
            UART_transmit_string(UART1, "CMD8: Host Supply Voltage is not equal to 0x01 \n\r", 0);
        }
        if(rec_array[4]!= 0xAA){ // Dont know what this does
            error_status = CMD8_error;
            UART_transmit_string(UART1, "CMD8: Received Array is not equal to 0xAA \n\r", 0);
        }
    }
    /*****************************************************************/

    /****************************CMD58*********************************/
    if(error_status==normal){
        UART_transmit_string(UART1, "Sending CMD58 \n\r", 0);
        //Clear the /CS bit (PB4) to start the communication
        GPIO_output_set_value(SD_CS_port, SD_CS_pin_clear);
        // Send CMD58 with argument 0x00;
        send_command(SPI_addr, 0x00, argument_0);
        //Receive response and check R1
        receive_response (SPI_addr, OCR_bytes, rec_array);
        R1 = rec_array[0];
        operating_v = rec_array[2];
        //Set /CS = 1, stop transmission
        GPIO_output_set_value(SD_CS_port, SD_CS_pin);
        
        if(R1!=0x01){
            error_status = CMD58_error;
            UART_transmit_string(UART1, "CMD58: R1 is not equal to 0x01 \n\r", 0);
        }
        if(operating_v != 0xFF){
            error_status = CMD58_error;
            UART_transmit_string(UART1, "CMD58: Operating Voltage is not equal to 0xFF \n\r", 0);
        }
        if (rec_array[3] != 0x80){
            error_status = CMD58_error;
            UART_transmit_string(UART1, "CMD58: Received Array is not equal to 0x80 \n\r", 0);
        }
    }
    
    return error_status;
        /*******************************ACMD41***************************/
    /*
     if (error_status == normal) {
    do{
        //Clear the /CS bit (PB4) to start the communication
        GPIO_output_set_value(SD_CS_port, SD_CS_pin_clear);
        //TODO: Check send command 55
        send_command (SPI_addr, 0x55, argument_0); //Sends command 55 with arg = 0
        //Check the R1 Response
        receive_response (SPI_addr, R1_bytes, rec_array); //Recieve one byte of data (R1 response), stored in the 0th element of rec_array
        R1 = rec_array[0];
        //Send command 41
        send_command(SPI_addr, 0x41, ACMD41_arg); // Arg by default is 0x40000000
        // Check the R1 response
        receive_response (SPI_addr, R1_bytes, rec_array); //Recieve one byte of data (R1 response), stored in the 0th element of rec_array
        R1 = rec_array[0];
        //Set /CS = 1, stop transmission
        GPIO_output_set_value(SD_CS_port, SD_CS_pin);
        //store the r1 response
        R1 = rec_array[0];
        timeout++;
        UART_transmit_string(UART1, "Loop Complete \n\r", 0);
    }while((R1 != normal) && timeout != 0);


    if(R1 == 0x00){
        send_command (SPI_addr, 0x58, argument_0); // Send command 58
        receive_response (SPI_addr,R1_bytes,rec_array); // Check R1
        R1 = rec_array[0]; 
    }
     }
     * /
    
    //**********************************************************************
        /*CMDO
        //All in ACMD41:^^
        do{
            CS = 0;
            send command(55,0)
            receiceresponse(1bytes)
            sendcommand(41, 0x40000000)
            CS = 1
        }while(R1 != 0x00)&&(timeout!=0)
        outside overall do while:
            if(R1 == 0x00)
                CMD5:
                response R1 = 0x00
                OCR = 0xC0FF8000
        If error == no errors{
        cs = 0;
        send command(0,0)
        REcieveresponse(1 byte)
        CS = 1
        Check R1 = 0x01;
        }
        CMD08:
        if(errorstatus==noerrors){
        CS=0
        sendcommand(8,0x000001AA)
        receiveresponse(5bytes)
        CS = 1
        check R1 = 0x01 GOOD!
        Check R1 = 0x05 illegal command!
            ACMD41_arg = 0x00 (optional)
        Check byte 4 = 0x01 (HostSupplyVoltage)
        byte 5 = 0xAA = OK!
        }
        CMD58:
        Same shit
        Arg = 0;
        Response 5 bytes should be 
            R1 = 0x01
            OCR = 0x00FF8000
        */
}