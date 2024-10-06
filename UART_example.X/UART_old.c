#include "UART.h"
#include "board.h"

// Defined private constants for modes in the UART
#define Async_Mode (0<<6) 
#define Sync_Mode  (1<<6) 
#define MSPI_Mode  (3<<6)
#define No_Parity   (0<<4) 
#define Even_Parity (2<<4) 
#define Odd_Parity  (3<<4)
#define One_Stop_Bit  (0<<3) 
#define Two_Stop_Bits (1<<3

// not sure what kind of data is being outputted yet
#define 5_Bit_Data     (0<<1) 
#define 6_Bit_Data     (1<<1) 
#define 7_Bit_Data     (2<<1) 
#define 8_Bit_Data     (3<<1) 
#define 9_Bit_Data     (3<<1)  //UCSZ2 must be set in UCSRB 
#define 9_Bit_UCSZ2    (1<<2)  //UCSZ2 must be set in UCSRB


// Need to define the function implementations here
// This is for questions 3-6

// function implementation for the UART_init. # Need to resolve this.
void UART_init (volatile UART_t * UART_addr, uint32_t Baud_Rate) {
    // disable xmit & receive (safety)
    // calculate BRR value
    UART_addr -> UBRRH = (BRR_value/256); // not sure where BRR_value would be defined
    UART_addr -> UBRRL = (BRR_value%256);
    // set or clear U2x_bit to match your setting (UART_UCSRA)
    // write to UCSRB
}

// function implementation for UART_transmit. # Need to resolve this
uint8_t UART_transmit(volatile UART_t *UART_addr, uint8_t send_value) {
    uint8_t status;
    do    {
    // Read the status bits in UCSRA
    status=UART_addr->UART_UCSRA;
    // AND to isolate only UDRE, repeat while UDRE==0
    // UDRE is a bit value defined in <avr/io.h>
    // It can be replaced by your definition (#define UDRE_bit (1<<UDRE))
    } while ((status & (1 << UDRE))!=(1 << UDRE));
    
    // Place the send_value into the USART data register
    UART_addr->UART_UDR = send_value;    // Return some value
    return 0
}

// function implementation for UART_receive. # Need to resolve this.
uint8_t UART_receive(volatile UART_t *UART_addr) { // Non blocking method
    while (1) {
        //blink LED0
        value = UART_receive(UART1); // need to resolve identifier
        UART_transmit(UART1, value);
        
    }
}
