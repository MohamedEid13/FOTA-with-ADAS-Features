
#ifndef INC_STM32F103C6_RCC_DRIVER_H_
#define INC_STM32F103C6_RCC_DRIVER_H_

#include "TYPES.h"
#include "RCC_private.h"
#include "RCC_config.h"


#define HSE_CLK			(u32)16000000
#define HSI_RC_CLK		(u32)8000000

/*** BUS Types ***/
#define AHB_BUS 0
#define APB2_BUS 2
#define	APB1_BUS 1
/********************/

#define RCC_HSI_CLK 			0
#define RCC_HSE_CRYSTAL_CLK 	1
#define RCC_HSE_RC_CLK 			2
#define RCC_PLL_CRYSTAL_CLK 	3
#define RCC_PLL_RC_CLK 			4

typedef enum EN_Peripheral_t{
	AFIO_EN_CLK = 0 	,
	IOPA_EN_CLK = 2 	,
	IOPB_EN_CLK			,
	IOPC_EN_CLK			,
	IOPD_EN_CLK			,
	IOPE_EN_CLK			,
	IOPF_EN_CLK			,
	IOPG_EN_CLK			,
	ADC1_EN_CLK			,
	ADC2_EN_CLK			,
	TIM1_EN_CLK			,
	SPI1_EN_CLK			,
	TIM8_EN_CLK			,
	USART1_EN_CLK		,
	ADC3_EN_CLK			,
	TIM9_EN_CLK	= 19	,
	TIM10_EN_CLK		,
	TIM11_EN_CLK		,

	DMA1_EN_CLK	 = 0 	,
	DMA2_EN_CLK			,
	SRAM_EN_CLK			,
	FLITF_EN_CLK = 4	,
	CRC_EN_CLK	 = 6	,
	FSMC_EN_CLK	 = 8	,
	SDIO_EN_CLK	 = 10	,

	TIM2_EN_CLK	 = 0 	,
	TIM3_EN_CLK			,
	TIM4_EN_CLK			,
	TIM5_EN_CLK			,
	TIM6_EN_CLK			,
	TIM7_EN_CLK			,
	TIM12_EN_CLK		,
	TIM13_EN_CLK		,
	TIM14_EN_CLK		,
	WWDG_EN_CLK	 = 11 	,
	SPI2_EN_CLK	 = 14 	,
	SPI3_EN_CLK	 		,
	USART2_EN_CLK = 17 	,
	USART3_EN_CLK	 	,
	UART4_EN_CLK	 	,
	UART5_EN_CLK	 	,
	I2C1_EN_CLK	 		,
	I2C2_EN_CLK	 		,
	USB_EN_CLK	 		,
	CAN_EN_CLK	 =25	,
	BKP_EN_CLK	 =27	,
	PWR_EN_CLK	 		,
	DAC_EN_CLK			,
}EN_Peripheral_t;


typedef enum RSTR_Peripheral_t{
	AFIO_RSTR_CLK = 0 	,
	IOPA_RSTR_CLK = 2 	,
	IOPB_RSTR_CLK			,
	IOPC_RSTR_CLK			,
	IOPD_RSTR_CLK			,
	IOPE_RSTR_CLK			,
	IOPF_RSTR_CLK			,
	IOPG_RSTR_CLK			,
	ADC1_RSTR_CLK			,
	ADC2_RSTR_CLK			,
	TIM1_RSTR_CLK			,
	SPI1_RSTR_CLK			,
	TIM8_RSTR_CLK			,
	USART1_RSTR_CLK		,
	ADC3_RSTR_CLK			,
	TIM9_RSTR_CLK	= 19	,
	TIM10_RSTR_CLK		,
	TIM11_RSTR_CLK		,

	TIM2_RSTR_CLK	 = 0 	,
	TIM3_RSTR_CLK			,
	TIM4_RSTR_CLK			,
	TIM5_RSTR_CLK			,
	TIM6_RSTR_CLK			,
	TIM7_RSTR_CLK			,
	TIM12_RSTR_CLK		,
	TIM13_RSTR_CLK		,
	TIM14_RSTR_CLK		,
	WWDG_RSTR_CLK	 = 11 	,
	SPI2_RSTR_CLK	 = 14 	,
	SPI3_RSTR_CLK	 		,
	USART2_RSTR_CLK = 17 	,
	USART3_RSTR_CLK	 	,
	UART4_RSTR_CLK	 	,
	UART5_RSTR_CLK	 	,
	I2C1_RSTR_CLK	 		,
	I2C2_RSTR_CLK	 		,
	USB_RSTR_CLK	 		,
	CAN_RSTR_CLK	 =25	,
	BKP_RSTR_CLK	 =27	,
	PWR_RSTR_CLK	 		,
	DAC_RSTR_CLK			,
}RSTR_Peripheral_t;

