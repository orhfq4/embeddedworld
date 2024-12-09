#include <stdio.h>
#include "peripherals.h"
#include "board.h"
#include "SPI.h"
#include "SPI_CS.h"
#include "File_System.h"
#include "Read_Sector.h"
#include "GPIO_Outputs.h"
#include "LEDS.h"
#include "GPIO_Inputs.h"
#include "STA013_Config.h"
#include "UART_Print.h"
#include "Play_Song.h"
extern uint8_t buffer1_g[512];
extern uint8_t buffer2_g[512]; 

void play_song(uint32_t Start_Cluster)
{
   uint16_t index1, index2;
   uint8_t buf_flag1, buf_flag2;
   INPUT_STATE_t temp8;
   uint32_t sector, sector_offset;
   uint32_t currentCluster = Start_Cluster;
   char *prnt_bffr;
   
   prnt_bffr=export_print_buffer();
   //**** LEDS initialized for debugging ****//
   LED_ctor(&led0, LED0_PORT, LED0_PIN, LED_OFF, ACTIVE_LOW);
   LED_ctor(&led1, LED1_PORT, LED1_PIN, LED_OFF, ACTIVE_LOW);
   LED_ctor(&led2, LED2_PORT, LED2_PIN, LED_OFF, ACTIVE_LOW);
   LED_ctor(&led3, LED3_PORT, LED3_PIN, LED_OFF, ACTIVE_LOW);
   SPI_CS_ctor(&sta013_biten, STA013_BITEN_Port, STA013_BITEN_Pin, 
                              CS_INACTIVE, CS_ACTIVE_HIGH);
   GPIO_input_ctor(&sta013_data_req, STA013_DATAREQ_Port, STA013_DATAREQ_Pin, PU_DISABLED);
   sprintf(prnt_bffr,"Starting Cluster = %lu\n\r",Start_Cluster);
   UART_transmit_string(UART1,prnt_bffr,0);
   sector=first_sector(Start_Cluster);
   sprintf(prnt_bffr,"Starting Sector = %lu\n\r",sector);
   UART_transmit_string(UART1,prnt_bffr,0);
   sector_offset=0;
   buf_flag1=1;
   buf_flag2=0;
   //P3_2=ON;
   LED_set_value(&led1, LED_ON);
   index1=0;
   
   read_sector(sector+sector_offset, 512, buffer1_g);

   sector_offset++;
   LED_set_value(&led1, LED_OFF);
   LED_set_value(&led2, LED_ON);
   index2=0;
   
   read_sector(sector+sector_offset, 512, buffer2_g);
   sector_offset++;
   LED_set_value(&led2, LED_OFF);
   do
  {      
     do
     {
        temp8=GPIO_input_get_value(&sta013_data_req);
		if(INPUT_CLEAR==temp8)
        {
           //GREENLED=ON;
           SPI_CS_set_value(&sta013_biten,CS_ACTIVE);
           SPI_transmit(STA013_SPI_Port,buffer1_g[index1]);
		   SPI_CS_set_value(&sta013_biten,CS_INACTIVE);
	       //GREENLED=OFF;
	       index1++;
           if(index1>511)
           {
              if(index2>511)
              {
                  //BIT_EN=0;              
                  LED_set_value(&led2, LED_ON);
				  index2=0;
				  
				  read_sector(sector+sector_offset, 512, buffer2_g);
				  sector_offset++;
                  LED_set_value(&led2, LED_OFF);
              }
              buf_flag1=0;
              buf_flag2=1;

          }
       }
       else
       {
          if(index2>511)
          {
              //BIT_EN=0;
              LED_set_value(&led2, LED_ON);
			  index2=0;
			  
			  read_sector(sector+sector_offset, 512, buffer2_g);
			  sector_offset++;
              LED_set_value(&led2, LED_OFF);
          }
          else
          {
              if(index1>511)
              {
                  buf_flag1=0;
                  buf_flag2=1;
              }
          }
      }
   }while(buf_flag1==1);
   do
   {
	   temp8=GPIO_input_get_value(&sta013_data_req);
      if(INPUT_CLEAR==temp8)
      {
          //REDLED=ON;
          SPI_CS_set_value(&sta013_biten,CS_ACTIVE);
          SPI_transmit(STA013_SPI_Port,buffer2_g[index2]);
		  SPI_CS_set_value(&sta013_biten,CS_INACTIVE);
          //REDLED=OFF;
          index2++;
          if(index2>511)
          {
              if(index1>511)
              {
                  //BIT_EN=0; 
                  LED_set_value(&led1, LED_ON);
				  index1=0;
				  
				  read_sector(sector+sector_offset, 512, buffer1_g);
				  sector_offset++;
                  LED_set_value(&led1, LED_OFF);
              }
              buf_flag2=0;
              buf_flag1=1;
         
           }
        }
        else
        {
           if(index1>511)
           {
              //BIT_EN=0; 
              LED_set_value(&led1, LED_ON);
			  index1=0;
			  
			  read_sector(sector+sector_offset, 512, buffer1_g);
			  sector_offset++;
              LED_set_value(&led1, LED_OFF);
           }
           else
           {
               if(index2>511)
               {
                  buf_flag2=0;
                  buf_flag1=1;
               }
           }
        }
      }while(buf_flag2==1);
      
      // After completing the sectors, check if we need to move to the next cluster
      if (sector_offset >= 128/*Drive_p->SecPerClus*/)  // Assuming a cluster has 128 sectors
        {
            currentCluster = find_next_clus(currentCluster, buffer1_g);
            if (currentCluster == 0x0FFFFFFF)
            {
                // EOF reached, stop playing
                break;
            }

            // Reset the sector offset for the next cluster
            sector = first_sector(currentCluster);
            sector_offset = 0;
        }
      
      
  }while(sector_offset< 128/*Drive_p->SecPerClus*/);
} 

