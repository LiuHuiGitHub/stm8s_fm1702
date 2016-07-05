#ifndef __HWA_FM1702_H__
#define __HWA_FM1702_H__

#include "typedef.h"
#include "drv_fm1702.h"

typedef struct
{
    UINT16 money;
    UINT8 crc[2];
    UINT8 Reserved[12];
} MIFATE_STRUCT;

extern MIFATE_STRUCT const *pMoney;

void hwa_fm1702Init(void);
void drv_fm1702PowerDownMode(void);
BOOL hwa_fm1702ReadBlock(UINT8 *buff, UINT8 block);
BOOL hwa_fm1702WriteBlock(UINT8 *buff, UINT8 block);
BOOL hwa_fm1702ReadSector(UINT8 *dat, UINT8 sector);
BOOL hwa_fm1702WriteSector(UINT8 *dat, UINT8 sector);

#endif

