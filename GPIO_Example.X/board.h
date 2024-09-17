/*
 * board.h
 *
 * Created: September 17th, 2024
 *  Author: Owen Hancock
 */ 

// This file was completed for question 1

// Microcontroller: ATMEGA324PB
#ifndef BOARD_H_
#define BOARD_H_
#include "gpio_3.h"
#include "led_3.h"
#include "peripherals.h" // included to define pins and ports

#define F_CPU (16000000UL) // sets CPU frequency
#define F_DIV (1)


/* LEDS */
#define LED0_PORT (PC)
#define LED0_PIN (1<<7)
/* Assumes the OLED board is connected to Connector EXT4 */
#define LED1_PORT (PB)
#define LED1_PIN (1<<3)
#define LED2_PORT (PE)
#define LED2_PIN (1<<4)
#define LED3_PORT (PA)
#define LED3_PIN (1<<7)

// LED3 Instance
extern LED_t LED3;

#endif /* BOARD_H_ */