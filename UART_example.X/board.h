/*
 * board.h
 *
 * Created: 9/4/2020 11:57:19 AM
 *  Author: youngerr
 */ 



// Microcontroller: ATMEGA324PB
#ifndef BOARD_H_
#define BOARD_H_

#include "peripherals.h"
#include "LEDS.h"

#define F_CPU (16000000UL)
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


extern led_inst_t led0, led1, led2, led3;


#endif /* BOARD_H_ */