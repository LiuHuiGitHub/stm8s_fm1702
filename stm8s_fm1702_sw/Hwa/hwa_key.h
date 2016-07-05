#ifndef __HWA_KEY_H__
#define __HWA_KEY_H__

#include "typedef.h"

/*explame
if(KEY_K[0].Flags.state == KEY_DOWN)
{
	KEY_K[0].Flags.state = KEY_UP;
	LED1 = !LED1;
}
if(KEY_K[0].Flags.trig == TRUE)
{
	KEY_K[0].Flags.trig = FALSE;
	LED1 = 0;
	sprintf((char*)s, "%d\0", (int)i++);
	drv_lcdShowString(0, 0, s);
}
*/
typedef struct
{
    BOOL state			: 1;
    BOOL level			: 1;
    BOOL trig			: 1;
    BOOL unlash 		: 1;
} KEY_flag;

typedef struct
{
    KEY_flag flags;				//按键标志组
    UINT8 changeDelay;			//延时时间计数
    UINT8 counter;				//状态转换时间计数
} KEY_STRUCT;

typedef enum
{
	KEY_SET = 0,
	KEY_UP,
	KEY_DN,
	NUM_OF_KEY
}KEY_ENUM;

extern KEY_STRUCT s_key[NUM_OF_KEY];

void hwa_keyInit(void);
void hwa_keyHandler10ms(void);

#endif

