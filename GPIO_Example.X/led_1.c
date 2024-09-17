#include "led_1.h"

// Function implementation to initialize the LED by calling the GPIO initialize function
void LED_init(volatile GPIO_t * addr, uint8_t pinmask) {
    GPIO_output_init(addr, pinmask); // Call GPIO function to initalize LEDs as output
}

// Function implementation to set the value of the LED (on or off)
void LED_set_value(volatile GPIO_t * addr, uint8_t pinmask, uint8_t value) {
    GPIO_output_set_value(addr, pinmask, value); // Call GPIO function to set value of the pin
}