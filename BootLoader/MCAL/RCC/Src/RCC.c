
#include "RCC.h"



//Bits 7:4 HPRE[3:0]: AHB prescaler
//Set and cleared by software to control AHB clock division factor.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
const u8 AHBPrescTable[16] = {0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};

//PPRE1[2:0]: APB Low-speed prescaler (APB1)
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16
const u8 APBPrescTable[8] = {0,0,0,0,1,2,3,4};

u32 MCAL_RCC_GetSYSCLKFreq(void){

	u32 retVal ;
	switch( (RCC->CFGR >> 2) & 0b11){
	case 0:
		retVal = HSI_RC_CLK;
		break;
	case 1:
		retVal =  HSE_CLK;
		break;
	case 2:
		retVal =  16000000 ;
		break;
	}

	return retVal;
}


u32 MCAL_RCC_GetHCLKFreq(void){

	return ( MCAL_RCC_GetSYSCLKFreq() >> AHBPrescTable[ (RCC->CFGR >> 4) & 0xf ] );
}

u32 MCAL_RCC_GetPCLK1Freq(void){

	return ( MCAL_RCC_GetHCLKFreq() >> APBPrescTable[ (RCC->CFGR >> 8) & 0b111 ] );

}

u32 MCAL_RCC_GetPCLK2Freq(void){

	return ( MCAL_RCC_GetHCLKFreq() >> APBPrescTable[ (RCC->CFGR >> 11) & 0b111 ] );
}


void MCAL_RCC_SysType_Init(){

	switch (RCC_CLK_Type_CFG) {

	case RCC_HSI_CLK:
		RCC->CR = 0x00000000 ;
		RCC->CR |= RCC_CR_HSION ;
		RCC->CR |= (0x1UL << (7));		//Trimming
		break;

	case RCC_HSE_CRYSTAL_CLK:
		RCC->CR = 0x00000000 ;
		RCC->CR = RCC_CR_HSEON ;
		break;

	case RCC_HSE_RC_CLK:
		RCC->CR = 0x00000000 ;
		RCC->CR |= RCC_CR_HSEON ;
		RCC->CR |= RCC_CR_HSEBYP ;
		break;

	case RCC_PLL_CRYSTAL_CLK:
		RCC->CR = 0x00000000 ;
		RCC->CR |= RCC_CR_HSEON ;
		RCC->CR |= RCC_CR_PLLON ;
		break;

	case RCC_PLL_RC_CLK:
		RCC->CR = 0x00000000 ;
		RCC->CR |= RCC_CR_HSEON ;
		RCC->CR |= RCC_CR_HSEBYP ;
		RCC->CR |= RCC_CR_PLLON ;
		break;

	default:
		break;
	}

}

