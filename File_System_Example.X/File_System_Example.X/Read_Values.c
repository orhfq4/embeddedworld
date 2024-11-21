
#include "Read_Values.h"
#include "peripherals.h"

//******************************* (Question 4) ******************************

uint8_t read_value_8(uint16_t offset, uint8_t array[])
{
    return array[offset];
}


uint16_t read_value_16(uint16_t offset, uint8_t array[])
{
    uint16_t temp16 = 0;
    temp16 = array[offset]; // LSB
    temp16 |= ((uint16_t)array[offset + 1] << 8); // MSB
    return temp16; 
}

uint32_t read_value_32(uint16_t offset, uint8_t array[]) // Little Endian
{
    uint32_t temp32 = 0;
    temp32 = array[offset];           // Byte 0 (LSB)
    temp32 |= ((uint32_t)array[offset + 1] << 8);  // Byte 1
    temp32 |= ((uint32_t)array[offset + 2] << 16); // Byte 2
    temp32 |= ((uint32_t)array[offset + 3] << 24); // Byte 3 (MSB)
    return temp32;
}
