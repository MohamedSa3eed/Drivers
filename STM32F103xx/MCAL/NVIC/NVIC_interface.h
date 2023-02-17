/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  13 FEB 2023                                           */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

u8 NVIC_u8EnableInterrupt (u8 copy_u8IntNumber);
u8 NVIC_u8DisableInterrupt (u8 copy_u8IntNumber);
u8 NVIC_SetPendingFlag (u8 copy_u8IntNumber);
u8 NVIC_ClearPendingFlag (u8 copy_u8IntNumber);
s8 NVIC_s8GetActiveFlag (u8 copy_u8IntNumber);

#define     NVIC_NO_SUB_PRIORITY           0x05fa0300
#define     NVIC_8_GRUOP_2_SUB_PRIORITY    0x05fa0400
#define     NVIC_4_GRUOP_4_SUB_PRIORITY    0x05fa0500
#define     NVIC_2_GRUOP_8_SUB_PRIORITY    0x05fa0600
#define     NVIC_NO_GROUP_PRIORITY         0x05fa0700

#endif // !NVIC_INTERFACE_H
