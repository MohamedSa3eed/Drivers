/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  4 FEB 2023                                           */
/* Version      :  V01                                                  */
/************************************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#define RCC_AHB   0
#define RCC_APB1  1
#define RCC_APB2  2

void RCC_voidInitSysClock(void);
void RCC_voidEnableClock(u8 Copy_u8Bus , u8 Copy_u8Periphral);
void RCC_voidDisableClock(u8 Copy_u8Bus , u8 Copy_u8Periphral);


#endif // !RCC_INTERFACE_H
