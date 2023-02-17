/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  17 FEB 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

typedef struct{
  u32 IMR ;
  u32 EMR ;
  u32 RTSR ;
  u32 FTSR ;
  u32 SWIER ;
  u32 PR ;
}EXTI_t ;

#define         EXTI               ((volatile EXTI_t *) 0x40010400)

#endif // !EXTI_PRIVATE_H
