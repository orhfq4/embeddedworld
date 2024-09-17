#ifndef LED_2_H_
#define LED_2_H_
#include "gpio_2.h" // include inline gpio functions

// Static inline function to initialize an LED
static inline void LED_init_2(volatile GPIO_t * addr, uint8_t pinmask) {
    GPIO_output_init_2(addr, pinmask); // Call the GPIO init function
}

// Static inline function to set value of an LED (on/off)
static inline void LED_set_value_2(volatile GPIO_t * addr, uint8_t pinmask, uint8_t value) {
    GPIO_output_set_value_2(addr, pinmask, value); // call the GPIO set value function
}

#endif // led_2.h