#include "UART.h"
#include "board.h"

// Need to define the function implementations here
// This is for questions 3-6

/*
 
 * UART_init();
 * UART_transmit();
 * UART_receive();
    Not sure about the actual values for each UCSR_ register - Josh
    might be goo to look at slide 24 of chaper 7? Has info making the options constants - Josh
 */

void UART_Init(volatile UART_t *UART_addr, uint16_t baud_rate){
    UBRR_value = (uint16_t)((((F_CPU/OSC_DIV)+(4UL*(2-U2X)*baud_rate))/(8UL*(2-U2X)*baud_rate))-1);
    UART_addr->UART_UCSRA = ((0<<1)|(1<<1)|(2<<1)|(3<<1)|());
    UART_addr->UART_UCSRB = ((0<<1)|(1<<1)|(2<<1)|(3<<1)|());
    UART_addr->UART_UCSRC = ((0<<1)|(1<<1)|(2<<1)|(3<<1)|());
}
uint8_t UART_Transmit(volatile UART_t *UART_addr, uint8_t send){
    uint8_t status;
    do{
        status = UART_addr->UART_UCSRA;
    }while((status&(1<<UDRE))!=(1<<UDRE));
    UART_addr->UART_UDR = send;
    return 0;
}
uint8_t UART_Receive(volatile UART_t *UART_addr){ //not sure about this one chief -Josh
    while(UARt_addr->RXC == 0){
        
    }
    UART_addr->UDR = Read_value; // maybe?
    UART_addr->RXC = 0;
    return Read_value;
}
