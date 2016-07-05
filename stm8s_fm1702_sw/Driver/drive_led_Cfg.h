#ifndef __DRIVER_LED_CFG_H__
#define __DRIVER_LED_CFG_H__

#include "typedef.h"

/*Seg Class*/
#define SEG_CLASS       0   //0->共阳 1->共阴

/*Seg Pin*/
#define SEG_PORT_A      BIT0
#define SEG_PORT_B      BIT1
#define SEG_PORT_C      BIT2
#define SEG_PORT_D      BIT3
#define SEG_PORT_E      BIT4
#define SEG_PORT_F      BIT5
#define SEG_PORT_G      BIT6
#define SEG_PORT_H      BIT7

/*数码管管脚定义
P20~7
a f b g c e h d
*/
/*Seg Coding*/
#define SEG_0           (UINT8)(SEG_PORT_A|SEG_PORT_B|SEG_PORT_C|SEG_PORT_D|SEG_PORT_E|SEG_PORT_F)
#define SEG_1           (UINT8)(SEG_PORT_B|SEG_PORT_C)
#define SEG_2           (UINT8)(SEG_PORT_A|SEG_PORT_B|SEG_PORT_D|SEG_PORT_E|SEG_PORT_G)
#define SEG_3           (UINT8)(SEG_PORT_A|SEG_PORT_B|SEG_PORT_C|SEG_PORT_D|SEG_PORT_G)
#define SEG_4           (UINT8)(SEG_PORT_B|SEG_PORT_C|SEG_PORT_F|SEG_PORT_G)
#define SEG_5           (UINT8)(SEG_PORT_A|SEG_PORT_C|SEG_PORT_D|SEG_PORT_F|SEG_PORT_G)
#define SEG_6           (UINT8)(SEG_PORT_A|SEG_PORT_C|SEG_PORT_D|SEG_PORT_E|SEG_PORT_F|SEG_PORT_G)
#define SEG_7           (UINT8)(SEG_PORT_A|SEG_PORT_B|SEG_PORT_C)
#define SEG_8           (UINT8)(SEG_PORT_A|SEG_PORT_B|SEG_PORT_C|SEG_PORT_D|SEG_PORT_E|SEG_PORT_F|SEG_PORT_G)
#define SEG_9           (UINT8)(SEG_PORT_A|SEG_PORT_B|SEG_PORT_C|SEG_PORT_D|SEG_PORT_F|SEG_PORT_G)
#define SEG_A           (UINT8)(SEG_PORT_A|SEG_PORT_B|SEG_PORT_C|SEG_PORT_E|SEG_PORT_F|SEG_PORT_G)
#define SEG_B           (UINT8)(SEG_PORT_C|SEG_PORT_D|SEG_PORT_E|SEG_PORT_F|SEG_PORT_G)
#define SEG_C           (UINT8)(SEG_PORT_A|SEG_PORT_D|SEG_PORT_E|SEG_PORT_F)
#define SEG_D           (UINT8)(SEG_PORT_B|SEG_PORT_C|SEG_PORT_D|SEG_PORT_E|SEG_PORT_G)
#define SEG_E           (UINT8)(SEG_PORT_A|SEG_PORT_D|SEG_PORT_E|SEG_PORT_F|SEG_PORT_G)
#define SEG_F           (UINT8)(SEG_PORT_A|SEG_PORT_E|SEG_PORT_F|SEG_PORT_G)
#define SEG_P           (UINT8)(SEG_PORT_A|SEG_PORT_B|SEG_PORT_E|SEG_PORT_F|SEG_PORT_G)
#define SEG_U           (UINT8)(SEG_PORT_B|SEG_PORT_C|SEG_PORT_D|SEG_PORT_E|SEG_PORT_F)
#define SEG_LINE        (UINT8)(SEG_PORT_G)
#define SEG_NULL        (UINT8)(~(SEG_8|SEG_PORT_H))
#define SEG_H        	(UINT8)(SEG_PORT_B|SEG_PORT_C|SEG_PORT_E|SEG_PORT_F|SEG_PORT_G)

/*Seg Level*/
#define SEG_ON          (SEG_CLASS==0)
#define SEG_OFF         (SEG_CLASS==1)

#endif
