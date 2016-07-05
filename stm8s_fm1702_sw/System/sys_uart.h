#ifndef __SYS_UART_H__
#define __SYS_UART_H__

#include "typedef.h"

#define BOUD_OVER_TIME		(10)		//100ms
#define RX_BUFF_LEN         (40)

void sys_uartInit(void);
void sys_uartSendByte(UINT8 data);
void sys_uartSendData(UINT8 *Data, UINT8 len);
UINT8 sys_uartReadData(UINT8 *pData);

#endif
