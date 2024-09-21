/* 
 * File:   gpio_3.h
 * Author: owenhancock
 *
 * Created on September 17, 2024, 11:02 AM
 */

// This file is used to solve question 5

#ifndef GPIO_3_H
#define GPIO_3_H
#include "peripherals.h"

typedef struct {
    volatile GPIO_t * port_addr; // pointer to GPIO port
    uint8_t pinmask;             // pinmask
} GPIO_init_t;

// Instances are stored in SRAM
    
// Constructor prototype for GPIO_pin
void GPIO_output_ctor(GPIO_init_t * const me, volatile GPIO_t * _port, uint8_t _pinmask, uint8_t _value);

// Function prototype to set the state of the GPIO pin
void GPIO_output_set_value_3(GPIO_init_t * const me, uint8_t _value);

#endif // gpio_3.h