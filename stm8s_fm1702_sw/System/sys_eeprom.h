#ifndef __SYS_EEPROM_H__
#define __SYS_EEPROM_H__

#include "typedef.h"

void sys_eepromInit(void);
void sys_eepromRead(UINT16 addr, UINT8 *dat, UINT16 len);
void sys_eepromWrite(UINT16 addr, UINT8 *dat, UINT16 len);
void sys_eepromEraseSector(UINT16 addr);

#endif
