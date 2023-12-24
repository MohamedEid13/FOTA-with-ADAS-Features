#ifndef FPEC_INTERFACE
#define FPEC_INTERFACE


/**=============================================
  * @Fn				- FPEC_voidEraseAppArea
  * @brief 			- Erase ALL APPs pages From Flash
  * @param [in] 	- None
  * Note			- Supported for STM32Fx MCUs Family only
  */
void FPEC_voidEraseAppArea(void);


/**=============================================
  * @Fn				- FPEC_voidFlashPageErase
  * @brief 			- Erase any selected pages From Flash
  * @param [in] 	- Copy_u8PageNumber : variable which indicate for page number to be Erased
  * Note			- Supported for STM32Fx MCUs Family only
 */
void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber);

/**=============================================
  * @Fn				- FPEC_voidFlashWrite
  * @brief 			- write data on a Flash memory
  * @param [in] 	- Copy_u32Address : Address of Data that will be written in flash
  * @param [in] 	- Copy_u16Data    : pointer of Data that will be written in flash
  * @param [in]     - Copy_u8Length   : Length of Data
  * Note			- Supported for STM32Fx MCUs Family only
  */

void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length);


/**=============================================
  * @Fn				- FPEC_voidErase_SecondAPPArea
  * @brief 			- Erase Application two on only from Flash
  * @param [in] 	- None
  * Note			- Supported for STM32Fx MCUs Family only
  */
void FPEC_voidErase_SecondAPPArea(void);

/**=============================================
  * @Fn				- FPEC_voidEraseAppArea
  * @brief 			- Erase Application one only from Flash
  * @param [in] 	- None
  * Note			- Supported for STM32Fx MCUs Family only
  */
void FPEC_voidErase_FirstAPPArea(void);


#endif
