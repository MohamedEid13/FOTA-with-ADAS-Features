

#ifndef INC_STM32F103C6_GPIO_DRIVER_H_
#define INC_STM32F103C6_GPIO_DRIVER_H_


#include "TYPES.h"
#include "GPIO_private.h"
#include "RCC.h"


#define NULL 0

typedef struct{

	u16 GPIO_PinNumber;			// specifies the GPIO Pins to be configured
	// this parameter can be a value of @ref GPIO_PINS_define
	u8 GPIO_Mode;					// specifies the operating mode for the selected pins
	// this parameter can be a value of @ref GPIO_MODE_define
	u8 GPIO_OutputSpeed; 			// specifies the speed for the selected pins
	// this parameter can be a value of @ref GPIO_SPEED_define
}GPIO_PinConfig_t;


//===================================================================
//@ref GPIO_PINS_define

#define GPIO_PIN_0			((u16)0x0001)
#define GPIO_PIN_1			((u16)0x0002)
#define GPIO_PIN_2			((u16)0x0004)
#define GPIO_PIN_3			((u16)0x0008)
#define GPIO_PIN_4			((u16)0x0010)
#define GPIO_PIN_5			((u16)0x0020)
#define GPIO_PIN_6			((u16)0x0040)
#define GPIO_PIN_7			((u16)0x0080)
#define GPIO_PIN_8			((u16)0x0100)
#define GPIO_PIN_9			((u16)0x0200)
#define GPIO_PIN_10			((u16)0x0400)
#define GPIO_PIN_11			((u16)0x0800)
#define GPIO_PIN_12			((u16)0x1000)
#define GPIO_PIN_13			((u16)0x2000)
#define GPIO_PIN_14			((u16)0x4000)
#define GPIO_PIN_15			((u16)0x8000)

//====================================================================
//@ref GPIO_MODE_define

#define GPIO_MODE_ANALOG			0x00000000UL	//0:Analog mode
#define GPIO_MODE_INPUT_FLO			0x00000001UL	//1:Floating input
#define GPIO_MODE_INPUT_PU			0x00000002UL	//2:Input with pull-up
#define GPIO_MODE_INPUT_PD			0x00000003UL	//3:Input with pull-down
#define GPIO_MODE_OUTPUT_PP			0x00000004UL	//4:Output with push_pull
#define GPIO_MODE_OUTPUT_OD			0x00000005UL	//5:Output with open_drain
#define GPIO_MODE_OUTPUT_AF_PP		0x00000006UL	//6:Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD		0x00000007UL	//7:Alternate function output Open_drain
#define GPIO_MODE_AF_INPUT			0x00000008U		//8: Alternate function input


//====================================================================
//@ref GPIO_SPEED_define

//00: Input mode (reset state)
//01: Output mode, max speed 10 MHz.
//10: Output mode, max speed 2 MHz.
//11: Output mode, max speed 50 MHz.

#define GPIO_SPEED_10				0x00000001UL  //1:Output mode, max speed 10 MHz.
#define GPIO_SPEED_2				0x00000002UL  //2:Output mode, max speed 2 MHz.
#define GPIO_SPEED_50				0x00000003UL  //3:Output mode, max speed 50 MHz.

//====================================================================

#define GPIO_PIN_SET		1
#define GPIO_PIN_RESET		0

// @ref GPIO_LOCK_Define
#define GPIO_LOCK_ENABLE 	1
#define GPIO_LOCK_ERROR		0
//======================================================================
//-------------------------------
// MCAL GPIO Driver APIs
//-------------------------------

/**=============================================
  * @Fn				- MCAL_GPIO_Init
  * @brief 			- Initializes the GPIOx PINy according to the specified paramters in the PinConfig
  * @param [in] 	- GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
  * @param [in] 	- PinConfig: Pointer to a GPIO_PinConfig_t structure that contains the configuration
  * 				  information for the specified GPIO PIN
  * @retval 		- None
  * Note			- STM32F103C8 MCU has GPIO A,B,C,D,E Modules, but LQFP48 package has only
  * 				  GPIO A,B and part of C/D exported as external PINS from the MCU
  * 				- It is mandatory to enable RCC clock for the corresponding GPIO PORT
  */
void MCAL_GPIO_Init(GPIO_Typedef *GPIOx, GPIO_PinConfig_t *PinConfig);


/**=============================================
  * @Fn				- MCAL_GPIO_DeInit
  * @brief 			- Resets the GPIO PORT
  * @param [in] 	- GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
  * @retval 		- None
  * Note			- None
  */

void MCAL_GPIO_DeInit(GPIO_Typedef *GPIOx);

/**=============================================
  * @Fn				- MCAL_GPIO_ReadPin
  * @brief 			- Reads Specific PIN
  * @param [in] 	- GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
  * @param [in] 	- PinNumber: Set pin number according to @ref GPIO_PINS_define
  * @retval 		- the input pin value (two values based on @ref GPIO_PIN_STATE
  * Note			- None
  */
u8 MCAL_GPIO_ReadPin(GPIO_Typedef *GPIOx, u16 PinNumber);


/**=============================================
  * @Fn				- MCAL_GPIO_ReadPort
  * @brief 			- Reads Specific PORT
  * @param [in] 	- GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
  * @retval 		- the input port value
  * Note			- None
  */

u16 MCAL_GPIO_ReadPort(GPIO_Typedef *GPIOx);

/**=============================================
  * @Fn				- MCAL_GPIO_WritePin
  * @brief 			- Write on specific pin
  * @param [in] 	- GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
  * @param [in] 	- PinNumber: Set pin number according to @ref GPIO_PINS_define
  * @param [in] 	- Value: Pin value to be written
  * @retval 		- None
  * Note			- None
  */

void MCAL_GPIO_WritePin(GPIO_Typedef *GPIOx, u16 PinNumber, u8 Value);


/**=============================================
  * @Fn				- MCAL_GPIO_WritePort
  * @brief 			- Write on specific port
  * @param [in] 	- GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
  * @param [in] 	- Value: Port value to be written
  * @retval 		- None
  * Note			- None
  */
void MCAL_GPIO_WritePort(GPIO_Typedef *GPIOx, u16 value);

/**=============================================
  * @Fn				- MCAL_GPIO_TogglePin
  * @brief 			- Toggle a specific pin
  * @param [in] 	- GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
  * @param [in] 	- PinNumber: Set pin number according to @ref GPIO_PINS_define
  * @retval 		- None
  * Note			- None
  */

void MCAL_GPIO_togglePin(GPIO_Typedef *GPIOx, u16 PinNumber);

/**=============================================
  * @Fn				- MCAL_GPIO_LockPin
  * @brief 			- The locking mechanism allows the IO configuration to be frozen
  * @param [in] 	- GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
  * @param [in] 	- PinNumber: Set pin number according to @ref GPIO_PINS_define
  * @retval 		- Ok if pin config is locked, or ERROR if pin is not locked @ref GPIO_RETURN_LOCK
  * Note			- None
  */

u8 MCAL_GPIO_LockPin(GPIO_Typedef *GPIOx, u16 PinNumber);

#endif /* INC_STM32F103C6_GPIO_DRIVER_H_ */
