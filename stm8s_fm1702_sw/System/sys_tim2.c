#include "iostm8s103f3.h"
#include "sys_vector.h"
#include "sys_tim2.h"


void sys_tim2Init(void)
{
    TIM2_PSCR = 0x04;				//TIM2 prescaler is 16 ,TIM2 clock is 1MHz
    TIM2_ARRH = 1000 >> 8;			//TIM2 Handler 1ms
    TIM2_ARRL = (UINT8)1000;
    TIM2_EGR = 0x01;				//enable update
    TIM2_IER = 0x01;				//enable update interrupt
    TIM2_CR1 = 0x01;				//enable TIM2
}

#pragma vector = TIM2_UPD_OVF_BRK_IRQ
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{
    TIM2_SR1 &= ~0x01;
}