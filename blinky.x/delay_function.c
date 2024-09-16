/*
 * delay_function.c
 *
 * Created: 8/21/2020 10:10:20 PM
 *  Author: ryoun
 */


void Delay_Loop_ms(unsigned int num_ms)
{
	unsigned int delay;
	do
	{
		delay=4000;
		do
		{
            --delay;
		} while (0!=delay);
        --num_ms;
	} while (0!=num_ms);
}

