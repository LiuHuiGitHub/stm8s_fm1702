/******************************************************************************

  Copyright (C), 2001-2011, DCN Co., Ltd.

 ******************************************************************************
  File Name     : hwa_eeprom.h
  Version       : Initial Draft
  Author        : Hui.Liu
  Created       : 2015/5/13
  Last Modified :
  Description   : hwa_eeprom.c header file
  Function List :
  History       :
  1.Date        : 2015/5/13
    Author      : Hui.Liu
    Modification: Created file

******************************************************************************/

#ifndef __HWA_EEPROM_H__
#define __HWA_EEPROM_H__

#include "typedef.h"

void hwa_eepromInit(void);
BOOL hwa_eepromReadSector(UINT8 *dat, UINT8 sector);
BOOL hwa_eepromWriteSector(UINT8 *dat, UINT8 sector);
void hwa_eepromEncrypt(UINT8 *dat, UINT16 size);
void hwa_eepromDecrypt(UINT8 *dat, UINT16 size);

#endif /* __HWA_EEPROM_H__ */
