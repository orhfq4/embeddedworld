#include "UART.h"
#include "board.h"
#include "LEDS.h"
#include "peripherals.h"
#include <util/delay.h>
#include <avr/io.h>

// Need to define the function implementations here
// This is for questions 3-6

// Defined private constants for modes in the UART

// Define the mode (pick one) all are defined though
#define Async_Mode (0<<6) 
#define Sync_Mode  (1<<6) 
#define MSPI_Mode  (3<<6)

// Define the parity (pick one) all are defined though
#define No_Parity   (0<<4) 
#define Even_Parity (2<<4) 
#define Odd_Parity  (3<<4)

// Define the number of stop bits (pick one) all are defined though
#define One_Stop_Bit  (0<<3) 
#define Two_Stop_Bits (1<<3)

// *******Function Comments are in UART.H********

// QUESTION 2: UART_Init implementation
// function implementation for the UART_Init.
void UART_Init(volatile UART_t *UART_addr, uint32_t baud_rate){
    // disable transmitter & receiver of the UART (safety)
    UART_addr->UART_UCSRB &= ~((1<<TXEN)|(1<<RXEN));
    
    // Disable UART interrupts
    UART_addr->UART_UCSRB &= ~((1 << RXCIE) | (1 << TXCIE) | (1 << UDRIE));
    
    // Calculate UBRR value based on U2X setting
    uint16_t UBRR_value;
    if (U2X) {
        UBRR_value = (F_CPU / (8UL * baud_rate)) - 1;
        UART_addr->UART_UCSRA |= (1<<U2X);  // Enable double speed
    } else {
        UBRR_value = (F_CPU / (16UL * baud_rate)) - 1;
        UART_addr->UART_UCSRA &= ~(1<<U2X); // Normal speed
    }
    
    
    // Set the baud rate in the upper and lower registers
    // Struct_Address -> Struct_Element
    UART_addr->UART_UBBRH =UBRR_value/256; // Calculates upper 8 bits
    UART_addr->UART_UBBRL =UBRR_value%256; // Calculates lower 8 bits

    // Set frame format (Async Mode, no parity, 1 stop bit)
    UART_addr->UART_UCSRC = (Async_Mode|No_Parity|One_Stop_Bit); // I think this is the format we need?

    // Enable transmitter & receiver of the UART
    UART_addr->UART_UCSRB = (1<<TXEN) | (1<<RXEN);
}

// QUESTION 3: UART_Transmit Implementation
// function implementation for UART_transmit
uint8_t UART_Transmit(volatile UART_t *UART_addr, uint8_t send_value){
    uint8_t status;
    do{
        // UDRE is a bit value defined in <avr/io.h>
        status = UART_addr->UART_UCSRA; // Read the status bits in UCSRA
        //blink LED0
        LED_set_value(&led0, LED_ON);
        _delay_ms(500); // 0.5s delay
        LED_set_value(&led0, LED_OFF);
        _delay_ms(500);
    }while((status&(1<<UDRE))!=(1<<UDRE));
    // Place the send_value into the USART data register
    UART_addr->UART_UDR = send_value; // optional step
    return 0; // could return send_value if you want
}
// QUESTION 4: Verify UART_transmit function works using a debugger

// QUESTION 5: UART_Receive function implementation
// function implementation for UART_receive
uint8_t UART_Receive(volatile UART_t *UART_addr){ 
    while(!(UART_addr->UART_UCSRA & (1 << RXC))){ // UART_addr -> RXC == 0
        //blink LED0
        LED_set_value(&led0, LED_ON);
        _delay_ms(500); // 0.5s delay
        LED_set_value(&led0, LED_OFF);
        _delay_ms(500);
    }
    uint8_t received_value = UART_addr->UART_UDR; 
    return received_value;
}
// QUESTION 6: Verify UART_receive function works using data visualizer