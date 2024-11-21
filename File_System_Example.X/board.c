#include "board.h"
#include "LEDS.h"
#include "GPIO_Outputs.h"


led_inst_t led0, led1, led2, led3;
spi_cs_inst_t sd_cs, oled_cs;
gpio_inst_t oled_reset, oled_cmd;


