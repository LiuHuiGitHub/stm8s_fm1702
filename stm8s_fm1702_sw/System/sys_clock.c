#include "iostm8s105k6.h"
#include "typedef.h"
#include "sys_iniHw.h"


UINT8 u8_taskCycleCount = 0;


void sys_clockInit(void)
{
    CLK_PCKENR1 |= BIT5;
    TIM2_PSCR = 0x07;				/* TIM2 prescaler is 128, TIM4 clock is 125KHz */
	sys_clockChange(RUN_1MS);
    TIM2_EGR = 0x01;				/* enable update */
    TIM2_IER = 0x01;				/* enable update interrupt */
    TIM2_CR1 = 0x01;				/* enable TIM2 */
}

void sys_clockChange(UINT16 clock)
{
    TIM2_ARRH = (UINT8)(clock >> 8);
    TIM2_ARRL = (UINT8)(clock);
}

#pragma vector = TIM2_OVR_UIF_vector
__interrupt void TIM2_UPD_OVF_IRQHandler(void)
{
    TIM2_SR1 &= ~BIT0;
	if(b_sleepFlag == FALSE)
	{
		u8_taskCycleCount++;
    	sys_taskHandler1ms();
	}
	else
	{
		u8_taskCycleCount += 10;
	}
}