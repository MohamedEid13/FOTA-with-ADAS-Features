

#ifndef NVIC_DRIVER_NVIC_H_
#define NVIC_DRIVER_NVIC_H_

#include "TYPES.h"
#include "NVIC_private.h"

// Interrupt_Requests_Numbers_define

#define WWDG_IRQ				0
#define PVD_IRQ					1
#define TAMPER_IRQ				2
#define RTC_IRQ					3
#define FLASH_IRQ				4
#define RCC_IRQ					5
#define EXTI0_IRQ				6
#define EXTI1_IRQ				7
#define EXTI2_IRQ				8
#define EXTI3_IRQ				9
#define EXTI4_IRQ				10
#define DMA1_CHANNEL1_IRQ		11
#define DMA1_CHANNEL2_IRQ		12
#define DMA1_CHANNEL3_IRQ		13
#define DMA1_CHANNEL4_IRQ		14
#define DMA1_CHANNEL5_IRQ		15
#define DMA1_CHANNEL6_IRQ		16
#define DMA1_CHANNEL7_IRQ		17
#define ADC1_2_IRQ				18
#define CAN1_TX_IRQ				19
#define CAN1_RX0_IRQ			20
#define CAN1_RX1_IRQ			21
#define CAN1_SCE_IRQ			22
#define EXTI5_IRQ				23
#define EXTI6_IRQ				23
#define EXTI7_IRQ				23
#define EXTI8_IRQ				23
#define EXTI9_IRQ				23

#define TIM1_BRK_IRQ			24
#define TIM1_UP_IRQ				25
#define TIM1_TRG_COM_IRQ		26
#define TIM1_CC_IRQ				27
#define TIM2_IRQ				28
#define TIM3_IRQ				29
#define TIM4_IRQ				30
#define I2C1_EV_IRQ				31

#define I2C1_ER_IRQ				32
#define I2C2_EV_IRQ				33
#define I2C2_ER_IRQ				34
#define SPI1_IRQ				35
#define SPI2_IRQ				36
#define USART1_IRQ				37
#define USART2_IRQ				38
#define USART3_IRQ				39
#define EXTI10_IRQ				40
#define EXTI11_IRQ				40
#define EXTI12_IRQ				40
#define EXTI13_IRQ				40
#define EXTI14_IRQ				40
#define EXTI15_IRQ				40


#define CAN2_TX_IRQ				63

#define CAN2_RX0_IRQ			64
#define OTG_FS_IRQ				67

////--------------------------------------------------------------------------
////--------------------------------------------------------------------------
//
//#define SCB_GROUP16_SUB0	3
//#define SCB_GROUP8_SUB2		4
//#define SCB_GROUP4_SUB4		5
//#define SCB_GROUP2_SUB8		6
//#define SCB_GROUP0_SUB16	7

//--------------------------------------------------------------------------
/*                                  API'S                                  */
//--------------------------------------------------------------------------

/**=============================================
  * @Fn				- MCAL_NVIC_EN
  * @brief 			- Enable IRQn
  * @param [in] 	- IRQn: Number of interrupt request as defined in vector table or in @ref Interrupt_Requests_Numbers_define
  * @param [out] 	- None
  * @retval 		- None
  * Note			- None
  */

void MCAL_NVIC_EN(u8 IRQ);


/**=============================================
  * @Fn				- MCAL_NVIC_Disable
  * @brief 			- Disable IRQn
  * @param [in] 	- IRQn: Number of interrupt request as defined in vector table or in @ref Interrupt_Requests_Numbers_define
  * @param [out] 	- None
  * @retval 		- None
  * Note			- None
  */
void MCAL_NVIC_Disable(u8 IRQ);




//void MCAL_NVIC_EN_Pendding(uint8_t IRQ);
//void MCAL_NVIC_Disable_pendding(uint8_t IRQ);
//uint8_t MCAL_NVIC_Read_Active_Flag(uint8_t IRQ);
//void MCAL_SCB_Select_Mode(uint8_t Mode);
//void MCA_NVIC_set_priority(uint8_t IRQ,uint8_t Group ,uint8_t Priority);


#endif /* NVIC_DRIVER_NVIC_H_ */
