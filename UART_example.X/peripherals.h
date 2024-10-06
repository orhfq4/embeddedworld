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
	volatile uint8_t UART_UCSRA;
	volatile uint8_t UART_UCSRB;
	volatile uint8_t UART_UCSRC;
	volatile uint8_t UART_UCSRD;
	volatile uint8_t UART_UBBRL;
	volatile uint8_t UART_UBBRH;
	volatile uint8_t UART_UDR;
} UART_t;

#define UART0 ((volatile UART_t *) (0xC0) // or (&UCSRA0)
#define UART1 ((volatile UART_t *) (0xC8) // or (&UCSRA1)
#define UART2 ((volatile UART_t *) (0xD0) // or (&UCSRA2)

#define UART0 (&(_SFR_MEM8(0xC0U)))   // or (&UCSRA0) 
#define UART1 (&(_SFR_MEM8(0xC8U)))   // or (&UCSRA1) 
#define UART2 (&(_SFR_MEM8(0xD0U)))   // or (&UCSRA2)

#define UCSRA (0) 
#define UCSRB (1) 
#define UCSRC (2) 
#define UCSRD (3) 
#define UBRRL (4) 
#define UBRRH (5) 
#define UDR   (6)

#endif	/* PERIPHERALS_H */

