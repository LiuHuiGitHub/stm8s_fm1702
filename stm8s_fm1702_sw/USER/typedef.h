#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_



#define SYS_CLOCK			(UINT32)16000000
#define BOUD				(UINT32)115200


#define _STM8_
#define _STM8_IAR_


#ifdef _STM8_IAR_
#define CONST				const __root
#else
#define CONST				const
#endif


#ifndef _TRUE_
#define TRUE                1
#endif
#ifndef _FALSE_
#define FALSE               0
#endif

#ifndef _ENABLE_
#define ENABLE				1
#endif
#ifndef _DISABLE_
#define DISABLE				0
#endif

#ifndef _ON_
#define ON					1
#endif
#ifndef _OFF_
#define OFF					0
#endif

#define BIT0				0x01
#define BIT1				0x02
#define BIT2				0x04
#define BIT3				0x08
#define BIT4				0x10
#define BIT5				0x20
#define BIT6				0x40
#define BIT7				0x80

#define TEST_BIT(_byte, _bit)			(_byte & _bit == _bit)
#define SET_BIT(_byte, _bit)			do{_byte |= _bit;}while(FALSE)
#define CLR_BIT(_byte, _bit)			do{_byte &= ~_bit;}while(FALSE)

#ifndef _BOOL_
#define _BOOL_
#ifdef _C51_
typedef bit         		BOOL;
#else
typedef unsigned char       BOOL;
#endif
#endif

#ifndef _UINT8_
#define _UINT8_
typedef unsigned char       UINT8;
#endif

#ifndef _SINT8_
#define _SINT8_
typedef signed char         INT8;
#endif

#ifndef _UINT16_
#define _UINT16_
typedef unsigned short		UINT16;
#endif

#ifndef _SINT16_
#define _SINT16_
typedef signed short		INT16;
#endif

#ifndef _UINT32
#define _UINT32
typedef unsigned long		UINT32;
#endif

#ifndef _SINT32_
#define _SINT32_
typedef signed long			INT32;
#endif

#define nop()				asm("nop")
#ifndef DEBUG
#define sleep()				asm("wfi")
#define stop()				asm("halt")
#else
#define sleep()
#define stop()
#endif
#define enable_interrupt()	asm("rim")
#define disable_interrupt()	asm("sim")

//typedef unsigned char		UINT8;
//typedef unsigned long       uint32_t;

#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports
  *         the name of the source file and the source line number of the call
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
#define assert_param(expr) if((expr)==0)assert_failed((UINT8 *)_FILE_, _LINE_)
/* Exported functions ------------------------------------------------------- */
void assert_failed(uint8_t *file, uint32_t line);
#else
#define assert_param(expr) /*((void)0)*/
#endif /* USE_FULL_ASSERT */

#endif
