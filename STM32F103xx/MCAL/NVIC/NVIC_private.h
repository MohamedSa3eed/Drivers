/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  13 FEB 2023                                           */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H


                  /*         Register Definition          */
#define  NVIC_BASE_REGISTER   0xe000e100
#define  SCB_BASE_REGISTER    0xe000ed00

#define  NVIC_ISER0           *((volatile u32 *)(NVIC_BASE_REGISTER + 0x00))          //Enable External interrrupts from 0  to 31
#define  NVIC_ISER1           *((volatile u32 *)(NVIC_BASE_REGISTER + 0x04))          //Enable External interrrupts from 32 to 63

#define  NVIC_ICER0           *((volatile u32 *)(NVIC_BASE_REGISTER + 0x80))          //Disable External interrrupts from 0  to 31
#define  NVIC_ICER1           *((volatile u32 *)(NVIC_BASE_REGISTER + 0x84))          //Disable External interrrupts from 32 to 63

#define  NVIC_ISPR0           *((volatile u32 *)(NVIC_BASE_REGISTER + 0x100))         //Set pending flag for External interrrupts from 0  to 31 
#define  NVIC_ISPR1           *((volatile u32 *)(NVIC_BASE_REGISTER + 0x104))         //Set pending flag for External interrrupts from 32  to 63 

#define  NVIC_ICPR0           *((volatile u32 *)(NVIC_BASE_REGISTER + 0x180))         //Clear pending flag for External interrrupts from 0  to 31 
#define  NVIC_ICPR1           *((volatile u32 *)(NVIC_BASE_REGISTER + 0x184))         //Clear pending flag for External interrrupts from 32  to 63 

#define  NVIC_IABR0           *((const volatile u32 *)(NVIC_BASE_REGISTER + 0x200))   //Soring the value of External interrrupts Active Bit from 0  to 31 (read only register)
#define  NVIC_IABR1           *((const volatile u32 *)(NVIC_BASE_REGISTER + 0x204))   //Soring the value of External interrrupts Active Bit from 0  to 31 (read only register)

#define  NVIC_IPR             ((volatile u8 *)(NVIC_BASE_REGISTER + 0x300))           //Define a pointer to array of IP Registers

#define  SCB_AIRCR            *((volatile u32 *)(SCB_BASE_REGISTER + 0x0c))           //Controlling priority

#endif // !NVIC_PRIVATE_H

