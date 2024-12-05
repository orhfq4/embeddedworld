#ifndef _Directory_Func_H
#define _Directory_Func_H

#include "board.h"
#include "Drive_Values.h"

//------- Public Constants  -----------------------------------------
#define FAT32 (4)
#define FAT16 (2)
#define FAT32_shift (2)
#define FAT16_shift (1)

#define Disk_Error (0xF0)
#define no_errors (0)
#define more_entries (0x8000)   
#define no_entry_found (0x80000000)  // msb set to indicate error
#define directory_bit  (0x10000000)  // lsb of first nibble (bit28)



// ------ Public function prototypes -------------------------------

/***********************************************************************
*   print_directory
DESC:    Prints all short file name entries for a given directory 
         from the starting sector.
RETURNS: uint16_t - The number of entries found in the directory.
CAUTION: Supports FAT16 and FAT32 file systems. 
         SD card and file system must be initialized before calling this function.
************************************************************************/

uint16_t print_directory(uint32_t Sector_num, uint8_t * array_in);


/***********************************************************************
*   read_dir_entry
DESC:    Locates a specified directory entry and returns the associated cluster.
         Returns a 32-bit value with cluster information, where the lower 
         28 bits contain the cluster number, bit 28 indicates if it's a directory, 
         and bit 31 indicates an error or no entry found.
RETURNS: uint32_t - Cluster information or error code.
CAUTION: Ensure directory is accessible and SD card is mounted before calling this function.
************************************************************************/

uint32_t read_dir_entry(uint32_t Sector_num, uint16_t Entry, uint8_t * array_in);

/***********************************************************************
*   open_file
DESC:    Opens a file by reading its sectors and clusters, and allows user 
         interaction to continue reading or exit.
RETURNS: uint8_t - Status code (0 for success, 1 for invalid input, 2 for read error).
CAUTION: SD card must be mounted, and file system initialized before using this function.
************************************************************************/

uint8_t open_file(FS_values_t *drive, uint32_t cluster, uint8_t array[]);



#endif // Directory_Functions.h