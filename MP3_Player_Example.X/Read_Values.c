
#include "Read_Values.h"
#include "peripherals.h"
uint8_t read_value_8(uint16_t offset, uint8_t array[])
{
    return array[offset];
}


uint16_t read_value_16(uint16_t offset, uint8_t array[])
{
    uint16_t temp16;
    temp16=(array[offset+1]<<8)|array[offset];
    return temp16;
}
uint32_t read_value_32(uint16_t offset, uint8_t array[])
{
    uint32_t temp32;
    temp32=0;
    for(uint8_t i=0; i<4; i++)
    {
        temp32=temp32<<8;
        temp32|=array[offset+(3-i)];
    }
    return temp32;
}
