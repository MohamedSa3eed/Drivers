/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  24 FEB 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

typedef struct {
  u32  CTRL ;     // control STK 
  u32  LOAD ;     // holds the pre value of the timer (24-bit)
  u32  VAL  ;     // holds the current value of the timer (24-bit)
  u32  CALIB;
} STK_t ;

#define     STK                     ((volatile STK_t * ) 0xe000e010)

//CTRL Register Bits
#define     STK_CTRL_COUNT_FLAG     16
#define     STK_CTRL_CLK_SOURCE     2 
#define     STK_CTRL_TICK_INT       1 
#define     STK_CTRL_ENABLE         0 

#define     AHB_8                   0 
#define     AHB                     1 

#define     DISABLED                0 
#define     ENABLED                 1  
 
#define     STK_SINGLE_INTERVAL     0 
#define     STK_PERIODIC_INTERVAL   1 

#endif  //STK_PRIVATE_H
