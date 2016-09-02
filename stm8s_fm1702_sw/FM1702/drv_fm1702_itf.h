#ifndef __DRV_FM1702_ITF_H__
#define __DRV_FM1702_ITF_H__


#include "typedef.h"

void drv_fm1702ItfGpioInit(void);
void drv_fm1702ItfClearReset(void);
void drv_fm1702ItfSetReset(void);
void drv_fm1702ItfClearCs(void);
void drv_fm1702ItfSetCs(void);
UINT8 drv_fm1702ItfReadByte(UINT8 addr);
void drv_fm1702ItfWriteByte(UINT8 addr, UINT8 byte);
void drv_fm1702ItfWrite(UINT8 addr, UINT8* dat, UINT8 len);
void drv_fm1702ItfRead(UINT8 addr, UINT8* dat, UINT8 len);

#endif
