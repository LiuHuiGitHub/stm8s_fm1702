#ifndef __DRV_FM1702_H__
#define __DRV_FM1702_H__

#include "typedef.h"
#include "drv_fm1702_itf.h"

//;==============================================
//;FM1702SL控制寄存器定义
//;==============================================
#define		Page_Reg                0x00	//			写：0x00
#define		Command_Reg             0x01	//读：0x82	写：0x02
#define		FIFO_Reg                0x02	//读：0x84	写：0x04
#define		FIFOLength_Reg		    0x04	//读：0x88
#define		SecondaryStatus_Reg  	0x05	//读：0x8A
#define		InterruptEn_Reg		    0x06	//			写：0x0C
#define		InterruptRq_Reg		    0x07	//读：0x8E	写：0x0E
#define		Control_Reg		        0x09	//读：0x92	写：0x12 
#define		ErrorFlag_Reg           0x0A	//读：0x94
#define		BitFraming_Reg	     	0x0F	//			写：0x1E
#define		TxControl_Reg           0x11	//			写：0x22
#define		CwConductance_Reg	    0x12
#define		RxControl2_Reg		    0x1E
#define     RxWait_Reg              0x21
#define		ChannelRedundancy_Reg	0x22


//;==============================================
//;FM1702SL发送命令代码
//;==============================================
#define		WriteEE			  	0x01
#define		LoadKeyE2		  	0x0B
#define 	LoadKey				0x19
#define    	Transmit			0x1A
#define		Transceive		  	0x1E
#define		Authent1		  	0x0C
#define		Authent2		  	0x14

//;==============================================
//;函数错误代码定义
//;==============================================
#define FM1702_OK			0		// 正确
#define FM1702_NOTAGERR		1		// 无卡
#define FM1702_CRCERR		2		// 卡片CRC校验错误
#define FM1702_EMPTY		3		// 数值溢出错误
#define FM1702_AUTHERR		4		// 验证不成功
#define FM1702_PARITYERR    5		// 卡片奇偶校验错误
#define FM1702_CODEERR		6		// 通讯错误(BCC校验错)
#define FM1702_SERNRERR		8		// 卡片序列号错误(anti-collision 错误)
#define FM1702_SELECTERR    9		// 卡片数据长度字节错误(SELECT错误)
#define FM1702_NOTAUTHERR	10		// 0x0A 卡片没有通过验证
#define FM1702_BITCOUNTERR	11		// 从卡片接收到的位数错误
#define FM1702_BYTECOUNTERR	12		// 从卡片接收到的字节数错误仅读函数有效
#define FM1702_RESTERR		13		// 调用restore函数出错
#define FM1702_TRANSERR		14		// 调用transfer函数出错
#define FM1702_WRITEERR		15		// 0x0F 调用write函数出错
#define FM1702_INCRERR		16		// 0x10 调用increment函数出错
#define FM1702_DECRERR		17      // 0x11 调用decrement函数出错
#define FM1702_READERR		18      // 0x12 调用read函数出错
#define FM1702_LOADKEYERR	19      // 0x13 调用LOADKEY函数出错
#define FM1702_FRAMINGERR	20      // 0x14 FM1702帧错误
#define FM1702_REQERR		21      // 0x15 调用req函数出错
#define FM1702_SELERR		22      // 0x16 调用sel函数出错
#define FM1702_ANTICOLLERR	23      // 0x17 调用anticoll函数出错
#define FM1702_INTIVALERR	24      // 0x18 调用初始化函数出错
#define FM1702_READVALERR	25      // 0x19 调用高级读块值函数出错
#define FM1702_DESELECTERR	26      // 0x1A
#define FM1702_CMD_ERR		42      // 0x2A 命令错误

//;==============================================
//;射频卡通信命令码定义
//;==============================================
#define RF_CMD_REQUEST_STD	0x26
#define RF_CMD_REQUEST_ALL	0x52
#define RF_CMD_ANTICOL		0x93
#define RF_CMD_SELECT		0x93
#define RF_CMD_AUTH_LA		0x60
#define RF_CMD_AUTH_LB		0x61
#define RF_CMD_READ         0x30
#define RF_CMD_WRITE		0xa0
#define RF_CMD_INC		    0xc1
#define RF_CMD_DEC		    0xc0
#define RF_CMD_RESTORE		0xc2
#define RF_CMD_TRANSFER		0xb0
#define RF_CMD_HALT		    0x50


extern UINT8 gBuff[16];             //M1卡数据块读取缓冲区
extern UINT8 gCard_UID[5];	//4个字节卡号（32位），一个校验字节

////===============================================
//以下为FM1702读写的子程序
//===============================================
void drv_fm1702PowerDown(void);
BOOL drv_fm1702Init(void);
UINT8 drv_fm1702ReadFifo(UINT8 *buff);
UINT8 drv_fm1702Command(UINT8 Comm_Set, UINT8 *buff, UINT8 count);
UINT8 drv_fm1702Request(UINT8 mode);
UINT8 drv_fm1702AntiColl(void);
UINT8 drv_fm1702SelectCard(void);
UINT8 drv_fm1702LoadKey(UINT8 *ramadr);
UINT8 Authentication(UINT8 *UID, UINT8 SecNR, UINT8 mode);
UINT8 drv_fm1702ReadBlock(UINT8 *buff, UINT8 index);
UINT8 drv_fm1702WriteBlock(UINT8 *buff, UINT8 index);
UINT8 drv_fm1702HaltCard(void);

#endif