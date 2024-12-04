/* 
 * File:   Drive_Values.h
 * Author: Younger
 *
 * Created on November 18, 2024, 9:23 PM
 */

#ifndef DRIVE_VALUES_H
#define	DRIVE_VALUES_H

#include <avr/pgmspace.h>
#include <stdio.h>
#include "peripherals.h"
//----------------- Typedefs ----------------------------------------
//FS object struct
typedef struct{
    uint8_t SecPerClus;
    uint8_t FATtype;
    uint8_t BytesPerSecShift;
    uint8_t FATshift;
    uint16_t BytesPerSec;
    uint32_t FirstRootDirSec;
    uint32_t FirstDataSec;
    uint32_t StartofFAT;
    uint32_t RootDirSecs;
    
} FS_values_t;

/***********************************************************************
*   export_drive_values
DESC:    Returns a pointer to the global `drive_values` structure for access to
         file system parameters.
RETURNS: FS_values_t* - Pointer to the `drive_values` structure.
CAUTION: Ensure `drive_values` is initialized before calling this function.
************************************************************************/

FS_values_t * export_drive_values(void);

#endif	/* DRIVE_VALUES_H */