#include "hwa_fm1702.h"
#include "drv_fm1702.h"
#include "string.h"


BOOL NormalErrorFlag = FALSE;
BOOL BackupErrorFlag = FALSE;

static MIFATE_STRUCT s_NormalBuff, s_BackupBuff, s_TempBuff;

#define NORMAL_DATA_BLOCK           1
#define BACKUP_DATA_BLOCK           2
#define DATA_BLOCK_SIZE             16
#define USE_DATA_BLOCK_LEN          2

#if USE_DATA_BLOCK_LEN > 14
#error Mifare Max Use Len is 14 Byte!
#endif

void hwa_fm1702Init(void)
{
    while (sizeof(MIFATE_STRUCT) != 16);
    while(!drv_fm1702Init());
}

/*加密和解密必须对称*/
void hwa_fm1702Encrypt(UINT8 *pData)        //利用卡ID加密
{
    /*
    UINT8 i, j;
    for (i = 0; i<USE_DATA_BLOCK_LEN + 2; i++)
    {
    	for (j = 4; j>0; j--)
    	{
    		pData[i] ^= gCard_UID[i % 5];
    		pData[i] = _cror_(pData[i], 1);
    	}
    }
    */
}

/*加密和解密必须对称*/
void hwa_fm1702Decrypt(UINT8 *pData)        //利用卡ID解密
{
    /*
    UINT8 i, j;
    for (i = 0; i<USE_DATA_BLOCK_LEN + 2; i++)
    {
    	for (j = 4; j>0; j--)
    	{
    		pData[i] = _crol_(pData[i], 1);
    		pData[i] ^= gCard_UID[i % 5];
    	}
    }*/
}

BOOL hwa_fm1702ReadBlock(UINT8 *buff, UINT8 block)
{
    UINT8 u8_ReadErrCount;
    UINT8 u8_Result;
    for (u8_ReadErrCount = 0; u8_ReadErrCount < 3; u8_ReadErrCount++)
    {
        u8_Result = drv_fm1702ReadBlock(buff, block);
        if (u8_Result == FM1702_OK)
        {
            return TRUE;
        }
        else if (u8_Result == FM1702_NOTAGERR)
        {
            return FALSE;
        }
    }
    return FALSE;
}

BOOL hwa_fm1702WriteBlock(UINT8 *buff, UINT8 block)
{
    UINT8 u8_ReadErrCount;
    UINT8 u8_Result;
    memcpy((UINT8 *)&s_TempBuff, buff, 16);
    hwa_fm1702Encrypt((UINT8 *)&s_TempBuff);            //利用卡ID加密
    for (u8_ReadErrCount = 0; u8_ReadErrCount < 3; u8_ReadErrCount++)
    {
        u8_Result = drv_fm1702WriteBlock((UINT8 *)&s_TempBuff, block);
        if (u8_Result == FM1702_OK)
        {
            return TRUE;
        }
        else if (u8_Result == FM1702_NOTAGERR)
        {
            return FALSE;
        }
    }
    return FALSE;
}

UINT16 hwa_fm1702CheckOut(UINT8 *dat, UINT16 len)
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

void hwa_fm1702CheckBlock(void)
{
    UINT16 crc, crcBak;
    hwa_fm1702Decrypt((UINT8 *)&s_NormalBuff);       //利用卡ID解密
    crc = hwa_fm1702CheckOut((UINT8 *)&s_NormalBuff, USE_DATA_BLOCK_LEN);
    if (crc == (s_NormalBuff.crc[0] << 8 | s_NormalBuff.crc[1]))
    {
        NormalErrorFlag = FALSE;
    }
    else
    {
        NormalErrorFlag = TRUE;
    }
    hwa_fm1702Decrypt((UINT8 *)&s_BackupBuff);       //利用卡ID解密
    crcBak = hwa_fm1702CheckOut((UINT8 *)&s_BackupBuff, USE_DATA_BLOCK_LEN);
    if (crcBak == (s_BackupBuff.crc[0] << 8 | s_BackupBuff.crc[1]))
    {
        BackupErrorFlag = FALSE;
    }
    else
    {
        BackupErrorFlag = TRUE;
    }
}

/*
*	写块并读出校验
*/
BOOL hwa_mifraeWriteBlockCheck(UINT8 *dat, UINT8 block)
{
    if (hwa_fm1702WriteBlock(dat, block) == FALSE)
    {
        return FALSE;
    }
    if (hwa_fm1702ReadBlock((UINT8 *)&s_TempBuff, block) == FALSE)
    {
        return FALSE;
    }
    hwa_fm1702Decrypt((UINT8 *)&s_TempBuff);
    if (memcmp(dat, (UINT8 *)&s_TempBuff, USE_DATA_BLOCK_LEN) != 0)
    {
        return FALSE;
    }
    return TRUE;
}

