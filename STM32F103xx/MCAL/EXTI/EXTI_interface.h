/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  1  MAR 2023                                          */
/* Version      :  V02                                                  */
/************************************************************************/

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

// to enable EXTI on a specefic line 
void EXTI_voidEnableEXTI(u8 copy_u8Line);

// to disable EXTI on a specefic line
void EXTI_voidDisableEXTI(u8 copy_u8Line);

// to set the trigger mode for a specefic line 
void EXTI_voidSetSignalLatch(u8 copy_u8Line , u8 copu_u8Mode);

// to create an EXTI event by software 
void EXTI_voidSWTriggerEXTI(u8 copy_u8Line);

// to set the callback for a specefic line 
void EXTI_voidSetCallBack(u8 copy_u8Line ,void (*copy_ptr)(void));

//define the lines 
#define         EXTI_LINE0              0
#define         EXTI_LINE1              1
#define         EXTI_LINE2              2
#define         EXTI_LINE3              3
#define         EXTI_LINE4              4
#define         EXTI_LINE5              5
#define         EXTI_LINE6              6
#define         EXTI_LINE7              7
#define         EXTI_LINE8              8
#define         EXTI_LINE9              9
#define         EXTI_LINE10             10
#define         EXTI_LINE11             11
#define         EXTI_LINE12             12
#define         EXTI_LINE13             13
#define         EXTI_LINE14             14
#define         EXTI_LINE15             15

//define the modes
#define         EXTI_RISING_EDGE        0
#define         EXTI_FALLING_EDGE       1
#define         EXTI_ON_CHANGE          2

#endif // !EXTI_INTERFACE_h
