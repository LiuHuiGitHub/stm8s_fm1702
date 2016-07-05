/******************************************************************************

  Copyright (C), 2001-2011, DCN Co., Ltd.

 ******************************************************************************
  File Name     : hwa_eeprom_cfg.h
  Version       : Initial Draft
  Author        : Hui.Liu
  Created       : 2015/5/13
  Last Modified :
  Description   : hwa_eeprom_cfg.c header file
  Function List :
  History       :
  1.Date        : 2015/5/13
    Author      : Hui.Liu
    Modification: Created file

******************************************************************************/

#ifndef __HWA_EEPROM_CFG_H__
#define __HWA_EEPROM_CFG_H__

#include "typedef.h"

typedef struct
{
    UINT16 UseSize;
    UINT8 Encrypt;
} EEPROM_CONFIG_STRUCT;

extern UINT8 e2_data[], e2_data_bak[];
extern const EEPROM_CONFIG_STRUCT c_s_eepromConfig[];
extern const UINT8 c_u8_eepromSectorNum;
extern const UINT16 c_u16_eepromSectorSize;
extern const UINT16 c_u16_eepromSectorAddr;
extern const UINT16 c_u16_eepromSectorBakAddr;

#endif /* __HWA_EEPROM_H__ */
