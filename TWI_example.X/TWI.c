// TWI.c
#include "TWI.h"
#include "UART_Print.h"

// DEFINES FOR ERRORS
#define NORMAL (0) // error_status normal
#define BUS_BUSY_ERROR (1)
#define NACK_ERROR (2)
#define PRESCALE_ERROR (3)
#define TWBR_ERROR (4)
#define ERROR_0x18 (5)
#define OTHER_ERROR (6)
#define ARBITRATION_ERROR (7)
#define INVALID_FREQ_ERROR (8)

// To account for "Magic Numbers"
#define TIMEOUT_LIMIT (1000)
#define PRESCALE_1    (0x00)
#define PRESCALE_4    (0x01)
#define PRESCALE_16   (0x02)
#define PRESCALE_64   (0x03)
#define TWI_START_ACK       (0x08)
#define TWI_REP_START_ACK   (0x10)
#define TWI_SLA_W_ACK       (0x18)
#define TWI_SLA_W_NACK      (0x20)
#define TWI_DATA_ACK        (0x28)
#define TWI_DATA_NACK       (0x30)
#define TWI_ARB_LOST        (0x38)



//******************************** TWI_master_init (Question 1) ********************************************

uint8_t TWI_master_init(volatile TWI_t *TWI_addr, uint32_t I2C_freq) {
    // returns an error status which is why there is uint8_t
    uint8_t prescale = 0;
    uint8_t error_status = 0;
    
    if (I2C_freq == 0) {
    error_status = INVALID_FREQ_ERROR;
    UART_transmit_string(UART1, "Invalid I2C frequency: 0 Hz.\n\r", 0);
    }

    prescale = (((F_CPU/OSC_DIV)/I2C_freq)-16UL)/(2UL*255); // TWBR must be less than 255

    if (prescale < 1) {
        prescale = 1;
        TWI_addr->TWI_TWSR &= ~0x03; // Clear TWPS bits (mask with 0xFC)
        TWI_addr->TWI_TWSR |= PRESCALE_1; // Set TWPS to 00
    }
    else if ((prescale >= 1) && (prescale < 4)) {
        prescale = 4;
        TWI_addr->TWI_TWSR &= ~0x03; // Clear TWPS bits (mask with 0xFC)
        TWI_addr->TWI_TWSR |= PRESCALE_4; // Set TWPS to 01
    }
    else if ((prescale >= 4) && (prescale < 16)) {
        prescale = 16;
        TWI_addr->TWI_TWSR &= ~0x03; // Clear TWPS bits (mask with 0xFC)
        TWI_addr->TWI_TWSR |= PRESCALE_16; // Set TWPS to 10
    }
    else if ((prescale >= 16) && (prescale < 64)) {
        prescale = 64;
        TWI_addr->TWI_TWSR &= ~0x03; // Clear TWPS bits (mask with 0xFC)
        TWI_addr->TWI_TWSR |= PRESCALE_64; // Set TWPS to 11
    }
    if (prescale > 64) {
        error_status = PRESCALE_ERROR;
        UART_transmit_string(UART1, "Please select a higher clock rate. \n\r SCL < 500 Hz, Prescale = 64, TWBR = 255\n\r", 0);
    }
    
    // Calculate the TWBR_value based on the selected prescale
    uint8_t TWBR_value = (((F_CPU/OSC_DIV)/I2C_freq)-16UL)/(2UL*prescale);
    
    if (TWBR_value >= 256) {
        error_status = TWBR_ERROR;
        UART_transmit_string(UART1, "Uh oh! TWBR_value is greater than 256. Need to recalculate.\n\r", 0);
    }
    else {
        // Write the TWBR_value to the TWBR register (Offset 0)
        TWI_addr->TWI_TWBR = TWBR_value;
    }
    
    return error_status;
}

//******************************** TWI_master_receive (Question 2) ********************************************

