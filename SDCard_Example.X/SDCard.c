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
#define high_capacity (0xC0)
#define std_capacity (0x80)

// ********************************Global Variables*************************************

gpio_inst_t sd_cs_gpio; // Declare it globally
gpio_inst_t sck_gpio;
uint8_t SD_Card_Type;

// ********************************CS and SCK init and control functions****************

void init_SD_CS(volatile GPIO_t *port, uint8_t pin) {
    GPIO_output_ctor(&sd_cs_gpio, port, pin, GPIO_CLEAR); // Initialize only once
}

void SD_CS_active() {
    GPIO_output_set_value(&sd_cs_gpio, GPIO_SET); // Set the pin to high
}

void SD_CS_inactive() {
    GPIO_output_set_value(&sd_cs_gpio, GPIO_CLEAR); // Set the pin to low
}

void init_SCK(volatile GPIO_t *port, uint8_t pin) {
    GPIO_output_ctor(&sck_gpio, port, pin, GPIO_CLEAR); // Initialize only once
}

void SCK_low() {
    GPIO_output_set_value(&sck_gpio, GPIO_CLEAR); // Set the pin to low
}

// ****************************send_command*************************************

uint8_t send_command(volatile SPI_t *SPI_addr, uint8_t CMD_value, uint32_t argument) {
    uint8_t error_status = 0;  // Assume no error initially

    // (4a) Check if the command is a 6-bit value
    if (error_status==normal) {
        if (CMD_value > 63) {
            error_status = 1;  // Set error flag for illegal command
            UART_transmit_string(UART1, "Send command: Error command greater than 63 \n\r", 0);
        }
    }

    // (4b) OR the command with 0x40 to add start and transmission bits
    uint8_t send_value = 0x40 | CMD_value;

    // (4c) Send the command byte
    uint8_t rcvd_value = SPI_transfer(SPI_addr, send_value); // The received value is not used in this function
    
    // (4d) Send the 32-bit argument, MSB first
    for (int8_t index = 0; index < 4; index++) {
        send_value = (uint8_t)(argument>>(24-(index*8)));
        rcvd_value = SPI_transfer(SPI_addr,send_value);
        }
    // (4e) Send the checksum byte or default end bit value
    uint8_t checksum;
    if (CMD_value == CMD0) {
        checksum = CMD0_CHECKSUM;  // CMD0 checksum
    } else if (CMD_value == CMD8) {
        checksum = CMD8_CHECKSUM;  // CMD8 checksum
    } else {
        checksum = 0x01;  // Default checksum with end bit only, CRC7=0
    }

    rcvd_value = SPI_transfer(SPI_addr, checksum);  // Send checksum byte
    
    return error_status;  // (4f) Return final error status
}

// ********************************receive_response***************************************

