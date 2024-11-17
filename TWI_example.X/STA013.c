// STA013.c

#include "STA013.h"
#include <stdint.h>
#include <stdio.h>
#include "GPIO_Outputs.h"
#include "TWI.h"
#include "UART.h"
#include "board.h"
#include <util/delay.h>

// "Magic Numbers"
#define STA013_RESET_PIN &STA013_reset
#define STA013_DEVICE_ADDRESS 0x43
#define NUM_BYTES_TO_READ 3
#define STA013_ID_REGISTER_VALUE 0xAC
#define TIMEOUT_VAL 50  // Maximum number of retry attempts
#define NORMAL (0)

void STA013_init() {
    uint8_t rec_array[NUM_BYTES_TO_READ] = {0}; // Array to hold received data
    uint8_t error_status = NORMAL;
    uint8_t timeout = TIMEOUT_VAL;
    char prnt_bffr[50]; // Buffer for UART printing
    
    // GPIO instances for STA013
    gpio_inst_t STA013_reset = {
        .port_addr = PB, // Port B
        .pin_mask = (1 << 1) // PB1
    };

    gpio_inst_t STA013_data_req = {
        .port_addr = PC, // Port C
        .pin_mask = (1 << 6) // PC6
    };

    gpio_inst_t STA013_BIT_EN = {
        .port_addr = PD, // Port D
        .pin_mask = (1 << 6) // PD6
    };
    
    // Initialize reset pin as output, start high
    GPIO_output_ctor(&STA013_reset, PB, (1 << 1), GPIO_SET);

    // Initialize data_req pin as input (no need to set value)
    GPIO_output_ctor(&STA013_data_req, PC, (1 << 6), GPIO_CLEAR);

    // Initialize BIT_EN pin as output, start low
    GPIO_output_ctor(&STA013_BIT_EN, PD, (1 << 6), GPIO_CLEAR);

    // Step 1: Reset the STA013 by pulsing PB1 low for at least 100ns
    
    // Pulse the reset pin low
    GPIO_output_set_value(&STA013_reset, GPIO_CLEAR); // Set low
    _delay_us(1); // Wait at least 100ns
    GPIO_output_set_value(&STA013_reset, GPIO_SET); // Set high

    // Step 2: Attempt to read 3 bytes from STA013 in a loop
    do {
        error_status = TWI_master_receive(TWI1, STA013_DEVICE_ADDRESS, NUM_BYTES_TO_READ, rec_array);
        timeout--;
    } while ((error_status != NORMAL) && (timeout != 0));
    
    if (rec_array[2] != STA013_ID_REGISTER_VALUE) {
        sprintf(prnt_bffr, "Error: STA013 ID mismatch (expected 0xAC, got 0x%02X)\n\r", rec_array[2]);
        UART_transmit_string(UART1, 0, prnt_bffr);
    }
    
    if (timeout!=0) {
        sprintf(prnt_bffr, "ID Value=%2.2X\n\r",rec_array[2]);
        UART_transmit_string(UART1,0,prnt_bffr);
    }
    
    if (timeout == 0) {
        sprintf(prnt_bffr, "Error: STA013 config failed after multiple attempts\n\r");
        UART_transmit_string(UART1, 0, prnt_bffr);
    }
    
    /*
     * Could get bonus points if we use optional function prototype for receive or transmit functions
     */
    
    //********************************** Now configure the STA013 with config_arrays.c************************
    
    uint8_t index=0;
    uint8_t send_array;
    do {
        send_array[0] = pgm_read_byte(&CONFIG[index]); // internal reg. address
        index++;
        send_array[1] = pgm_read_byte(&CONFIG[index]); // value for the reg.
        index++;
        timeout=50;
        do {
            error_status=TWI_master_transmit(TWI1,STA013_DEVICE_ADDRESS, 2, send_array);
            timeout--;
        } while((error_status!=0)&&(timeout!=0));
    } while ((send_array[0]!=0xFF)||(send_array[1]!=0xFF)&&(timeout!=0));
    
    if(timeout!=0) sprintf(prnt_bffr, "Config sent...\n\r");
}
