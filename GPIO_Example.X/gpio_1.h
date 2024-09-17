#ifndef GPIO_1_H
#define GPIO_1_H
#include "peripherals.h" // included to utilize GPIO_t

// Function to initialize a GPIO pin as an output
void GPIO_output_init(volatile GPIO_t * addr, uint8_t pinmask);

// Function to set the output of a GPIO pin
void GPIO_output_set_value(volatile GPIO_t * addr, uint8_t pinmask, uint8_t value);

#endif // gpio_1.h