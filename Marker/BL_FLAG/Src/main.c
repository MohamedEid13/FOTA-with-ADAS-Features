
#include "FPEC_interface.h"

int main(void)
{
	volatile u16 FLag = 0x01 ;
	FPEC_voidFlashWrite(0x0800FFF0 , &FLag , 1);
}
