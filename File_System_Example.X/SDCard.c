#include "board.h"
#include "SDCard.h"
#include "GPIO_Outputs.h"
#include "print_memory.h"
#include "SPI.h"
#include <stdio.h>
#include <avr/pgmspace.h>
#include "UART.h"
#include "UART_Print.h"
#include "LEDS.h"
#include "SPI_CS.h"

static uint8_t SD_Card_Type;

//******************************* (Question 1) *******************************


/***********************************************************************
DESC:    Sends Commands to SD card using the SPI peripheral
         cmnd=Command number to be sent
         argum=32bit argument for a command
RETURNS: error flag
CAUTION: Must be followed by a read to capture SD card response
         nCS0 must be set/cleared outside of this routine 
************************************************************************/
uint8_t Send_Command(uint8_t cmnd, uint32_t argum)
{
 uint8_t SPI_send, return_val, error_flag;

 return_val=no_errors;
 if(cmnd<64)
 {
   SPI_send=cmnd | 0x40;
   error_flag=SPI_transmit(SD_Card_Port,SPI_send);
   if((error_flag)==no_errors)
   {
     SPI_send=argum>>24;   // MSB
     error_flag=SPI_transmit(SD_Card_Port,SPI_send);
   }
   else
   {
     return_val=SPI_error;
   }
   if((return_val==no_errors)&&(error_flag==no_errors))
   {
     argum=argum & 0x00ffffff;
     SPI_send=argum>>16;  // BYTE2
     error_flag=SPI_transmit(SD_Card_Port,SPI_send);
   }
   else
   {
     return_val=SPI_error;
   }
   if((return_val==no_errors)&&(error_flag==no_errors))
   {
     argum=argum & 0x0000ffff;
     SPI_send=argum>>8;   // BYTE1
     error_flag=SPI_transmit(SD_Card_Port,SPI_send);
   }
   else
   {
     return_val=SPI_error;
   }     
   if((return_val==no_errors)&&(error_flag==no_errors))
   {
     SPI_send=argum & 0x000000ff;  // LSB
     error_flag=SPI_transmit(SD_Card_Port,SPI_send);
   }
   else
   {
     return_val=SPI_error;
   }
   if((return_val==no_errors)&&(error_flag==no_errors))
   {         
      if (cmnd == 0)
      {
         SPI_send=0x95;  // CRC7 and end bit for CMD0
      }
      else if (cmnd == 8)
      {
         SPI_send=0x87;   // CRC7 and end bit for CMD8
      }
      else
      {
         SPI_send=0x01;  // end bit only for other commands
      }
      error_flag=SPI_transmit(SD_Card_Port,SPI_send);
    }
 }
 else
 {
   return_val=illegal_cmnd;
 }
 return return_val;  
}
/***********************************************************************
DESC:    Read values from SPI port, 0xff sent for each byte read 
		 num_bytes=number of bytes to read
RETURNS: error flag
         *valout=address of array of bytes read
CAUTION: Used to capture SD card response
         nCS0 must be set/cleared outside of this routine 
************************************************************************/
uint8_t Receive_Response(uint8_t num_bytes, uint8_t * valout)
{
   uint8_t index,return_val,error_flag, SPI_return;

   index=0;
   return_val=no_errors;
   do
   {
      error_flag=SPI_receive(SD_Card_Port, 0xFF, &SPI_return);
      index++;
   }while((((SPI_return&0x80)==0x80)||((SPI_return&0x0E)==0x0E))&&(index!=0)&&(error_flag==no_errors));
   if(error_flag!=no_errors)
   {
      return_val=error_flag;
   }
   else if(index==0)
   {
      return_val=rr_timeout_error;
   }
   else
   {
     *valout=SPI_return;
     if((SPI_return==0x00)||(SPI_return==0x01))
     {
       if(num_bytes>1)
       {
         for(index=1;index<num_bytes;index++)
         {
            error_flag=SPI_receive(SD_Card_Port, 0xFF, &SPI_return);
            *(valout+index)=SPI_return;
         }
       }
     }
     else
     {
        return_val=response_error;
     }
   }
   error_flag=SPI_receive(SD_Card_Port, 0xFF, &SPI_return);  // send 8 more clock cycles to complete read
   return return_val;
}


