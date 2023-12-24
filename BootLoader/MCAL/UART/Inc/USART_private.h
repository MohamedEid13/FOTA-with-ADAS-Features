

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

//UART1 Address
#define USART1_BASE							 	0x40013800

//UART2 Address
#define USART2_BASE							 	0x40004400

//UART3 Address
#define USART3_BASE							 	0x40004800

//UART Registers
typedef struct{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}USART_Typedef;

//UART Instant
#define USART1			((USART_Typedef *) USART1_BASE)
#define USART2			((USART_Typedef *) USART2_BASE)
#define USART3			((USART_Typedef *) USART3_BASE)

#endif /* USART_PRIVATE_H_ */
