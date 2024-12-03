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



FS_values_t * export_drive_values(void);






#endif	/* DRIVE_VALUES_H */

