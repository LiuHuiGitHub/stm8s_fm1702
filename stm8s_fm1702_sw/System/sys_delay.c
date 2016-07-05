#include "sys_delay.h"

void sys_delayus(UINT8 xus)
{
	volatile UINT8 x = xus;
    while(x--)
    {
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
    }
}

void sys_delayms(UINT16 xms)
{
	volatile UINT16 x = xms;
    while(x--)
    {
		sys_delayus(250);
		sys_delayus(250);
		sys_delayus(250);
		sys_delayus(229);
    }
}
