/* 
 * File:   UART.h
 * Author: owenhancock
 *
 * Created on September 30, 2024, 10:31 AM
 */

// Need to complete for question 2

#ifndef UART_H
#define	UART_H

/*
 Need to add in the following functions:
 * UART_init();
 * UART_transmit();
 * UART_receive();
 
 */

#ifdef	__cplusplus
extern "C" {

void UART_Init(volatile UART_t *UART_addr, uint16_t baud_rate);
uint8_t UART_Transmit(volatile UART_t *UART_addr, uint8_t send);
uint8_t UART_Receive(volatile UART_t *UART_addr);


}

#endif	/* UART_H */

