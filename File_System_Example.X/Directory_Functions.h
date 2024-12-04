#ifndef _Directory_Func_H
#define _Directory_Func_H

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
uint16_t print_directory(uint32_t Sector_num, uint8_t * array_in);

uint32_t read_dir_entry(uint32_t Sector_num, uint16_t Entry, uint8_t * array_in);

uint8_t open_file(FS_values_t *drive, uint32_t cluster, uint8_t array[]);



#endif