uint8_t TWI_master_receive(volatile TWI_t *TWI_addr, uint8_t slave_addr, 
        uint16_t num_bytes, uint8_t * rec_array) {
    // returns an error status which is why there is uint8_t
    
    uint8_t error_status = NORMAL;
    uint8_t status = 0;
    uint8_t temp8 = 0;
    uint8_t index = 0;

    // Start a TWI Communication (same as transmit)
    (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWSTA)|(1<<TWEN));
    
    // Wait for the TWINT bit to be set in the TWCR (same as transmit)
    uint16_t timeout = 0;
    
    do {
        status = (TWI_addr -> TWI_TWCR);
        timeout++;
    } while (((status & (1<<TWINT)) == 0) && (timeout!=TIMEOUT_LIMIT));
    
    if (timeout == TIMEOUT_LIMIT) {
        error_status = BUS_BUSY_ERROR;
        UART_transmit_string(UART1, "Uh oh! Timeout Error! Bus is busy.\n\r", 0);
    }
    
    if (error_status == NORMAL) {
       // Read the error_status value to determine what happens next (same as transmit)
        temp8 = ((TWI_addr->TWI_TWSR)&0xF8); // 1111 1000 Gets rid of TWDS (lowest 3 bits 000)
        
        // Device Address + Write bit (SLA + R)
        uint8_t send_value = (slave_addr<<1) | 0x01; // LSB will be '1'
        
        // If start was sent, then send SLA+R (temp==0x10 is for repeated start)
        if ((temp8==0x08 || (temp8==0x10))) { // start sent
            (TWI_addr->TWI_TWDR) = send_value;
            (TWI_addr->TWI_TWCR) = ((1<<TWINT) | (1<<TWEN));
        } else {
            error_status = OTHER_ERROR;
            UART_transmit_string(UART1, "Uh oh! Start condition failed.\n\r", 0);
        }
        
        // Use a while loop to send data bytes until all bytes are sent or an error occurs
        while((num_bytes!=0)&&(error_status==NORMAL)) {
            if(temp8==0x40) { // SLA+R sent, ACK Received
                // good
            }
            if (num_bytes == 1) { // Send stop condition if only 1 byte is received
                (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(0<<TWEA)|(1<<TWEN));
            }
            else {
                (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEA)|(1<<TWEN));
            }
            
            // Wait until TWINT is set
            do {
                status = (TWI_addr->TWI_TWCR);
            } while((status&0x80)==0);
            
            // Read the status value to determine what to do next
            temp8=((TWI_addr->TWI_TWSR)&0xF8); // Clear the lower 3 bits
            
            // Repeat the loop until:
            // 1) There are no more bytes to receive
            // 2) An error occurs
            // If else statements below check the above:
            
            if (temp8==0x50) { // Data byte received, ACK sent
                num_bytes--;
                rec_array[index]=(TWI_addr->TWI_TWDR);
                index++;
                if(num_bytes==1) { // Send stop condition if only 1 byte is received
                    (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(0<<TWEA)|(1<<TWEN)); // Disable ACK for last byte
                }
                else {
                    (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEA)|(1<<TWEN)); // Continue sending ACK
                }
            } else if(temp8==0x58) { // Data byte received, NACK sent
                // Read the final data byte
                num_bytes--;
                rec_array[index]=(TWI_addr->TWI_TWDR);
                index++;
                (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWSTO)|(1<<TWEN));
                // Wait for TWSTO to return to 0
            } else {
                // If any other status code occurs, return error
                error_status = OTHER_ERROR;
                UART_transmit_string(UART1, "Uh oh! Unexpected TWI status received.\n\r", 0);
                return error_status;
            }
        }   
    }
    return error_status; // SUCCESS!
    
    //****************************************** (BONUS) *************************************
    
    // Optional Function prototype can be implemented for bonus points:
    // Could try it once we know the transmit function works
    // Additionally we could try implementing non-blocking methods
    
    /*
     * With the original prototype, the internal address is placed in the data array
     * With this prototype, the internal address is a separate value
     * The int_addr_size is used to determine how many bytes of internal_addr are used and sent
     * If int_addr_size = 0, then internal_addr is not used
     * If int_addr_size = 1, then the least significant byte is used
     * If int_addr_size = 2, then the two least significant bytes are used
     * If int_addr_size = 3, then the three least significant bytes are used
     * The more significant byte is sent first
     * 
     * The bytes are sent before the data bytes and in the same manner as the data bytes
     * 
     * The receive function cannot send an internal address
     * If int_addr_size!=0 then the TWI_master_receive function would call the
     * TWI_master_trasnmit with num_bytes=0 to send the internal address only
     */
}

//******************************** TWI_master_transmit (Question 4) ********************************************

