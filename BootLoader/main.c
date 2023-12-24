#include "RCC.h"
#include "GPIO.h"
#include "USART.h"
#include "TYPES.h"
#include "FPEC_interface.h"
#include "Parser_interface.h"
//#include "BootLoader.h"


void BootLoader_UART_ISR(void)
//{
	//	MCAL_USART_SendString(USART1, "Ok", 3);
	//
	//	MCAL_USART_ReceiveData(USART1,&u8RecBuffer[u8RecCounter],enable);
	//
	//	if(u8RecBuffer[u8RecCounter] == '\n')
	//	{
	//
	//		if (u8BLWriteReq == 1 && APP_FLAG==0x1)
	//		{
	//			FPEC_voidErase_SecondAPPArea();
	//			u8BLWriteReq = 0;
	//		}
	//		else if (u8BLWriteReq == 1 && APP_FLAG==0x2)
	//		{
	//			FPEC_voidErase_FirstAPPArea();
	//			u8BLWriteReq = 0;
	//		}
	//
	//		if(Parser_voidParseRecord(u8RecBuffer)==1)
	//		{
	//			MCAL_USART_SendString(USART1, "Ok", 3);
	//
	//			if(u8RecBuffer[8]=='1')
	//			{
	//				MCAL_USART_SendString(USART1, "Ok", 3);
	//				if(APP_FLAG==0x1)
	//				{
	//					FPEC_voidFlashPageErase(63);
	//					u16 FLag = 0x2 ;
	//					FPEC_voidFlashWrite(FLAG_ADDRESS , &FLag , 1);
	//
	//				}
	//				else if (APP_FLAG==0x2)
	//				{
	//					FPEC_voidFlashPageErase(63);
	//					u16 FLag = 0x1;
	//					FPEC_voidFlashWrite(FLAG_ADDRESS , &FLag , 1);
	//
	//				}
	//			}
	//		}
	//		else
	//		{
	//			MCAL_USART_SendString(USART1, "error", 6);
	//			/*
	//			if(APP_FLAG==0x1)
	//			{
	//				FPEC_voidErase_SecondAPPArea();
	//			}
	//			else if(APP_FLAG==0x2)
	//			{
	//				FPEC_voidErase_FirstAPPArea();
	//			}
	//			else
	//			{
	//				/* Do Nothing */
	//			//}
	//			// */
	//
	//		}
	//
	//		u8RecCounter=0; //Zero the counter to burn a new record
	//	}
	//	else
	//	{
	//		u8RecCounter++;
	//	}
//}

int main(void)
{

	//BootLoader_Init();
	/* Enable Periherals Clock */

	MCAL_RCC_Enable_Clock(IOPC_EN_CLK, IOPC_BUS);
	MCAL_RCC_Enable_Clock(AFIO_EN_CLK, AFIO_BUS);
	MCAL_RCC_Enable_Clock(IOPA_EN_CLK, IOPA_BUS);

	/* UART Configuration */

	USART_Config_t Bootloader_Uart;
	Bootloader_Uart.BaudRate = USART_BaudRate_9600;
	Bootloader_Uart.HwFlowCtl = USART_HwFlowCtl_NONE;
	Bootloader_Uart.IRQ_EN = USART_IRQ_EN_NONE;
	Bootloader_Uart.P_IRQ_CallBack = BootLoader_UART_ISR;
	Bootloader_Uart.Parity = USART_Parity_NONE;
	Bootloader_Uart.Payload_Length = USART_Payload_Length_8B;
	Bootloader_Uart.StopBits = USART_StopBits_1;
	Bootloader_Uart.USART_Mode = USART_Mode_Tx_RX;

	MCAL_USART_Init(USART1, &Bootloader_Uart);
	MCAL_USART_GPIO_Set_Pins(USART1);

	GPIO_PinConfig_t LED_13 ;
	LED_13.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	LED_13.GPIO_OutputSpeed=GPIO_SPEED_10;
	LED_13.GPIO_PinNumber=GPIO_PIN_13;

	MCAL_GPIO_Init(GPIOC,&LED_13);
	u32 localCounter=0;
	while(1)
	{
		u8 securityAccess = 0; // Flag for security access

		// Sending services 32, sub-services 01, and routine AA00
		u8 cmd1[] = {0x31, 0x01, 0xAA, 0x00};
		MCAL_USART_SendData(USART1,cmd1, enable);

		// Receiving response
		u8 response[4];
		MCAL_USART_ReceiveData(USART1,response,disable);

		if (response[0] == 0x73 && response[1] == 0x31 && response[2] == 0x33) {
			// Didn't have security access
			// Handle accordingly
		} else if (response[0] == 0x71 && response[1] == 0x01 && response[2] == 0xAA && response[3] == 0x00) {
			// Have security access, LED is on
			MCAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
			securityAccess = 1; // Set security access flag
		}

		// Handling 2701 command
		if (securityAccess) {
			u8 cmd2[] = {0x27, 0x01};
			MCAL_USART_SendData(USART1,cmd2, enable);

			// Generating and sending random bytes
			u8 randomBytes[4] = {0x01, 0x02, 0x03, 0x04}; // Replace with actual random bytes
			u8 encryptedBytes[4];
			encryptData(randomBytes, encryptedBytes, sizeof(randomBytes));

			// Sending encrypted bytes
			u8 cmd3[] = {0x27, 0x02};
			MCAL_USART_SendData(USART1,cmd3, enable);
			MCAL_USART_SendData(USART1,encryptedBytes, enable);

			// Receiving calculated bytes by Mc
			u8 calculatedBytes[4]; // Replace with actual calculated bytes
			MCAL_USART_ReceiveData(USART1,calculatedBytes, disable);

			// Checking if the received bytes match the calculated bytes
			int match = 1;
			for (int i = 0; i < sizeof(calculatedBytes); i++) {
				if (calculatedBytes[i] != encryptedBytes[i]) {
					match = 0;
					break;
				}
			}

			// Displaying result on LCD
			if (match)
			{
				u8 lcdData[] = {0x67, 0x02};
				displayOnLCD(lcdData, sizeof(lcdData));
			}
			else
			{
				u8 lcdData[] = {0x7F, 0x27, 0x35};
				displayOnLCD(lcdData, sizeof(lcdData));
			}
		}


	}

}

