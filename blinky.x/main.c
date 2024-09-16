/*
 * Hello_Embedded_World.c
 *
 * Created: 8/21/2020 5:26:08 PM
 * Author : ryoun
 */ 

#include <avr/io.h>
#include "delay_function.h"

#define LED_bit (7)
unsigned char g_LED_State;

void LED_Flash_Init(void);
void LED_Flash_Change_State(void);



int main(void)
{
	LED_Flash_Init();
    while (1) 
    {
		LED_Flash_Change_State();
		Delay_Loop_ms(1000);
    }
}

void LED_Flash_Init(void)
{
	DDRC |=(1<<LED_bit);
	PORTC &=~(1<<LED_bit);
	g_LED_State=0;
}

void LED_Flash_Change_State(void)
{
	if(g_LED_State==0)
	{
		PORTC |=1<<LED_bit;
		g_LED_State=1;
	}
	else
	{
		PORTC &=~1<<LED_bit;
		g_LED_State=0;
	}
}