uint8_t TWI_master_transmit(volatile TWI_t *TWI_addr, uint8_t slave_addr, 
        uint16_t num_bytes, uint8_t *array) {
    // returns an error status which is why there is uint8_t
    
    uint8_t error_status = NORMAL;
    uint8_t status = 0;
    
    // Start TWI communication (send START condition)
    TWI_addr->TWI_TWCR = ((1<<TWINT)|(1<<TWSTA)|(1<<TWEN));
    uint16_t timeout = 0;
    
    // Wait for TWINT to be set (indicating start condition is transmitted)
    do {
        status = (TWI_addr -> TWI_TWCR);
        timeout++;
    } while (((status & (1<<TWINT)) == 0) && (timeout!=TIMEOUT_LIMIT));
    
    if (timeout == TIMEOUT_LIMIT) {
        error_status = BUS_BUSY_ERROR;
        UART_transmit_string(UART1, "Uh oh! Timeout Error! Bus is busy.\n\r", 0);
    }
    
    // If statement used to determine if next task is done or exit
    if (error_status == NORMAL) {
        // Read the error_status value to determine what happens next
        uint8_t temp8 = ((TWI_addr->TWI_TWSR)&0xF8); // 1111 1000 Gets rid of TWDS (lowest 3 bits 000)
        
        // Device Address + Write bit (SLA + W)
        uint8_t send_value = slave_addr<<1; // LSB will be '0'
        
        // If start was sent, then send SLA+W
        if (temp8 == TWI_SLA_W_ACK) { // SLA + W sent, ACK received
            (TWI_addr->TWI_TWDR) = send_value;
            (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEN)); // Start transmission
            UART_transmit_string(UART1, "Starting Transmission...\n\r", 0);
        } else if(temp8==TWI_SLA_W_NACK){
            (TWI_addr->TWI_TWCR)=((1<<TWINT)|(1<<TWSTO)|(1<<TWEN));
            do{
                status=(TWI_addr->TWI_TWCR);
            }while((status & (1<<TWSTO))!=0); // Wait for STOP condition
            error_status = NACK_ERROR;
            UART_transmit_string(UART1, "Uh oh! Nack Error. 0x20\n\r", 0);
        } else if (temp8 == TWI_DATA_NACK) {  // NACK received after data byte
            error_status = NACK_ERROR;
            UART_transmit_string(UART1, "Uh oh! Nack Error. 0x30\n\r", 0);
        } else if (temp8 == TWI_ARB_LOST) {  // Arbitration lost
            error_status = ARBITRATION_ERROR;
            UART_transmit_string(UART1, "Uh oh! Arbitration Error. 0x38\n\r", 0);
        }else {
            error_status = OTHER_ERROR; // for handling other errors
            UART_transmit_string(UART1, "Uh oh! Unrecognized command.\n\r", 0);
        }
    }
    
    // If statement used to determine if next task is done or exit
    if (error_status == NORMAL) {
        // Now send the data bytes in the array
        for (uint16_t i = 0; i < num_bytes; i++) {
        // Wait for TWINT flag to be set before sending the next byte
        timeout = 0;
        do {
            status = TWI_addr->TWI_TWCR;
            timeout++;
        } while ((status & (1 << TWINT)) == 0 && timeout < TIMEOUT_LIMIT);
        
        if (timeout == TIMEOUT_LIMIT) {
            error_status = BUS_BUSY_ERROR;
            UART_transmit_string(UART1, "Uh oh! Timeout Error while transmitting data.\n\r", 0);
        }

        // Check the status after each byte is transmitted
        uint8_t temp8 = (TWI_addr->TWI_TWSR) & 0xF8;  // Mask status bits
        if (temp8 == TWI_DATA_ACK) {  // Data byte transmitted, ACK received
            TWI_addr->TWI_TWDR = array[i];  // Write data to TWDR
            TWI_addr->TWI_TWCR = (1 << TWINT) | (1 << TWEN);  // Send next byte
        } else if (temp8 == TWI_DATA_NACK) {  // NACK received after data byte
            error_status = NACK_ERROR;
            UART_transmit_string(UART1, "Uh oh! Nack Error. 0x30\n\r", 0);
        } else if (temp8 == TWI_ARB_LOST) {  // Arbitration lost
            error_status = ARBITRATION_ERROR;
            UART_transmit_string(UART1, "Uh oh! Arbitration Error. 0x38\n\r", 0);
        }else {
            error_status = OTHER_ERROR; // for handling other errors
            UART_transmit_string(UART1, "Uh oh! Unrecognized command.\n\r", 0);
            }
        }
    }
    
    // After sending all data, send STOP condition
    TWI_addr->TWI_TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);  // Send STOP condition
    timeout = 0;
    do {
        status = TWI_addr->TWI_TWCR;
        timeout++;
    } while ((status & (1 << TWSTO)) == 0 && timeout < TIMEOUT_LIMIT);  // Wait for STOP condition to complete
    
    if (timeout == TIMEOUT_LIMIT) {
        error_status = BUS_BUSY_ERROR;
        UART_transmit_string(UART1, "Uh oh! Timeout Error while sending STOP condition.\n\r", 0);
    }
    
    return error_status; // SUCCESS!
    
    //****************************************** (BONUS) *************************************
    
    // Optional Function prototype can be implemented for bonus points:
    // Could try it once we know the transmit function works
    // Additionally we could try implementing non-blocking methods
    
    /*
     * With the original prototype, the internal address is placed in the data array
     * With this prototype, the internal address is a separate value
     * The int_addr_size is used to detemine how many bytes of internal_addr are used and sent
     * If int_addr_size=0, then internal_addr is not used
     * if int_add_size=1, then the least significant byte is used
     * if int_addr_size=2, then the two least significant bytes are used
     * if int_addr_size=3, then the three least significant bytes are used
     * The more significant byte is sent first
     * 
     * The bytes are sent before the data bytes and in the same manner as the data bytes
     */
}