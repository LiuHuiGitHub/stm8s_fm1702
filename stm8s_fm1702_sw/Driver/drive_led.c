#include "iostm8s103f3.h"
#include "drive_led.h"
#include "drive_led_Cfg.h"

#define LED_CS0 PC_ODR_ODR3
#define LED_CS1 PD_ODR_ODR4


/*Seg Port*/
//#define SEG_PORT        (PD_ODR<<1|PC_ODR>>6)


//与显示相关变量
CONST UINT8 ledCoding[] =
{
    (UINT8)(~SEG_0), (UINT8)(~SEG_1), (UINT8)(~SEG_2), (UINT8)(~SEG_3), (UINT8)(~SEG_4),
    (UINT8)(~SEG_5), (UINT8)(~SEG_6), (UINT8)(~SEG_7), (UINT8)(~SEG_8), (UINT8)(~SEG_9),
    (UINT8)(~SEG_A), (UINT8)(~SEG_B), (UINT8)(~SEG_C), (UINT8)(~SEG_D), (UINT8)(~SEG_E),
    (UINT8)(~SEG_F), (UINT8)(~SEG_LINE), (UINT8)(~SEG_P), (UINT8)(~SEG_U), (UINT8)(~SEG_NULL),
    (UINT8)(~SEG_H),
};

UINT16 u16_ledRequestCounter = 0;
UINT8 u8_ledRequestCount = 0;
UINT8 u8_ledRequestData[2] = {0};

UINT8 u8_ledDisBuff[2] = {8, 8};
UINT8 u8_ledDot = 0x00;
static UINT8 u8_ledIndex = 0;//从左到右为0,1,2

BOOL b_keyStart = FALSE;
BOOL b_keyTimeSet = FALSE;
BOOL b_keyTempSet = FALSE;

void drv_ledInit(void)
{
    LED_CS0 = SEG_OFF;
    LED_CS1 = SEG_OFF;
}

