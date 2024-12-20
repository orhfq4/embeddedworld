// STA013.c

#include "GPIO_Outputs.h"
#include "STA013.h"
#include "TWI.h"
#include "UART.h"
#include "board.h"
#include <util/delay.h>
#include "Config_Arrays.h"
#include "UART_Print.h"
#include <stdio.h>
#include <avr/pgmspace.h>

//bring in CONFIG arrays to be referenced later
extern const uint8_t CONFIG[3998];
extern const uint8_t CONFIG2[50];
extern const uint8_t CONFIG3[50];


// "Magic Numbers"
#define STA013_RESET_PIN &STA013_reset
#define STA013_DEVICE_ADDRESS 0x43
#define NUM_BYTES_TO_READ 3
#define STA013_ID_REGISTER_VALUE 0xAC
#define TIMEOUT_VAL 50  // Maximum number of retry attempts
#define NORMAL (0)

//************************************* STA013_init (Question 3) ***********************
void configArray(const uint8_t CONFIG[]){
    uint16_t index=0;
    uint8_t send_array[2];
    uint16_t timeout_step3 = 50;
    uint8_t error_status = NORMAL;
    char debug_buffer[100];// Buffer for debugging!
    // Send configuration data array  
    uint16_t big_timeout = 5000;
    do {
        send_array[0] = pgm_read_byte(&CONFIG[index]); // internal reg. address
        index++;
        send_array[1] = pgm_read_byte(&CONFIG[index]); // value for the reg.
        index++;
        timeout_step3 = 50;
        if (send_array[0] != 0xFF || send_array[1] != 0xFF){ // Added if statment to not transmit if the last two array values are 0xFF
            do {
                error_status = TWI_master_transmit(TWI1,STA013_DEVICE_ADDRESS, 2, send_array);
                timeout_step3--;
                //UART_transmit_string(UART1, "Config sent successfully...\n\r", 0);
            } while((error_status!=0x00)&&(timeout_step3!=0));
        }
        big_timeout--;
       //sprintf(debug_buffer, "Index ct: 0x%04X\n\r", index);
       //UART_transmit_string(UART1, debug_buffer, 0);
    } while (((send_array[0] != 0xFF) || (send_array[1] != 0xFF)) && (big_timeout!=0));
    
    // Check for successful configuration or timeout
    if (timeout_step3 != 0) {
        sprintf(debug_buffer, "Config sent successfully...\n\r");
        UART_transmit_string(UART1, "Config sent successfully...\n\r", 0);
    } else {
        sprintf(debug_buffer, "Config failed to send after multiple attempts\n\r");
        UART_transmit_string(UART1, debug_buffer, 0);
    }
}

void STA013_init() {
    uint8_t rec_array[NUM_BYTES_TO_READ] = {0}; // Array to hold received data
    uint8_t timeout = TIMEOUT_VAL;
    uint8_t error_status = NORMAL;
    char prnt_bffr[50]; // Buffer for UART printing
    
    // GPIO instances for STA013
    gpio_inst_t STA013_reset;

    gpio_inst_t STA013_data_req;

    gpio_inst_t STA013_BIT_EN;
    
 
    
    // Initialize reset pin as output, start high
    GPIO_output_ctor(&STA013_reset, PB, (1 << 1), GPIO_SET);

    // Initialize data_req pin as input (no need to set value)
    GPIO_output_ctor(&STA013_data_req, PC, (1 << 6), GPIO_CLEAR);

    // Initialize BIT_EN pin as output, start low
    GPIO_output_ctor(&STA013_BIT_EN, PD, (1 << 6), GPIO_CLEAR);

    // Step 1: Reset the STA013 by pulsing PB1 low for at least 100ns
    
    // Pulse the reset pin low
    GPIO_output_set_value(&STA013_reset, GPIO_CLEAR); // Set low
    _delay_ms(10); // Wait at least 100ns
    GPIO_output_set_value(&STA013_reset, GPIO_SET); // Set high

    // ******************************* STA013 DEBUG (Question 5) **********************************
    
    // Step 2: Attempt to read 3 bytes from STA013 in a loop
    do {
        error_status = TWI_master_receive(TWI1, STA013_DEVICE_ADDRESS, NUM_BYTES_TO_READ, rec_array);
        timeout--;
    } while ((error_status != NORMAL) && (timeout != 0));
    
    if (rec_array[2] != STA013_ID_REGISTER_VALUE) {
        sprintf(prnt_bffr, "Error: STA013 ID mismatch (expected 0xAC, got 0x%02X)\n\r", rec_array[2]);
        UART_transmit_string(UART1, prnt_bffr, 0);
    }
    
    if (timeout!=0) {
        sprintf(prnt_bffr, "ID Value=%2.2X\n\r",rec_array[2]);
        UART_transmit_string(UART1, prnt_bffr, 0);
    } else {
        sprintf(prnt_bffr, "Error: STA013 config failed after multiple attempts\n\r");
        UART_transmit_string(UART1, prnt_bffr, 0);
    }
    
        //****************************************** (BONUS) *************************************
    
    /*
     * Could get bonus points if we use optional function prototype for receive or transmit functions
     */
    
    //********************* Now configure the STA013 with config_arrays.c (Question 6) ***********************
    
    configArray(CONFIG);
    configArray(CONFIG2);
    configArray(CONFIG3);
            
    
    // Step 3: Handle software reset after config
    // Software reset may need a short delay after sending the reset command
    _delay_ms(10); // Wait for reset to complete (10ms or as per datasheet)
    
}




