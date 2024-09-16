/*

#include "gpio_3.h"

void gpio_output_ctor() {
    me -> port_addr = _port;
    me -> pin_mask = _pinmask;
    // initialize the port
    if (0 != value) {
        me -> port_addr -> GPIO_port |= ~_pinmask
    }
    else {
        me -> port_addr -> GPIO_port &= ~_pinmask;
    }
    me -> port_addr -> GPIO_DDR |= _pinmask;

}

void GPIO_output_set_value_3() {
    if (0 != value) {
        me -> port_addr -> GPIO_port |= (me -> pinmask);
    }
    else {
        me -> port_addr -> GPIO_port &= ~(me -> pinmask);
    }
}

*/