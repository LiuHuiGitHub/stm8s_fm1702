#ifndef __DRIVE_LCD_H__
#define __DRIVE_LCD_H__


#include "typedef.h"

void drv_lcdInit(void);
void drv_lcdReset(void);
void drv_lcdDrawPicture(const UINT8 *ptr);
void drv_lcdClearPicBuff(void);
void Ldrv_lcdDisPlayPicBuff(void);
void drv_lcdDrawFillColor(UINT8 color);
UINT8 drv_lcdReadPoint(UINT8 x, UINT8 y);
void drv_lcdDrawPoint(UINT8 x, UINT8 y, UINT8 color);

#endif
