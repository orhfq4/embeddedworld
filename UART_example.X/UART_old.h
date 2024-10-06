/* 
 * File:   UART.h
 * Author: owenhancock
 *
 * Created on September 30, 2024, 10:31 AM
 */

// Need to complete for question 2

#ifndef UART_H
#define	UART_H

// function prototype for UART_init function
void UART_init (volatile UART_t * UART_addr, uint32_t Baud_Rate);

// function prototype for UART_transmit function
uint8_t UART_transmit(volatile UART_t *UART_addr, uint8_t send_value); 

// function prototype for UART_receive function
uint8_t UART_receive(volatile UART_t *UART_addr);

#endif	/* UART_H */