void MCAL_RCC_Enable_Clock(EN_Peripheral_t peripheral,u8 Bus){

	if(Bus == APB2_BUS){
		switch (peripheral) {

		case AFIO_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_AFIO ;
			break;

		case IOPA_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_IOPA ;
			break;

		case IOPB_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_IOPB ;
			break;

		case IOPC_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_IOPC ;
			break;

		case IOPD_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_IOPD ;
			break;

		case IOPE_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_IOPE ;
			break;

		case IOPF_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_IOPF ;
			break;

		case IOPG_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_IOPG ;
			break;

		case ADC1_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_ADC1 ;
			break;

		case ADC2_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_ADC2 ;
			break;

		case TIM1_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_TIM1 ;
			break;

		case SPI1_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_SPI1 ;
			break;

		case TIM8_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_TIM8 ;
			break;

		case USART1_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_USART1 ;
			break;

		case ADC3_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_ADC3 ;
			break;

		case TIM9_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_TIM9 ;
			break;

		case TIM10_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_TIM10 ;
			break;

		case TIM11_EN_CLK:
			RCC->APB2ENR |= RCC_APB2ENR_TIM11 ;
			break;
		default:
			break;
		}
	}



	if(Bus == AHB_BUS){
		switch (peripheral) {
		case DMA1_EN_CLK:
			RCC->AHBENR |= RCC_AHBENR_DMA1 ;
			break;

		case DMA2_EN_CLK:
			RCC->AHBENR |= RCC_AHBENR_DMA2 ;
			break;

		case SRAM_EN_CLK:
			RCC->AHBENR |= RCC_AHBENR_SRAM ;
			break;

		case FLITF_EN_CLK:
			RCC->AHBENR |= RCC_AHBENR_FLITF ;
			break;

		case CRC_EN_CLK:
			RCC->AHBENR |= RCC_AHBENR_CRC ;
			break;

		case FSMC_EN_CLK:
			RCC->AHBENR |= RCC_AHBENR_FSMC ;
			break;

		case SDIO_EN_CLK:
			RCC->AHBENR |= RCC_AHBENR_SDIO ;
			break;
		default:
			break;
		}

	}


	if(Bus == APB1_BUS){
		switch (peripheral) {
		case TIM2_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_TIM2 ;
			break;

		case TIM3_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_TIM3 ;
			break;

		case TIM4_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_TIM4 ;
			break;

		case TIM5_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_TIM5 ;
			break;

		case TIM6_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_TIM6 ;
			break;

		case TIM7_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_TIM7 ;
			break;

		case TIM12_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_TIM12 ;
			break;

		case TIM13_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_TIM13 ;
			break;

		case TIM14_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_TIM14 ;
			break;

		case WWDG_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_WWDG ;
			break;

		case SPI2_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_SPI2 ;
			break;

		case SPI3_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_SPI3 ;
			break;

		case USART2_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_USART2 ;
			break;

		case USART3_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_USART3 ;
			break;

		case UART4_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_UART4 ;
			break;

		case UART5_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_UART5 ;
			break;

		case I2C1_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_I2C1 ;
			break;

		case I2C2_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_I2C2 ;
			break;

		case USB_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_USB ;
			break;

		case CAN_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_CAN ;
			break;

		case BKP_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_BKP ;
			break;

		case PWR_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_PWR ;
			break;

		case DAC_EN_CLK:
			RCC->APB1ENR |= RCC_APB1ENR_DAC ;
			break;

		default:
			break;
		}
	}
}

void MCAL_RCC_Reset_Clock(RSTR_Peripheral_t Peripheral,u8 Bus){

	if(Bus == APB2_BUS){
		switch (Peripheral) {

		case AFIO_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_AFIO ;
			break;

		case IOPA_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_IOPA ;
			break;

		case IOPB_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_IOPB ;
			break;

		case IOPC_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_IOPC ;
			break;

		case IOPD_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_IOPD ;
			break;

		case IOPE_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_IOPE ;
			break;

		case IOPF_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_IOPF ;
			break;

		case IOPG_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_IOPG ;
			break;

		case ADC1_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_ADC1 ;
			break;

		case ADC2_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_ADC2 ;
			break;

		case TIM1_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_TIM1 ;
			break;

		case SPI1_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_SPI1 ;
			break;

		case TIM8_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_TIM8 ;
			break;

		case USART1_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_USART1 ;
			break;

		case ADC3_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_ADC3 ;
			break;

		case TIM9_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_TIM9 ;
			break;

		case TIM10_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_TIM10 ;
			break;

		case TIM11_RSTR_CLK:
			RCC->APB2RSTR |= RCC_APB2RSTR_TIM11 ;
			break;
		default:
			break;
		}
	}

	if(Bus == APB1_BUS){
		switch (Peripheral) {

		case TIM2_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_TIM2 ;
			break;

		case TIM3_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_TIM3 ;
			break;

		case TIM4_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_TIM4 ;
			break;

		case TIM5_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_TIM5 ;
			break;

		case TIM6_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_TIM6 ;
			break;

		case TIM7_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_TIM7 ;
			break;

		case TIM12_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_TIM12 ;
			break;

		case TIM13_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_TIM13 ;
			break;

		case TIM14_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_TIM14 ;
			break;

		case WWDG_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_WWDG ;
			break;

		case SPI2_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_SPI2 ;
			break;

		case SPI3_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_SPI3 ;
			break;

		case USART2_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_USART2 ;
			break;

		case USART3_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_USART3 ;
			break;

		case UART4_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_UART4 ;
			break;

		case UART5_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_UART5 ;
			break;

		case I2C1_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_I2C1 ;
			break;

		case I2C2_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_I2C2 ;
			break;

		case USB_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_USB ;
			break;

		case CAN_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_CAN ;
			break;

		case BKP_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_BKP ;
			break;

		case PWR_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_PWR ;
			break;

		case DAC_RSTR_CLK:
			RCC->APB1RSTR |= RCC_APB1RSTR_DAC ;
			break;

		default:
			break;
		}
	}
}
