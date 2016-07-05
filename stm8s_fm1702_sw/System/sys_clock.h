#ifndef __SYS_CLOCK_H__
#define __SYS_CLOCK_H__


#include "typedef.h"


#define RUN_1MS				(125-1)
#define RUN_10MS			(1250-1)
#define SLEEP_10MS			(1250-1)
#define SLEEP_100MS			(12500-1)


extern UINT8 u8_taskCycleCount;

void sys_clockInit(void);
void sys_clockChange(UINT16 clock);

#endif
