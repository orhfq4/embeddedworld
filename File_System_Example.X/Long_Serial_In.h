#ifndef _Long_Serial_In_H
#define _Long_Serial_In_H

// ASCII characters
#define space (0x20)
#define CR (0x0D)
#define LF (0x0A)
#define BS (0x08)
#define DEL (0x7F)

// ------ Public function prototypes -------------------------------

/***********************************************************************
DESC:    Waits for user input of a long integer as ASCII characters
INPUT:   volatile UART_t * UART_addr - Pointer to the UART instance
RETURNS: unsigned long - The entered long integer
CAUTION: UART must be initialized first
************************************************************************/

uint32_t long_serial_input(volatile UART_t * UART_addr);

#endif