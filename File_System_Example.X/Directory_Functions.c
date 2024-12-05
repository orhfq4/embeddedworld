#include <stdio.h>
#include "board.h"
#include "File_System.h"
#include "UART.h"
#include "Directory_Functions.h"
#include "Read_Sector.h"
#include "UART_Print.h"
#include "Drive_Values.h"
#include "Read_Values.h"
#include "print_memory.h"
#include "Long_Serial_In.h"
#include <avr/pgmspace.h>

/******* Private Constants *************/
#define CR (0x0D)
#define LF (0x0A) 

const char openFilePrompt[33] PROGMEM = {"Enter 1 to continue, 0 to exit\n\r\0"};

/***********************************************************************
DESC: Prints all short file name entries for a given directory 
INPUT: Starting Sector of the directory and the pointer to a 
block of memory in xdata that can be used to read blocks from the SD card
RETURNS: uint16_t number of entries found in the directory
CAUTION: Supports FAT16, SD_shift must be set before using this function
************************************************************************/

//******************************* (Question 2) ********************************

uint16_t  print_directory(uint32_t Sector_num, uint8_t * array_in)
{ 
   uint32_t Sector, max_sectors;
   uint16_t i, entries;
   uint8_t temp8, j, attr, out_val, error_flag;
   uint8_t * values;
   char *prnt_bffr;

   prnt_bffr=export_print_buffer();
   
   FS_values_t * drive;
   
   drive=export_drive_values();
   values=array_in;
   entries=0;
   i=0;
   if (drive->FATtype==FAT16)  // included for FAT16 compatibility
   { 
      max_sectors=drive->RootDirSecs;   // maximum sectors in a FAT16 root directory
   }
   else
   {
      max_sectors=drive->SecPerClus;
   }
   Sector=Sector_num;
   error_flag=read_sector(Sector,drive->BytesPerSec,values);
   if(error_flag==no_errors)
   {
     do
     {
        temp8=read_value_8(0+i,values);  // read first byte to see if empty
        if((temp8!=0xE5)&&(temp8!=0x00))
	    {  
	       attr=read_value_8(0x0b+i,values);
		   if((attr&0x0E)==0)   // if hidden, system or Vol_ID bit is set do not print
		   {
		      entries++;
			  sprintf(prnt_bffr,"%5d. ",entries);  // print entry number with a fixed width specifier
		      UART_transmit_string(UART1,prnt_bffr,0);
			  for(j=0;j<8;j++)
			  {
			     out_val=read_value_8(i+j,values);   // print the 8 byte name
			     UART_transmit(UART1,out_val);
			  }
              if((attr&0x10)==0x10)  // indicates directory
			  {
			     for(j=8;j<11;j++)
			     {
			        out_val=read_value_8(i+j,values);
			        UART_transmit(UART1,out_val);
			     }
			     sprintf(prnt_bffr,"[DIR]\r\n");
				 UART_transmit_string(UART1,prnt_bffr,0);
			  }
			  else       // print a period and the three byte extension for a file
			  {
			     UART_transmit(UART1,0x2E);       
			     for(j=8;j<11;j++)
			     {
			        out_val=read_value_8(i+j,values);
			        UART_transmit(UART1,out_val);
			     }
			     UART_transmit(UART1,CR);
                 UART_transmit(UART1,LF);
			  }
		    }
		}
		    i=i+32;  // next entry
		    if(i>510)
		    {
			  Sector++;
              if((Sector-Sector_num)<max_sectors)
			  {
                 error_flag=read_sector(Sector,drive->BytesPerSec,values);
			     if(error_flag!=no_errors)
			     {
			        entries=0;   // no entries found indicates disk read error
				    temp8=0;     // forces a function exit
			     }
                 i=0;
			  }
			  else
			  {
			     entries=entries|more_entries;  // set msb to indicate more entries in another cluster
			     temp8=0;                       // forces a function exit
			  }
		    }
         
	  }while(temp8!=0);
	}
	else
	{
	   entries=0;    // no entries found indicates disk read error
	}
   return entries;
 }


/***********************************************************************
DESC: Uses the same method as Print_Directory to locate short file names,
      but locates a specified entry and returns and cluster  
INPUT: Starting Sector of the directory, an entry number and a pointer to a 
block of memory in xdata that can be used to read blocks from the SD card
RETURNS: uint32_t with cluster in lower 28 bits.  Bit 28 set if this is 
         a directory entry, clear for a file.  Bit 31 set for error.
CAUTION: 
************************************************************************/

//******************************* (Question 2) ********************************

