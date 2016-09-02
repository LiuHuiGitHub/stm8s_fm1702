#include "sys_iniHw.h"

BOOL b_sleepFlag = FALSE;
#define SLEEP_DELAY_TIME		5
static UINT8 u8_sleepDelay = 0;

#define SLEEP_WARKUP			0
#define SLEEP_SLEEP				1

void sys_sleepReruest(UINT8 cmd)
{
	if(cmd == SLEEP_WARKUP)
	{
		sys_clockChange(RUN_1MS);
	}
	else if(cmd == SLEEP_SLEEP)
	{
	}
}

BOOL sys_sleepGet(void)
{
	return FALSE;
}

void sys_sleep(void)
{
	sleep();
}

void sys_sleepCycle1s(void)
{
	if(sys_sleepGet())
	{
		if(u8_sleepDelay < SLEEP_DELAY_TIME)
		{
			u8_sleepDelay++;
		}
		else
		{
			sys_clockChange(SLEEP_10MS);
		}
	}
	else
	{
		u8_sleepDelay =  0;
	}
}

