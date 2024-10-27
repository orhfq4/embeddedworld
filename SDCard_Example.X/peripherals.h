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


/***** UARTS ******/
typedef struct _UART
{
	volatile uint8_t UCSRA;
	volatile uint8_t UCSRB;
	volatile uint8_t UCSRC;
	volatile uint8_t UCSRD;
	volatile uint8_t UBBRL;
	volatile uint8_t UBBRH;
	volatile uint8_t UDR;
} UART_t;

#define UART0 ((volatile UART_t *) &UCSR0A)
#define UART1 ((volatile UART_t *) &UCSR1A)
#define UART2 ((volatile UART_t *) &UCSR2A)

/***** SPI PORTS ******/
// Define the SPI register struct for memory-mapped access
typedef struct SPI
{
    volatile uint8_t SPCR; // SPI Control Register
    volatile uint8_t SPSR; // SPI Status Register
    volatile uint8_t SPDR; // SPI Data Register
} SPI_t;

// Define pointers to SPI0 and SPI1 with specific memory addresses
#define SPI0 ((SPI_t *)0x004C) // Starting address for SPI0
#define SPI1 ((SPI_t *)0x00AC) // Starting address for SPI1

#endif	/* PERIPHERALS_H */
