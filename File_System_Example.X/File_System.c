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
uint8_t mount_drive(FS_values_t *drive, uint8_t *array) {
    uint8_t Success = 0; //0 for mounting failure, 1 for mounting success
    drive->FATtype = value; // value? Not sure what value means
    drive->StartofFAT = value;
    BPB_BytesPerSec = drive->BytesPerSec;

    //Step 1: Determine how many sectors are in the Root Dir
    drive->RootDirSecs = ((BPB_RootEntCnt*32) + (BPB_BytesPerSec-1)) / (BPB_BytesPerSec); // need to define rootentcnt still, not sure where to define tho

    //Step 2: Determine how many sectors are data sectors
    if(BPB_FATSz16 != 0){
        drive->FATSz = BPB_FATSz16;
    }
    else{
        drive->FATSz = BPB_FATSz32;
    }

    if(drive->BPB_TotSec != 0){
        drive->BPB_TotSec = BPB_TotSec16;
    }
    else{
        drive->BPB_TotSec = BPB_TotSec32;
    }

    drive->DataSec = drive->BPB_TotSec - (BPB_ResvdSecCnt + (BPB_NumFATs*FATSz) + RootDirSectors);

    //Step 3: Determine the count of clusters and FAT type
    uint8_t CountofClusters = DataSec/BPB_SecPerClus;
    if(CountofClusters < 65525){
        drive->FATType = FAT16; //uh
    }
    else{
        drive->FATType = FAT32;
    }

    //Step 4: Determine the first sector of the file allocation table
    //Need to define FAT16 and FAT32 constants?  and 
    if(drive->FATType == FAT16){
        FATOffset = N*2; //N is the cluster number, need to define cluster number
    }
    else if (drive->FATType == FAT32){
        FATOffset = N*4;
    }
    uint8_t = ThisFATSecNum = BPB_ResvdSecCnt + (FATOffset/BPB_BytesPerSec);

    //Step 5: Determine the first sector of the data area
    drive->FirstDataSector = BPB_ResvdSecCnt + (BPB_NumFATs * FATSz) + RootDirSectors;

    //Step 6: Determine the first sector of the Root Directory (FAT16)
    if(drive->FATType == FAT16/*?*/){
        drive->FirstRootDirSec = BPB_ResvdSecCnt + (BPB_NumFATs * BPB_FATSz16) + MBR_RelativeSectors;
    }
    //Step 6: Determine the first sector of the Root Directory (FAT32)
    else{
        drive->FirstRootDirSec = ((BPB_RootClus - 2) * BPB_SecPerClus) + First Data Sector;
    }    
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
    sector = ((cluster * drive->FATType)/drive->BytesPerSec) + drive->StartofFAT;

    //Step 2: Read the FAT sector into SRAM
    read_sector(sector, drive->BytesPerSec, array);

    //Step 3: Determine the entry offeset of the cluster within this sector
    FATOffset = (uint16_t)((cluster * drive->FATType)%(drive->BytesPerSec));

    //Step 4: Read the cluster entry from the FAT sector in SRAM
    if(drive->FATType == FAT32){
        return_clus = (read_value_32(FATOffset,array)&0x0FFFFFFF);
    }
    else{
        return_clus = (read_value_16(FATOffset,array));
    }
    return return_clus;
}