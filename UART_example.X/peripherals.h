/* 
 * File:   peripherals.h
 * Author: Younger
 *
 * Created on September 10, 2024, 4:58 PM
 */

#ifndef PERIPHERALS_H
#define	PERIPHERALS_H

#include <avr/io.h>

/* GPIO */
typedef struct GPIO
{
	volatile uint8_t GPIO_PIN;
	volatile uint8_t GPIO_DDR;
	volatile uint8_t GPIO_PORT;
} GPIO_t;

#define PA ((volatile GPIO_t *)(&PINA))
#define PB ((volatile GPIO_t *)(&PINB))
#define PC ((volatile GPIO_t *)(&PINC))
#define PD ((volatile GPIO_t *)(&PIND))
#define PE ((volatile GPIO_t *)(&PINE))


// QUESTION 1: Defines UART struct and Defines UART registers

/***** UARTS ******/
typedef struct UART
{
	volatile uint8_t UART_UCSRA; // USART Control and Status Register A
	volatile uint8_t UART_UCSRB; // USART Control and Status Register B
	volatile uint8_t UART_UCSRC; // USART Control and Status Register C
	volatile uint8_t UART_UCSRD; // USART Control and Status Register D
	volatile uint8_t UART_UBBRL; // USART Baud Rate Register Low
	volatile uint8_t UART_UBBRH; // USART Baud Rate Register High
	volatile uint8_t UART_UDR;   // USART Data Register
} UART_t;

#define UART0 ((volatile UART_t *)(0xC0)) // or (&UCSRA0)
#define UART1 ((volatile UART_t *)(0xC8)) // or (&UCSRA1)
#define UART2 ((volatile UART_t *)(0xD0)) // or (&UCSRA2)

#endif	/* PERIPHERALS_H */

