/*

#ifndef GPIO_3_H
#define GPIO_3_H

#include "peripherals.h"

typedef strcut {
    voltaile GPIO_t * port_addr;
    uint8_t pinmask;
} gpio_init_t;

// Instances are stored in SRAM

void GPIO_output_ctor(gpio_inst_t * const me, volatile gpio_t * _port, uint8_t _pin_mask, uint8_t _value);
void GPIO_output_set_value_3(gpio_inst_t * const me, uint8_t _value);

*/