#define AFIO_BUS 	APB2_BUS
#define	IOPA_BUS 	APB2_BUS
#define IOPB_BUS	APB2_BUS
#define IOPC_BUS	APB2_BUS
#define IOPD_BUS	APB2_BUS
#define IOPE_BUS	APB2_BUS
#define IOPF_BUS	APB2_BUS
#define IOPG_BUS	APB2_BUS
#define ADC1_BUS	APB2_BUS
#define	ADC2_BUS 	APB2_BUS
#define TIM1_BUS	APB2_BUS
#define SPI1_BUS	APB2_BUS
#define TIM8_BUS	APB2_BUS
#define USART1_BUS 	APB2_BUS
#define ADC3_BUS	APB2_BUS
#define TIM9_BUS	APB2_BUS
#define TIM10_BUS 	APB2_BUS
#define TIM11_BUS 	APB2_BUS

#define DMA1_BUS	AHB_BUS
#define	DMA2_BUS	AHB_BUS
#define	SRAM_BUS	AHB_BUS
#define	FLITF_BUS 	AHB_BUS
#define	CRC_BUS	 	AHB_BUS
#define	FSMC_BUS	AHB_BUS
#define	SDIO_BUS 	AHB_BUS

#define TIM2_BUS	 	APB1_BUS
#define	TIM3_BUS		APB1_BUS
#define	TIM4_BUS		APB1_BUS
#define	TIM5_BUS		APB1_BUS
#define TIM6_BUS		APB1_BUS
#define TIM7_BUS		APB1_BUS
#define TIM12_BUS		APB1_BUS
#define TIM13_BUS		APB1_BUS
#define TIM14_BUS		APB1_BUS
#define WWDG_BUS 		APB1_BUS
#define	SPI2_BUS	 	APB1_BUS
#define	SPI3_BUS	 	APB1_BUS
#define	USART2_BUS		APB1_BUS
#define	USART3_BUS		APB1_BUS
#define	UART4_BUS		APB1_BUS
#define	UART5_BUS		APB1_BUS
#define	I2C1_BUS	 	APB1_BUS
#define	I2C2_BUS	 	APB1_BUS
#define	USB_BUS		 	APB1_BUS
#define	CAN_BUS		 	APB1_BUS
#define	BKP_BUS		 	APB1_BUS
#define	PWR_BUS		 	APB1_BUS
#define	DAC_BUS			APB1_BUS


/************************************************************************************************
 *                                          API'S                                               *
 ************************************************************************************************/

/**=============================================
  * @Fn				- MCAL_RCC_SysType_Init
  * @brief 			- Init the clock source of the MCU
  * @param [in] 	- None
  * @param [out] 	- None
  * @retval 		- None
  * Note			- None
  */

void MCAL_RCC_SysType_Init(void);

/**=============================================
  * @Fn				- MCAL_RCC_Enable_Clock
  * @brief 			- Enable the clock for a specific peripheral
  * @param [in] 	- peripheral: Select the peripheral from @ref RSTR_Peripheral_t
  * @param [in] 	- Bus       : Select the Bus from @ref  Bus Types
  * @retval 		- None
  * Note			- None
  */
void MCAL_RCC_Enable_Clock(EN_Peripheral_t Peripheral,u8 Bus);


/**=============================================
  * @Fn				- MCAL_RCC_Enable_Clock
  * @brief 			- Reset the clock for a specific peripheral
  * @param [in] 	- peripheral: Select the peripheral from @ref RSTR_Peripheral_t
  * @param [in] 	- Bus       : Select the Bus from @ref  Bus Types
  * @retval 		- None
  * Note			- None
  */
void MCAL_RCC_Reset_Clock(RSTR_Peripheral_t Peripheral,u8 Bus);


/**=============================================
  * @Fn				- MCAL_RCC_GetSYSCLKFreq
  * @brief 			- Gets the frequency of the system clock in HZ
  * @param [in] 	- None
  * @retval 		- Frequency of the system clock
  * Note			- None
  */

u32 MCAL_RCC_GetSYSCLKFreq(void);

/**=============================================
  * @Fn				- MCAL_RCC_GetHCLKFreq
  * @brief 			- Gets the frequency of the AHB bus clock in HZ
  * @param [in] 	- None
  * @retval 		- Frequency of the AHB bus clock
  * Note			- None
  */

u32 MCAL_RCC_GetHCLKFreq(void);

/**=============================================
  * @Fn				- MCAL_RCC_GetPCLK1Freq
  * @brief 			- Gets the frequency of the APB1 bus clock in HZ
  * @param [in] 	- None
  * @retval 		- Frequency of the APB1 bus clock
  * Note			- None
  */

u32 MCAL_RCC_GetPCLK1Freq(void);

/**=============================================
  * @Fn				- MCAL_RCC_GetPCLK1Freq
  * @brief 			- Gets the frequency of the APB2 bus clock in HZ
  * @param [in] 	- None
  * @retval 		- Frequency of the APB2 bus clock
  * Note			- None
  */

u32 MCAL_RCC_GetPCLK2Freq(void);

#endif /* INC_STM32F103C6_RCC_DRIVER_H_ */
