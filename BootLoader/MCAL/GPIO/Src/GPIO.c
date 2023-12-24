
#include "GPIO.h"



//=====================================================================
//						Generic Macros
//=====================================================================


//=====================================================================
//						Generic Functions
//=====================================================================

u8 Get_CRLH_Postion(u16 PinNumber){

	switch(PinNumber){
	case GPIO_PIN_0 :
		return 0;
		break;
	case GPIO_PIN_1 :
		return 4;
		break;
	case GPIO_PIN_2 :
		return 8;
		break;
	case GPIO_PIN_3 :
		return 12;
		break;
	case GPIO_PIN_4 :
		return 16;
		break;
	case GPIO_PIN_5 :
		return 20;
		break;
	case GPIO_PIN_6 :
		return 24;
		break;
	case GPIO_PIN_7 :
		return 28;
		break;
	case GPIO_PIN_8 :
		return 0;
		break;
	case GPIO_PIN_9 :
		return 4;
		break;
	case GPIO_PIN_10 :
		return 8;
		break;
	case GPIO_PIN_11 :
		return 12;
		break;
	case GPIO_PIN_12 :
		return 16;
		break;
	case GPIO_PIN_13 :
		return 20;
		break;
	case GPIO_PIN_14 :
		return 24;
		break;
	case GPIO_PIN_15 :
		return 28;
		break;
	}
	return 0;
}



//=====================================================================
//						APIs Functions Definitions
//=====================================================================

