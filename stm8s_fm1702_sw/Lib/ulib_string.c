#include "ulib_string.h"

const UINT8 u8_hexTable[16] = 
{
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
};

UINT8 ulib_stringStrToHex(UINT8 *str)
{
	UINT8 hex;
	hex = str[0]-
}

void ulib_stringHexToStr(UINT8 hex, UINT8 *string)
{
	string[0] = u8_hexTable[hex>>4];
	string[1] = u8_hexTable[hex&0x0F];
}

void ulib_stringHexsToStrs(UINT8 *hexs, UINT8 hexLen, UINT8 *strings)
{
	while(hexLen--)
	{
		ulib_stringHexToStr(*hexs, strings);
		hexs++;
		strings += 2;
	}
}

void ulib_stringStrsToHexs(UINT8 *str, UINT8 *hex)
{
}



