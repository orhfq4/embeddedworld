/* 
 * File:   led_3.c
 * Author: owenhancock
 *
 * Created on September 17, 2024, 11:02 AM
 */

// This file is used to solve question 5

#include "led_3.h"
#include "gpio_3.h"

// Initialize LED
void LED_init_3(LED_t * const led, volatile GPIO_t *port, uint8_t pinmask, uint8_t initial_state, uint8_t active_low) {
    // Initialize GPIO part
    GPIO_output_ctor(&led->super, port, pinmask, initial_state);

    // Set LED active low or high
    led->active_low = active_low;
    
    // Adjust initial state based on active_low flag
    if (led->active_low) {
        GPIO_output_set_value_3(&led->super, !initial_state);  // Invert state for active low
    } else {
        GPIO_output_set_value_3(&led->super, initial_state);
    }
}

// Set LED state
void LED_set_value_3(LED_t * const led, uint8_t state) {
    if (led->active_low) {
        GPIO_output_set_value_3(&led->super, !state);  // Invert state for active low
    } else {
        GPIO_output_set_value_3(&led->super, state);
    }
}

