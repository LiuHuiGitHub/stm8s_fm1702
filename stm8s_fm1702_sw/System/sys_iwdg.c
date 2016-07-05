#include "iostm8s105k6.h"
#include "typedef.h"
#include "sys_iwdg.h"


void sys_iwdgInit(void)
{
#ifndef DEBUG
    CLK_ICKR |= BIT3;			/*enable LSI*/
    while(!TEST_BIT(CLK_ICKR, BIT4));	/*wait LSI ready*/
    IWDG_KR = 0xCC;
    IWDG_KR = 0x55;				//
    IWDG_PR = 0x06;				//256
    IWDG_RLR = 250;				//250*256/128000 = 0.5s
    IWDG_KR = 0xAA;
#else
#warning "DEBUG MODE!"
#endif
}

void sys_iwdgReset(void)
{
#ifndef DEBUG
    IWDG_KR = 0xAA;
#endif
}
