#include "File_System.h"
#include "board.h"
#include "print_memory.h"
#include "Read_Sector.h"
#include "Read_Values.h"
#include "UART_Print.h"
#include <stdio.h>


#define NORMAL (0)
#define RELATIVE_SECTORS_32 (0x01C6)

// *********************************** (Question 5) *****************************


uint8_t mount_drive(FS_values_t *drive, uint8_t buffer[]) {
    uint8_t error_status = NORMAL; //!0 for mounting failure, 0 for mounting success
           
    //******************** FINDING BPB **********************************
    uint32_t sector_number = 0;
    uint16_t sector_size = 512; // ASSUMING 512 AT FIRST, CHECK IN BPB
    uint8_t temp8 = 0;
    uint16_t ReadOffset = 0;
    uint8_t readVal8 = 0x00;
    uint32_t readVal32 = 0x00000000;
    uint32_t MBR_RelativeSectors = 0x000000000;
    uint8_t BPB_error = 5;
    uint8_t read_sector_error = 6;
    char * debug_buffer;
    debug_buffer = export_print_buffer();
    
    temp8 = read_sector(sector_number, sector_size, buffer); // Using the global buffer 1
    
    print_memory(buffer,512);
   
    
        
    if (temp8 == 0){ // Sector read successfully!
        readVal8 = read_value_8(0, buffer);
               
        if (readVal8 == 0xEB || readVal8 == 0xE9){ // EB and E9 denote the start of BPB
             // Good to go! EB or E9 read immediately (BPB Found)        
        }
        else{ // BPB ain't at 0, try using relative offset
            ReadOffset = RELATIVE_SECTORS_32; // Relative sectors 32
            
            readVal32 = read_value_32(ReadOffset, buffer);
            
            sector_number = readVal32;
           
            
            
            //read a new sector with the relative sectors value stored at 0x01C6
            temp8 = read_sector(sector_number, sector_size, buffer);
            
            print_memory(buffer,512);
            
            readVal8 = read_value_8(0x00, buffer);
            
                       
            if (readVal8 == 0xEB || readVal8 == 0xE9){ // EB and E9 denote the BPB
             // BPB at offset!
             MBR_RelativeSectors = readVal32;
             
             
            UART_transmit_string(UART1, debug_buffer , 0);
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
    uint16_t BPB_BytesPerSec, BPB_ResvdSecCnt, BPB_RootEntCnt, BPB_TotSec16, BPB_FATSz16;
    uint8_t BPB_NumFATs, BPB_SecPerClus; 
    uint32_t NumDataSec;
    uint32_t FATSz;
    uint32_t TotSec;
    
    //********************* READ VALUES FROM BPB ************************
    
    if (error_status == 0) {        
               
        // Read values for both FAT16 and FAT32
        BPB_BytesPerSec = read_value_16(0x0B, buffer);
        BPB_SecPerClus = read_value_8(0x0D, buffer);
        drive -> BytesPerSec = BPB_BytesPerSec; // Storing as globals
        drive -> SecPerClus = BPB_SecPerClus; // Storing as globals
        BPB_ResvdSecCnt = read_value_16(0x0E, buffer);
        BPB_NumFATs = read_value_8(0x10, buffer);
        BPB_TotSec16 = read_value_16(0x13, buffer);
        BPB_TotSec32 = read_value_32(0x20, buffer);
        
        // Read values for FAT16
        BPB_RootEntCnt = read_value_16(0x11, buffer);
        BPB_FATSz16 = read_value_16(0x16, buffer);
        
        // Read values for FAT32
        BPB_FATSz32 = read_value_32(0x24, buffer);
        BPB_RootClus = read_value_32(0x2C, buffer);
    
    //*****************************************************************
    
        //Step 2: Determine how many sectors are in the Root Dir

        drive->RootDirSecs = ((BPB_RootEntCnt*32) + (BPB_BytesPerSec-1)) / (BPB_BytesPerSec); 

        //Step 3: Determine how many sectors are data sectors

        if(BPB_FATSz16 != 0){
            FATSz = (uint32_t)BPB_FATSz16;
            error_status = 1;
        }
        else{
            FATSz = BPB_FATSz32;
        }

        if(BPB_TotSec16 != 0){
            TotSec = (uint32_t)BPB_TotSec16;
            error_status = 1;
        }
        else{
            TotSec = BPB_TotSec32;
        }
        // Need to add support for FAT16
        NumDataSec = TotSec - (BPB_ResvdSecCnt + (BPB_NumFATs*FATSz) + drive->RootDirSecs);


        //Step 4: Determine the count of clusters and FAT type    
        uint32_t CountofClusters = NumDataSec/BPB_SecPerClus;


        if(CountofClusters < 65525){
            drive->FATtype = FAT16; // FAT16 and FAT32 are defined in Directory_Functions.h
            error_status = FAT16; // FAT16 not supported, error thrown
        }
        else{
            drive->FATtype = FAT32;
        }



        //Step 5: Determine the first sector of the file allocation table


        drive->StartofFAT = BPB_ResvdSecCnt + MBR_RelativeSectors;


        //Step 6: Determine the first sector of the data area
        drive->FirstDataSec = BPB_ResvdSecCnt + (BPB_NumFATs * BPB_FATSz32) + drive->RootDirSecs + MBR_RelativeSectors;


        //Relative to the start of the volume and not to sector 0
        //Step 7: Determine the first sector of the Root Directory (FAT16)
        if(drive->FATtype == FAT16){
            drive->FirstRootDirSec = BPB_ResvdSecCnt + (BPB_NumFATs * BPB_FATSz16) + MBR_RelativeSectors;
        }
        //Step 7: Determine the first sector of the Root Directory (FAT32)
        else{
            drive->FirstRootDirSec = ((BPB_RootClus - 2) * BPB_SecPerClus) + drive->FirstDataSec;
        }
    }
    return error_status;
}
//14e slides
/************************************** (Question 6) *************************/
uint32_t First_Sector (FS_values_t *drive, uint32_t cluster_num){
    uint32_t sector;
    if (cluster_num == 0){
        sector = drive->FirstRootDirSec;
    }
    else{
        sector = ((cluster_num-2) * drive->SecPerClus) + drive->FirstDataSec;
    }
    return sector;
}

/************************************** (Question 7) *************************/

uint32_t find_next_clus(FS_values_t *drive, uint32_t cluster, uint8_t array[]){
    uint32_t sector;
    uint32_t return_clus;
    uint16_t FATOffset = 0x0000;
    //Step 1: Determine the FAT sector number for the cluster.
    // FATtype should be 2 for FAT16 or 4 for FAT32
    sector = ((cluster * drive->FATtype)/drive->BytesPerSec) + drive->StartofFAT;

    //Step 2: Read the FAT sector into SRAM
    read_sector(sector, drive->BytesPerSec, array);
    
   
    
    //Step 3: Determine the entry offset of the cluster within this sector
    if(drive->FATtype == FAT16){
        FATOffset = cluster*2; //N (cluster) is the cluster number, need to define cluster number
    }
    else if (drive->FATtype == FAT32){
        FATOffset = cluster*4;
    }
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