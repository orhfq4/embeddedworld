/* 
 * File:   UART.h
 * Author: owenhancock
 *
 * Created on September 30, 2024, 10:31 AM
 */

// Need to complete for question 2

#include "peripherals.h"
#include "board.h"

#ifndef UART_H
#define	UART_H

/**************************************************************
*   UART_Init
*   Inputs: UART object from the UART struct,
            a 32-bit number for the baud rate
*   Output: None
**************************************************************
*   Function: Initiatlizes the UART.
*
*   Caution: 
***************************************************************/
void UART_Init(volatile UART_t * UART_addr, uint32_t baud_rate);
// can be called using UART_Init(UART1, 9600);

/**************************************************************
*   UART_Transmit
*   Inputs: UART object from the UART struct,
            an 8-bit value to send to the UART and transmit out
*   Output: Outpus the send value to the UDR.
**************************************************************
*   Function: Transmits a value to the UART's UDR
*
*   Caution: 
***************************************************************/
uint8_t UART_Transmit(volatile UART_t *UART_addr, uint8_t send_value);

/**************************************************************
*   LED_ctor
*   Inputs: UART object from the UART struct
*   Output: The value received from the UDR
**************************************************************
*   Function: Reads a value from the UART's UDR.
*
*   Caution: 
***************************************************************/
uint8_t UART_Receive(volatile UART_t *UART_addr);

#endif	/* UART_H */

