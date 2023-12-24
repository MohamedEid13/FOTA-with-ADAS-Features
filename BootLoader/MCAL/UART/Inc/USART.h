
#ifndef INC_STM32F103C6_USART_DRIVER_H_
#define INC_STM32F103C6_USART_DRIVER_H_

#include "GPIO.h"
#include "RCC.h"
#include "NVIC.h"
#include "TYPES.h"
#include "USART_private.h"

typedef struct {

	u8 USART_Mode;				// to enable TX and RX
									//@ref USART_Mode_define

	u32 BaudRate;				// to set baudrate
									//@ref USART_BaudRate_define

	u8	Payload_Length;			//number of data bits
									//@ref USART_Payload_Length_define

	u8 Parity;					//parity mode
									//@ref USART_Parity_define

	u8 StopBits; 				//number of stop bits
									//@ref USART_StopBits_define

	u8 HwFlowCtl;				//hardware flow control enable or disable
									//@ref USART_HwFlowCtl_define

	u8 IRQ_EN;					//En or Disable uart Irq tx/rx
									//@ref USART_IRQ_EN_define

	void(* P_IRQ_CallBack)(void); 	//set the c function() which will be called once the Irq happen

}USART_Config_t;

//=========================================================================
//Reference Macros

//@ref USART_Mode_define
#define USART_Mode_Tx			(u32)(1<<3)
#define USART_Mode_Rx			(u32)(1<<2)
#define USART_Mode_Tx_RX		((u32)(1<<2 | 1<<3))

//@ref USART_BaudRate_define
#define USART_BaudRate_2400			2400
#define USART_BaudRate_9600			9600
#define USART_BaudRate_19200		19200
#define USART_BaudRate_57600		57600
#define USART_BaudRate_115200		115200
#define USART_BaudRate_230400		230400
#define USART_BaudRate_460800		460800
#define USART_BaudRate_921600		921600
#define USART_BaudRate_2250000		2250000
#define USART_BaudRate_4500000		4500000

//@ref USART_Payload_Length_define
#define USART_Payload_Length_8B		(u32)(0)
#define USART_Payload_Length_9B		(u32)(1<<12)

//@ref USART_Parity_define
#define USART_Parity_NONE			(u32)(0)
#define USART_Parity_EVEN			(u32)(1<<10)
#define USART_Parity_ODD			((u32)(1<<9 | 1<<10))

//@ref USART_StopBits_define
#define USART_StopBits_half			(u32)(1<<12)
#define USART_StopBits_1			(u32)(0)
#define USART_StopBits_1_half		(u32)(3<<12)
#define USART_StopBits_2			(u32)(2<<12)

//@ref USART_HwFlowCtl_define
#define USART_HwFlowCtl_NONE		(u32)(0)
#define USART_HwFlowCtl_CTS			(u32)(1<<9)
#define USART_HwFlowCtl_RTS			(u32)(1<<8)
#define USART_HwFlowCtl_RTS_CTS		((u32)(1<<8 |1<<9))

//@ref USART_IRQ_EN_define
#define USART_IRQ_EN_NONE			(u32)(0)
#define USART_IRQ_EN_TXE			(u32)(1<<7) 	//Transmit data register empty
#define USART_IRQ_EN_TC				(u32)(1<<6) 	//Transmission complete
#define USART_IRQ_EN_RXNEIE			(u32)(1<<5)	//Received data ready to be read & Overrun error detected
#define USART_IRQ_EN_PE				(u32)(1<<8)	//Parity error

enum Polling_mechism{
	enable,
	disable
};


#define USARTDIV(_PCLK_,_BAUD_)   				(u32) (_PCLK_ / (16 * _BAUD_) )
#define USARTDIV_MUL100(_PCLK_,_BAUD_)   		(u32) ( (25 * _PCLK_) / (4 * _BAUD_))
#define Mantissa(_PCLK_,_BAUD_)   				(u32) (USARTDIV(_PCLK_,_BAUD_))
#define Mantissa_MUL100(_PCLK_,_BAUD_)			(u32) (USARTDIV(_PCLK_,_BAUD_) * 100)
#define DIV_Fraction(_PCLK_,_BAUD_)				(u32) (((USARTDIV_MUL100(_PCLK_,_BAUD_) - Mantissa_MUL100(_PCLK_,_BAUD_)) * 16 ) / 100 )
#define USART_BBR_Register(_PCLK_,_BAUD_)		( ( Mantissa(_PCLK_,_BAUD_) )<<4) | ( ( DIV_Fraction(_PCLK_,_BAUD_) ) & 0xF )


