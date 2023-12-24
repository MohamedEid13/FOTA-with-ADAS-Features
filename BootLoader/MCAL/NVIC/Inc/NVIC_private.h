

#ifndef NVIC_DRIVER_NVIC_PRIVATE_H_
#define NVIC_DRIVER_NVIC_PRIVATE_H_

#define NVIC_BASE			0xE000E100UL
#define SCB_BASE			0xE000E008UL

// Interrupt set-enable registers (NVIC_ISERx)
#define NVIC_ISER0			*((volatile u32*)(NVIC_BASE + 0x00))
#define NVIC_ISER1			*((volatile u32*)(NVIC_BASE + 0x04))
#define NVIC_ISER2			*((volatile u32*)(NVIC_BASE + 0x08))

// Interrupt clear-enable registers (NVIC_ICERx)
#define NVIC_ICER0			*((volatile u32*)NVIC_BASE + 0x80)
#define NVIC_ICER1			*((volatile u32*)NVIC_BASE + 0x84)
#define NVIC_ICER2			*((volatile u32*)NVIC_BASE + 0x88)

// Interrupt set-pending registers (NVIC_ISPRx)
#define NVIC_ISPR0			*((volatile uint32_t*)NVIC_BASE + 0x100)
#define NVIC_ISPR1			*((volatile uint32_t*)NVIC_BASE + 0x104)
#define NVIC_ISPR2			*((volatile uint32_t*)NVIC_BASE + 0x108)

// Interrupt clear-pending registers (NVIC_ICPRx)
#define NVIC_ICPR0			*((volatile uint32_t*)NVIC_BASE + 0x180)
#define NVIC_ICPR1			*((volatile uint32_t*)NVIC_BASE + 0x184)
#define NVIC_ICPR2			*((volatile uint32_t*)NVIC_BASE + 0x188)

// Interrupt active bit registers (NVIC_IABRx)
#define NVIC_IABR0			*((volatile uint32_t*)NVIC_BASE + 0x200)
#define NVIC_IABR1			*((volatile uint32_t*)NVIC_BASE + 0x204)
#define NVIC_IABR2			*((volatile uint32_t*)NVIC_BASE + 0x208)

// Interrupt priority registers (NVIC_IPRx)
#define NVIC_IPR0			((volatile uint32_t*)NVIC_BASE + 0x300)

#define NVIC_IPR20			*((volatile uint32_t*)NVIC_BASE + 0x320)

// Software trigger interrupt register (NVIC_STIR)
#define NVIC_STIR			*((volatile uint32_t*)NVIC_BASE + 0xE00)

//0Application interrupt and reset control register (SCB_AIRCR)
#define SCB_AIRCR			*((volatile uint32_t*)SCB_BASE + 0xE0C)

#endif /* NVIC_DRIVER_NVIC_PRIVATE_H_ */