uint8_t receive_response (volatile SPI_t *SPI_addr, uint8_t num_bytes, uint8_t rec_array[]) {
    uint16_t timeout = 0;
    uint8_t error_status = 0; // assume no initial errors
    uint8_t rcvd_value = 0;
    
    // (5a) Wait for the R1 response by repeatedly sending 0xFF
    do {
        rcvd_value = SPI_receive(SPI_addr);
        timeout++;
        
        // Check for timeout
        if (error_status==normal) {
            if (timeout >= SD_CMD_TIMEOUT) {
                error_status = 1;  // Timeout error
                UART_transmit_string(UART1, "Receive response: Error timeout \n\r", 0);
            }
        }
        
    } while ((rcvd_value == 0xFF)&&(timeout != 0));
    
    // Store the R1 response in the array
    rec_array[0] = rcvd_value;
    
    // (5b) Read additional bytes if specified
    if (error_status==normal){
        if(timeout == 0) {
            error_status = 2;
            UART_transmit_string(UART1, "Received Response: Error timeout \n\r", 0);
        }
        else if((rcvd_value&0xFE) != 0x00) { // 0x00 and 0x01 are good
            *rec_array=rcvd_value; // return the value to see the array
            error_status = 3;
            UART_transmit_string(UART1, "Receive Response: Error rcvd_value isn't 0xFE \n\r", 0);
            
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

    // (5c) Send a final 0xFF after receiving the response
    rcvd_value = SPI_transfer(SPI_addr, 0xFF);

    return error_status;  // Success (5d)
}

// ****************************sd_card_init********************************************

uint8_t sd_card_init(volatile SPI_t *SPI_addr){
    uint16_t timeout = 0;
    uint8_t error_status = normal; 
    uint8_t rcvd_value = 0;
    uint8_t R1_bytes = 1;
    uint8_t OCR_bytes = 5;
    uint32_t ACMD41_arg = 0x40000000;

    uint8_t R1;
    uint8_t host_supply_v;
    uint8_t operating_v;
    uint8_t SD_Card_type_g;
    uint32_t argument_0 = 0x00000000;
    uint32_t argument_8 = 0x000001AA;
    uint8_t rec_array[5];
    
    UART_transmit_string(UART1, "Entering SD_CARD INIT \n\r", 0);
    
    init_SD_CS(SD_CS_port, SD_CS_pin); // Creates PB4 for the /CS, initial value set to 1
    SD_CS_active();
    
    init_SCK(SCK_PORT_SD, SCK_PIN_SD); //Creates PB7 which acts as the SCK. Initial value of 0.
    SCK_low();
    

    // (6a) 10 SPI_transfers of 0xFF
    for(uint8_t i = 0; i<10; i++){
        UART_transmit_string(UART1, "Sending initial 10 transfers of 0xFF... \n\r", 0);
        uint8_t send_value = 0xFF; 
        rcvd_value = SPI_transfer(SPI_addr,send_value);
    }
    
    /****************************CMD0*********************************/
    if(error_status==normal){ // (6b)
        UART_transmit_string(UART1, "Sending CMD0... \n\r", 0);
        //Clear the /CS bit (PB4) to start the communication
        SD_CS_inactive();
        // Send CMD0 with argument 0x00;
        send_command(SPI_addr, 0, argument_0);
        //Receive response and check R1
        receive_response (SPI_addr, R1_bytes, rec_array);
        R1 = rec_array[0];
        //Set /CS = 1, stop transmission
        SD_CS_active();
        if(R1!=0x01){
            error_status = CMD0_error;
            UART_transmit_string(UART1, "CMD0: R1 is not equal to 0x01 \n\r", 0);
        }
    }
    /*****************************************************************/
    
    /****************************CMD8*********************************/
    // Not sure if we need to read the R7 response here too
    if(error_status==normal){ // (6c)
        UART_transmit_string(UART1, "Sending CMD8... \n\r", 0);
        //Clear the /CS bit (PB4) to start the communication
        SD_CS_inactive();
        // Send CMD8 with argument 0x000001AA;
        send_command(SPI_addr, 8, argument_8);
        //Receive response and check R1
        receive_response (SPI_addr, OCR_bytes, rec_array);
        R1 = rec_array[0];
        host_supply_v = rec_array[3]; // Read host supply voltage
        //Set /CS = 1, stop transmission
        SD_CS_active();
        if(R1!=0x01){
            error_status = CMD8_error;
            UART_transmit_string(UART1, "CMD8: R1 is not equal to 0x01 \n\r", 0);
        }
        if(R1 == 0x05){
            error_status = illegal_command; // Checks for illigal command
            UART_transmit_string(UART1, "CMD8: R1 is equal to 0x05 ILLEGAL \n\r", 0);
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
    // Not sure if we need to read the R3 response here too
    if(error_status==normal){ // (6d)
        UART_transmit_string(UART1, "Sending CMD58... \n\r", 0);
        //Clear the /CS bit (PB4) to start the communication
        SD_CS_inactive();
        // Send CMD58 with argument 0x00;
        send_command(SPI_addr, 58, argument_0);
        //Receive response and check R1
        receive_response (SPI_addr, OCR_bytes, rec_array);
        R1 = rec_array[0];
        operating_v = rec_array[2];        
        //Set /CS = 1, stop transmission
        SD_CS_active();
        
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
    
        /*******************************ACMD41***************************/
    if (error_status == normal) { // (6e)
    do{  
        //Clear the /CS bit (PB4) to start the communication
        SD_CS_inactive();
        //TODO: Check send command 55
        send_command (SPI_addr, 55, argument_0); //Sends command 55 with arg = 0
        //Check the R1 Response
        receive_response (SPI_addr, R1_bytes, rec_array); //Recieve one byte of data (R1 response), stored in the 0th element of rec_array
        R1 = rec_array[0];
        //Send command 41
        send_command(SPI_addr, 41, ACMD41_arg); // Arg by default is 0x40000000
        // Check the R1 response
        receive_response (SPI_addr, R1_bytes, rec_array); //Recieve one byte of data (R1 response), stored in the 0th element of rec_array
        R1 = rec_array[0];
        //Set /CS = 1, stop transmission
        SD_CS_active();
        //store the r1 response
        R1 = rec_array[0];
        timeout++;
        UART_transmit_string(UART1, "ACMD41 Looping... \n\r", 0);
    }while((R1 != normal) && (timeout <= SD_CMD_TIMEOUT));

    if (timeout == 0) {
        error_status = 10;
        UART_transmit_string(UART1, "ACMD41 Timeout occurred :( \n\r", 0);
    }
    
    // (6f)
    if(R1 == normal){
        SD_CS_inactive();
        send_command(SPI_addr, 58, argument_0); // Send command 58
        receive_response(SPI_addr,OCR_bytes,rec_array); // Check R3
        SD_Card_type_g = rec_array[1];
        SD_CS_active();
        if (SD_Card_type_g==high_capacity) {
            UART_transmit_string(UART1, "High capacity card! \n\r", 0);
            SD_Card_Type = 0; // high capacity card
        } else if(SD_Card_type_g==std_capacity) {
            error_status = 7;
            UART_transmit_string(UART1, "Standard capacity! Will handle block_number later \n\r", 0);
            SD_Card_Type = 9; // standard capacity
        } else {
            error_status = 8;
            UART_transmit_string(UART1, "No card detected :( \n\r", 0); 
        }
        R1 = rec_array[0];
    }
}
    
    // (6f)
    /* If the SD card is successfully activated CMD58 should be sent again to 
     * Reevaluate the R3 response
     * MSB of the OCR should be set to 1 to power up SD card. (bit 31)
     * CCS bit 30 should be set to designate high capacity card
     * Return an error if standard capacity cards are not supported
     * 
     */
    return error_status; // (6g)
    
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
        Arg = 0;
        Response 5 bytes should be 
            R1 = 0x01
            OCR = 0x00FF8000
        */
}

// **************************read_block****************************************

uint8_t read_block (volatile SPI_t *SPI_addr, uint8_t array[ ],uint16_t num_bytes) {
    uint8_t rcvd_value;
    uint8_t error_status = normal;
    
    
     // Wait for initial 0x00 response (indicates no errors)
    do {
        rcvd_value = SPI_transfer(SPI_addr, 0xFF);
    } while(rcvd_value==0xFF);
    
    if (error_status==normal) {
        if(rcvd_value!=0x00) { // if R1 is not 0x00
            error_status = 1; // Error if response is not 0x00
            UART_transmit_string(UART1, "READ BLOCK: R1 is not 0x00 \n\r", 0);
        }
    }
    
    // Wait for start token 0xFE
    do {
        rcvd_value = SPI_transfer(SPI_addr, 0xFF);
    } while(rcvd_value==0xFF);
    
    if (error_status==normal) {
        if(rcvd_value!=0xFE) {
            error_status = 2; // Error if start token not received
            UART_transmit_string(UART1, "READ BLOCK: Data Start is not 0xFE \n\r", 0);
        }
    }
    
    // Read the specified number of bytes
    for(uint16_t index=0;index<num_bytes;index++) {
        rcvd_value=SPI_transfer(SPI_addr, 0xFF);
        array[index]=rcvd_value;
    }
    
    // Read and discard CRC bytes (2 bytes)
    rcvd_value=SPI_transfer(SPI_addr,0xFF); // CRC Byte 1
    rcvd_value=SPI_transfer(SPI_addr,0xFF); // CRC Byte 2 
    rcvd_value=SPI_transfer(SPI_addr,0xFF); // one final SPI transfer
    
    return error_status; // return 0 if successful
}

// BONUS :) ******************************************************************
uint8_t adjust_block_number(uint32_t block_number) {
    uint8_t response;
    uint8_t error_status = normal;
    
    // Only send CMD16 if it's a standard capacity card (SDSC)
    if (SD_Card_Type == 9) {  // Check if SDSC
        SD_CS_inactive();
        response = send_command(SPI0, 16, block_number);  // CMD16 with 512-byte block length
        SD_CS_active();
        if (response != 0x00) {
            // Error handling: CMD16 failed
            error_status = 1;  // Return an error code if CMD16 fails
            UART_transmit_string(UART1, "CMD16 error. Standard Capacity handling error.",0);

        }
        if (error_status == normal) {
            UART_transmit_string(UART1, "CMD16 Successfully sent. Standard Capacity handled.",0);
        }
    }
    return 0;  // Success
}
// ****************************************************************************