static void hwa_fm1702RecoveryOldCard(UINT8 sector)
{
    UINT8 money;
    hwa_fm1702Encrypt((UINT8 *)&s_NormalBuff);            //旧卡由于未加密，校验时进行了解密操作，故此时利用卡ID加密
    money = *(UINT8 *)&s_NormalBuff;
    if (money != 0xFF && money <= 200
            && s_NormalBuff.crc[0] == 0
            && s_NormalBuff.crc[1] == 0
       )
    {
        s_NormalBuff.money = (UINT16)money * 100;
        hwa_fm1702WriteSector((UINT8 *)&s_NormalBuff, sector);
        return;
    }
    hwa_fm1702Encrypt((UINT8 *)&s_BackupBuff);            //旧卡由于未加密，校验时进行了解密操作，故此时利用卡ID加密
    money = *(UINT8 *)&s_BackupBuff;
    if (money != 0xFF && money <= 200
            && s_BackupBuff.crc[0] == 0
            && s_BackupBuff.crc[1] == 0
       )
    {
        s_BackupBuff.money = (UINT16)money * 100;
        hwa_fm1702WriteSector((UINT8 *)&s_BackupBuff, sector);
        return;
    }
}

static void hwa_fm1702RecoveryNewCard(UINT8 sector)
{
    hwa_fm1702Encrypt((UINT8 *)&s_NormalBuff);            //旧卡由于未加密，校验时进行了解密操作，故此时利用卡ID加密
    if (s_NormalBuff.money == 0
            && s_NormalBuff.crc[0] == 0
            && s_NormalBuff.crc[1] == 0
       )
    {
        hwa_fm1702WriteSector((UINT8 *)&s_NormalBuff, sector);
        return;
    }
    hwa_fm1702Encrypt((UINT8 *)&s_BackupBuff);            //旧卡由于未加密，校验时进行了解密操作，故此时利用卡ID加密
    if (s_BackupBuff.money == 0
            && s_BackupBuff.crc[0] == 0
            && s_BackupBuff.crc[1] == 0
       )
    {
        hwa_fm1702WriteSector((UINT8 *)&s_BackupBuff, sector);
        return;
    }
}

BOOL hwa_fm1702ReadSector(UINT8 *dat, UINT8 sector)
{
    UINT8 block = sector * 4 + NORMAL_DATA_BLOCK;
    UINT8 blockBak = sector * 4 + BACKUP_DATA_BLOCK;

    if (dat == NULL
            || sector == 0
            || sector >= 16)
    {
        return FALSE;
    }

    if (hwa_fm1702ReadBlock((UINT8 *)&s_NormalBuff, block) == FALSE)
    {
        return FALSE;
    }

    if (hwa_fm1702ReadBlock((UINT8 *)&s_BackupBuff, blockBak) == FALSE)
    {
        return FALSE;
    }

    hwa_fm1702CheckBlock();

    if (NormalErrorFlag && BackupErrorFlag)				//正常块和备份块都校验错误
    {
        return FALSE;
    }
    else if (NormalErrorFlag)							//正常块校验错误
    {
        if (hwa_mifraeWriteBlockCheck((UINT8 *)&s_BackupBuff, block) == FALSE)
        {
            return FALSE;
        }
        memcpy(dat, (UINT8 *)&s_BackupBuff, DATA_BLOCK_SIZE);
    }
    else if (BackupErrorFlag							//备份块校验错误
             || s_NormalBuff.crc[0] != s_BackupBuff.crc[0]	//正常块和备份块校验正确但数据不一样，用正常块替换备份块
             || s_NormalBuff.crc[1] != s_BackupBuff.crc[1]
            )
    {
        if (hwa_mifraeWriteBlockCheck((UINT8 *)&s_NormalBuff, blockBak) == FALSE)
        {
            return FALSE;
        }
        memcpy(dat, (UINT8 *)&s_NormalBuff, DATA_BLOCK_SIZE);
    }
    else
    {
        memcpy(dat, (UINT8 *)&s_NormalBuff, DATA_BLOCK_SIZE);
    }
    return TRUE;
}

BOOL hwa_fm1702WriteSector(UINT8 *dat, UINT8 sector)
{
    UINT8 block = sector * 4 + NORMAL_DATA_BLOCK;
    UINT8 blockBak = sector * 4 + BACKUP_DATA_BLOCK;
    UINT16 crc;

    if (dat == NULL
            || sector == 0
            || sector >= 16)
    {
        return FALSE;
    }

    crc = hwa_fm1702CheckOut(dat, USE_DATA_BLOCK_LEN);
    dat[USE_DATA_BLOCK_LEN] = (UINT8)(crc >> 8);
    dat[USE_DATA_BLOCK_LEN + 1] = (UINT8)(crc & 0xFF);

    if (hwa_fm1702WriteBlock(dat, block) == FALSE)
    {
        return FALSE;
    }

    hwa_fm1702WriteBlock(dat, blockBak);

    return TRUE;
}

