/* 
 * File:   Config_Arrays.h
 * Author: owenhancock
 *
 * Created on November 17, 2024, 6:51 PM
 */

#ifndef CONFIG_ARRAYS_H
#define	CONFIG_ARRAYS_H

#include <avr/pgmspace.h> // For PROGMEM on AVR
#include "board.h"

extern const uint8_t CONFIG[3998] PROGMEM;
extern const  uint8_t CONFIG2[50] PROGMEM;

#endif	/* CONFIG_ARRAYS_H */

