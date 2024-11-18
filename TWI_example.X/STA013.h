/* 
 * File:   STA013.h
 * Author: owenhancock
 *
 * Created on November 8, 2024, 11:14 AM
 */

#ifndef STA013_H
#define	STA013_H

void STA013_init();
/*
 
 * Use to initialize the STA013
 * Use I2C functions to write the patch file (Config_Arrays.c) and configure data to the STA013 
 
 */


//Pre: None
//Post:Set up values for I2C and PLL according to the datasheet for the crystal frequency
//Desc: Configures the values
//Caution: Seperate function from STA013 init, must be called immediately after
void i2s_pll_config();

#endif	/* STA013_H */

