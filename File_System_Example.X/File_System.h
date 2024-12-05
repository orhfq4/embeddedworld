/* 
 * File:   File_System.h
 * Author: owenhancock
 *
 * Created on November 21, 2024, 12:38 PM
 */

#ifndef FILE_SYSTEM_H
#define	FILE_SYSTEM_H

#include "board.h"
#include <stdio.h>

//****************** Function Prototypes **********************

/***********************************************************************
*   mount_drive
DESC:    Mounts a FAT file system from a drive and extracts its parameters
         like BytesPerSec, SecPerClus, StartofFAT, etc. It identifies whether
         the file system is FAT16 or FAT32.
INPUT:   FS_values_t *drive - Pointer to the drive structure containing file system parameters.
         uint8_t *array - Buffer to read sector data.
RETURNS: uint8_t - Mounting status (0 = success, non-zero = error).
************************************************************************/

uint8_t mount_drive(FS_values_t *drive, uint8_t *array);

/***********************************************************************
*   first_sector
DESC:    Returns the first sector for the given cluster number. For cluster 0, it returns
         the first root directory sector. Otherwise, it calculates the sector based on the cluster number.
INPUT:   FS_values_t *drive - Pointer to the drive structure.
         uint32_t cluster_num - The cluster number for which the first sector is requested.
RETURNS: uint32_t - The first sector number for the given cluster.
************************************************************************/

uint32_t First_Sector(FS_values_t *drive, uint32_t cluster_num);

/***********************************************************************
*   find_next_clus
DESC:    Retrieves the next cluster in the chain from the FAT table for the given cluster.
INPUT:   FS_values_t *drive - Pointer to the drive structure.
         uint32_t cluster - The current cluster number.
         uint8_t *array - Buffer to store the FAT sector data.
RETURNS: uint32_t - The next cluster number.
************************************************************************/

uint32_t find_next_clus(FS_values_t *drive, uint32_t cluster, uint8_t array[]);

#endif	/* FILE_SYSTEM_H */