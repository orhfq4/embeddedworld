/* 
 * File:   led_1.h
 * Author: owenhancock
 *
 * Created on September 17, 2024, 11:02 AM
 */

// This file is used to complete question 3

#ifndef LED_1_H_
#define LED_1_H_
#include "board.h"
#include "peripherals.h"
#include "gpio_1.h"

// Function prototype to intialize the LED
void LED_init(volatile GPIO_t * addr, uint8_t pinmask);
// Function to set the value of the LED (on/off)
void LED_set_value(volatile GPIO_t * addr, uint8_t pinmask, uint8_t value);

#endif // led_1.h   