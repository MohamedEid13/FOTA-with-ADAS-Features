
#include "NVIC.h"


void MCAL_NVIC_EN(u8 IRQ){


	if((IRQ >= WWDG_IRQ) && (IRQ <= I2C1_EV_IRQ) ){
		NVIC_ISER0 |= (1 << IRQ) ;
	}
	else if((IRQ >= I2C1_ER_IRQ) && (IRQ <= CAN2_TX_IRQ) )
	{
		NVIC_ISER1 |= (1 << (IRQ-32)) ;
	}
	else if(IRQ >= CAN2_RX0_IRQ && IRQ <= OTG_FS_IRQ )
	{
		NVIC_ISER2 |= (1 << (IRQ-64)) ;
	}
}

void MCAL_NVIC_Disable(u8 IRQ){


	if(IRQ >= WWDG_IRQ && IRQ <= I2C1_EV_IRQ ){
		NVIC_ICER0 |= (1 << IRQ) ;
	}
	else if(IRQ >= I2C1_ER_IRQ && IRQ <= CAN2_TX_IRQ )
	{
		NVIC_ICER1 |= (1 << (IRQ-32)) ;
	}
	else if(IRQ >= CAN2_RX0_IRQ && IRQ <= OTG_FS_IRQ )
	{
		NVIC_ICER2 |= (1 << (IRQ-64)) ;
	}


}

//void MCAL_NVIC_EN_Pendding(uint8_t IRQ){
//
//	if(IRQ >= WWDG && IRQ <= I2C1_EV ){
//		NVIC_ISPR0 |= (1 << IRQ) ;
//	}
//	else if(IRQ >= I2C1_ER && IRQ <= CAN2_TX )
//	{
//		NVIC_ISPR1 |= (1 << IRQ) ;
//	}
//	else if(IRQ >= CAN2_RX0 && IRQ <= OTG_FS )
//	{
//		NVIC_ISPR2 |= (1 << IRQ) ;
//	}
//}
//
//void MCAL_NVIC_Disable__Pendding(uint8_t IRQ){
//
//	if(IRQ >= WWDG && IRQ <= I2C1_EV ){
//		NVIC_ICPR0 |= (1 << IRQ) ;
//	}
//	else if(IRQ >= I2C1_ER && IRQ <= CAN2_TX )
//	{
//		NVIC_ICPR1 |= (1 << IRQ) ;
//	}
//	else if(IRQ >= CAN2_RX0 && IRQ <= OTG_FS )
//	{
//		NVIC_ICPR2 |= (1 << IRQ) ;
//	}
//}
//
//
//uint8_t MCAL_NVIC_Read_Active_Flag(uint8_t IRQ){
//
//	uint8_t Active_Flag ;
//
//	if(IRQ >= WWDG && IRQ <= I2C1_EV )
//	{
//		Active_Flag = ((NVIC_IABR0 & (1<<IRQ)) >> IRQ);
//	}
//	else if(IRQ >= I2C1_ER && IRQ <= CAN2_TX )
//	{
//		Active_Flag = ((NVIC_IABR1 & (1<<IRQ)) >> IRQ);
//	}
//	else if(IRQ >= CAN2_RX0 && IRQ <= OTG_FS )
//	{
//		Active_Flag = ((NVIC_IABR2 & (1<<IRQ)) >> IRQ);
//	}
//
//	return Active_Flag ;
//}
//
//void MCAL_SCB_Select_Mode(uint8_t Mode){
//
//	uint32_t key = 0xFA050000 ;
//
//	SCB_AIRCR = ((key & 0xFFFF0000) | ((Mode & 0xFF) << 8)) ;
//
//}
//
//void MCA_NVIC_set_priority(uint8_t IRQ , uint8_t group ,uint8_t subGroup){
//
//	uint8_t mode ;
//
//	uint8_t conValue ;
//
//	uint8_t *temp_ptr  =   (uint8_t*)NVIC_IPR0 ;
//	temp_ptr = temp_ptr + IRQ ;
//
//	mode = (uint8_t)(SCB_AIRCR >> 8) ;
//
//	mode = (mode & 0x00000111) ;
//
//	subGroup = subGroup << 4 ;
//
//
//	switch(mode){
//
//		case SCB_GROUP16_SUB0 :
//			conValue = group << 4 ;
//			break ;
//
//		case SCB_GROUP8_SUB2 :
//			conValue = ((group << 5 ) | subGroup ) ;
//			break ;
//
//		case SCB_GROUP4_SUB4 :
//			conValue = ((group << 6) | subGroup ) ;
//			break ;
//
//		case SCB_GROUP2_SUB8 :
//			conValue = ((group << 7) | subGroup ) ;
//			break ;
//		case SCB_GROUP0_SUB16 :
//			conValue = subGroup ;
//			break ;
//	}
//
//	*temp_ptr = conValue ;
//
//}

