
#include "TYPES.h"


/******************* Global BootLoader Data ***********************/

typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

#define APP_FLAG   *((volatile u8*)0x0800FFF0)
#define SCB_VTOR   *((volatile u32*)0xE000ED08)


int main(void)
{

	while(1)
	{
		if(APP_FLAG==0x1)
		{
			/** If Data is Ended Correctly Jump To APPlication 1 **/
			SCB_VTOR = 0x08001400; // 5 Kbyte BootLoader
			addr_to_call = *(Function_t*)(0x08001404);
			addr_to_call();
		}
		else if (APP_FLAG==0x2)
		{
			/** If Data is Ended Correctly Jump To APPlication 1 **/
			SCB_VTOR = 0x08008800; // 5 Kbyte BootLoader
			addr_to_call = *(Function_t*)(0x08008804);
			addr_to_call();
		}


	}
}