/**********************************************************************
DESC:    Reads a specified number of bytes from SD card,
         0xff sent for each byte read 
RETURNS: error flag
         block of data stored in array_out[]
CAUTION: Used to capture SD card response
         nCS0 must be set/cleared outside of this routine 
************************************************************************/
uint8_t Read_Block(uint16_t num_bytes, uint8_t array_out[])
{
   uint8_t error_flag,return_val,SPI_return;
   uint16_t index;
   index=0;
   return_val=no_errors;
   do
   {
      error_flag=SPI_receive(SD_Card_Port, 0xFF, &SPI_return);
      index++;
   }while(((SPI_return&0x80)==0x80)&&(index!=0)&&(error_flag==no_errors));
   if(error_flag!=no_errors)
   {
      return_val=error_flag;
   }
   else if(index==0)
   {
      return_val=rr_timeout_error;
   }
   else
   {
     if (SPI_return==0x00)
     {
        index=0;
	    do
        { 
           error_flag=SPI_receive(SD_Card_Port, 0xFF, &SPI_return);
           index++;
        }while((SPI_return==0xFF)&&(index!=0)&&(error_flag==no_errors));          // wait for data token response  
        if(error_flag!=no_errors)
        {
           return_val=SPI_error;
        }
        else if(index==0)
        {
          return_val=fe_timeout_error;
        }
        else if(SPI_return==0xfe)
        {
          for(index=0;index<num_bytes;index++)
          {
             error_flag=SPI_receive(SD_Card_Port, 0xFF, &SPI_return);
             *(array_out + index)=SPI_return;
          }
          error_flag=SPI_receive(SD_Card_Port, 0xFF, &SPI_return); // discard byte 1 of CRC16	
          error_flag=SPI_receive(SD_Card_Port, 0xFF, &SPI_return); // discard byte 2 of CRC16
        }
	    else
	    {
	      return_val=data_error;
	    }
     }
     else
     {
        return_val=response_error;
     }
   }
 error_flag=SPI_receive(SD_Card_Port, 0xFF, &SPI_return);  // send 8 more clock cycles to complete read
return return_val;
}

/**********************************************************************
  Strings in Flash Memory for SD_Card_Init diagnostic outputs
***********************************************************************/
const char SD_Card_Intro[30] PROGMEM = {"SD Card Initialization ... \n\r"}; 
const char SD_Card_CMD0[15] PROGMEM = {"CMD0 sent ... "};
const char SD_Card_CMD8[15] PROGMEM = {"CMD8 sent ... "};
const char SD_Card_CMD16[16] PROGMEM = {"CMD16 sent ... "};
const char SD_Card_CMD58[16] PROGMEM = {"CMD58 sent ... "};
const char SD_Card_ACMD41[17] PROGMEM = {"ACMD41 sent ... "};
const char SD_Card_Resp[12] PROGMEM = {"Response = "};	
const char SD_Card_V1[30] PROGMEM = {"Version 1 SD Card detected.\n\r"};
const char SD_Card_V2[30] PROGMEM = {"Version 2 SD Card detected.\n\r"};
const char SD_Card_SC[35] PROGMEM = {"Standard Capacity Card detected.\n\r"};
const char SD_Card_HC[31] PROGMEM = {"High Capacity Card detected.\n\r"};	
const char SD_Card_BlSz[30] PROGMEM = {"Block size set to 512 bytes\n\r"};	


