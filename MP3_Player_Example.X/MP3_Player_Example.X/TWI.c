#include <avr/io.h>
#include "board.h"
#include "TWI.h"
#include <stdio.h>

#define START_sent (0x08)
#define r_START_sent (0x10)
#define SLA_W_ACK (0x18)
#define SLA_W_NACK (0x20)
#define DATA_SENT_ACK (0x28)
#define DATA_SENT_NACK (0x30)
#define ARB_LOST (0x38)
#define SLA_R_ACK (0x40)
#define SLA_R_NACK (0x48)
#define DATA_RCV_ACK (0x50)
#define DATA_RCV_NACK (0x58)

/***********************************************************************
DESC:    Sets the Prescale and Clock Rate Generator for the two wire interface
INPUT: Desired SCL clock frequency
RETURNS: Nothing
CAUTION: 
          
************************************************************************/

uint8_t TWI_master_init(volatile TWI_t *TWI_addr, uint32_t I2C_FREQ)
{
	uint32_t temp32;
	uint8_t Prescale=0, return_val=0;
    uint8_t prescale_value=1;
	
	
	do
    {
       temp32 = (((F_CPU/OSC_DIV)/I2C_FREQ)-16)/(2*prescale_value); 
       if(temp32>255)
       {
         Prescale++;
         prescale_value*=4;  
       } 
    }while(temp32>255);

	if(Prescale>3)
	{
		(TWI_addr->TWI_TWSR)=3;
		(TWI_addr->TWI_TWBR)=255U;

        return_val=TWI_CLOCK_ERROR;
	}
	else
	{
		(TWI_addr->TWI_TWSR)=Prescale;
		(TWI_addr->TWI_TWBR)=(uint8_t)temp32;
	}
	return return_val;
	
}

typedef enum {IDLE,DEV_ADDR,INT_ADDR,DATA_SEND,DATA_RCV,SEND_STOP,TWI_EXIT} TWI_state_t;

/***********************************************************************
DESC:    Uses the TWI peripheral to transmit the device address
         internal address and data contained in an array
INPUTS: Base address of the TWI peripheral to use
        The device address and internal address of where to start writing data
        The internal address size allows for more flexibility in bus devices
        The number of bytes to send and an array of those bytes
RETURNS: Error status
CAUTION: 
          
************************************************************************/