/* LED动态显示 */
void drv_ledHandler1ms(void)
{
    UINT8 coding = ledCoding[19];
    LED_CS0 = SEG_OFF;
    LED_CS1 = SEG_OFF;
    u8_ledIndex++;
    u8_ledIndex %= 20;

    if (u8_ledIndex == 0 || u8_ledIndex == 4 || u8_ledIndex == 6 || u8_ledIndex == 8 || u8_ledIndex == 10 || u8_ledIndex == 12 || u8_ledIndex == 14 || u8_ledIndex == 16 || u8_ledIndex == 18)
    {
        if(u8_ledRequestCount == 0)
        {
            coding = ledCoding[u8_ledDisBuff[0]];
        }
        else
        {
            if(u16_ledRequestCounter < 280)
            {
                coding = ledCoding[u8_ledRequestData[0]];
            }
            else if(u16_ledRequestCounter < 500)
            {
                coding = ledCoding[19];
            }
        }
        PC_ODR_ODR4 = coding >> 6;
        PC_ODR_ODR5 = coding >> 5;
        PD_ODR_ODR6 = coding >> 4;
        PA_ODR_ODR1 = coding >> 3;
        PD_ODR_ODR5 = coding >> 2;
        PC_ODR_ODR7 = coding >> 1;
        PC_ODR_ODR6 = coding >> 0;
        if(u8_ledIndex == 0)
        {
            PC_ODR_ODR4 = 1;
            PC_ODR_ODR5 = 1;
            PD_ODR_ODR6 = 1;
            PA_ODR_ODR1 = coding >> 3;
            PD_ODR_ODR5 = 1;
            PC_ODR_ODR7 = 1;
            PC_ODR_ODR6 = 1;
        }
        LED_CS0 = SEG_ON;
    }
    else if(u8_ledIndex == 1 || u8_ledIndex == 5 || u8_ledIndex == 7 || u8_ledIndex == 9 || u8_ledIndex == 11 || u8_ledIndex == 13 || u8_ledIndex == 15 || u8_ledIndex == 17 || u8_ledIndex == 19)
    {
        if(u8_ledRequestCount == 0)
        {
            u16_ledRequestCounter = 0;
            coding = ledCoding[u8_ledDisBuff[1]];
        }
        else
        {
            u16_ledRequestCounter++;
            if(u16_ledRequestCounter < 280)
            {
                coding = ledCoding[u8_ledRequestData[1]];
            }
            else if(u16_ledRequestCounter < 500)
            {
                coding = ledCoding[19];
            }
            else
            {
                u16_ledRequestCounter = 0;
                if(u8_ledRequestCount != 0xFF)
                {
                    u8_ledRequestCount--;
                }
            }
        }
        PC_ODR_ODR4 = coding >> 6;
        PC_ODR_ODR5 = coding >> 5;
        PD_ODR_ODR6 = coding >> 4;
        PA_ODR_ODR1 = coding >> 3;
        PD_ODR_ODR5 = coding >> 2;
        PC_ODR_ODR7 = coding >> 1;
        PC_ODR_ODR6 = coding >> 0;
        if(u8_ledIndex == 1)
        {
            PC_ODR_ODR4 = 1;
            PC_ODR_ODR5 = 1;
            PD_ODR_ODR6 = 1;
            PA_ODR_ODR1 = coding >> 3;
            PD_ODR_ODR5 = 1;
            PC_ODR_ODR7 = 1;
            PC_ODR_ODR6 = 1;
        }
        LED_CS1 = SEG_ON;
    }
    else if (u8_ledIndex == 2)
    {
        PC_ODR_ODR4 = 1;//g
        PC_ODR_ODR5 = 1;//h
        PD_ODR_ODR6 = 1;//e
        PA_ODR_ODR1 = 1;//d
        PD_ODR_ODR5 = 1;//c
        PC_ODR_ODR7 = 1;//b
        PC_ODR_ODR6 = 1;//a

        PC_DDR_DDR6 = 0;
        PC_CR1_C16 = 1;
        PC_CR2_C26 = 0;

        PC_DDR_DDR4 = 0;
        PC_CR1_C14 = 1;
        PC_CR2_C24 = 0;

        PC_DDR_DDR7 = 0;
        PC_CR1_C17 = 1;
        PC_CR2_C27 = 0;
    }
    else if (u8_ledIndex == 3)
    {
        if(PC_IDR_IDR7 == 0)
        {
            b_keyStart = TRUE;
        }
        else
        {
            b_keyStart = FALSE;
        }
        if(PC_IDR_IDR6 == 0)
        {
            b_keyTempSet = TRUE;
        }
        else
        {
            b_keyTempSet = FALSE;
        }
        if(PC_IDR_IDR4 == 0)
        {
            b_keyTimeSet = TRUE;
        }
        else
        {
            b_keyTimeSet = FALSE;
        }

        PC_DDR_DDR6 = 1;
        PC_CR1_C16 = 1;
        PC_CR2_C26 = 0;

        PC_DDR_DDR4 = 1;
        PC_CR1_C14 = 1;
        PC_CR2_C24 = 0;

        PC_DDR_DDR7 = 1;
        PC_CR1_C17 = 1;
        PC_CR2_C27 = 0;
    }
}

void drv_ledRequest(UINT8 count, UINT8 n)
{
    u8_ledRequestCount = count;
    if(count != 0xFF)
    {
        u16_ledRequestCounter = 0;
    }
    if(n == 0xE1)
    {
        u8_ledRequestData[0] = 14;
        u8_ledRequestData[1] = 1;
    }
    else if(n == 0xE2)
    {
        u8_ledRequestData[0] = 14;
        u8_ledRequestData[1] = 2;
    }
    else if(n == 0xE3)
    {
        u8_ledRequestData[0] = 20;
        u8_ledRequestData[1] = 20;
    }
    else
    {
        u8_ledRequestData[0] = n / 10;
        u8_ledRequestData[1] = n % 10;
    }
}

UINT8 drv_ledGetRequest(void)
{
    return u8_ledRequestCount;
}

