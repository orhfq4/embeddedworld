#include "board.h"
#include "LEDS.h"
#include "GPIO_Outputs.h"
#include "SPI_CS.h"
#include "GPIO_Inputs.h"


led_inst_t led0, led1, led2, led3;
gpio_inst_t  sta013_reset;
spi_cs_inst_t sd_cs, oled_cs, sta013_biten;
gpio_inst_t oled_reset, oled_cmd;
input_inst_t sta013_data_req;



