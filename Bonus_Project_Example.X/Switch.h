/* 
 * File:   Switch.h
 * Author: tshan
 *
 * Created on December 6, 2024, 7:53 PM
 */

#ifndef SWITCH_H
#define	SWITCH_H

#include "GPIO_Outputs.h"
#include "GPIO_Inputs.h"
// typedefs for switch
typedef enum {SW_NOT_PRESSED=0, SW_PRESSED} sw_state_t;
typedef enum {SW_ACTIVE_LOW=0, SW_ACTIVE_HIGH} sw_polarity_t;

typedef struct {
    input_inst_t super; // Parent class always listed first
    sw_polarity_t switch_polarity;
    sw_state_t switch_state;
} sw_inst_t;

void sw_ctor(input_inst_t * const me, volatile GPIO_t * _port_addr, uint8_t _pin_mask, sw_state_t _state, sw_polarity_t _polarity);

sw_state_t sw_get_value(sw_inst_t * const me);

sw_state_t switch_read(sw_inst_t * const me);


#endif	/* SWITCH_H */

