#include "board.h"
#include "LEDS.h"
#include "GPIO_Outputs.h"
#include "GPIO_Inputs.h"
#include "Switch.h"


led_inst_t led0, led1, led2, led3;
gpio_inst_t  sta013_reset;
gpio_inst_t oled_reset, oled_cmd;
sw_inst_t sw1, sw2, sw3;


