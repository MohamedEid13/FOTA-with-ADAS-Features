

#ifndef PARSER_INTERFACE_H_
#define PARSER_INTERFACE_H_


/**=============================================
  * @Fn				- Parser_voidParseRecord
  * @brief 			- Parse the record Based on It's Record type and Burn it in Flash
  * @param [in] 	- Copy_u8BufData : Pointer to DataBuffer
  * return          - it return '1'  if the data flashed or '0' if not
  * Note			- Supported for STM32Fx MCUs Family only
 */

u8 Parser_voidParseRecord(u8* Copy_u8BufData);

#endif /* PARSER_INTERFACE_H_ */
