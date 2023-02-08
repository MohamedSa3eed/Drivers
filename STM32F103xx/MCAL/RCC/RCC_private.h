/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  4 FEB 2023                                           */
/* Version      :  V01                                                  */
/************************************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

//Registers
#define  RCC_CR           *((volatile u32*)0x40021000)
#define  RCC_GFGR         *((volatile u32*)0x40021004)
#define  RCC_CIR          *((volatile u32*)0x40021008)
#define  RCC_APB2RSTR     *((volatile u32*)0x4002100c)
#define  RCC_APB1RSTR     *((volatile u32*)0x40021010)
#define  RCC_AHBENR       *((volatile u32*)0x40021014)
#define  RCC_APB2ENR      *((volatile u32*)0x40021018)
#define  RCC_APB1ENR      *((volatile u32*)0x4002101c)
#define  RCC_BDCR         *((volatile u32*)0x40021020)
#define  RCC_CRR          *((volatile u32*)0x40021024)


//Clock Types
#define  RCC_HSE_CRYSTAL  1 
#define  RCC_HSE_RC       2 
#define  RCC_HSI          3 
#define  RCC_PLL          4

#endif // !RCC_PRIVATE_H
