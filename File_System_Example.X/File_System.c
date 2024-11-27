#include "File_System.h"
#include "board.h"

/************************************************ Question 5 ***********************************************************/
/*Variables to determine (according to 14b and 14d):
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
        /* Fat 16 */
    }
    else{
        /* Fat 32 */
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

    //Step 6: Determine the first sector of the Root Directory (FAT16)

    //Step 6: Determine the first sector of the Root Directory (FAT32)

    
}
