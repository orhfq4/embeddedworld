/*
 * board.h
 *
 * Created: 9/4/2020 11:57:19 AM
 *  Author: youngerr
 */ 



// Microcontroller: ATMEGA324PB
#ifndef BOARD_H_
#define BOARD_H_

#include "peripherals.h"
#include "LEDS.h"
#include "SPI_CS.h"
#include "GPIO_Outputs.h"
#include "GPIO_Inputs.h"

#define F_CPU (16000000UL)
#define F_DIV (1)
#define OSC_DIV (1)


/* LEDS */
#define LED0_PORT (PC)
#define LED0_PIN (1<<7)
/* Assumes the OLED board is connected to Connector EXT4 */
#define LED1_PORT (PB)
#define LED1_PIN (1<<3)
#define LED2_PORT (PE)
#define LED2_PIN (1<<4)
#define LED3_PORT (PA)
#define LED3_PIN (1<<7)


extern led_inst_t led0, led1, led2, led3;

/* SPI pins */
#define SPI0_SS_PORT (PB)
#define SPI0_SS_PIN (1<<4)
#define SPI0_MOSI_PORT (PB)
#define SPI0_MOSI_PIN (1<<5)
#define SPI0_MISO_PORT (PB)
#define SPI0_MISO_PIN (1<<6)
#define SPI0_SCK_PORT (PB)
#define SPI0_SCK_PIN (1<<7)

#define SPI1_SS_PORT (PD)
#define SPI1_SS_PIN (1<<6)
#define SPI1_MOSI_PORT (PE)
#define SPI1_MOSI_PIN (1<<3)
#define SPI1_MISO_PORT (PE)
#define SPI1_MISO_PIN (1<<2)
#define SPI1_SCK_PORT (PD)
#define SPI1_SCK_PIN (1<<7)

/****** SD Card IO Definitions ******/
#define SD_Card_Port (SPI0)  // Defines which SPI port is used for SD Card communication
#define SD_CS_Port (PB)  // Defines the GPIO Port for SD Card Chip Select
#define SD_CS_Pin (1<<4) // Defines the GPIO Pin for SD Card Chip Select

#define SD_CS_ACTIVE (0)
#define SD_CS_INACTIVE (1)

#define OLED_CS_ACTIVE (0)
#define OLED_CS_INACTIVE (1)

extern gpio_inst_t  sta013_reset;
extern spi_cs_inst_t sd_cs, oled_cs, sta013_biten;
extern gpio_inst_t oled_reset, oled_cmd;
extern input_inst_t sta013_data_req;


#define MP3_DEVICE_ADDR (0x43)
#define TEMP_SENSOR_ADDR (0x4F)
#define EEPROM_ADDR (0x53)


#endif /* BOARD_H_ */