
#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

//GPIO Address
//A,B fully included in LQFP48 Package
#define GPIOA_BASE								0x40010800
#define GPIOB_BASE								0x40010C00
//C,D partial included in LQFP48 Package
#define GPIOC_BASE								0x40011000
#define GPIOD_BASE								0x40011400
//E not included in LQFP48 Package
#define GPIOE_BASE								0x40011800

//GPIO Registers
typedef struct{
	volatile u32 CRL ;
	volatile u32 CRH ;
	volatile u32 IDR ;
	volatile u32 ODR ;
	volatile u32 BSRR;
	volatile u32 BRR ;
	volatile u32 LCKR ;
}GPIO_Typedef;

//GPIO Instant
#define GPIOA			((GPIO_Typedef *) GPIOA_BASE)
#define GPIOB           ((GPIO_Typedef *) GPIOB_BASE)
#define GPIOC   		((GPIO_Typedef *) GPIOC_BASE)
#define GPIOD 			((GPIO_Typedef *) GPIOD_BASE)
#define GPIOE			((GPIO_Typedef *) GPIOE_BASE)

#endif /* GPIO_PRIVATE_H_ */
