/* 
 * File:   gpio_1.c
 * Author: owenhancock
 *
 * Created on September 17, 2024, 11:02 AM
 */

// This file is used to solve question 3

#include "gpio_1.h"

// Function implementation to initialize a GPIO pin as an output
void GPIO_output_init(volatile GPIO_t * addr, uint8_t pinmask) {
    // Set the pin value to high (off for LEDs) by default
    addr -> GPIO_PORT |= pinmask;
    // Set the pin direction as output by setting the corresponding bit in the DDR
    addr -> GPIO_DDR |= pinmask;
}

void GPIO_output_set_value (volatile GPIO_t * addr, uint8_t pinmask, uint8_t value) {
    if (value) {
        // Set the pin to high
        addr -> GPIO_PORT |= pinmask;
    }
    else {
        // Set the pin to low
        addr -> GPIO_PORT &= ~pinmask;
    }
}