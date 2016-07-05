#include "iostm8s105k6.h"
#include "sys_pwm.h"

static void TIM1_Init(void)
{
    CLK_PCKENR1 |= 0x80;	//开启TIM1时钟
    TIM1_EGR = 0x01;		//重新初始化TIM1
    TIM1_EGR |= 0x20;

    TIM1_ARRH = 0x00;		//自动重装初值
    TIM1_ARRL = 100;

    TIM1_PSCRH = 0;			//TIM1输入时钟分频
    TIM1_PSCRL = 3;			//约20.8KHz
    /*
    TIM_CR1：
    	7：	ARPE：自动预装载允许位
    	6~5：CMS：
    		00：边沿对齐模式
    		01：中央对齐模式1
    		10：中央对齐模式2
    		11：中央对齐模式3
    	4：DIR：方向
    	3：OPM：单脉冲模式
    	2：URS：更新请求源
    	1：UDIS：禁止更新
    	0：CEN：允许计数器
    */
    TIM1_CR1 = 0x00;		//边沿对齐，向上计数
}

static void PWM1_Init(void)
{
    /*
    TIM1_CCER1：
    	7：CC2NP：输入捕获/比较2互补输出极性
    	6：CC2NE：输入捕获/比较2互补输出使能
    	5：CC2P：输入捕获/比较2输出极性
    	4：CC2E：输入捕获/比较2输出使能
    	3：CC1NP：输入捕获/比较1互补输出极性
    	2：CC1NE：输入捕获/比较1互补输出使能
    	1：CC1P：输入捕获/比较1输出极性
    	0：CC1E：输入捕获/比较1输出使能，0：OC1高电平有效
    TIM1_CCER2~3：与TIM1_CCER1类同
    */
    TIM1_CCER1 = 0x05;				//PWM1、PWM2输出使能
    TIM1_CCER2 = 0x00;
    /*
    TIM1_CCMR1：
    	7：	OC1CE：输出比较1清零使能
    	6~4：0C1M[2:0]：输出比较1模式
    		000：冻结
    		001：匹配时设置通道1的输出为有效电平
    		010：匹配时设置通道1的输出为无效电平
    		011：翻转
    		100：强制为无效电平
    		101：强制为有效电平
    		110：PWM模式1 - 上计数时，TIM1_CNT<TIM1_CCR1时通道1为有效电平；下计数时，则为无效电平
    		111：PWM模式2 - 与模式1相反
    	3：OC1PE： 输出比较1预装载使能
    	2：OC1FE： 输出比较1快速使能
    	1~0：CC1S[1:0]：捕获/比较1选择
    		00： CC1通道被配置为输出
    		01： CC1通道被配置为输入，IC1映射在TI1FP1上
    		10： CC1通道被配置为输入，IC1映射在TI2FP1上
    		11： CC1通道被配置为输入，IC1映射在TRC上
    TIM1_CCMR2~3与TIM1_CCMR1类同
    */
    TIM1_CCMR1 = 0x60;		//PWM模式2，通道1
    TIM1_CCMR2 = 0x60;		//PWM模式2，通道2

    TIM1_CCR1H = 0x00;		//通道1占空比
    TIM1_CCR1L = 0xFF / 2;

    //	TIM1_CCR2H = 0x00;		//通道2占空比
    //	TIM1_CCR2L = 0xFF/2;

    TIM1_EGR = 0x01;		//重新初始化TIM1

    TIM1_CR1 |= 0x01;		//使能计数器
    TIM1_DTR = 0x30;		//设置死区时间
    /*
    TIM1_BKR：
    	7：MOE: 主输出使能
    	6：AOE: 自动输出使能
    	5：BKP: 刹车输入极性 0：刹车输入低电平有效
    	4：BKE: 刹车功能使能
    	3：OSSR: 运行模式下“关闭状态”选择
    	2：OSSI: 空闲模式下“关闭状态”选择
    	1~0：LOOK[1:0]: 锁定设置
    		00：锁定关闭，寄存器无写保护
    		01 ：锁定级别1，不能写入TIM1_BKR寄存器的BKE、BKP、AOE位和TIM1_OISR寄存器的OISI位
    		10：锁定级别2，不能写入锁定级别1中的各位，也不能写入CC极性位
    		11：锁定级别3，不能写入锁定级别2中的各位，也不能写入CC控制位
    */
    TIM1_BKR = 0x80;		//输出使能
}

static void TIM2_Init(void)
{
    CLK_PCKENR1 |= 0x20;	//开启TIM2时钟

    TIM2_ARRH = 0x00;		//自动重装初值
    TIM2_ARRL = 0xFF;

    TIM2_PSCR = 0x03;		//设置预分频
    /*
    TIM_CR1：
    7：	ARPE：自动预装载允许位
    6~5：CMS：
    	00：边沿对齐模式
    	01：中央对齐模式1
    	10：中央对齐模式2
    	11：中央对齐模式3
    4：DIR：方向
    3：OPM：单脉冲模式
    2：URS：更新请求源
    1：UDIS：禁止更新
    0：CEN：允许计数器
    */
    TIM2_CR1 = 0x00;		//边沿对齐，向上计数
}

