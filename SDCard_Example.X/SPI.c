// SPI.c
#include "SPI.h"
#include <avr/io.h>

// SPI Control Register bit masks
#define SPI_ENABLE (1 << 6)       // SPE bit in SPCR
#define SPI_MASTER_MODE (1 << 4)  // MSTR bit in SPCR
#define clock_rate_error (1)      // Define clock rate error
#define MOSI_PORT_SPI0 (PB)
#define SCK_PORT_SPI0 (PB)
#define MOSI_PORT_SPI1 (PE)
#define SCK_PORT_SPI1 (PD)
#define MOSI_PIN_SPI0 (1<<5)
#define SCK_PIN_SPI0 (1<<7)
#define MOSI_PIN_SPI1 (1<<3)
#define SCK_PIN_SPI1 (1<<7)

uint8_t SPI_Master_Init(volatile SPI_t *SPI_addr, uint32_t clock_freq){
    
    /***********************************************************************/
    gpio_inst_t MOSI_pin, SCK_pin;
    // Set MOSI and SCK as outputs with initial values. MISO is setup automatically
    if(SPI_addr == SPI0) {
        // MOSI (PB5) setup
        GPIO_output_ctor(&MOSI_pin, MOSI_PORT_SPI0, MOSI_PIN_SPI0, 1); // PB5 is MOSI pin for SPI0, set to an initial value of 1
        // SCK (PB7) setup
        GPIO_output_ctor(&SCK_pin, SCK_PORT_SPI0, SCK_PIN_SPI0, 0); // PB7 is SCK pin for SPI0, set to an initial value of 0
    }
    else if (SPI_addr == SPI1) {
        // MOSI (PE3) setup
        GPIO_output_ctor(&MOSI_pin, MOSI_PORT_SPI1, MOSI_PIN_SPI1, 1); // PB5 is MOSI pin for SPI1, set to an initial value of 1
        
        // SCK (PD7) setup
        GPIO_output_ctor(&MOSI_pin, SCK_PORT_SPI1, SCK_PIN_SPI1, 0); // PD7 is MOSI pin for SPI1, set to an initial value of 0
    } else {
        return 1; // Invalid SPI address
    }
    
    // Configure SPCR with SPE and MSTR bits
    SPI_addr->SPCR = (1 << SPE) | (1 << MSTR) | (CPOL_bit << CPOL) | (CPHA_bit << CPHA);
    
    /***********************************************************************/

    uint8_t divider = (F_CPU/OSC_DIV)/(clock_freq);
    
    if(divider<2) { // divider=(F_CPU/OSC_DIV)/(clock_freq)= 0 to 1.9999999
        (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        // SPE = 6, MSTR = 4, CPOL = 3, CPHA = 2
        (SPI_addr->SPSR)=1; // Sets the SPI2X bit
    }
    else if(divider<4) { //divider=(F_CPU/OSC_DIV)/(clock_freq)=2.0000 to 3.9999999
        (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        (SPI_addr->SPSR)=0; // Clears the SPI2X bit
    }
    else if(divider<8) { //divider=(F_CPU/OSC_DIV)/(clock_freq)=4.0000 to 7.9999999
        (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        (SPI_addr->SPSR)=1; // Sets the SPI2X bit
    }
    else if(divider<16) { //divider=(F_CPU/OSC_DIV)/(clock_freq)=8.0000 to 15.9999999
        (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        (SPI_addr->SPSR)=0; // Clears the SPI2X bit
    }
    else if(divider<32) { //divider=(F_CPU/OSC_DIV)/(clock_freq)=16.0000 to 31.9999999
        (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        (SPI_addr->SPSR)=1; // Sets the SPI2X bit
    }
    else if(divider<64) { //divider=(F_CPU/OSC_DIV)/(clock_freq)=32.0000 to 63.9999999
        (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        (SPI_addr->SPSR)=1; // Sets the SPI2X bit
    }
    else if(divider<128) { //divider=(F_CPU/OSC_DIV)/(clock_freq)=64.0000 to 127.9999999
        (SPI_addr->SPCR)=((1<<SPE)|(1<<MSTR)|(CPOL_bit<<CPOL)|(CPHA_bit<<CPHA)|(0<<0));
        (SPI_addr->SPSR)=0; // Clears the SPI2X bit
    }
    else {
        return clock_rate_error; // SCLK<125,000Hz
    }

    return 0;  // Successful initialization
}

uint8_t SPI_transfer(volatile SPI_t *SPI_addr, uint8_t send_value) { // returns the received value
    (SPI_addr->SPDR)=send_value; // First, start a transfer by writing send_value to SPDR
    uint8_t status;
    do { // Next, wait in a loop until SPIF is set
        status = (SPI_addr->SPSR); // Read SPSR to check the SPIF bit
    } while((status & 0x80)==0);
    
    return (SPI_addr->SPDR); // Then, return the value from the SPDR
}

void SPI_transmit(volatile SPI_t *SPI_addr, uint8_t send_value) { // doesn't return a value (we don't care)
    (SPI_addr->SPDR)=send_value; // First, start a transfer by writing send_value to SPDR
    uint8_t status;
    do { // Next, wait in a loop until SPIF is set
        status = (SPI_addr->SPSR);
    } while((status & 0x80)==0);
    
    (void)SPI_addr->SPDR; // Read from SPDR to clear the SPIF flag and discard the received value
}

uint8_t SPI_receive(volatile SPI_t *SPI_addr) {
    // Send a dummy value (0xFF) to initiate the receive process
    (SPI_addr->SPDR) = 0xFF;

    uint8_t status;
    do { // Next, wait in a loop until SPIF is set
        status = (SPI_addr->SPSR);
    } while((status & 0x80)==0);

    // Return the received value from SPDR
    return (SPI_addr->SPDR);
}