/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_VECTRO_H__
#define __SYS_VECTRO_H__

/* Includes ------------------------------------------------------------------*/
#include "iostm8s105k6.h"
/* Includes ------------------------------------------------------------------*/
#include "sys_vector.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define STRINGVECTOR(x) #x
#define VECTOR_ID(x) STRINGVECTOR( vector = (x) )
#define INTERRUPT_HANDLER( a, b )  \
_Pragma( VECTOR_ID( (b)+2 ) )        \
__interrupt void (a)( void )
#define INTERRUPT_HANDLER_TRAP(a) \
_Pragma( VECTOR_ID( 1 ) ) \
__interrupt void (a) (void)
/* Exported functions ------------------------------------------------------- */

__interrupt void TRAP_IRQHandler(void); /* TRAP */
__interrupt void TLI_IRQHandler(void); /* TLI */
__interrupt void AWU_IRQHandler(void); /* AWU */
__interrupt void CLK_IRQHandler(void); /* CLOCK */
__interrupt void EXTI_PORTA_IRQHandler(void); /* EXTI PORTA */
__interrupt void EXTI_PORTB_IRQHandler(void); /* EXTI PORTB */
__interrupt void EXTI_PORTC_IRQHandler(void); /* EXTI PORTC */
__interrupt void EXTI_PORTD_IRQHandler(void); /* EXTI PORTD */
__interrupt void EXTI_PORTE_IRQHandler(void); /* EXTI PORTE */

#ifdef STM8S903
__interrupt void EXTI_PORTF_IRQHandler(void); /* EXTI PORTF */
#endif /*STM8S903*/

#if defined (STM8S208) || defined (STM8AF52Ax)
__interrupt void CAN_RX_IRQHandler(void); /* CAN RX */
__interrupt void CAN_TX_IRQHandler(void); /* CAN TX/ER/SC */
#endif /* STM8S208 || STM8AF52Ax */

__interrupt void SPI_IRQHandler(void); /* SPI */
__interrupt void TIM1_CAP_COM_IRQHandler(void); /* TIM1 CAP/COM */
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void); /* TIM1 UPD/OVF/TRG/BRK */

#ifdef STM8S903
__interrupt void TIM5_UPD_OVF_BRK_TRG_IRQHandler(void); /* TIM5 UPD/OVF/BRK/TRG */
__interrupt void TIM5_CAP_COM_IRQHandler(void); /* TIM5 CAP/COM */
#else /*STM8S208, STM8S207, STM8S105 or STM8S103 or STM8AF52Ax or STM8AF62Ax or STM8A626x*/
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void); /* TIM2 UPD/OVF/BRK */
__interrupt void TIM2_CAP_COM_IRQHandler(void); /* TIM2 CAP/COM */
#endif /*STM8S903*/

#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S105) || \
    defined(STM8S005) ||  defined (STM8AF52Ax) || defined (STM8AF62Ax) || defined (STM8AF626x)
__interrupt void TIM3_UPD_OVF_BRK_IRQHandler(void); /* TIM3 UPD/OVF/BRK */
__interrupt void TIM3_CAP_COM_IRQHandler(void); /* TIM3 CAP/COM */
#endif /*STM8S208, STM8S207 or STM8S105 or STM8AF52Ax or STM8AF62Ax or STM8A626x */

#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S103) || \
    defined(STM8S003) ||  defined (STM8AF52Ax) || defined (STM8AF62Ax) || defined (STM8S903)
__interrupt void UART1_TX_IRQHandler(void); /* UART1 TX */
__interrupt void UART1_RX_IRQHandler(void); /* UART1 RX */
#endif /*STM8S208, STM8S207, STM8S903 or STM8S103 or STM8AF52Ax or STM8AF62Ax */

__interrupt void I2C_IRQHandler(void); /* I2C */

#if defined(STM8S105) || defined(STM8S005) ||  defined (STM8AF626x)
__interrupt void UART2_RX_IRQHandler(void); /* UART2 RX */
__interrupt void UART2_TX_IRQHandler(void); /* UART2 TX */
#endif /* STM8S105 or STM8AF626x */

#if defined(STM8S207) || defined(STM8S007) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
__interrupt void UART3_RX_IRQHandler(void); /* UART3 RX */
__interrupt void UART3_TX_IRQHandler(void); /* UART3 TX */
#endif /*STM8S207, STM8S208, STM8AF62Ax or STM8AF52Ax */

#if defined(STM8S207) || defined(STM8S007) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
__interrupt void ADC2_IRQHandler(void); /* ADC2 */
#else /*STM8S105, STM8S103 or STM8S903*/
__interrupt void ADC1_IRQHandler(void); /* ADC1 */
#endif /*STM8S207, STM8S208, STM8AF62Ax or STM8AF52Ax */

#ifdef STM8S903
__interrupt void TIM6_UPD_OVF_TRG_IRQHandler(void); /* TIM6 UPD/OVF/TRG */
#else /*STM8S208, STM8S207, STM8S105 or STM8S103 or STM8AF62Ax or STM8AF52Ax or STM8AF626x */
__interrupt void TIM4_UPD_OVF_IRQHandler(void); /* TIM4 UPD/OVF */
#endif /*STM8S903*/
__interrupt void EEPROM_EEC_IRQHandler(void); /* EEPROM ECC CORRECTION */

#endif /* __SYS_VECTRO_H__ */
