#ifndef FPEC_INTERFACE
#define FPEC_INTERFACE

#include "STD_TYPES.h"
#include "BIT_MATH.h"

void FPEC_voidEraseAppArea(void);
	
void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber);

void FPEC_voidFlashWrite(u32 Copy_u32Address, volatile u16* Copy_u16Data, u8 Copy_u8Length);

void FPEC_voidErase_SecondAPPArea(void);

void FPEC_voidErase_FirstAPPArea(void);
#endif
