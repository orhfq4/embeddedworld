#ifndef GPIO_2_H
#define GPIO_2_H
#include "peripherals.h"

// Inline function to initalize a GPIO pin as an output
static inline void GPIO_output_init_2(volatile GPIO_t * addr, uint8_t pinmask) {
    addr -> GPIO_DDR |= pinmask; // set pin direction as output
}

// Inline function to set the output value of a GPIO pin
static inline void GPIO_output_set_value_2(volatile GPIO_t * addr, uint8_t pinmask, uint8_t value) {
    if (value) {
        addr -> GPIO_PORT |= pinmask; // set pin to high
    }
    else {
        addr -> GPIO_PORT &= ~pinmask; // set pin to low
    }
}

#endif //gpio_2.h