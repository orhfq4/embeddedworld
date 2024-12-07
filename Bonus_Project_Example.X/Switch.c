#include "Switch.h"
#include "board.h"
#include <util/delay.h>

sw_state_t sw_get_value(sw_inst_t * const me) {
    uint8_t temp8; // Jerry
    sw_state_t return_val = SW_NOT_PRESSED;
    temp8 = GPIO_output_get_value(&me->super);
    temp8 ^= me->switch_polarity;
    if (2 > temp8) {
        return_val = (sw_state_t)temp8;
    }
    return return_val;
}

sw_state_t switch_read(sw_inst_t * me) {
    sw_state_t temp; // Kevin
    temp = sw_get_value(me);
    if(temp==SW_PRESSED) {
        _delay_ms(50); // inefficient and blocking
        temp = sw_get_value(me);
    }
    return temp;
}

//*************************************** Need to fix sw_ctor function

/*
void sw_ctor(input_inst_t * const me, volatile GPIO_t * _port_addr, uint8_t _pin_mask, sw_state_t _state, sw_polarity_t _polarity) {
    // Initialize the base GPIO input struct
    GPIO_input_ctor(&me->super, _port_addr, _pin_mask, _polarity == ACTIVE_HIGH ? PU_DISABLED : PU_ENABLED);

    // Set the switch-specific properties
    me->switch_state = _state;
    me->switch_polarity = _polarity;
}
*/