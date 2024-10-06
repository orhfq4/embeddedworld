/* 
 * File:   UART.h
 * Author: owenhancock
 *
 * Created on September 30, 2024, 10:31 AM
 */

// Need to complete for question 2

#ifndef UART_H
#define	UART_H

// function prototype for UART_Init function
void UART_Init(volatile UART_t *UART_addr, uint16_t baud_rate);

// function prototype for UART_Transmit function
uint8_t UART_Transmit(volatile UART_t *UART_addr, uint8_t send);

// function prototype for UART_Receive function
uint8_t UART_Receive(volatile UART_t *UART_addr);

#endif	/* UART_H */

