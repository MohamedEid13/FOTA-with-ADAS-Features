/*** Includes ***/

#include "TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"


/***** Functions Implementation ***/


void FPEC_voidErase_FirstAPPArea(void)
{
	u8 Local_u8Counter;

	for (Local_u8Counter=FIRSTAPP_STARTPAGE;Local_u8Counter<FIRSTAPP_ENDPAGE;Local_u8Counter++)
	{
		FPEC_voidFlashPageErase(Local_u8Counter);
	}
}


void FPEC_voidErase_SecondAPPArea(void)
{
	u8 Local_u8Counter;

	for (Local_u8Counter=SECONDAPP_STARTPAGE;Local_u8Counter<SECONDAPP_ENDPAGE;Local_u8Counter++)
	{
		FPEC_voidFlashPageErase(Local_u8Counter);
	}
}



void FPEC_voidEraseAppArea(void)
{
	u8 Local_u8Counter;
	
	for (Local_u8Counter=FIRSTAPP_STARTPAGE;Local_u8Counter<Flash_MAXPAGE;Local_u8Counter++)
	{
		FPEC_voidFlashPageErase(Local_u8Counter);
	}
}


void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber)
{
	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,BSY) == 1);

	/* Check if FPEC is locked or not */
	if ( GET_BIT(FPEC->CR,LOCK) == 1)
	{
		FPEC -> KEYR = KEY_1;
		FPEC -> KEYR = KEY_2;
	}
	
	/* Page Erase Operation */
	SET_BIT(FPEC->CR,PER);

	/* Write Page address */
	FPEC->AR = (u32)(Copy_u8PageNumber * 1024) + 0x08000000 ;

	/* Start operation */
	SET_BIT(FPEC->CR,STRT);

	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,BSY) == 1);

	/* EOP */
	SET_BIT(FPEC->SR,EOP);
	CLR_BIT(FPEC->CR,PER);
}



void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length)
{
	u8 Local_u8Counter;
	 u16 Local_u16Temp;

	while (GET_BIT(FPEC->SR,BSY) == 1);

	/* Check if FPEC is locked or not */
	if ( /* FPEC_CR->BitAccess.LOCK == 1 */ GET_BIT(FPEC->CR,LOCK) == 1 )
	{
		FPEC -> KEYR = KEY_1;
		FPEC -> KEYR = KEY_2;
	}
	
	
	for (Local_u8Counter = 0; Local_u8Counter< Copy_u8Length; Local_u8Counter++)
	{
		/* Write Flash Programming */
		SET_BIT(FPEC->CR,PG);

		/* Half word operation */
		Local_u16Temp = Copy_u16Data[Local_u8Counter];
		*((volatile u16*)Copy_u32Address) = Copy_u16Data[Local_u8Counter];
		Copy_u32Address += 2 ;

		/* Wait Busy Flag */
		while (GET_BIT(FPEC->SR,BSY) == 1);
	
		/* EOP */
		SET_BIT(FPEC->SR,EOP);
		CLR_BIT(FPEC->CR,PG);
	}

}