uint8_t TWI_master_transmit(volatile TWI_t *TWI_addr, uint8_t device_addr, uint32_t internal_addr, uint8_t int_addr_bytes, uint8_t num_bytes, uint8_t send_array[])
{
  uint8_t send_val, return_val, index, status;
  TWI_state_t TWI_master_state;
  volatile uint8_t temp8;
  uint16_t timeout; 
  TWI_master_state=IDLE;
  return_val=no_errors;
  index=0;
  timeout=0;
  // Send START condition;  
  (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWSTA)|(1<<TWEN));   // TWIINT=1 to clear flag, TWSTA=1 for Start, TWEN=1
  do 
  {
	 status=(TWI_addr->TWI_TWCR);
	 timeout++;
  } while (((status&0x80)==0)&&(timeout!=0));
  temp8=((TWI_addr->TWI_TWSR)&0xF8);
  if((temp8==START_sent)||(temp8==r_START_sent))   // Start sent
  {
	  TWI_master_state=DEV_ADDR;
  }
  else if(timeout==0)
  {
	  TWI_master_state=TWI_EXIT;
	  return_val=BUS_BUSY_ERROR;
  }
  else
  {
	  TWI_master_state=TWI_EXIT;
	  return_val=BUS_BUSY_ERROR;
  }

  if(TWI_master_state==DEV_ADDR)
  {
	  send_val=device_addr<<1; // lsb is 0 for W
	  (TWI_addr->TWI_TWDR)=send_val;
	  (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEN));   // TWIINT=1 to clear flag, TWEN=1
	  do
	  {
		  status=(TWI_addr->TWI_TWCR);
	  } while ((status&0x80)==0);
	  temp8=((TWI_addr->TWI_TWSR)&0xF8);
	  if(temp8==SLA_W_ACK)   // SLA+W sent, ACK received
	  {
		  if(int_addr_bytes!=0)
		  {
		     TWI_master_state=INT_ADDR;
			 index=5-int_addr_bytes;
		  }
		  else if(num_bytes!=0)
		  {
			 TWI_master_state=DATA_SEND;
		  }
		  else
		  {
			  TWI_master_state=SEND_STOP;
		  }
	  }
	  else if(temp8==SLA_W_NACK)  // SLA+W sent, NACK received
	  {
		  TWI_master_state=SEND_STOP;
		  return_val=NACK_ERROR;
	  }
	  else if(temp8==ARB_LOST)  // Arbitration lost
	  {
		  (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEN));   // TWIINT=1 to clear flag, TWEN=1
		  TWI_master_state=TWI_EXIT;
		  return_val=BUS_BUSY_ERROR;
	  } 
  }
  
  /**** Send Internal Address *****/
     while(TWI_master_state==INT_ADDR)
     {
	    send_val=(uint8_t)(internal_addr>>(8*(4-index)));
	    index++;
	    (TWI_addr->TWI_TWDR)=send_val;
	    (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEN));   // TWIINT=1 to clear flag, TWEN=1
		do
		{
		   status=(TWI_addr->TWI_TWCR);
		} while ((status&0x80)==0);
		temp8=((TWI_addr->TWI_TWSR)&0xF8);
		if(temp8==DATA_SENT_ACK)  // Data sent, ACK received
		{
			if(index==5 /*int_addr_bytes_max*/)
			{
				if(num_bytes!=0)
				{
					TWI_master_state=DATA_SEND;
				}
				else
				{
					TWI_master_state=SEND_STOP;
				}
				
			}   
		}
		else if(temp8==DATA_SENT_NACK)  // Data sent, NACK received
		{
		   TWI_master_state=SEND_STOP;
		    return_val=NACK_ERROR;
		}
		else if(temp8==ARB_LOST)  // Arbitration lost
		{
			(TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEN));   // TWIINT=1 to clear flag, TWEN=1
			TWI_master_state=IDLE;
			return_val=BUS_BUSY_ERROR;
		}
     }
  index=0;	  
  /**** Send Data Bytes ******/
     while(TWI_master_state==DATA_SEND)
     {
		 send_val=send_array[index];
		 index++;
		 (TWI_addr->TWI_TWDR)=send_val;
		 (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEN));   // TWIINT=1 to clear flag, TWEN=1
		 do
		 {
		   status=(TWI_addr->TWI_TWCR);
		 } while ((status&0x80)==0);    // Wait for TWINT to be set
		 temp8=((TWI_addr->TWI_TWSR)&0xF8);
		 if(temp8==DATA_SENT_ACK)  // Data sent, ACK received
		 {
			 if(num_bytes==index)
			 {
				 TWI_master_state=SEND_STOP;
			 }
			   
		 }
		 else if(temp8==DATA_SENT_NACK)  // Data sent, NACK received
		 {
			   TWI_master_state=SEND_STOP;
			   return_val=NACK_ERROR;
		 }
		 else if(temp8==ARB_LOST)  // Arbitration lost
		 {
			   (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEN));   // TWIINT=1 to clear flag, TWEN=1
			   TWI_master_state=TWI_EXIT;
			   return_val=BUS_BUSY_ERROR;
		 }
	   }
	   /**** Send Stop Condition ******/
	   if(TWI_master_state==SEND_STOP)
	   {
		   (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWSTO)|(1<<TWEN));   // TWIINT=1 to clear flag, TWSTO=1 for Stop, TWEN=1
		   do
		   {
			   status=(TWI_addr->TWI_TWCR);
		   } while ((status&(1<<TWSTO))!=0); // Wait for the Stop flag to be cleared // Wait for the Stop flag to be cleared
		   TWI_master_state=TWI_EXIT;
	   }
	   /***** TWI EXIT *****/
	   if(TWI_master_state==TWI_EXIT)
	   {
		   TWI_master_state=IDLE;
	   }
       return return_val;
}

/***********************************************************************
DESC:    Uses the TWI peripheral to transmit the device address
         internal address from which data should be received
         The values that are received are stored in an array
INPUTS: Base address of the TWI peripheral to use
        The device address and internal address of where to start writing data
        The internal address size allows for more flexibility in bus devices
        The number of bytes to send and an array of those bytes
RETURNS: Error status, received values in an array
CAUTION: 
          
************************************************************************/

