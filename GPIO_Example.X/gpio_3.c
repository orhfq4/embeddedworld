/* 
 * File:   gpio_3.c
 * Author: owenhancock
 *
 * Created on September 17, 2024, 11:02 AM
 */

// This file is used to solve question 5

#include "gpio_3.h"

void GPIO_output_ctor(GPIO_init_t * const me, volatile GPIO_t * _port, uint8_t _pinmask, uint8_t _value) {
    me -> port_addr = _port;
    me -> pinmask = _pinmask;
    me -> port_addr -> GPIO_DDR |= _pinmask; // initialize the pin as output
    
    // initialize the port
    if (_value) {
        me -> port_addr -> GPIO_PORT |= _pinmask; // set the pin high
    }
    else {
        me -> port_addr -> GPIO_PORT &= ~_pinmask; //set the pin low
    }
}

void GPIO_output_set_value_3(GPIO_init_t * const me, uint8_t _value) {
    if (_value) {
        me -> port_addr -> GPIO_PORT |= (me -> pinmask); // set the pin high
    }
    else {
        me -> port_addr -> GPIO_PORT &= ~(me -> pinmask); // set the pin low
    }
}