/**********************************************************************
DESC:    Sends the commands needed to initialize the SD card 
RETURNS: error flag
CAUTION: The SPI port for the SD Card is defined as SD_Card_Port in SDCard.h
************************************************************************/
uint8_t SD_Card_Init(void)
{
   uint8_t error_status,tx_error_flag,SPI_return;
   uint16_t i;
   uint8_t valsout[8]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
   uint8_t rx_error_flag=rr_timeout_error;
   uint32_t argument;
   uint16_t timeout;
   char *prnt_bffr;
   
   prnt_bffr=export_print_buffer();
   
   error_status=no_errors;
   SD_Card_Type=unknown;
   
   /* LEDs initialized for debugging status signals */
   LED_ctor(&led0,LED0_PORT,LED0_PIN,LED_OFF,ACTIVE_LOW); 
   LED_ctor(&led3,LED3_PORT,LED3_PIN,LED_OFF,ACTIVE_LOW);
   
   SPI_CS_ctor(&sd_cs, SD_CS_Port,SD_CS_Pin,CS_INACTIVE,CS_ACTIVE_LOW); 
   copy_string_to_buffer(SD_Card_Intro,prnt_bffr,0);
   UART_transmit_string(print_port,prnt_bffr,0);
   copy_string_to_buffer(SD_Card_CMD0,prnt_bffr,0);
   UART_transmit_string(print_port,prnt_bffr,0);
   timeout=0;
   //**** CMD0 is in a loop to possibly clear pending communication for more reliable startup ****
   do 
   {
   //**** Power Up ******
          SPI_CS_set_value(&sd_cs, CS_INACTIVE);
		  
		  for(i=0;i<10;i++)
		  {
			  SPI_return=SPI_transmit(SD_Card_Port,0xFF);
		  }
		  //**** CMD0 ******
		  LED_set_value(&led0,LED_ON);
	      SPI_CS_set_value(&sd_cs, CS_ACTIVE);
	      tx_error_flag=Send_Command(CMD0,0);
	      if(tx_error_flag==no_errors)
	      {
		      rx_error_flag=Receive_Response(1,valsout);
		      SPI_CS_set_value(&sd_cs, CS_INACTIVE);
		      LED_set_value(&led0,LED_OFF);
		      copy_string_to_buffer(SD_Card_Resp,prnt_bffr,0);
		      UART_transmit_string(print_port,prnt_bffr,0);
		      sprintf(prnt_bffr, "%2.2X\n\r",valsout[0]);
		      UART_transmit_string(print_port,prnt_bffr,0);  
	      }
	      else
	      {
		      SPI_CS_set_value(&sd_cs, CS_INACTIVE);
		      LED_set_value(&led0,LED_OFF);
		      LED_set_value(&led3,LED_ON);   //indicates error has occurred.
	      }
		  
		  if(valsout[0]!=0x01)
		  {
			  //**** If the IN_IDLE_STATE R1 response is not received ***//
			  //**** Attempt to clear any incomplete communications ****//
			  SPI_CS_set_value(&sd_cs, CS_ACTIVE);
			  for(i=0;i<530;i++)
			  {
				  tx_error_flag=SPI_receive(SD_Card_Port, 0xFF, &SPI_return);
			  }
			  SPI_CS_set_value(&sd_cs, CS_INACTIVE);
		  }
		  else
		  {
			  error_status=no_errors;
		  }
		  timeout++;
		  
		  if(rx_error_flag!=no_errors)
		  {
			error_status=rx_error_flag;
		  }
		  
   } while ((timeout<10)&&(error_status!=no_errors));
   if(timeout==10)
   {
	   rx_error_flag=response_error;
	   error_status=response_error;
   }

   if(tx_error_flag!=no_errors)
   {
     error_status=tx_error_flag;
   }
   //**** CMD8 ******
   if(error_status==no_errors)
   {
     LED_set_value(&led0,LED_ON);
     copy_string_to_buffer(SD_Card_CMD8,prnt_bffr,0);
     UART_transmit_string(print_port,prnt_bffr,0);
     SPI_CS_set_value(&sd_cs, CS_ACTIVE);
     tx_error_flag=Send_Command(CMD8,0x000001AA);
	 if(tx_error_flag==no_errors)
     {
        rx_error_flag=Receive_Response(5,valsout);
		SPI_CS_set_value(&sd_cs, CS_INACTIVE);
		LED_set_value(&led0,LED_OFF);
	    copy_string_to_buffer(SD_Card_Resp,prnt_bffr,0);
	    UART_transmit_string(print_port,prnt_bffr,0);
        for(i=0;i<5;i++)
		{   
		        sprintf(prnt_bffr, "%2.2X ",valsout[i]);
				UART_transmit_string(print_port,prnt_bffr,0);
		}
        UART_transmit(print_port,CR);
        UART_transmit(print_port,LF);
		if(valsout[4]!=0xAA)
		{
		   tx_error_flag=response_error;
		}
     }
     else
     {
        SPI_CS_set_value(&sd_cs, CS_INACTIVE);
        LED_set_value(&led0,LED_OFF);
	    LED_set_value(&led3,LED_ON);  //indicates error has occured.
     }
	 if(rx_error_flag!=no_errors)
	 {
        if(rx_error_flag==illegal_cmnd)
        {
           error_status=no_errors;
		   SD_Card_Type=Standard_Capacity;
		   copy_string_to_buffer(SD_Card_V1,prnt_bffr,0);
		   UART_transmit_string(print_port,prnt_bffr,0);
		   copy_string_to_buffer(SD_Card_SC,prnt_bffr,0);
		   UART_transmit_string(print_port,prnt_bffr,0);
        }
		else
		{
		   error_status=rx_error_flag;
		}
	 }
	 else
	 {
		SD_Card_Type=Ver2;
		copy_string_to_buffer(SD_Card_V2,prnt_bffr,0);
		UART_transmit_string(print_port,prnt_bffr,0);
	 }
   }
   //**** CMD58 ******
   if(error_status==no_errors)
   {
     LED_set_value(&led0,LED_ON);
     copy_string_to_buffer(SD_Card_CMD58,prnt_bffr,0);
     UART_transmit_string(print_port,prnt_bffr,0);
     SPI_CS_set_value(&sd_cs, CS_ACTIVE);
     tx_error_flag=Send_Command(CMD58,0);
	 if(tx_error_flag==no_errors)
     {
        rx_error_flag=Receive_Response(5,valsout);
		SPI_CS_set_value(&sd_cs, CS_INACTIVE);
		LED_set_value(&led0,LED_OFF);
	    copy_string_to_buffer(SD_Card_Resp,prnt_bffr,0);
	    UART_transmit_string(print_port,prnt_bffr,0);
        for(i=0;i<5;i++)
		{   
		     sprintf(prnt_bffr, "%2.2X ",valsout[i]);
			 UART_transmit_string(print_port,prnt_bffr,0);
		}
        UART_transmit(print_port,CR);
        UART_transmit(print_port,LF);
		if((valsout[2]&0xFC)!=0xFC)
		{
		   tx_error_flag=voltage_error;
		}
     }
     else
     {
        SPI_CS_set_value(&sd_cs, CS_INACTIVE);
        LED_set_value(&led0,LED_OFF);
	    LED_set_value(&led3,LED_ON);  //indicates error has occurred.
     }
	 if(tx_error_flag!=no_errors)
	 {		
	    error_status=tx_error_flag;
	 }
   }
   if(error_status==no_errors)
   {
     if(SD_Card_Type==Ver2)
	 {
	    argument=0x40000000;
	 }
	 else
	 {
	    argument=0;
	 }
	 timeout=0;
     LED_set_value(&led0,LED_ON);
     copy_string_to_buffer(SD_Card_ACMD41,prnt_bffr,0);
     UART_transmit_string(print_port,prnt_bffr,0);
     //SD_Card_CS_Active(SD_CS_Port,SD_CS_Pin);
	 //**** ACMD41  (CMD55,CMD41) ******
	 do
	 {
	    //P3_5=0;
		SPI_CS_set_value(&sd_cs, CS_ACTIVE);
	    tx_error_flag=Send_Command(CMD55,0);
		if(tx_error_flag==no_errors)  rx_error_flag=Receive_Response(1,valsout);
		//P3_5=1;
	    if((valsout[0]==0x01)||(valsout[0]==0x00))
		   tx_error_flag=Send_Command(ACMD41,argument);
	    if(tx_error_flag==no_errors) rx_error_flag=Receive_Response(1,valsout);
		SPI_CS_set_value(&sd_cs, CS_INACTIVE);
		timeout++;
		if(timeout==0) tx_error_flag=acmd41_timeout_error;
	   }while(((valsout[0]&0x01)==0x01)&&(tx_error_flag==no_errors));
	 if(tx_error_flag==no_errors)
     {
		//SD_Card_CS_Inactive(SD_CS_Port,SD_CS_Pin);
        LED_set_value(&led0,LED_OFF);
	    copy_string_to_buffer(SD_Card_Resp,prnt_bffr,0);
	    UART_transmit_string(print_port,prnt_bffr,0);
		sprintf(prnt_bffr, "%2.2X \n\r",valsout[0]);
		UART_transmit_string(print_port,prnt_bffr,0);
     }
     else
     {
        //SD_Card_CS_Inactive(SD_CS_Port,SD_CS_Pin);
        LED_set_value(&led0,LED_OFF);
	    LED_set_value(&led3,LED_ON);
     }
	 if(tx_error_flag!=no_errors)
	 {		
	    error_status=tx_error_flag;
	 }
   }
   //**** CMD58 (determine Card Capacity) ******
   if((error_status==no_errors)&&(SD_Card_Type==Ver2))
   {
     LED_set_value(&led0,LED_ON);
     copy_string_to_buffer(SD_Card_CMD58,prnt_bffr,0);
     UART_transmit_string(print_port,prnt_bffr,0);
     SPI_CS_set_value(&sd_cs, CS_ACTIVE);
     tx_error_flag=Send_Command(CMD58,0);
	 if(tx_error_flag==no_errors)
     {
        rx_error_flag=Receive_Response(5,valsout);
		SPI_CS_set_value(&sd_cs, CS_INACTIVE);
        LED_set_value(&led0,LED_OFF);
	    copy_string_to_buffer(SD_Card_Resp,prnt_bffr,0);
	    UART_transmit_string(print_port,prnt_bffr,0);
        for(i=0;i<5;i++)
		{   
           sprintf(prnt_bffr, "%2.2X ",valsout[i]);
		   UART_transmit_string(print_port,prnt_bffr,0);
		}
        UART_transmit(print_port,CR);
        UART_transmit(print_port,LF);
		if((valsout[1]&0x80)!=0x80)
		{
		   tx_error_flag=card_inactive;
		}
		else
		{
		   if((valsout[1]&0xC0)==0xC0)
		   {
		      SD_Card_Type=High_Capacity;
		      copy_string_to_buffer(SD_Card_HC,prnt_bffr,0);
		      UART_transmit_string(print_port,prnt_bffr,0);
		   }
		   else
		   {
		      SD_Card_Type=Standard_Capacity;
			  copy_string_to_buffer(SD_Card_SC,prnt_bffr,0);
			  UART_transmit_string(print_port,prnt_bffr,0);
			  LED_set_value(&led0,LED_ON);
              copy_string_to_buffer(SD_Card_CMD16,prnt_bffr,0);
              UART_transmit_string(print_port,prnt_bffr,0);
              SPI_CS_set_value(&sd_cs, CS_ACTIVE);
              tx_error_flag=Send_Command(CMD16,512);
	          if(tx_error_flag==no_errors)
              {
                  rx_error_flag=Receive_Response(1,valsout);
		          SPI_CS_set_value(&sd_cs, CS_INACTIVE);
                  LED_set_value(&led0,LED_OFF);
				  copy_string_to_buffer(SD_Card_Resp,prnt_bffr,0);
				  UART_transmit_string(print_port,prnt_bffr,0);
	              sprintf(prnt_bffr, "%2.2X \n\r",valsout[0]);
				  UART_transmit_string(print_port,prnt_bffr,0);
                  copy_string_to_buffer(SD_Card_BlSz,prnt_bffr,0);
                  UART_transmit_string(print_port,prnt_bffr,0);
		      }
			}
		 }
     }
     else
     {
        SPI_CS_set_value(&sd_cs, CS_INACTIVE);
        LED_set_value(&led0,LED_OFF);
	    LED_set_value(&led3,LED_ON); //indicates error has occurred.
     }
	 if(tx_error_flag!=no_errors)
	 {		
	    error_status=tx_error_flag;
	 }
   }
 
return error_status;
}

