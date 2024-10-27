// SPI.c
#include "SPI.h"
#include <avr/io.h>

// SPI Control Register bit masks
#define SPI_ENABLE (1 << 6)       // SPE bit in SPCR
#define SPI_MASTER_MODE (1 << 4)  // MSTR bit in SPCR
#define clock_rate_error (1)      // Define clock rate error

uint8_t SPI_Master_Init(volatile SPI_Registers *SPI_addr, uint32_t clock_freq){
    
    /***********************************************************************/
    
    // Set MOSI and SCK as outputs with initial values
    if(SPI_addr == SPI0) {
        // MOSI (PB5) setup
        GPIO_output_set_value(PB5, 1); // Set initial value high (1)
        
        // SCK (PB7) setup
        GPIO_output_set_value(PB7, CPOL_bit); // Set to CPOL bit
    }
    else if (SPI_addr == SPI1) {
        // MOSI (PE3) setup
        GPIO_output_set_value(PE3, 1); // Set initial value high (1)
        
        // SCK (PD7) setup
        GPIO_output_set_value(PD7, CPOL_bit); // Set to CPOL bit
    } else {
        return 1; // Invalid SPI address
    }
    
    // Configure SPCR with SPE and MSTR bits
    SPI_addr->SPCR = (1 << SPE) | (1 << MSTR) | (CPOL_bit << CPOL) | (CPHA_bit << CPHA);
    
    /***********************************************************************/

    uint8_t divider = (F_CPU/OSC_DIV)/(clock_freq);
    
    if(divider<2) { // divider=(F_CPU/OSC_DIV)/(clock_freq)= 0 to 1.9999999
        * (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        // SPE = 6, MSTR = 4, CPOL = 3, CPHA = 2
        * (SPI_addr->SPSR)=1; // Sets the SPI2X bit
    }
    else if(divider<4) { //divider=(F_CPU/OSC_DIV)/(clock_freq)=2.0000 to 3.9999999
        * (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        * (SPI_addr->SPSR)=0; // Clears the SPI2X bit
    }
    else if(divider<8) { //divider=(F_CPU/OSC_DIV)/(clock_freq)=4.0000 to 7.9999999
        * (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        * (SPI_addr->SPSR)=1; // Sets the SPI2X bit
    }
    else if(divider<16) { //divider=(F_CPU/OSC_DIV)/(clock_freq)=8.0000 to 15.9999999
        * (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        * (SPI_addr->SPSR)=0; // Clears the SPI2X bit
    }
    else if(divider<32) { //divider=(F_CPU/OSC_DIV)/(clock_freq)=16.0000 to 31.9999999
        * (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        * (SPI_addr->SPSR)=1; // Sets the SPI2X bit
    }
    else if(divider<64) { //divider=(F_CPU/OSC_DIV)/(clock_freq)=32.0000 to 63.9999999
        * (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        * (SPI_addr->SPSR)=1; // Sets the SPI2X bit
    }
    else if(divider<128) { //divider=(F_CPU/OSC_DIV)/(clock_freq)=64.0000 to 127.9999999
        * (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        * (SPI_addr->SPSR)=0; // Clears the SPI2X bit
    }
    else {
        return clock_rate_error; // SCLK<125,000Hz
    }

    return 0;  // Successful initialization
}


