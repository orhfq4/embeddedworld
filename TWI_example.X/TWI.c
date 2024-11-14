// TWI.c
#include "TWI.h"

#define NORMAL (0) // error_status normal

uint8_t TWI_master_init(volatile TWI_t *TWI_addr, uint32_t I2C_freq) {
    uint8_t prescale = 0;
    prescale = (((F_CPU/OSC_DIV)/I2C_freq)-16UL)/(2UL*255); // TWBR must be less than 255
    
    if (prescale < 1) {
        prescale = 1;
        // need to write prescale to TWSR
        // TWPS are two lowest bits of TWSR
    }
    else if ((prescale >= 1) && (prescale < 4)) {
        prescale = 4;
        // need to write prescale to TWSR
        // TWPS are two lowest bits of TWSR
    }
    else if ((prescale >= 1) && (prescale < 4)) {
        prescale = 4;
        // need to write prescale to TWSR
        // TWPS are two lowest bits of TWSR
    }
    else if ((prescale >= 4) && (prescale < 16)) {
        prescale = 16;
        // need to write prescale to TWSR
        // TWPS are two lowest bits of TWSR
    }
    else if ((prescale >= 16) && (prescale < 64)) {
        prescale = 64;
        // need to write prescale to TWSR
        // TWPS are two lowest bits of TWSR
    }
    else {
        UART_transmit_string(UART1, "Please select a higher clock rate. \n\r SCL < 500 Hz, Prescale = 64, TWBR = 255\n\r", 0);
    }
    
    uint8_t TWBR_value = (((F_CPU/OSC_DIV)/I2C_freq)-16UL)/(2UL*prescale);
    
    if (TWBR_value >= 256) {
        UART_transmit_string(UART1, "Uh oh! TWBR_value is greater than 256. Need to recalculate.\n\r", 0);
    }
    else {
        // write the TWBR_value to the TWBR register (Offset 0)
    }
    
    return TWI_addr; // not sure what value to return here
}

uint8_t TWI_master_transmit(volatile TWI_t *TWI_addr, uint8_t slave_addr, 
        uint16_t num_bytes, uint8_t *array) {
    // returns an error status which is why there is uint8_t
    
    uint8_t error_status = NORMAL;
    
    // start a TWI communication
    TWI_addr->TWI_TWCR = ((1<<TWINT)|(1<<TWSTA)|(1<<TWEN));
    uint16_t timeout = 0;
    
    // Wait for TWINT bit to be set in TWCR
    do {
        error_status = (TWI_addr -> TWI_TWCR);
        timeout++;
    } while ((error_status & (1<<TWINT) == 0) && (timeout!=0));
    // if(timeout==0) error_status = BUS_BUSY;
    
    // If statement used to determine if next task is done or exit
    if (error_status == NORMAL) {
        // Read the error_status value to determine what happens next
        uint8_t temp8 = ((TWI_addr->TWI_TWSR)&0xF8); // 1111 1000 Gets rid of TWDS (lowest 3 bits 000)
        
        // Device Address + Write bit (SLA + W)
        uint8_t send_value = slave_addr<<1; // LSB will be '0'
        
        // If start was sent, then send SLA+W
        if (temp8 == 0x08) { // Start sent // 0x10 is a repeated start
            (TWI_addr->TWI_TWDR) = send_value;
            (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEN=1));
        }
        // Should check for other error conditions here as well
    }
    
    // Pick up from slide 39
   
    
}