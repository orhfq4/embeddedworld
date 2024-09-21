/* 
 * File:   led_3.h
 * Author: owenhancock
 *
 * Created on September 17, 2024, 11:02 AM
 */

// Unsure about this file. We haven't learned this yet
// This file is used to solve question 5

#ifndef LED_3_H
#define	LED_3_H
#include "peripherals.h"

#include "gpio_3.h"

// LED Object
typedef struct {
    GPIO_init_t super;   // Inherit GPIO_init_t
    uint8_t active_low; // Indicates if the LED is active low
} LED_t;

// Constructor for LED
void LED_init_3(LED_t * const led, volatile GPIO_t *port, uint8_t pinmask, uint8_t initial_state, uint8_t active_low);

// Function to set the state of the LED
void LED_set_value_3(LED_t * const led, uint8_t state);

#endif	/* LED_3_H */

