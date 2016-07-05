#include "iostm8s105k6.h"
#include "hwa_key.h"

const BOOL c_b_keyValidValue[NUM_OF_KEY] = {0, 0, 0};
const UINT8 c_u8_keyChangeDealyTime = 3;			//30ms
const UINT8 c_u8_keyTunkMinTime = 50;				//500ms		¶Ì°´Ê±¼ä·¶Î§

KEY_STRUCT s_key[NUM_OF_KEY];

static BOOL hwa_getKey(UINT8 key)
{
    if(key == KEY_SET)
    {
        return PB_IDR_IDR3;
    }
    else if(key == KEY_UP)
    {
        return PB_IDR_IDR2;
    }
    else if(key == KEY_DN)
    {
        return PB_IDR_IDR1;
    }
	else
	{
		return 0;
	}
}

void hwa_keyInit(void)
{
    UINT8 i;
    for(i = 0; i < NUM_OF_KEY; i++)
    {
        s_key[i].flags.state 	= OFF;
        s_key[i].flags.level 	= hwa_getKey(i);
        s_key[i].flags.trig 	= FALSE;
        s_key[i].flags.unlash	= TRUE;
        s_key[i].changeDelay 	= 0;
        s_key[i].counter		= 0;
    }
}

void hwa_keyHandler10ms(void)
{
    UINT8 i = 0;
    for(i = 0; i < NUM_OF_KEY; i++)
    {
        s_key[i].flags.level = hwa_getKey(i);
        if(s_key[i].flags.level != c_b_keyValidValue[i])
        {
            if(s_key[i].counter && s_key[i].counter < c_u8_keyTunkMinTime)
            {
                s_key[i].flags.trig = TRUE;
            }
            s_key[i].counter = 0;
            s_key[i].changeDelay = 0;
            s_key[i].flags.state = OFF;
            s_key[i].flags.unlash = TRUE;
        }
        else if(s_key[i].flags.unlash == TRUE)
        {
            if(s_key[i].changeDelay < c_u8_keyChangeDealyTime)
            {
                s_key[i].changeDelay++;
            }
            else
            {
                s_key[i].flags.state = ON;
                s_key[i].flags.unlash = FALSE;
            }
        }
        else if(s_key[i].counter < 0xFF)
        {
            s_key[i].counter++;
        }
    }
}


