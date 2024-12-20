
#include "Read_Values.h"
#include "peripherals.h"

//******************************* (Question 4) ******************************

uint8_t read_value_8(uint16_t offset, uint8_t array[])
{
    uint8_t temp;
    temp=*(array+offset);
    return temp;
}


uint16_t read_value_16(uint16_t offset, uint8_t array[])
{   
    uint16_t return_val;
    uint8_t temp, i=0;
    return_val = 0;
    for (i=0;i<2;i++) {
        temp=*(array+offset+(1-i));
        return_val=return_val<<8;
        return_val|=temp;
    }
    return return_val;
}

uint32_t read_value_32(uint16_t offset, uint8_t array[]) // Little Endian
{   
    uint32_t return_val;
    uint8_t temp, i=0;
    return_val = 0;
    for (i=0;i<4;i++) {
        temp=*(array+offset+(3-i));
        return_val=return_val<<8;
        return_val|=temp;
    }
    return return_val;
}
