#include "File_System.h"
#include "board.h"

/************************************************ Question 5 ***********************************************************/
/*Variables to determine (according to 14b and 14d) and store for global access by other functions:
    BPB_BytesPerSec
    BPB_SecPerClus
    StartofFAT(relative to sector 0)
    FirstDataSector (relative to sector 0)
    FirstRootDirSec(relative to sector 0)
    RootDirSecs (if FAT 16 is supported)

    Current variables on the FS_values_t struct:
    uint8_t SecPerClus;
    uint8_t FATType;
    uint8_t BytesPerSecShift;
    uint8_t FATshift;
    uint16_t BytesPerSec;
    uint32_t FirstRootDirSec;
    uint32_t FirstDataSec;
    uint32_t StartofFAT;
    uint32_t RootDirSecs;
*/
#define NORMAL (0)
// FAT16 and FAT32 are defined in Directory_Functions.h

// *********************************** (Question 5) *****************************

uint8_t mount_drive(FS_values_t *drive, uint8_t *array) {
    uint8_t Success = 0; //0 for mounting failure, 1 for mounting success
    
    // call a function that returns FATtype then assign to value
    
    drive->FATtype = value;
    
    // call a function that returns StartofFat then assign to value
    
    drive->StartofFAT = value; // Should be first sector 
    BPB_BytesPerSec = drive->BytesPerSec;
    
    // Read block 0 to check if its the volume BPB, 
    //if not, read MBR RelativeSectors val
    //******************** FINDING BPB **********************************
    uint32_t sector_number = 0;
    uint16_t sector_size = 512; // ASSUMING 512 AT FIRST, CHECK IN BPB
    uint8_t temp8 = 0;
    uint16_t offset = 0;
    uint8_t readVal8 = 0x00;
    uint32_t readVal32 = 0x00000000;
    uint8_t error_status = NORMAL;
    uint8_t BPB_error = 5;
    uint8_t read_sector_error = 6;
    char debug_buffer[100];
    
    temp8 = read_sector(uint32_t sector_number, sector_size, buffer1_g); // Using the global buffer 1
    if (temp8 == 0){ // Sector read successfully!
        readVal8 = read_value_8(0, buffer1_g);
        if (readVal8 == 0xEB || readVal8 == 0xE9){
             // Good to go!

        }
        else{ // BPB aint at 0, try using offset found in tables
            offset = 0x01C6; // Relative sectors 32
            
            readVal32 = read_value_32(offset, buffer1_g);
            
            // for debugging
            sprintf(debug_buffer, "Read Value 32 is: 0x%02X\n\r", readVal32);
            UART_transmit_string(UART1, debug_buffer , 0);
            
            sector_number = readVal32;
            //read a new sector with the relative sectors value stored at 0x01C6
            temp8 = read_sector(uint32_t sector_number, sector_size, buffer1_g);
            
            readVal8 = read_value_8(0, buffer1_g);
            
            if (readVal8 == 0xEB || readVal8 == 0xE9){
             // BPB at offset!
                
            }
            else if(temp8 != 0){
                error_status = read_sector_error;
            }
            else{
                // You have an error
                error_status = BPB_error;
            }
            
        }
    }
    else{
        error_status = read_sector_error;
    }
    
    // Define variables for BPB before reading in
    
    uint32_t BPB_TotSec32, BPB_FATSz32, BPB_RootClus;
    uint16_t BPB_ResvdSecCnt, BPB_RootEntCnt, BPB_TotSec16, BPB_FATSz16;
    uint8_t BPB_NumFATs;
    
    // Global variables needed for more than one function
    extern uint16_t BPB_BytesPerSec;
    extern uint8_t BPB_SecPerClus;   
    
    if (error_status == 0) {
        
        // Read values for both FAT16 and FAT32
        BPB_BytesPerSec = read_value_16(0x0B, buffer1_g);
        BPB_SecPerClus = read_value_8(0x0D, buffer1_g);
        BPB_ResvdSecCnt = read_value_16(0x0E, buffer1_g);
        BPB_NumFATs = read_value_8(0x10, buffer1_g);
        BPB_TotSec16 = read_value_16(0x13, buffer1_g);
        BPB_TotSec32 = read_value_32(0x20, buffer1_g);
        
        // Read values for FAT16
        BPB_RootEntCnt = read_value_16(0x11, buffer1_g);
        BPB_FATSz16 = read_value_16(0x16, buffer1_g);
        
        // Read values for FAT32
        BPB_FATSz32 = read_value_32(0x24, buffer1_g);
        BPB_RootClus = read_value_32(0x2C, buffer1_g);

    }
    
    //Step 1: Determine how many sectors are in the Root Dir
    drive->RootDirSecs = ((BPB_RootEntCnt*32) + (BPB_BytesPerSec-1)) / (BPB_BytesPerSec); // need to define rootentcnt still, not sure where to define tho

    //Step 2: Determine how many sectors are data sectors
    if(BPB_FATSz16 != 0){
        drive->FATSz16 = BPB_FATSz16;
    }
    else{
        drive->FATSz32 = BPB_FATSz32;
    }

    if(drive->TotSec16 != 0){
        drive->TotSec16 = BPB_TotSec16;
    }
    else{
        drive->TotSec32 = BPB_TotSec32;
    }

    // Need to add support for FAT16
    drive->NumDataSec = drive->TotSec32 - (BPB_ResvdSecCnt + (BPB_NumFATs*drive->FATSz32) + drive->RootDirSecs);

    //Step 3: Determine the count of clusters and FAT type
    uint8_t CountofClusters = drive->NumDataSec/BPB_SecPerClus;
    if(CountofClusters < 65525){
        drive->FATtype = FAT16; // FAT16 and FAT32 are defined in Directory_Functions.h
    }
    else{
        drive->FATtype = FAT32;
    }

    //Step 4: Determine the first sector of the file allocation table
  
    /* Ask Dr. Younger what this means? Maybe the values in the Directory_Functions.h
    if(drive->FATtype == FAT16){
        FATOffset = N*2; //N is the cluster number, need to define cluster number
    }
    else if (drive->FATtype == FAT32){
        FATOffset = N*4;
    }
    */
    
    // Ask Dr. Younger what to do about FATOffset
    uint32_t ThisFATSecNum = BPB_ResvdSecCnt + (FATOffset/BPB_BytesPerSec);
    
    // Ask Dr. Younger what to do about MBR_RelativeSectors
    drive->StartofFAT = BPB_ResvdSecCnt + MBR_RelativeSectors;
    //Step 5: Determine the first sector of the data area
    drive->FirstDataSec = BPB_ResvdSecCnt + (BPB_NumFATs * FATSz) + drive->RootDirSecs;
    
    //Relative to the start of the volume and not to sector 0
    //Step 6: Determine the first sector of the Root Directory (FAT16)
    if(drive->FATtype == FAT16){
        drive->FirstRootDirSec = BPB_ResvdSecCnt + (BPB_NumFATs * BPB_FATSz16) + MBR_RelativeSectors;
    }
    //Step 7: Determine the first sector of the Root Directory (FAT32)
    else{
        drive->FirstRootDirSec = ((BPB_RootClus - 2) * BPB_SecPerClus) + drive->FirstDataSec;
    }

    return error_status;
}
//14e slides
/* Question 6 */
uint32_t First_Sector (FS_values_t *drive, uint32_t cluster_num){
    uint32_t sector;
    if (cluster_num == 0){
        sector = drive->FirstRootDirSec;
    }
    else{
        sector = ((cluster_num-2) * drive->SecPerClus) + drive->FirstDataSec;
    }
}

uint32_t find_next_clus(FS_values_t *drive, uint32_t cluster, uint8_t array[]){
    uint32_t sector;
    uint32_t return_clus;
    //Step 1: Determine the FAT sector number for the cluster.
    sector = ((cluster * drive->FATtype)/drive->BytesPerSec) + drive->StartofFAT;

    //Step 2: Read the FAT sector into SRAM
    read_sector(sector, drive->BytesPerSec, array);

    //Step 3: Determine the entry offset of the cluster within this sector
    FATOffset = (uint16_t)((cluster * drive->FATtype)%(drive->BytesPerSec));

    //Step 4: Read the cluster entry from the FAT sector in SRAM
    if(drive->FATtype == FAT32){
        return_clus = (read_value_32(FATOffset,array)&0x0FFFFFFF);
    }
    else{
        return_clus = (read_value_16(FATOffset,array));
    }
    return return_clus;
}