/**********************************************************************
DESC:    Returns the SD card type 
RETURNS: SD_Card_Type
CAUTION: SD card must be initialized first
************************************************************************/

uint8_t Return_SD_Card_Type(void)
{
   return SD_Card_Type;
}


/**** The following function is obsolete and needs to be updated ******/
/**********************************************************************
DESC:    Prints an error text based on the error code  
RETURNS: nothing
CAUTION: Mainly used for debugging
***********************************************************************/

/*
void Print_Error(uint8_t error)
{
   uint8_t print_buffer[25];
   if(error==timeout_error) sprintf(print_buffer, "Timeout Error\n\r");
   else if(error==illegal_cmnd) sprintf(print_buffer, "Illegal Command\n\r");
   else if(error==response_error) sprintf(print_buffer, "Response Error\n\r");
   else if(error==data_error) sprintf(print_buffer, "Data Token Error\n\r");
   else if(error==voltage_error) sprintf(print_buffer, "Incompatible Voltage\n\r");
   else if(error==card_inactive) sprintf(print_buffer, "Card is Inactive\n\r");
   else if(error==SPI_error) sprintf(print_buffer, "SPI or Timeout Error\n\r");
   else sprintf(print_buffer, "Unknown Error\n\r");
   print_port_Transmit_String(0,print_buffer);
} */

