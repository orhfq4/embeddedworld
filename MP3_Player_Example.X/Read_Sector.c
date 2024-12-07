#include "board.h"
#include "SDCard.h"
#include "Read_Sector.h"
#include "SPI_CS.h"




uint8_t read_sector(uint32_t sector_number, uint16_t sector_size, uint8_t array_for_data[])
{
	uint8_t SDtype,error_flag=No_Disk_Error;

	SDtype=Return_SD_Card_Type();
    SPI_CS_set_value(&sd_cs, CS_ACTIVE);  // Clear nCS = 0
	error_flag=Send_Command(CMD17,(sector_number<<SDtype));
	if(error_flag==no_errors) error_flag=Read_Block(sector_size,array_for_data);
	SPI_CS_set_value(&sd_cs, CS_INACTIVE);  // Clear nCS = 1

	if(error_flag!=no_errors)
	{
		error_flag=Disk_Error;
	}
	
    return error_flag;
}
