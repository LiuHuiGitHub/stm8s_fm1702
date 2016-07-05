#ifndef __DRIVE_LED_H__
#define __DRIVE_LED_H__

#include "typedef.h"

extern UINT8 u8_ledDisBuff[2];
extern UINT8 u8_ledDot;
extern BOOL b_keyStart;
extern BOOL b_keyTimeSet;
extern BOOL b_keyTempSet;

void drv_ledInit(void);
void drv_ledHandler1ms(void);
void drv_ledRequest(UINT8 count, UINT8 n);
UINT8 drv_ledGetRequest(void);

#endif
