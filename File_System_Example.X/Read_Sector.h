#ifndef _Read_Sector_H
#define _Read_Sector_H


//------- Public Constants  -----------------------------------------
#define Disk_Error (0xF0)
#define No_Disk_Error (0)

// ------ Public function prototypes -------------------------------

/***********************************************************************
*   read_sector
DESC:    Reads a sector from the SD card into the provided buffer.
         The sector number is adjusted based on the SD card type (HC or SC).
INPUT:   uint32_t sector_number - The sector number to read.
         uint16_t sector_size - The size of the sector in bytes.
         uint8_t array_for_data[] - The buffer to store the sector data.
RETURNS: uint8_t - Status of the read operation (0 = success, non-zero = error).
CAUTION: Ensure that the SD card is properly initialized before calling.
************************************************************************/

uint8_t read_sector(uint32_t sector_number, uint16_t sector_size, uint8_t array_for_data[]);



#endif