#include "board.h"
#include "SDCard.h"
#include "Read_Sector.h"
#include "SPI_CS.h"


//*************************************** (Question 3) ************************

uint8_t read_sector(uint32_t sector_number, uint16_t sector_size, uint8_t array_for_data[])
{
	uint8_t error_flag=No_Disk_Error;

	uint8_t SD_Card_Type=Return_SD_Card_Type(); // HC=0, no change to sector number     
    // SC=9, multiplies sector number by 512 to convert to byte addr.
    
    SPI_CS_set_value(&sd_cs,CS_ACTIVE); //nCS0=0;     
    error_flag=Send_Command(17,(sector_number<<SD_Card_Type));     
    if(error_flag==no_errors) {
        error_flag=Read_Block(sector_size,array_for_data);
    }
    SPI_CS_set_value(&sd_cs,CS_INACTIVE);  // nCS0=1;
    if(error_flag!=no_errors) {
        error_flag=Disk_Error;
    } 
	
    return error_flag;
}
