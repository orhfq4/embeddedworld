/* 
 * File:   peripherals.h
 * Author: Owen Hancock
 *
 * Created on September 17th, 2024
 */

// This file was completed for question 1

#ifndef PERIPHERALS_H
#define	PERIPHERALS_H
#include <avr/io.h>

/* GPIO */
typedef struct GPIO
{
	volatile uint8_t GPIO_PIN; // 0
	volatile uint8_t GPIO_DDR; // 1
	volatile uint8_t GPIO_PORT; // 2
} GPIO_t;

#define PA ((volatile GPIO_t *)(&PINA)) // 0x20
#define PB ((volatile GPIO_t *)(&PINB))
#define PC ((volatile GPIO_t *)(&PINC))
#define PD ((volatile GPIO_t *)(&PIND))
#define PE ((volatile GPIO_t *)(&PINE))




#endif	/* PERIPHERALS_H */