uint32_t read_dir_entry(uint32_t Sector_num, uint16_t Entry, uint8_t * array_in)
{ 
   uint32_t Sector, max_sectors, return_clus;
   uint16_t i, entries;
   uint8_t temp8, attr, error_flag;
   uint8_t * values;
   FS_values_t * drive;
   
   drive=export_drive_values();
   values=array_in;
   entries=0;
   i=0;
   return_clus=0;
   if (drive->FATtype==FAT16)  // included for FAT16 compatibility
   { 
      max_sectors=drive->RootDirSecs;   // maximum sectors in a FAT16 root directory
   }
   else
   {
      max_sectors=drive->SecPerClus;
   }
   Sector=Sector_num;
   error_flag=read_sector(Sector,drive->BytesPerSec,values);
   if(error_flag==no_errors)
   {
     do
     {
        temp8=read_value_8(0+i,values);  // read first byte to see if empty
        if((temp8!=0xE5)&&(temp8!=0x00))
	    {  
	       attr=read_value_8(0x0b+i,values);
		   if((attr&0x0E)==0)    // if hidden do not print
		   {
		      entries++;
              if(entries==Entry)
              {
			    if(drive->FATtype==FAT32)
                {
                   return_clus=read_value_8(21+i,values);
				   return_clus=return_clus<<8;
                   return_clus|=read_value_8(20+i,values);
                   return_clus=return_clus<<8;
                }
                return_clus|=read_value_8(27+i,values);
			    return_clus=return_clus<<8;
                return_clus|=read_value_8(26+i,values);
			    attr=read_value_8(0x0b+i,values);
			    if(attr&0x10) return_clus|=directory_bit;
                temp8=0;    // forces a function exit
              }
              
		    }
		}
		    i=i+32;  // next entry
		    if(i>510)
		    {
			  Sector++;
			  if((Sector-Sector_num)<max_sectors)
			  {
                 error_flag=read_sector(Sector,drive->BytesPerSec,values);
			     if(error_flag!=no_errors)
			     {
			         return_clus=no_entry_found;
                     temp8=0; 
			     }
			     i=0;
			  }
			  else
			  {
			     temp8=0;                       // forces a function exit
			  }
		    }
         
	  }while(temp8!=0);
	}
	else
	{
	   return_clus=no_entry_found;
	}
	if(return_clus==0) return_clus=no_entry_found;
   return return_clus;
 }

uint8_t open_file(FS_values_t *drive, uint32_t start_cluster, uint8_t array[]){
    uint8_t error_status = 0;
    uint8_t exit = 0;
    char * buffer; 
    buffer=export_print_buffer();
    uint32_t tempSector = 0; //Gilbert
    uint8_t temp8 = 0; //Ronald
    uint32_t temp32 = 0; //Jerry
    //reading the first sector of the cluster
    tempSector = First_Sector(drive, start_cluster); 
    //header print after first sector read
    sprintf(buffer, "Cluster: %X\r\n", start_cluster);
    UART_transmit_string(print_port, buffer, 0);
    sprintf(buffer, "Sector: %X\r\n", tempSector);
    UART_transmit_string(print_port, buffer, 0);
    temp8 = read_sector(tempSector, drive->BytesPerSec, array); // temp8 holds error status
    print_memory(array,512); //print_memory(buffer1_g, drive->BytesPerSec);
    if (1/*temp8 == 0*/){ // No read sector errors
        do{
            // PROMPT THE USER FOR CONT OR EXIT:
            copy_string_to_buffer(openFilePrompt,buffer,0);
            UART_transmit_string(print_port,buffer,0);
            temp32=long_serial_input(print_port); // Waiting for input. 
            sprintf(buffer," %lu \n\r",temp32);
            UART_transmit_string(print_port,buffer,0); // Printing the input
            if(temp32 == 1){
                //continue
                tempSector++; // Move on to the next sector (inc the sector index)
                exit = 0;
                if(tempSector == drive->SecPerClus){
                   start_cluster = find_next_clus(drive, start_cluster, array);
                   if(start_cluster == 0x0FFFFFFF){  // End of file reached
                       exit = 1; // exit the loop
                   }
                   tempSector = First_Sector(drive, start_cluster); // Could be just set to 0?
                }
                else{ // Print the next sector
                    temp8 = read_sector(tempSector, 512, array); // temp8 holds error status
                    print_memory(array,512);
                }
            }
            else if(temp32 == 0){
                //exit 
                exit = 1; // exits do-while
            }
            else{
                // user typed the wrong thing
                error_status = 1;
                exit = 1;
            }
        }while(exit == 0);
    }
    else{
        // There's an error
        error_status = 2;
    }
    return error_status;
    
}