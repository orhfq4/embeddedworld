#ifndef _STA013_Config_H
#define _STA013_Config_H

#include "board.h"



#define STA013 (0x43)
/******* STA013 IO Definitions ********/
#define STA013_TWI_Port (TWI1)  // Defines which TWI port is used for STA013 communication
#define STA013_SPI_Port (SPI0)  // Defines which SPI port is used for STA013 communication
#define STA013_BITEN_Port (PD)  // Defines the GPIO Port for STA013 BITEN
#define STA013_BITEN_Pin (1<<6) // Defines the GPIO Pin for STA013 BITEN
#define STA013_Reset_Port (PB)  // Defines the GPIO Port for STA013 Reset
#define STA013_Reset_Pin (1<<1) // Defines the GPIO Pin for STA013 Reset
#define STA013_DATAREQ_Port (PC)  // Defines the GPIO Port for STA013 DATAREQ
#define STA013_DATAREQ_Pin (1<<6) // Defines the GPIO Pin for STA013 DATAREQ


// ------ Public function prototypes -------------------------------
/**************************************************************
*   STA013_reset_init
*   Inputs: pointer to a gpio object instance
*           pointer to a GPIO port struct,
*           pin_mask to select GPIO pin(s)
*           initial state of the port pin
*   Output: None
**************************************************************
*   Function: Pin set to be an output by setting that bit in the DDR
*
*   Caution: 
***************************************************************/
void STA013_Reset_Init(gpio_inst_t * const me, 
                        volatile GPIO_t * _port_addr, 
                        uint8_t _pin_mask, 
                        GPIO_PIN_STATE_t _state);


void STA013_Reset_Control(gpio_inst_t * const me, GPIO_PIN_STATE_t _state);

/**************************************************************
*   STA013_BIT_EN_init
*   Inputs: pointer to a gpio object instance
*           pointer to a GPIO port struct,
*           pin_mask to select GPIO pin(s)
*           initial state of the port pin
*   Output: None
**************************************************************
*   Function: Pin set to be an output by setting that bit in the DDR
*
*   Caution: 
***************************************************************/

void STA013_BIT_EN_Init(gpio_inst_t * const me, 
                         volatile GPIO_t * _port_addr, 
                         uint8_t _pin_mask, 
                         GPIO_PIN_STATE_t _state);

void STA013_BIT_EN_Control(gpio_inst_t * const me, GPIO_PIN_STATE_t _state);

// void STA013_DATA_REQ_Init(void);



/***********************************************************************
DESC:    Initializes the STA013 with the following steps:
         Applies a hardware reset signal, checks the ID register for an 0xAC
		 response and then sends the configuration data.
RETURNS: error flag
CAUTION: 
          
************************************************************************/

uint8_t STA013_Init(void);



#endif