/*
 * GPIO_Inputs.h
 *
 * Created: 6/30/2020 11:42:34 AM
 *  Author: Roger Younger
 */ 


#ifndef _GPIO_INPUTS_H_
#define _GPIO_INPUTS_H_

/*** Defined constants for GPIO_input_init ****/


#include "peripherals.h"

typedef enum {PU_DISABLED=0,PU_ENABLED} PU_STATE_t;
typedef enum {INPUT_CLEAR=0,INPUT_SET} INPUT_STATE_t;

// Define the states for the playback state machine
typedef enum {
    Data_Idle_1,
            Data_Send_1,
            Load_Buffer_2,
            Find_Cluster_2,
            Data_Idle_2,
            Data_Send_2,
            Load_Buffer_1,
            Find_Cluster_1
    // Add other states as needed
} PLAYBACK_STATE_t;

// Declare the state variable
extern PLAYBACK_STATE_t play_state_g;

typedef struct
{
    volatile GPIO_t * port_addr;
    uint8_t pin_mask;
    PU_STATE_t pullup_state; 
}input_inst_t;

/**************************************************************
*   GPIO_input_init
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select a GPIO pin,
*           pullup set to PU_ENABLE or PU_DISABLE
*   Output: None
**************************************************************
*   Function: Pin set to be an input by clearing that bit in the DDR
*             Pull-up enabled by setting that bit in the PORT reg.
*
*   Caution: Must use the defined constants PU_ENABLE, PU_DISABLE
***************************************************************/
void GPIO_input_ctor(input_inst_t * const me, volatile GPIO_t * _port_addr, uint8_t _pin_mask, PU_STATE_t _pu_state);

void GPIO_input_set_pullup(input_inst_t * const me, PU_STATE_t _pu_state);


/**************************************************************
*   GPIO_input_get_value
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select a GPIO pin
*   Output: State of input pin (0 or 1)
**************************************************************
*   Function: Checks the value of an input pin and returns that value
*
*   Caution: Intended to work with only one pin, output is 0 or 1
*            Will work with multiple pins, but all must be 0 to get output=0
***************************************************************/

static inline INPUT_STATE_t GPIO_input_get_value(input_inst_t * const me)
{
    uint8_t temp8;
    INPUT_STATE_t return_value=INPUT_CLEAR;
    temp8=(me->port_addr->GPIO_PIN)&(me->pin_mask);
    if(0!=temp8)
    {
        return_value=INPUT_SET;
    }
    return return_value;
}
/**************************************************************
*   GPIO_read_input
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select a GPIO pin
*   Output: State of input pin (0 or 1)
**************************************************************
*   Function: Checks the value of an input pin and returns that value
*
*   Caution: Intended to work with only one pin, output is 0 or 1
*            Will work with multiple pins, but all must be 0 to get output=0
***************************************************************/

static inline uint8_t GPIO_read_pin(input_inst_t * const me)
{
	return ((me->port_addr->GPIO_PIN)&(me->pin_mask));
}


/**************************************************************
*   GPIO_read_port
*   Inputs: pointer to a GPIO port struct,
*           pin_mask to select GPIO pin(s)
*   Output: State of GPIO pin(s) in their bit locations
**************************************************************
*   Function: Checks the value of an GPIO pin and returns that value
*             Inline function to reduce read time
*   Caution: Output is pin_mask & pins that are '1'
*            Output value is in the bit location of the port
*               and is not purely '0' or '1'
***************************************************************/
static inline uint8_t GPIO_read_port(input_inst_t * const me)
{
	return ((me->port_addr->GPIO_PIN));
}


#endif /* _GPIO_INPUTS_H_ */