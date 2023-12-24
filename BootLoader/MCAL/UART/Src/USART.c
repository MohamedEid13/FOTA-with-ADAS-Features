
#include "USART.h"

USART_Config_t* G_USART_Config = NULL;


void MCAL_USART_Init(USART_Typedef *USARTx,USART_Config_t* USART_Config){



	G_USART_Config = USART_Config;

	u32 PCLK , BRR;

	// enalbe clock for each uart
	if(USARTx == USART1){
		MCAL_RCC_Enable_Clock(USART1_EN_CLK, USART1_BUS);
		//RCC_EN_CLK_USART1();
	}
	else if(USARTx == USART2){
		MCAL_RCC_Enable_Clock(USART2_EN_CLK, USART2_BUS);
//		RCC_EN_CLK_USART2();
	}
	else if(USARTx == USART3){
		MCAL_RCC_Enable_Clock(USART2_EN_CLK, USART2_BUS);
//		RCC_EN_CLK_USART3();
	}

	// enable uart
	USARTx->CR1 |= 1<<13;

	//enable each tx and rx
	USARTx->CR1 |= USART_Config->USART_Mode;

	// set payload length
	USARTx->CR1 |= USART_Config->Payload_Length;

	// set parity
	USARTx->CR1 |= USART_Config->Parity;

	// set stop bits
	USARTx->CR2 |= USART_Config->StopBits;

	// set flow control
	USARTx->CR3 |= USART_Config->HwFlowCtl;

	// config Baud rate
	//	PCLK2 for UART1
	//	PCLK1 for UART2,3

	if(USARTx == USART1){
		PCLK = MCAL_RCC_GetPCLK2Freq();
	}
	else
	{
		PCLK = MCAL_RCC_GetPCLK1Freq();
	}

	BRR = USART_BBR_Register(PCLK,USART_Config->BaudRate);

	USARTx->BRR = BRR;

	//	enable / disable uart

	if(USART_Config->IRQ_EN != USART_IRQ_EN_NONE)
	{
		USARTx->CR1 |= (USART_Config->IRQ_EN) ;
		// enable NVIC
		if(USARTx == USART1){
			MCAL_NVIC_EN(USART1_IRQ);
			//NVIC_IRQ37_USART1_EN;
		}
		else if(USARTx == USART2){
			MCAL_NVIC_EN(USART2_IRQ);
			//NVIC_IRQ38_USART2_EN;
		}
		else if(USARTx == USART3){
			MCAL_NVIC_EN(USART3_IRQ);
			//NVIC_IRQ39_USART3_EN;
		}
	}

}
void MCAL_USART_DeInit(USART_Typedef* USARTx){

	if(USARTx == USART1){
		MCAL_RCC_Reset_Clock(USART1_EN_CLK, USART1_BUS);
		//RCC_Reset_USART1();
		MCAL_NVIC_Disable(USART1_IRQ);
		//NVIC_IRQ37_USART1_Disable;
	}
	else if(USARTx == USART2){
		MCAL_RCC_Reset_Clock(USART2_EN_CLK, USART2_BUS);
//		RCC_Reset_USART2();
		MCAL_NVIC_Disable(USART2_IRQ);
//		NVIC_IRQ38_USART2_Disable;
	}
	else if(USARTx == USART3){
		MCAL_RCC_Reset_Clock(USART3_EN_CLK, USART3_BUS);
//		RCC_Reset_USART3();
		MCAL_NVIC_Disable(USART3_IRQ);
//		NVIC_IRQ39_USART3_Disable;
	}
}



void MCAL_USART_SendData(USART_Typedef *USARTx , u16 *pTxBuffer,enum Polling_mechism pollingEn){

//	uint16_t *pdata;

	if(pollingEn == enable){
		while (! (USARTx->SR & 1<<7 ));
	}

	if(G_USART_Config->Payload_Length == USART_Payload_Length_9B){

		USARTx->DR = (*pTxBuffer & (u16)0x01FF);

	}
	else{

		USARTx->DR = (*pTxBuffer & (u8)0xFF);

	}
}


void MCAL_USART_Wait_TC(USART_Typedef *USARTx ){

	while(!(USARTx->SR & 1<<6));

}


