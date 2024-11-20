/* 
 * File:   STA013.h
 * Author: owenhancock
 *
 * Created on November 8, 2024, 11:14 AM
 */

#ifndef STA013_H
#define	STA013_H

/*
 * Use to initialize the STA013
 * Use I2C functions to write the patch file (Config_Arrays.c) and configure data to the STA013 
 */
void STA013_init();



//Pre: None
//Post:Set up values for I2C and PLL according to the datasheet for the crystal frequency
//Desc: Configures the values
//Caution: Seperate function from STA013 init, must be called immediately after
void i2s_pll_config();

//Pre: Reference to the array to configure
//Post:uses the macro to read the byte and update specific registers
//Desc: Configures the values
//Caution: Can overwrite other values, ensure array passed into the function is correct
void configArray(const uint8_t CONFIG[]);

#endif	/* STA013_H */