uint8_t TWI_master_receive(volatile TWI_t *TWI_addr, uint8_t device_addr, uint32_t internal_addr, uint8_t int_addr_bytes, uint8_t num_bytes, uint8_t rec_array[])
{
  uint8_t temp8, send_val, return_val, index, status;
  TWI_state_t TWI_master_state;
  uint16_t timeout;
  uint8_t send_array[2];
  return_val=no_errors;
  if(int_addr_bytes!=0)
  {
	  return_val=TWI_master_transmit(TWI_addr,device_addr,internal_addr, int_addr_bytes,0,send_array);
  }
  index=0;
  timeout=0;
  // Send START
  (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWSTA)|(1<<TWEN));   // TWIINT=1 to clear flag, TWSTA=1 for Start, TWEN=1
  do
  {
	  status=(TWI_addr->TWI_TWCR);
	  timeout++;
  } while (((status&0x80)==0)&&(timeout!=0)); // Wait for Status flag to be set
  temp8=((TWI_addr->TWI_TWSR)&0xF8);
  if((temp8==START_sent)||(temp8==r_START_sent))   // Start or Repeated Start sent
  {
	  TWI_master_state=DEV_ADDR;
  }
  else if(timeout==0)
  {
	  TWI_master_state=TWI_EXIT;
	  return_val=BUS_BUSY_ERROR;
  }
  else
  {
	  TWI_master_state=TWI_EXIT;
	  return_val=BUS_BUSY_ERROR;
  }
  if(TWI_master_state==DEV_ADDR)
  {
	 send_val=((device_addr<<1)|0x01); // lsb is 1 for R
	 (TWI_addr->TWI_TWDR)=send_val;
	 (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEN));   // TWIINT=1 to clear flag, TWEN=1
	  do
	  {
		  status=(TWI_addr->TWI_TWCR);
	  } while ((status&0x80)==0); // Wait for Status flag to be set
	  temp8=((TWI_addr->TWI_TWSR)&0xF8);
	  if(temp8==SLA_R_ACK)   // SLA+R sent, ACK received
	  {
		  TWI_master_state=DATA_RCV;
	  }
	  else if(temp8==SLA_R_NACK)
	  {
		   TWI_master_state=SEND_STOP;
		   return_val=NACK_ERROR;
	  }
	  else if(temp8==ARB_LOST)
	  {
		  TWI_master_state=TWI_EXIT;
		  return_val=BUS_BUSY_ERROR;
	  }
  }
  index=0;
  while(TWI_master_state==DATA_RCV)
  {
	 if(num_bytes==1)
	 {
		 (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEN));   // TWIINT=1 to clear flag, TWEA=0 for NACK, TWEN=1 
	 }
	 else
	 {
		 (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEA)|(1<<TWEN));   // TWIINT=1 to clear flag, TWEA=1 for ACK, TWEN=1
	 }
     do
	 {
		status=(TWI_addr->TWI_TWCR);
	  } while ((status&0x80)==0); // Wait for Status flag to be set
	  temp8=((TWI_addr->TWI_TWSR)&0xF8);
	  num_bytes--;
	  rec_array[index]=(TWI_addr->TWI_TWDR);
	  index++;
	  if(temp8==DATA_RCV_ACK)   // Data byte received, ACK sent
	  {
	      // TWI_master_state=DATA_RCV;
	  }
	  else if(temp8==DATA_RCV_NACK)  // Data byte received, NACK sent
	  {
		  TWI_master_state=SEND_STOP;
	  }
	  else if(temp8==ARB_LOST)  // Arbitration lost
	  {
		  (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWEN));   // TWIINT=1 to clear flag, TWEN=1
		   return_val=BUS_BUSY_ERROR;
		   TWI_master_state=TWI_EXIT;
      }
   }
   if(TWI_master_state==SEND_STOP)
   {
	  (TWI_addr->TWI_TWCR) = ((1<<TWINT)|(1<<TWSTO)|(1<<TWEN));   // TWIINT=1 to clear flag, TWSTO=1 for Stop, TWEN=1
	  do
	  {
		  status=(TWI_addr->TWI_TWCR);
	  } while ((status&(1<<TWSTO))!=0); // Wait for the Stop flag to be cleared // Wait for the Stop flag to be cleared
	  TWI_master_state=TWI_EXIT;
  }
  /***** TWI EXIT *****/
  if(TWI_master_state==TWI_EXIT)
  {
	  TWI_master_state=IDLE;
  }
  return return_val; 
}
 
 



