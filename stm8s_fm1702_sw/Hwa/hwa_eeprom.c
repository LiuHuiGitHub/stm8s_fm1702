#include "hwa_eeprom.h"
#include "hwa_eeprom_cfg.h"
#include "sys_eeprom.h"
#include "string.h"

static UINT16 hwa_eepromCheck( UINT8 *dat, UINT16 len)
{
    UINT16 crc = 0xFFFF;
    UINT8 i;
    while(len--)
    {
        crc = crc ^ *dat++;
        for ( i = 0; i < 8; i++)
        {
            if( ( crc & 0x0001) > 0)
            {
                crc = crc >> 1;
                crc = crc ^ 0xa001;
            }
            else
            {
                crc = crc >> 1;
            }
        }
    }
    return ( crc );
}

void hwa_eepromInit(void)
{
    sys_eepromInit();
}

BOOL hwa_eepromReadSector(UINT8 *dat, UINT8 sector)
{
    BOOL e2_error = FALSE, e2_bak_error = FALSE;
    UINT16 e2_addr, e2_bak_addr;
    UINT16 e2_check_sum, e2_bak_check_sum;
    UINT16 Size, SectorSize;

    if(sector >= c_u8_eepromSectorNum)
    {
        return FALSE;
    }
    Size = c_s_eepromConfig[sector].UseSize;
    SectorSize = Size + 2;

    e2_addr = c_u16_eepromSectorAddr + c_u16_eepromSectorSize * sector;
    e2_bak_addr = c_u16_eepromSectorBakAddr + c_u16_eepromSectorSize * sector;

    sys_eepromRead(e2_addr, e2_data, SectorSize);
    if (c_s_eepromConfig[sector].Encrypt)
    {
        hwa_eepromDecrypt(e2_data, Size);
    }
    e2_check_sum = e2_data[Size] << 8 | e2_data[Size + 1];

    sys_eepromRead(e2_bak_addr, e2_data_bak, SectorSize);
    if (c_s_eepromConfig[sector].Encrypt)
    {
        hwa_eepromDecrypt(e2_data_bak, Size);
    }
    e2_bak_check_sum = e2_data_bak[Size] << 8 | e2_data_bak[Size + 1];

    if(e2_check_sum != hwa_eepromCheck(e2_data, Size))
    {
        e2_error = TRUE;
    }
    if(e2_bak_check_sum != hwa_eepromCheck(e2_data_bak, Size))
    {
        e2_bak_error = TRUE;
    }

    if(e2_error && e2_bak_error)    //~1~备份块和正常块都校验错误，返回错误
    {
        return FALSE;
    }
    else if(e2_error)                                 //~2~备份块校验错误，恢复正常块
    {
        memcpy(e2_data, e2_data_bak, SectorSize);
        sys_eepromEraseSector(e2_addr);
        sys_eepromWrite(e2_addr, e2_data, SectorSize);
    }
    else if(e2_bak_error ||                          //~3~正常块校验错误，恢复备份块
            (e2_error == FALSE                                //~4~正常块、备份块都检验正确，但数据不同，则以
             && e2_bak_error == FALSE                         //   最新写入的正常块覆盖备份块
             && e2_check_sum != e2_bak_check_sum)
           )
    {
        memcpy(e2_data_bak, e2_data, SectorSize);
        sys_eepromEraseSector(e2_bak_addr);
        sys_eepromWrite(e2_bak_addr, e2_data_bak, SectorSize);
    }
    memcpy(dat, e2_data, Size);
    return TRUE;
}

BOOL hwa_eepromWriteSector(UINT8 *dat, UINT8 sector)
{
    UINT16 e2_addr, e2_bak_addr;
    UINT16 e2_check_sum;

    UINT16 Size, SectorSize;

    if(sector >= c_u8_eepromSectorNum)
    {
        return FALSE;
    }
    Size = c_s_eepromConfig[sector].UseSize;
    SectorSize = Size + 2;

    e2_addr = c_u16_eepromSectorAddr + c_u16_eepromSectorSize * sector;
    e2_bak_addr = c_u16_eepromSectorBakAddr + c_u16_eepromSectorSize * sector;
    e2_check_sum = hwa_eepromCheck(dat, Size);

    hwa_eepromReadSector(e2_data, sector);                                  //  写入之前，如果有错误块，先恢复

    memcpy(e2_data, dat, Size);

    if (c_s_eepromConfig[sector].Encrypt)
    {
        hwa_eepromEncrypt(e2_data, Size);
    }
    e2_data[Size] = (UINT8)(e2_check_sum >> 8);
    e2_data[Size + 1] = (UINT8)(e2_check_sum & 0xFF);
    sys_eepromEraseSector(e2_addr);
    sys_eepromWrite(e2_addr, e2_data, SectorSize);

    //    memcpy(e2_data_bak, e2_data, SectorSize);
    sys_eepromEraseSector(e2_bak_addr);
    sys_eepromWrite(e2_bak_addr, e2_data, SectorSize);
    return TRUE;
}
