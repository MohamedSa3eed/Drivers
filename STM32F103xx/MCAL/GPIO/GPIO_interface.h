/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  8 FEB 2023                                           */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#define   GPIOA       0
#define   GPIOB       1
#define   GPIOC       2

#define   PIN0        0  
#define   PIN1        1  
#define   PIN2        2  
#define   PIN3        3  
#define   PIN4        4  
#define   PIN5        5  
#define   PIN6        6  
#define   PIN7        7  
#define   PIN8        8  
#define   PIN9        9  
#define   PIN10       10  
#define   PIN11       11  
#define   PIN12       12  
#define   PIN13       13  
#define   PIN14       14  
#define   PIN15       15  

//Modes
#define     GPIO_OUT_2M_PP        0b0010
#define     GPIO_OUT_2M_OD        0b0110
#define     GPIO_OUT_2M_AFPP      0b1010
#define     GPIO_OUT_2M_AFOD      0b1110

#define     GPIO_OUT_10M_PP       0b0001
#define     GPIO_OUT_10M_OD       0b0101
#define     GPIO_OUT_10M_AFPP     0b1001
#define     GPIO_OUT_10M_AFOD     0b1101

#define     GPIO_OUT_50M_PP       0b0011
#define     GPIO_OUT_50M_OD       0b0111
#define     GPIO_OUT_50M_AFPP     0b1011
#define     GPIO_OUT_50M_AFOD     0b1111

#define     GPIO_IN_ANALOG        0b0000
#define     GPIO_IN_FLOATING      0b0100
#define     GPIO_IN_PULL_UP_DOWN  0b1000

//Directions 
#define     GPIO_HIGH             1 
#define     GPIO_LOW              0 


void GPIO_voidSetPinDirection(u8 copy_u8Port , u8 copy_u8Pin , u8 copy_u8Mode);
void GPIO_voidSetPinValue(u8 copy_u8Port , u8 copy_u8Pin , u8 copy_u8Value);
u8   GPIO_u8GetPinValue(u8 copy_u8Port , u8 copy_u8Pin);


#endif // !GPIO_INTERFACE_H 
