/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  17 FEB 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef AFIO_CONFIG_H
#define AFIO_CONFIG_H

typedef struct{
  u32 EVCR ;
  u32 MAPR ;
  u32 EXTICR[4];
  u32 MAPR2 ;
}AFIO_t;

#define  AFIO   ((volatile AFIO_t * ) 0x40010000)

#endif // !AFIO_CONFIG_H
