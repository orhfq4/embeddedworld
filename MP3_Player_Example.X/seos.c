/*
 * File:   seos.c
 * Author: Jacob Byers
 *
 * Created on December 10, 2024, 10:44 PM
 */


#include "xc.h"
#include "seos.h"
#include "board.h"
#include "avr/pgmspace.h"
#include "stdio.h"
#include "Drive_Values.h"
#include "peripherals.h"
#include <avr/interrupt.h>

#define INTERVAL (12) // 12ms interval each time interrupt occurs

uint8_t sEOS_Init(uint8_t interval_ms){
    uint8_t OCR_value,error_flag;
    OCR_value =(uint8_t)((((interval_ms*F_CPU)+(1023999UL))/(1024000UL))-1);
    if(OCR_value<=255)
    {
        error_flag=0; // no errors;
        OCR2A=OCR_value;
        TIMSK2=0x02; // Enables OCRA match interrupt
        TCCR2A=0x02; // Auto-Reload counter on match with OCRA
        TCCR2B=0x07; // Starts the counter with a prescale of 1024
    }
    else{
        error_flag=0x80; // interval too big
    }
    return error_flag;
}

ISR(TIMER2_COMPA_vect){
    FS_values_t * drive;
    uint8_t buffer_flag, DR_input;
    drive=export_drive_values();
    
    time_g += INTERVAL;
    
    switch(play_state_g)
    {
        case data_idle_1:
        {
            DR_input=GPIO_read_pin(sta013_data_req);
            if(DR_input==0)
            {
                play_state_g=send_data_1;
            }
            break;
        }
        case send_data_1:
        {
            buffer_flag=0;
            DR_input=GPIO_read_pin(sta013_data_req);
            while((DR_input==0)&&(buffer_flag==0))
            {
                // Output_Set(PD,(BIT_EN)); //BIT_EN=1;
                // Maybe we need to use the spi_cs_inst_t sta013_biten object here?
                
                GPIO_output_ctor(sta013_biten, PD, /*Don't know which PIN Mask*/, GPIO_CLEAR /*Probably clear because it's for CS*/);
                GPIO_output_toggle_value(sta013_biten); // BIT_EN = 1
                
                SPI_transfer(SPI0,buffer1[index1_g]);
                //Output_Clear(PD,(BIT_EN)); //BIT_EN=0;
                GPIO_output_toggle_value(sta013_biten); // BIT_EN = 0
                
                index1_g++;
                if(index1_g>511) {
                    if(index2_g>511 {
                        if(num_sectors_g==(drive->SecPerClus)) {
                            play_state_g=/*locate_cluster_2*/ find_next_clus(num_sectors_g);
                        }
                        else {
                            play_state_g=load_buf_2;
                        }
                    }
                else // if index2_g==0
                {
                    play_state_g=send_data_2;
                }
                buffer_flag=1;
            } // end of if(index1_g>511)
                DR_input=GPIO_read_pin(sta013_data_req);
        } // end of while loop
        // Checks for empty buffer 2 when DATA_REQ goes inactive
            DR_input=GPIO_read_pin(sta013_data_req);
            if((DR_input==1)&&(play_state_g==send_data_1)) {
                if(index2_g>511) {
                    if(num_sectors_g==(drive->SecPerClus)) { // if num_sectors is at the limit reset
                        play_state_g=/*locate_cluster_2*/ find_next_clus(num_sectors_g);
                    }
                    else {
                        play_state_g=load_buf_2;
                    }
                }
                else {
                    play_state_g= data_idle_1;
                }
            }   
            break;
        }
    }
}