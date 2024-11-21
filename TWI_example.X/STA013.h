/* 
 * File:   STA013.h
 * Author: owenhancock
 *
 * Created on November 8, 2024, 11:14 AM
 */

#ifndef STA013_H
#define	STA013_H

/**************************************************************
*   STA013_init
*   Inputs: None
*   Output: None
**************************************************************
*   Function: Initializes the STA013 which uses the I2C functions to write the config arrays and data to the STA013.
*
*   Caution: 
***************************************************************/
/*
 * Use to initialize the STA013
 * Use I2C functions to write the patch file (Config_Arrays.c) and configure data to the STA013 
 */
void STA013_init();


/**************************************************************
*   i2s_pll_config
*   Inputs: none
*   Output: none
**************************************************************
*   Function: Sets up the values for the I2C and PLL according to the datasheet for the crystal frequency
*
*   Caution: This function is a separate function from STA013 init and must be called immediately after STA013_init
***************************************************************/
void i2s_pll_config();

/**************************************************************
*   configArray
*   Inputs: an array of unsigned 8-bit integers for the configuration values
*   Output: none
**************************************************************
*   Function: updates specific registers in the config array
*
*   Caution: can overwrite other values, make sure the array passed into the function is correct
***************************************************************/
void configArray(const uint8_t CONFIG[]);

#endif	/* STA013_H */

