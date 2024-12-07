
//*** Define timer interrupt service routine
#include "peripherals.h"
#include <avr/interrupt.h>

#define INTERVAL (10)

uint16_t time_g;

ISR(TIMER2_COMPA_vect)
{
   // Increment time variable for scheduler
    time_g+=INTERVAL;  
   // Tasks are performed ?
}

