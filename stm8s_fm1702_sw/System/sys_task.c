#include "iostm8s105k6.h"
#include "include.h"
#include "sys_iniAppl.h"
#include "sys_iniHw.h"

static UINT8 u8_taskCycleCount100ms = 0;

static UINT8 temp = 10;
UINT16 u16_test = 0x00;

static void sys_taskCycle100ms(void);

void sys_taskHandler1ms(void)
{
	hwa_uartHandler1ms();
}

void sys_taskCycle10ms(void)
{
	hwa_uartHandler10ms();
	hwa_keyHandler10ms();
	
	u16_test++;
	
	if(++u8_taskCycleCount100ms >= 10)
	{
		u8_taskCycleCount100ms -= 10;
		sys_taskCycle100ms();
	}
	
	if(s_key[KEY_UP].flags.state == TRUE)
	{
		s_key[KEY_UP].flags.state = FALSE;
		if(temp < 100 - 10)
		{
			temp += 10;
		}
		else
		{
			temp = 100;
		}
		sys_pwmSet(temp);
	}
	
	if(s_key[KEY_DN].flags.state == TRUE)
	{
		s_key[KEY_DN].flags.state = FALSE;
		if(temp > 10)
		{
			temp -= 10;
		}
		else
		{
			temp = 0;
		}
		sys_pwmSet(temp);
	}
	
	if(s_key[KEY_SET].flags.state == TRUE)
	{
		s_key[KEY_SET].flags.state = FALSE;
		WWDG_CR = 0x80;
	}
}

typedef struct
{
    UINT8 ico[128];		//32*32
    UINT8 title[78];	//44*13
} gImageMenuIco;

const gImageMenuIco ico_download =
{
    {
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XF0, 0X1F, 0XFF, 0XFF, 0XF8,
        0X3F, 0XFF, 0XFF, 0XFC, 0X3C, 0X00, 0X00, 0X3C, 0X38, 0X00, 0X00, 0X1C, 0X38, 0X00, 0X00, 0X1C,
        0X38, 0X00, 0X00, 0X1C, 0X38, 0X00, 0X00, 0X1C, 0X38, 0X00, 0X00, 0X1C, 0X38, 0X00, 0X00, 0X1C,
        0X38, 0X00, 0X00, 0X1C, 0X38, 0X00, 0X00, 0X1C, 0X38, 0X00, 0X00, 0X1C, 0X38, 0X00, 0X00, 0X1C,
        0X38, 0X00, 0X00, 0X1C, 0X38, 0X00, 0X00, 0X1C, 0X38, 0X00, 0X00, 0X1C, 0X38, 0X00, 0X00, 0X1C,
        0X38, 0X00, 0X00, 0X1C, 0X3E, 0X00, 0X00, 0X7C, 0X3F, 0XFF, 0XFF, 0XFC, 0X1F, 0XFF, 0XFF, 0XF8,
        0X0F, 0XFF, 0XFF, 0XF0, 0X00, 0X07, 0XE0, 0X00, 0X00, 0X0F, 0XF0, 0X00, 0X00, 0X7F, 0XFE, 0X00,
        0X00, 0X7F, 0XFE, 0X00, 0X00, 0X7F, 0XFE, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00
    },
    {
        0X00, 0X00, 0X10, 0X88, 0X00, 0X00, 0X00, 0X7F, 0XFB, 0XEA, 0X00, 0X00, 0X00, 0X02, 0X00, 0X89,
        0X00, 0X00, 0X00, 0X02, 0X07, 0XFF, 0X80, 0X00, 0X00, 0X03, 0X01, 0X08, 0X00, 0X00, 0X00, 0X02,
        0X87, 0XE9, 0X00, 0X00, 0X00, 0X02, 0X62, 0X89, 0X00, 0X00, 0X00, 0X02, 0X23, 0XEA, 0X00, 0X00,
        0X00, 0X02, 0X00, 0X84, 0X00, 0X00, 0X00, 0X02, 0X07, 0XE4, 0X80, 0X00, 0X00, 0X02, 0X00, 0X8A,
        0X80, 0X00, 0X00, 0X02, 0X00, 0XB1, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00
    }
};
const gImageMenuIco ico_update =
{
    {
        0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0XFE,0X00,
		0X00,0X7F,0XFF,0X00,0X01,0XFE,0XFF,0X98,0X03,0XF0,0X0F,0XF8,0X07,0XE0,0X07,0XF8,
		0X0F,0X80,0X01,0XF8,0X0F,0X00,0X03,0XF8,0X1E,0X00,0X07,0XF8,0X1E,0X00,0X07,0XF8,
		0X0C,0X00,0X03,0XF8,0X00,0X00,0X00,0XF8,0X00,0X00,0X00,0X18,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X1C,0X00,0X00,0X00,0X1F,0X00,0X00,0X38,0X1F,0XE0,0X00,0X78,
		0X1F,0XF0,0X00,0XF8,0X1F,0XE0,0X00,0XF8,0X1F,0X80,0X00,0XF0,0X1F,0X80,0X01,0XE0,
		0X1F,0XC0,0X07,0XC0,0X18,0XFC,0X3F,0X80,0X18,0XFF,0XFF,0X00,0X00,0X7F,0XFC,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00
    },
    {
        0X00,0X00,0X41,0X02,0X00,0X00,0X00,0X07,0X41,0X7F,0X00,0X00,0X00,0X3C,0X42,0X92,
		0X00,0X00,0X00,0X04,0X47,0X94,0X00,0X00,0X00,0X04,0X51,0X17,0X00,0X00,0X00,0X7F,
		0XFA,0X32,0X00,0X00,0X00,0X04,0X47,0XAA,0X00,0X00,0X00,0X04,0X40,0X2A,0X00,0X00,
		0X00,0X04,0X41,0XA4,0X00,0X00,0X00,0X08,0X46,0X4A,0X00,0X00,0X00,0X10,0X40,0X91,
		0X00,0X00,0X00,0X60,0X41,0X60,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00
    }
};
const gImageMenuIco ico_set =
{
    {
        0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X07,0XE0,0X00,0X00,0X0F,0XF0,0X00,
		0X03,0XCF,0XF3,0XC0,0X07,0XFE,0X7F,0XE0,0X0F,0XFE,0X7F,0XF0,0X0F,0XFC,0X1F,0XF0,
		0X0F,0X20,0X00,0XF0,0X0F,0X00,0X00,0XF0,0X07,0X00,0X00,0XE0,0X07,0X00,0X00,0XE0,
		0X3F,0X03,0XC0,0XF8,0X7F,0X07,0XE0,0XFC,0X7E,0X0F,0XF0,0X7E,0X78,0X0F,0XF0,0X3E,
		0X78,0X0F,0XF0,0X3E,0X7E,0X0F,0XF0,0X7E,0X7F,0X07,0XF0,0XFC,0X3F,0X03,0XC0,0XF8,
		0X0F,0X00,0X00,0XE0,0X0F,0X80,0X00,0XE0,0X0F,0X00,0X00,0XF0,0X0F,0X20,0X00,0XF0,
		0X0F,0XFC,0X3F,0XF0,0X0F,0XFE,0X7F,0XF0,0X07,0XFE,0X7F,0XE0,0X03,0XDF,0XF3,0XC0,
		0X00,0X0F,0XF0,0X00,0X00,0X07,0XE0,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00
    },
    {
        0X00,0X23,0XE3,0XFE,0X00,0X00,0X00,0X12,0X22,0X4A,0X00,0X00,0X00,0X12,0X23,0XFE,
		0X00,0X00,0X00,0X02,0X20,0X20,0X00,0X00,0X00,0X74,0X1F,0XFF,0X80,0X00,0X00,0X13,
		0XE0,0X20,0X00,0X00,0X00,0X12,0X21,0XFC,0X00,0X00,0X00,0X11,0X41,0X24,0X00,0X00,
		0X00,0X15,0X41,0X14,0X00,0X00,0X00,0X18,0X81,0XFC,0X00,0X00,0X00,0X13,0X61,0X05,
		0X00,0X00,0X00,0X0C,0X1F,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00
    }
};

