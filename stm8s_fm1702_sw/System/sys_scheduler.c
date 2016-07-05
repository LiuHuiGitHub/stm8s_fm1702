#include "iostm8s105k6.h"
#include "sys_iniHw.h"
#include "sys_iniAppl.h"

#define RUN_MODE_CYCLE				10

int main(void)
{
    CLK_CKDIVR = 0x00;				/* cpu clock is HSI 16MHz */
    sys_iwdgInit();
	sys_iniHW();
	sys_iniAppl();
    enable_interrupt();
	while(1)
	{
		sys_iwdgReset();
		if(u8_taskCycleCount >= RUN_MODE_CYCLE)
		{
			u8_taskCycleCount -= RUN_MODE_CYCLE;
			sys_taskCycle10ms();
		}
		sys_sleep();
	}
}