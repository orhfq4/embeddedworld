/* 
 * File:   SPI_CS.h
 * Author: Younger
 *
 * Created on September 12, 2024, 3:29 PM
 */

#ifndef SPI_CS_H
#define	SPI_CS_H

#include "GPIO_Outputs.h"


typedef enum {CS_ACTIVE=0,CS_INACTIVE} spi_cs_state_t;
typedef enum {CS_ACTIVE_LOW=0,CS_ACTIVE_HIGH} spi_cs_polarity_t;

typedef struct
{
    gpio_inst_t super;
    spi_cs_polarity_t cs_pol;
}spi_cs_inst_t;


void SPI_CS_ctor(spi_cs_inst_t * const me, volatile GPIO_t * _port_addr, 
                                  uint8_t _pin_mask, spi_cs_state_t _state,
                                  spi_cs_polarity_t _polarity);

void SPI_CS_set_value(spi_cs_inst_t * const me, spi_cs_state_t _state);

spi_cs_state_t SPI_CS_get_value(spi_cs_inst_t * const me);

void SPI_CS_toggle_value(spi_cs_inst_t * const me);


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SPI_CS_H */