MENUICO menuIco[] = 
{
	{48, 15, (UINT8 *)ico_download.ico, (UINT8 *)ico_download.title,	0, NULL},
	{48, 15, (UINT8 *)ico_update.ico, 	(UINT8 *)ico_update.title, 		0, NULL},
	{48, 15, (UINT8 *)ico_set.ico, 		(UINT8 *)ico_set.title,			0, NULL},
};

UINT8 head[] = {"stm8s_fm1702"};
UINT8 text[] = "";
WINDOWS winxp;

UINT8 PWD_Card[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

static void sys_taskCycle100ms(void)
{
    static UINT8 ledCounter = 0;
//	static BOOL b_flag = FALSE;
	UINT8 temp1;
	char buff[20];
    ledCounter++;
	ledCounter %= 10;
    if(ledCounter > 5)
    {
		PE_ODR_ODR5 = 1;
    }
    else
    {
        PE_ODR_ODR5 = 0;
    }             
	
	if(ledCounter == 5)
	{		
		//drv_fm1702PowerDown();
		//sys_pwmSet(0);
		
		winxp.x = 0;
		winxp.y = 0;
		winxp.with = 128;
		winxp.hight = 64;
		winxp.title = head;
		winxp.state = NULL;
		
		GUI_WindowsDraw(&winxp);
		
		
		temp1 = drv_fm1702ItfReadByte(Page_Reg);
		
//		if(temp1 == 0x80)
//		{
//			hwa_fm1702Init();
//		}
		
		sprintf(buff, "Page_Reg: 0x%2x", (UINT16)temp1);
		
		GUI_PutString(8, 20, buff);

		
		drv_fm1702LoadKey(PWD_Card);
		drv_fm1702HaltCard();
		if(drv_fm1702Request(RF_CMD_REQUEST_STD) == FM1702_OK
			&& drv_fm1702AntiColl() == FM1702_OK
			&& drv_fm1702SelectCard() == FM1702_OK
			&& Authentication(gCard_UID, 1, 0x60) == FM1702_OK
		  )
		{
			GUI_PutString(8, 30, "Brush Card !");
    		sys_pwmSet(100);
		}
		else
		{
			sys_pwmSet(temp);
		}
		
//		menuIco[0].x = 8;
//		menuIco[0].state = 0;
//		GUI_MenuIcoDraw(&menuIco[0]);
//		menuIco[1].x = 48;
//		menuIco[1].state = 1;
//		GUI_MenuIcoDraw(&menuIco[1]);
//		menuIco[2].x = 88;
//		menuIco[2].state = 0;
//		GUI_MenuIcoDraw(&menuIco[2]);
		
//		b_flag = !b_flag;
//		if(b_flag)
//		{
//			GUI_ClearSCR();
//		}
		GUI_Exec();
	}
}