void MCAL_GPIO_Init(GPIO_Typedef* GPIOx, GPIO_PinConfig_t* PinConfig){
	//Port configuration register low (GPIOx_CRL)  	Pins from 0 to 7
	//Port configuration register low (GPIOx_CRL) 	Pins from 8 to 15

	volatile u32* configregister = NULL ;
	u8 PIN_Config = 0;

	configregister  = (PinConfig->GPIO_PinNumber < GPIO_PIN_8) ? &GPIOx->CRL : &GPIOx->CRH;

	//clear CNF0[1:0] MODE0[1:0]
	(*configregister) &= ~(0xf << Get_CRLH_Postion(PinConfig->GPIO_PinNumber));

	// if pin is output
	if(PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_OD || PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_PP ||
			PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_OD || PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_PP ){
		//set CNF0[1:0] MODE0[1:0]
		PIN_Config = ((((PinConfig->GPIO_Mode - 4) << 2) | (PinConfig->GPIO_OutputSpeed)) & 0x0f );
	}

	// if pin is input
	// MODE = 00: Input mode (reset state)
	else{
		if(PinConfig->GPIO_Mode == GPIO_MODE_ANALOG || PinConfig->GPIO_Mode == GPIO_MODE_INPUT_FLO  ){
			//set CNF0[1:0] MODE0[1:0]
			PIN_Config = ((((PinConfig->GPIO_Mode) << 2) | 0x0) & 0x0f );
		}
		else if (PinConfig->GPIO_Mode == GPIO_MODE_AF_INPUT){
			//set CNF0[1:0] MODE0[1:0]
			PIN_Config = ((((GPIO_MODE_INPUT_FLO) << 2) | 0x0) & 0x0f );
		}
		else{
			//set CNF0[1:0] MODE0[1:0]
			PIN_Config = ((((GPIO_MODE_INPUT_PU) << 2) | 0x0) & 0x0f );

			if(PinConfig->GPIO_Mode == GPIO_MODE_INPUT_PU){
				GPIOx->ODR |= PinConfig->GPIO_PinNumber ;
			}
			else{
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}

	//write on CRL,CRH Register
	(*configregister) |= ((PIN_Config) << Get_CRLH_Postion(PinConfig->GPIO_PinNumber));
}
void MCAL_GPIO_DeInit(GPIO_Typedef *GPIOx){

	//	GPIOx->BRR= 0x00000000 ;
	//	GPIOx->BSRR= 0x00000000;
	//	GPIOx->CRH= 0x44444444 ;
	//	GPIOx->CRL= 0x44444444 ;
	//	//	GPIOx->IDR= (Read Only);
	//	GPIOx->LCKR= 0x00000000 ;
	//	GPIOx->ODR= 0x00000000 ;

	if (GPIOx == GPIOA) {
		MCAL_RCC_Reset_Clock(IOPA_RSTR_CLK, IOPA_BUS);
//		RCC->APB2RSTR |= (GPIO_PIN_2);
//		RCC->APB2RSTR &= ~(GPIO_PIN_2);
	}else if (GPIOx == GPIOB) {
		MCAL_RCC_Reset_Clock(IOPB_RSTR_CLK, IOPB_BUS);
//		RCC->APB2RSTR |= (GPIO_PIN_3);
//		RCC->APB2RSTR &= ~(GPIO_PIN_3);
	}else if (GPIOx == GPIOC) {
		MCAL_RCC_Reset_Clock(IOPC_RSTR_CLK, IOPC_BUS);
//		RCC->APB2RSTR |= (GPIO_PIN_4);
//		RCC->APB2RSTR &= ~(GPIO_PIN_4);
	}else if (GPIOx == GPIOD) {
		MCAL_RCC_Reset_Clock(IOPD_RSTR_CLK, IOPD_BUS);
//		RCC->APB2RSTR |= (GPIO_PIN_5);
//		RCC->APB2RSTR &= ~(GPIO_PIN_5);
	}else if (GPIOx == GPIOE) {
		MCAL_RCC_Reset_Clock(IOPE_RSTR_CLK, IOPE_BUS);
//		RCC->APB2RSTR |= (GPIO_PIN_6);
//		RCC->APB2RSTR &= ~(GPIO_PIN_6);
	}
}

u8 MCAL_GPIO_ReadPin(GPIO_Typedef *GPIOx, u16 PinNumber){
	u8 bit_value;
	if(((GPIOx->IDR) & PinNumber) != (u32)GPIO_PIN_RESET )
	{
		bit_value = GPIO_PIN_SET;
	}
	else{
		bit_value = GPIO_PIN_RESET;
	}
	return bit_value;
}





u16 MCAL_GPIO_ReadPort(GPIO_Typedef *GPIOx){
	u16 port_value;
	port_value = (u16)GPIOx->IDR;
	return port_value;
}

void MCAL_GPIO_WritePin(GPIO_Typedef *GPIOx, u16 PinNumber, u8 Value){

	if(Value != GPIO_PIN_RESET){

		//		GPIOx->ODR |= PinNumber;
		//		or
		GPIOx->BSRR = (u32)PinNumber;
	}
	else{

		//		GPIOx->ODR &= ~(PinNumber);
		//		or
		GPIOx->BRR = (u32)PinNumber ;
	}
}


void MCAL_GPIO_WritePort(GPIO_Typedef *GPIOx, u16 value){

	GPIOx->ODR = (u32)value;
}


void MCAL_GPIO_togglePin(GPIO_Typedef *GPIOx, u16 PinNumber){

	GPIOx->ODR ^= (PinNumber);
}

u8 MCAL_GPIO_LockPin(GPIO_Typedef *GPIOx, u16 PinNumber){

	volatile u32 flag = 1<<16;
	flag |= PinNumber;

	//	Write 1
	GPIOx->LCKR = flag;

	//	Write 0
	GPIOx->LCKR = PinNumber;

	//	Write 1
	GPIOx->LCKR = flag;

	//	Read 0
	GPIOx->LCKR = PinNumber;

	//	Read 1 (this read is optional but confirms that the lock is active)
	if(((GPIOx->LCKR) & 1<<16)){
		return GPIO_LOCK_ENABLE;
	}
	else{
		return GPIO_LOCK_ERROR;
	}
}
