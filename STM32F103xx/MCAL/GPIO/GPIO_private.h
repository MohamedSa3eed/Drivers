/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  8 FEB 2023                                           */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H


#define     GPIOA_BASE_ADDRESS    0x40010800
#define     GPIOB_BASE_ADDRESS    0x40010c00
#define     GPIOC_BASE_ADDRESS    0x40011000

//Port A     
#define     GPIOA_CRL             *((u32 *)GPIOA_BASE_ADDRESS + 0x00)
#define     GPIOA_CRH             *((u32 *)GPIOA_BASE_ADDRESS + 0x04)
#define     GPIOA_IDP             *((u32 *)GPIOA_BASE_ADDRESS + 0x08)
#define     GPIOA_ODR             *((u32 *)GPIOA_BASE_ADDRESS + 0x0c)
#define     GPIOA_BSRR            *((u32 *)GPIOA_BASE_ADDRESS + 0x10)
#define     GPIOA_BIRR            *((u32 *)GPIOA_BASE_ADDRESS + 0x14)
#define     GPIOA_LCKR            *((u32 *)GPIOA_BASE_ADDRESS + 0x18)

//Port B     
#define     GPIOB_CRL             *((u32 *)GPIOB_BASE_ADDRESS + 0x00)
#define     GPIOB_CRH             *((u32 *)GPIOB_BASE_ADDRESS + 0x04)
#define     GPIOB_IDP             *((u32 *)GPIOB_BASE_ADDRESS + 0x08)
#define     GPIOB_ODR             *((u32 *)GPIOB_BASE_ADDRESS + 0x0c)
#define     GPIOB_BSRR            *((u32 *)GPIOB_BASE_ADDRESS + 0x10)
#define     GPIOB_BIRR            *((u32 *)GPIOB_BASE_ADDRESS + 0x14)
#define     GPIOB_LCKR            *((u32 *)GPIOB_BASE_ADDRESS + 0x18)

//Port C     
#define     GPIOC_CRL             *((u32 *)GPIOC_BASE_ADDRESS + 0x00)
#define     GPIOC_CRH             *((u32 *)GPIOC_BASE_ADDRESS + 0x04)
#define     GPIOC_IDP             *((u32 *)GPIOC_BASE_ADDRESS + 0x08)
#define     GPIOC_ODR             *((u32 *)GPIOC_BASE_ADDRESS + 0x0c)
#define     GPIOC_BSRR            *((u32 *)GPIOC_BASE_ADDRESS + 0x10)
#define     GPIOC_BIRR            *((u32 *)GPIOC_BASE_ADDRESS + 0x14)
#define     GPIOC_LCKR            *((u32 *)GPIOC_BASE_ADDRESS + 0x18)

//Modes
#define     GPIO_OUT_10M_PP       0b0001
#define     GPIO_OUT_2M_PP        0b0010
#define     GPIO_OUT_50M_PP       0b0011
#define     GPIO_OUT_10M_OD       0b0101
#define     GPIO_OUT_2M_OD        0b0110
#define     GPIO_OUT_50M_OD       0b0111
#define     GPIO_OUT_10M_AFPP     0b1001
#define     GPIO_OUT_2M_AFPP      0b1010
#define     GPIO_OUT_50M_AFPP     0b1011
#define     GPIO_OUT_10M_AFOD     0b1101
#define     GPIO_OUT_2M_AFOD      0b1110
#define     GPIO_OUT_50M_AFOD     0b1111
#define     GPIO_IN_ANALOG        0b0000
#define     GPIO_IN_FLOATING      0b0100
#define     GPIO_IN_PULL_UP_DOWN  0b1000


#endif // !GPIO_PRIVATE_H 
