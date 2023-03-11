/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  4  MAR 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

typedef struct
{
  volatile u32 CR1     ;
  volatile u32 CR2     ;
  volatile u32 SR      ;
  volatile u32 DR      ; 
  volatile u32 CRCPR   ;
  volatile u32 RXCRCR  ;
  volatile u32 TXCRCR  ;
  volatile u32 I2SCFGR ;
  volatile u32 I2SPR   ;
}SPI_t;

#define  SPI1      ((SPI_t *)0x40013000) 

static void (*SPI1_static_global_ptr)(u16) = NULL ;

//* frame format 
#define SPI_BYTE 1
#define SPI_WORD 2

//* slave mangment
#define SPI_HARDWARE 1 
#define SPI_SOFTWARE 2

//* data order
#define SPI_LSB_FIRST 1
#define SPI_MSB_FIRST 2

//* SPI enable
#define SPI_ENABLED  1
#define SPI_DISABLED 2

//* SPI clock
#define  SPI_FPCLK_2   1
#define  SPI_FPCLK_4   2 
#define  SPI_FPCLK_8   3
#define  SPI_FPCLK_16  4 
#define  SPI_FPCLK_32  5 
#define  SPI_FPCLK_64  6
#define  SPI_FPCLK_128 7
#define  SPI_FPCLK_256 8

//* SPI selection
#define SPI_MASTER 1
#define SPI_SLAVE  2

//* clock polarity
#define SPI_LOW  1
#define SPI_HIGH 2

//* clock phase 
#define SPI_RECEIVE_FIRST 1
#define SPI_SEND_FIRST    2


#endif // !SPI_PRIVATE_H
