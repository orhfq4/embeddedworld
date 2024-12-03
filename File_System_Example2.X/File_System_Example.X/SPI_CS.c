#include "board.h"
#include "GPIO_Outputs.h"
#include "SPI_CS.h"


void SPI_CS_ctor(spi_cs_inst_t * const me, volatile GPIO_t * _port_addr, 
                                  uint8_t _pin_mask, spi_cs_state_t _state,
                                  spi_cs_polarity_t _polarity)
{
    GPIO_output_ctor(&me->super, _port_addr, _pin_mask, (_state^_polarity));
    me->cs_pol=_polarity;
}

void SPI_CS_set_value(spi_cs_inst_t * const me, spi_cs_state_t _state)
{
        GPIO_output_set_value(&me->super,((_state)^(me->cs_pol)));
}

spi_cs_state_t SPI_CS_get_value(spi_cs_inst_t * const me)
{
    uint8_t temp8;
    spi_cs_state_t return_val=CS_INACTIVE;
    temp8=GPIO_output_get_value(&me->super);
    temp8^=me->cs_pol;
    if(2>temp8)
    {
        return_val=(spi_cs_state_t)temp8;
    }
    return return_val;
}

void SPI_CS_toggle_value(spi_cs_inst_t * const me)
{
    GPIO_output_toggle_value(&me->super);
}