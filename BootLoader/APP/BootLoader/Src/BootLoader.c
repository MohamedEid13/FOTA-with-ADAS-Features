#include "RCC.h"
#include "GPIO.h"
#include "USART.h"
#include "TYPES.h"
#include "FPEC_interface.h"
#include "Parser_interface.h"
#include "BootLoader_Config.h"
#include "BootLoader.h"


/******************* Global BootLoader Data ***********************/
static volatile u8  u8RecBuffer[100]   ;
static volatile u8  u8RecCounter     = 0;
static volatile u8  u8BLWriteReq     = 1;


typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

#define APP_FLAG   *((volatile u8*)FLAG_ADDRESS)

#define SCB_VTOR   *((volatile u32*)0xE000ED08)


void BootLoader_UART_ISR(void);

/***************************************************************************/



void BootLoader_Init(void)
{
	/*Set the Vector Table at the Begin of the APP */
	//SCB_VTOR = 0x08001404;

	/* Enable Periherals Clock */

	MCAL_RCC_Enable_Clock(IOPC_EN_CLK, IOPC_BUS);
	MCAL_RCC_Enable_Clock(AFIO_EN_CLK, AFIO_BUS);
	MCAL_RCC_Enable_Clock(IOPA_EN_CLK, IOPA_BUS);

	/* UART Configuration */

	USART_Config_t Bootloader_Uart;
	Bootloader_Uart.BaudRate = USART_BaudRate_115200;
	Bootloader_Uart.HwFlowCtl = USART_HwFlowCtl_NONE;
	Bootloader_Uart.IRQ_EN = USART_IRQ_EN_RXNEIE;
	Bootloader_Uart.P_IRQ_CallBack = BootLoader_UART_ISR;
	Bootloader_Uart.Parity = USART_Parity_NONE;
	Bootloader_Uart.Payload_Length = USART_Payload_Length_8B;
	Bootloader_Uart.StopBits = USART_StopBits_1;
	Bootloader_Uart.USART_Mode = USART_Mode_Tx_RX;

	MCAL_USART_Init(USART1, &Bootloader_Uart);
	MCAL_USART_GPIO_Set_Pins(USART1);
}

void BootLoader_UART_ISR(void)
{
	MCAL_USART_SendString(USART1, "Ok", 3);

	MCAL_USART_ReceiveData(USART1,&u8RecBuffer[u8RecCounter],enable);

	if(u8RecBuffer[u8RecCounter] == '\n')
	{

		if (u8BLWriteReq == 1 && APP_FLAG==0x1)
		{
			FPEC_voidErase_SecondAPPArea();
			u8BLWriteReq = 0;
		}
		else if (u8BLWriteReq == 1 && APP_FLAG==0x2)
		{
			FPEC_voidErase_FirstAPPArea();
			u8BLWriteReq = 0;
		}

		if(Parser_voidParseRecord(u8RecBuffer)==1)
		{
			MCAL_USART_SendString(USART1, "Ok", 3);

			if(u8RecBuffer[8]=='1')
			{
				MCAL_USART_SendString(USART1, "Ok", 3);
				if(APP_FLAG==0x1)
				{
					FPEC_voidFlashPageErase(63);
					u16 FLag = 0x2 ;
					FPEC_voidFlashWrite(FLAG_ADDRESS , &FLag , 1);

				}
				else if (APP_FLAG==0x2)
				{
					FPEC_voidFlashPageErase(63);
					u16 FLag = 0x1;
					FPEC_voidFlashWrite(FLAG_ADDRESS , &FLag , 1);

				}
			}
		}
		else
		{
			MCAL_USART_SendString(USART1, "error", 6);
			/*
			if(APP_FLAG==0x1)
			{
				FPEC_voidErase_SecondAPPArea();
			}
			else if(APP_FLAG==0x2)
			{
				FPEC_voidErase_FirstAPPArea();
			}
			else
			{
				/* Do Nothing */
			//}
			// */

		}

		u8RecCounter=0; //Zero the counter to burn a new record
	}
	else
	{
		u8RecCounter++;
	}
}
