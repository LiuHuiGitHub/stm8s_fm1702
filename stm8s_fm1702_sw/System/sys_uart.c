#include "iostm8s105k6.h"
#include "typedef.h"
#include "sys_vector.h"
#include "sys_uart.h"
#include "string.h"

#define BOOT_ADDR                			(0x8000ul+32*1024ul-4)
#define BOOT_LOAD_READY_CMD_LENGTH			10

typedef void (*pFunc)(void);
CONST UINT8 c_bootLoadReadyCmd[BOOT_LOAD_READY_CMD_LENGTH] = {0x12, 0x34, 0x56, 0x78, 0x90, 0x90, 0x78, 0x56, 0x34, 0x12};
static UINT8 u8_bootloadReadyCmdIndex = 0;

static UINT8 a_u8_rxBuff[RX_BUFF_LEN + 1];
static UINT8 u8_rxIndex = 0;
static UINT8 u8_rxOverCount = 0;

void sys_uartInit(void)
{
    CLK_PCKENR1 |= BIT3;		//enable uart2 clock

    UART2_CR1 = 0x00;
    UART2_CR2 = 0x00;
    UART2_CR3 = 0x00;
    UART2_CR4 = 0x00;
    //UART2_CR5 = 0x00;

    UART2_GTR = 0x00;
    UART2_PSCR = 0x00;

    (void)UART2_SR;
    (void)UART2_DR;

    UART2_BRR2 = ((UINT8)((UINT16)(SYS_CLOCK / BOUD) >> 8) & 0xF0) | ((UINT8)(SYS_CLOCK / BOUD) & 0x0F);
    UART2_BRR1 = (UINT8)((SYS_CLOCK / BOUD) >> 4); /*先给BRR2赋值 最后再设置BRR1*/

    UART2_CR2 = 0x2C;
}

void sys_uartSendByte(UINT8 data)
{
    /* Loop until the end of transmission */
    while (!(UART2_SR & BIT7));
    UART2_DR = data;
}

void sys_uartSendData(UINT8 *Data, UINT8 len)
{
    while(len--)
    {
        sys_uartSendByte(*Data++);
    }
}

#pragma vector = UART2_R_RXNE_vector
__interrupt void UART2_RX_IRQHandler(void)
{
    UINT8 data;
    if(UART2_SR & BIT3)
    {
        (void)UART2_DR;
    }
    if(UART2_SR & BIT5)
    {
        data = UART2_DR;
        a_u8_rxBuff[u8_rxIndex] = data;
        if(u8_rxIndex < RX_BUFF_LEN)
        {
            u8_rxIndex++;
        }
        u8_rxOverCount = BOUD_OVER_TIME;

        if(c_bootLoadReadyCmd[u8_bootloadReadyCmdIndex++] == data)
        {
            if(u8_bootloadReadyCmdIndex >= BOOT_LOAD_READY_CMD_LENGTH)
            {
                (*(pFunc)BOOT_ADDR)();
            }
        }
        else
        {
            u8_bootloadReadyCmdIndex = 0;
        }
    }
}

UINT8 sys_uartReadData(UINT8 *pData)
{
    UINT8 len;
    if(u8_rxOverCount)
    {
        u8_rxOverCount--;
        if(u8_rxOverCount == 0)
        {
            len = u8_rxIndex;
            memcpy(pData, a_u8_rxBuff, len);
            u8_rxIndex = 0;
            return len;
        }
    }
    return 0;
}