void MCAL_USART_ReceiveData(USART_Typedef *USARTx, u16 *pRxBuffer,enum Polling_mechism pollingEn){

	if(pollingEn == enable){
		while(!(USARTx->SR & 1<<5));
	}

	if(G_USART_Config->Payload_Length == USART_Payload_Length_9B){

		if(G_USART_Config->Parity == USART_Parity_NONE){

			*((u16*)pRxBuffer) = USARTx->DR;
		}
		else{
			*((u16*)pRxBuffer) = ( USARTx->DR & (u8)0xFF );
		}

	}
	else{

		if(G_USART_Config->Parity == USART_Parity_NONE){

			*((u16*)pRxBuffer) = (USARTx->DR & (u8)0xFF) ;

		}else{

			*((u16*)pRxBuffer) = (USARTx->DR & (u8)0x7F);

		}
	}
}


void MCAL_USART_GPIO_Set_Pins(USART_Typedef * USARTx){

	GPIO_PinConfig_t PinCfg;

	if(USARTx == USART1){
		//PA9  Tx
		//PA10 Rx
		//PA11 CTS
		//PA12 RTS

		//PA9
		PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_OutputSpeed = GPIO_SPEED_10;
		MCAL_GPIO_Init(GPIOA , &PinCfg);

		//PA10
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_Mode = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA , &PinCfg);

		if(G_USART_Config->HwFlowCtl == USART_HwFlowCtl_CTS || G_USART_Config->HwFlowCtl == USART_HwFlowCtl_RTS_CTS ){
			//PA11
			PinCfg.GPIO_PinNumber = GPIO_PIN_11;
			PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA , &PinCfg);
		}
		if(G_USART_Config->HwFlowCtl == USART_HwFlowCtl_RTS || G_USART_Config->HwFlowCtl == USART_HwFlowCtl_RTS_CTS ){
			//PA12
			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OutputSpeed = GPIO_SPEED_10;
			MCAL_GPIO_Init(GPIOA , &PinCfg);
		}

	}
	if(USARTx == USART2){
		//PA2  Tx
		//PA3 Rx
		//PA0 CTS
		//PA1 RTS

		//PA2
		PinCfg.GPIO_PinNumber = GPIO_PIN_2;
		PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_OutputSpeed = GPIO_SPEED_10;
		MCAL_GPIO_Init(GPIOA , &PinCfg);

		//PA3
		PinCfg.GPIO_PinNumber = GPIO_PIN_3;
		PinCfg.GPIO_Mode = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA , &PinCfg);

		if(G_USART_Config->HwFlowCtl == USART_HwFlowCtl_CTS || G_USART_Config->HwFlowCtl == USART_HwFlowCtl_RTS_CTS ){
			//PA0
			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
			PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA , &PinCfg);
		}
		if(G_USART_Config->HwFlowCtl == USART_HwFlowCtl_RTS || G_USART_Config->HwFlowCtl == USART_HwFlowCtl_RTS_CTS ){
			//PA1
			PinCfg.GPIO_PinNumber = GPIO_PIN_1;
			PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OutputSpeed = GPIO_SPEED_10;
			MCAL_GPIO_Init(GPIOA , &PinCfg);
		}

	}
	if(USARTx == USART3){
		//PB10  Tx
		//PB11 Rx
		//PB13 CTS
		//PB14 RTS

		//PB10
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_OutputSpeed = GPIO_SPEED_10;
		MCAL_GPIO_Init(GPIOB , &PinCfg);

		//PB11
		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_Mode = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOB , &PinCfg);

		if(G_USART_Config->HwFlowCtl == USART_HwFlowCtl_CTS || G_USART_Config->HwFlowCtl == USART_HwFlowCtl_RTS_CTS ){
			//PB13
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB , &PinCfg);
		}
		if(G_USART_Config->HwFlowCtl == USART_HwFlowCtl_RTS || G_USART_Config->HwFlowCtl == USART_HwFlowCtl_RTS_CTS ){
			//PB14
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OutputSpeed = GPIO_SPEED_10;
			MCAL_GPIO_Init(GPIOB , &PinCfg);
		}

	}

}


void MCAL_USART_SendString(USART_Typedef* USARTx, u8 *str, u8 str_len){
	// if str_len != 0 send with predefined length
	if(str_len){
		u8 i;
		for(i = 0; i < str_len; i++){
			MCAL_USART_SendData(USARTx, (u16*)(&(str[i])), enable);
		}
	}
	else{
		// if str_len = 0 send until we find null character '\0'
		while(*str){
			MCAL_USART_SendData(USARTx, (u16*)str, enable);
			MCAL_USART_Wait_TC(USARTx);
			str++;
		}
	}
}


void USART1_IRQHandler(void){

	G_USART_Config->P_IRQ_CallBack ();
}

void USART2_IRQHandler(void){

	G_USART_Config->P_IRQ_CallBack ();
}

void USART3_IRQHandler(void){

	G_USART_Config->P_IRQ_CallBack ();
}