//==================================================================================
//					                   API                                         //
//==================================================================================

/**=============================================
  * @Fn				- MCAL_USART_Init
  * @brief 			- Initializes UART
  * @param [in] 	- USARTx: Pointer to the USART peripheral instance, where x can be (1..3 depending on device used)
  * @param [in] 	- USART_Config: Pointer to the UART configuration
  * @retval 		- None
  * Note			- Support for now asynchronous mode and clock 8MHZ
  */
void MCAL_USART_Init(USART_Typedef *USARTx,USART_Config_t* USART_Config);

/**=============================================
  * @Fn				- MCAL_USART_DeInit
  * @brief 			- DeInitializes UART
  * @param [in] 	- USARTx: Pointer to the USART peripheral instance, where x can be (1..3 depending on device used)
  * @retval 		- None
  * Note			- Reset the model by RCC
  */
void MCAL_USART_DeInit(USART_Typedef *USARTx);

/**=============================================
  * @Fn				- MCAL_USART_GPIO_Set_Pins
  * @brief 			- Initializes GPIO pins
  * @param [in] 	- USARTx: Pointer to the USART peripheral instance, where x can be (1..3 depending on device used)
  * @retval 		- None
  * Note			- Called automatically at the end of MCAL_UART_Init()
  */

void MCAL_USART_GPIO_Set_Pins(USART_Typedef *USARTx);

/**=============================================
  * @Fn				- MCAL_USART_SendData
  * @brief 			- Send buffer on UART
  * @param [in] 	- USARTx	: Pointer to the USART peripheral instance, where x can be (1..3 depending on device used)
  * @param [in] 	- pTxBuffer	: Buffer to be transmitted
  * @param [in] 	- PollingEn	: Enable or disable polling
  * @retval 		- None
  * Note			- Should initialize UART first
  * 				When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
  * 				the value written in the MSB(bit 7 or bit 8 depending on the data length) has no effect
  * 				because it is replaced by the parity.
  * 				When receiving with the parity enabled, the value read in the MSB bit is the received parity bit
  */

void MCAL_USART_SendData(USART_Typedef*  USARTx , u16 *pTxBuffer,enum Polling_mechism pollingEn);


/**=============================================
  * @Fn				- MCAL_USART_SendString
  * @brief 			- Send string on UART
  * @param [in] 	- USARTx	: Pointer to the USART peripheral instance, where x can be (1..3 depending on device used)
  * @param [in] 	- str		: Pointer to the string to be transmitted
  * @param [in] 	- str_len	: Length of string to be transmitted (0 = send until you find null '\0')
  * @retval 		- None
  * Note			- Should initialize UART first
  * 				Uses Polling Mechanism
  */

void MCAL_USART_SendString(USART_Typedef* USARTx, u8 *str, u8 str_len);

/**=============================================
  * @Fn				- MCAL_USART_ReceiveData
  * @brief 			- Receive buffer from UART
  * @param [in] 	- USARTx	: Pointer to the USART peripheral instance, where x can be (1..3 depending on device used)
  * @param [in] 	- pRxBuffer	: Buffer to be received
  * @param [in] 	- PollingEn	: Enable or disable polling
  * @retval 		- None
  * Note			- Should initialize UART first
  * 				When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
  * 				the value written in the MSB(bit 7 or bit 8 depending on the data length) has no effect
  * 				because it is replaced by the parity.
  * 				When receiving with the parity enabled, the value read in the MSB bit is the received parity bit
  */
void MCAL_USART_ReceiveData(USART_Typedef* USARTx, u16 *pRxBuffer,enum Polling_mechism pollingEn);


/**=============================================
  * @Fn				- MCAL_USART_Wait_TC
  * @brief 			- Waits until transmission is completed by polling on TC flag
  * @param [in] 	- USARTx: Pointer to the USART peripheral instance, where x can be (1..3 depending on device used)
  * @retval 		- None
  * Note			- None
  */

void MCAL_USART_Wait_TC(USART_Typedef *USARTx);




#endif /* INC_STM32F103C6_USART_DRIVER_H_ */