static void PWM2_Init(void)
{
    /*
    TIM2_CCER1：
    	5：CC2P：输入捕获/比较2输出极性
    	4：CC2E：输入捕获/比较2输出使能
    	1：CC1P：输入捕获/比较1输出极性，0：OC1高电平有效
    	0：CC1E：输入捕获/比较1输出使能
    */
    TIM2_CCER1 = 0x00;
    /*
    TIM2_CCER2：
    	1：CC3P：输入捕获/比较3输出极性，0：OC1高电平有效
    	0：CC3E：输入捕获/比较3输出使能
    */
    TIM2_CCER2 = 0x03;
    /*
    TIM1_CCMR1：
    	7：	OC1CE：输出比较1清零使能
    	6~4：0C1M[2:0]：输出比较1模式
    		000：冻结
    		001：匹配时设置通道1的输出为有效电平
    		010：匹配时设置通道1的输出为无效电平
    		011：翻转
    		100：强制为无效电平
    		101：强制为有效电平
    		110：PWM模式1 - 上计数时，TIM1_CNT<TIM1_CCR1时通道1为有效电平；下计数时，则为无效电平
    		111：PWM模式2 - 与模式1相反
    	3：OC1PE： 输出比较1预装载使能
    	2：OC1FE： 输出比较1快速使能
    	1~0：CC1S[1:0]：捕获/比较1选择
    		00： CC1通道被配置为输出
    		01： CC1通道被配置为输入，IC1映射在TI1FP1上
    		10： CC1通道被配置为输入，IC1映射在TI2FP1上
    		11： CC1通道被配置为输入，IC1映射在TRC上
    TIM1_CCMR2~3与TIM1_CCMR1类同
    */
    TIM2_CCMR1 = 0x00;
    TIM2_CCMR2 = 0x00;
    TIM2_CCMR3 = 0x70;		//PWM模式2，通道3

    TIM2_CCR1H = 0x00;		//通道3占空比
    TIM2_CCR1L = 0x00;
    TIM2_CCR2H = 0x00;		//通道3占空比
    TIM2_CCR2L = 0x00;
    TIM2_CCR3H = 0x00;		//通道3占空比
    TIM2_CCR3L = 0x00;

    TIM2_IER = 0x00;

    TIM2_CR1 |= 0x01;		//使能计数器
}


static void TIM3_Init(void)
{
    CLK_PCKENR1 |= 0x40;	//开启TIM3时钟

    TIM3_ARRH = 0x00;		//自动重装初值
    TIM3_ARRL = 100;

    TIM3_PSCR = 0x07;		//设置预分频
    /*
    TIM_CR1：
    7：	ARPE：自动预装载允许位
    6~5：CMS：
    	00：边沿对齐模式
    	01：中央对齐模式1
    	10：中央对齐模式2
    	11：中央对齐模式3
    4：DIR：方向
    3：OPM：单脉冲模式
    2：URS：更新请求源
    1：UDIS：禁止更新
    0：CEN：允许计数器
    */
    TIM3_CR1 = 0x00;		//边沿对齐，向上计数
}

static void PWM3_Init(void)
{
    /*
    TIM3_CCER1：
    	5：CC2P：输入捕获/比较2输出极性
    	4：CC2E：输入捕获/比较2输出使能
    	1：CC1P：输入捕获/比较1输出极性，0：OC1高电平有效
    	0：CC1E：输入捕获/比较1输出使能
    */
    TIM3_CCER1 = 0x10;
    /*
    TIM3_CCMR1：
    	7：	OC1CE：输出比较1清零使能
    	6~4：0C1M[2:0]：输出比较1模式
    		000：冻结
    		001：匹配时设置通道1的输出为有效电平
    		010：匹配时设置通道1的输出为无效电平
    		011：翻转
    		100：强制为无效电平
    		101：强制为有效电平
    		110：PWM模式1 - 上计数时，TIM1_CNT<TIM1_CCR1时通道1为有效电平；下计数时，则为无效电平
    		111：PWM模式2 - 与模式1相反
    	3：OC1PE： 输出比较1预装载使能
    	2：OC1FE： 输出比较1快速使能
    	1~0：CC1S[1:0]：捕获/比较1选择
    		00： CC1通道被配置为输出
    		01： CC1通道被配置为输入，IC1映射在TI1FP1上
    		10： CC1通道被配置为输入，IC1映射在TI2FP1上
    		11： CC1通道被配置为输入，IC1映射在TRC上
    */
    TIM3_CCMR1 = 0x00;
    TIM3_CCMR2 = 0x00;

    TIM3_CCR1H = 0x00;		//通道1占空比
    TIM3_CCR1L = 0x00;
    TIM3_CCR2H = 0x00;		//通道2占空比
    TIM3_CCR2L = 0x00;

    TIM3_IER = 0x00;

    TIM3_CR1 |= 0x01;		//使能计数器
}

void sys_pwmInit(void)
{
    //    TIM1_Init();
    //    PWM1_Init();
    //	TIM1_RCR = 0x00;
    TIM3_Init();
    PWM3_Init();
}

void sys_pwmSet(UINT8 pwm)
{
    if(pwm == 0 )
    {
        TIM3_CCMR2 = 0x40;	//输出无效电平
    }
    else if(pwm == 0xFF)
    {
        TIM3_CCMR2 = 0x50;	//输出有效电平
    }
    else
    {
        TIM3_CCMR2 = 0x60;
        TIM3_CCR2H = 0x00;
        TIM3_CCR2L = pwm;
    }
}

void sys_pwm2Channel3Set(UINT8 pwm)
{
    if(pwm == 0 )
    {
        TIM2_CCMR3 = 0x40;	//输出无效电平
    }
    else if(pwm == 0xFF)
    {
        TIM2_CCMR3 = 0x50;	//输出有效电平
    }
    else
    {
        TIM2_CCMR3 = 0x60;
        TIM2_CCR3H = 0x00;
        TIM2_CCR3L = pwm;
    }
}
