/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  17 FEB 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H

void AFIO_voidSetEXTILineConfig(u8 copy_u8Line , u8 copy_u8Config);

#define AFIO_EXTI_PORT_A	0b0000
#define AFIO_EXTI_PORT_B	0b0001
#define AFIO_EXTI_PORT_C	0b0010
#define AFIO_EXTI_PORT_D	0b0011
#define AFIO_EXTI_PORT_E	0b0100
#define AFIO_EXTI_PORT_F	0b0101
#define AFIO_EXTI_PORT_G	0b0110

#endif // !AFIO_INTERFACE_H
