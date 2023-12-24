/*** Includes ***/
#include "TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
#include "Parser_interface.h"
#include "Parse_Config.h"

/*** Global Variables ***/
u16 Data[100] = {0};
u32 Address= Flash_StartADDRESS;

/***************************************************/


/*** Static Functions Prototypes ***/
static u8 AsciToHex(u8 Copy_u8Asci);
static u8 Parse_voidCheckSum(u8* Copy_u8BufData,u8 Copy_u8DataLength);
static u8 ParseData(u8* Copy_u8BufData);
static u8 ParseUpperAddress(u8* Copy_u8BufData);
/***************************************************/

/*** Implementations ***/
static u8 AsciToHex(u8 Copy_u8Asci)
{
	u8 Result;
	if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) ) /* Characters from 0 to 9 */
	{
		Result = Copy_u8Asci - 48;
	}

	else
	{
		Result = Copy_u8Asci - 55; 			/* A B C D E F characters */
	}

	return Result;
}



static u8 Parse_voidCheckSum(u8* Copy_u8BufData,u8 Copy_u8DataLength){

	u8 CheckSumLow;
	u8 CheckSumHigh;
	u8 CheckSum;

	u8 LowNibble;
	u8 HighNibble;
	u8 DataByte;

	u32 sum = 0;
	u8 ClaculatedSum;

	CheckSumHigh = AsciToHex(Copy_u8BufData[9+(Copy_u8DataLength*2)]);
	CheckSumLow = AsciToHex(Copy_u8BufData[9+(Copy_u8DataLength*2)+1]);
	CheckSum = (CheckSumHigh<<4) | CheckSumLow;

	for(u8 Local_u8Counter=1;Local_u8Counter<(9+(Copy_u8DataLength*2));Local_u8Counter+=2){

		HighNibble = AsciToHex(Copy_u8BufData[Local_u8Counter]);
		LowNibble = AsciToHex(Copy_u8BufData[Local_u8Counter+1]);
		DataByte = (HighNibble<<4) | LowNibble;

		sum += DataByte;
	}

	ClaculatedSum = (~((u8)sum))+1;

	if(ClaculatedSum == CheckSum){
		return VALID;
	}
	else{
		return NOTVALID;
	}
}

static u8 ParseData(u8* Copy_u8BufData)
{
	u8 DigitLow,DigitHigh,CC,Local_u8Counter;
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	u8 DataCounter = 0;

	/* Get Character Count */
	DigitHigh = AsciToHex (Copy_u8BufData[1]);
	DigitLow  = AsciToHex (Copy_u8BufData[2]);
	CC        = (DigitHigh<<4) | DigitLow ;

	if(Parse_voidCheckSum(Copy_u8BufData,CC) == 0){

		return NOTVALID;
	}
	else{
		/* Get Address */
		DataDigit0 = AsciToHex (Copy_u8BufData[3]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4]);
		DataDigit2 = AsciToHex (Copy_u8BufData[5]);
		DataDigit3 = AsciToHex (Copy_u8BufData[6]);

		/* Clear Low Part of Address */
		Address = Address & 0xFFFF0000;
		Address = Address | (DataDigit3) | (DataDigit2 << 4) | (DataDigit1 << 8) | (DataDigit0<<12);

		/* CC/2 Because We Send Half Word */
		for (Local_u8Counter=0;Local_u8Counter<CC/2; Local_u8Counter++)
		{
			DataDigit0 = AsciToHex (Copy_u8BufData[4*Local_u8Counter+9 ]);
			DataDigit1 = AsciToHex (Copy_u8BufData[4*Local_u8Counter+10]);
			DataDigit2 = AsciToHex (Copy_u8BufData[4*Local_u8Counter+11]);
			DataDigit3 = AsciToHex (Copy_u8BufData[4*Local_u8Counter+12]);

			Data[DataCounter] = (DataDigit3 << 8) | (DataDigit2 << 12) | (DataDigit1) | (DataDigit0<<4);
			DataCounter++;
		}

		FPEC_voidFlashWrite(Address,Data,CC/2);	

		return VALID;
	}
}

static u8 ParseUpperAddress(u8* Copy_u8BufData)
{
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;

	if(Parse_voidCheckSum(Copy_u8BufData,2) == 0){

		return NOTVALID;
	}
	else{
		/* Get Address */
		DataDigit0 = AsciToHex (Copy_u8BufData[3]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4]);
		DataDigit2 = AsciToHex (Copy_u8BufData[5]);
		DataDigit3 = AsciToHex (Copy_u8BufData[6]);

		/* Clear high Part of Address */
		Address = Address & (u32)0x0000FFFF;
		Address = Address | (u32)((u32)(DataDigit3 << 28) | (u32)(DataDigit2 << 24) | (u32)(DataDigit1 << 20) | (u32)(DataDigit0 << 16));

		return VALID;
	}
}


u8 Parser_voidParseRecord(u8* Copy_u8BufData)
{
	switch (Copy_u8BufData[8])
	{
	case '0': return(ParseData(Copy_u8BufData)); break;
	case '4': return(ParseUpperAddress(Copy_u8BufData)); break;
	case '1': return(Parse_voidCheckSum(Copy_u8BufData,0));break;
	case '5': return(Parse_voidCheckSum(Copy_u8BufData,4));break;
	}
	return NOTVALID;
}
