/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  1  MAR 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H

#define  CHANNELS_NUM  7

typedef struct 
{
  volatile u32 CCR  ;
  volatile u32 CNDTR;
  volatile u32 CPAR ;
  volatile u32 CMAR ;
  volatile u32 Reserved;
}DMA_Channel ;

typedef struct 
{
  volatile u32 ISR ;
  volatile u32 IFCR;
  DMA_Channel CHANNEL[CHANNELS_NUM];
}DMA_t; 

#define  DMA  ((volatile DMA_t *)0x40020000)

static void DMA_CLRINTFlags(u8 copy_u8ChannelID);

#endif // !DMA_PRIVATE_H
