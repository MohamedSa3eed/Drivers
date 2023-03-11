/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  7  MAR 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../MCAL/STK/STK_interface.h"
#include "../../MCAL/SPI/SPI_interface.h"

#include "TFT_interface.h"
#include "TFT_config.h"
#include "TFT_private.h"

void TFT_voidInit(void)
{
  /* initialize pins */ 
  GPIO_voidSetPinDirection(TFT_RST_PIN, GPIO_OUT_2M_PP);
  GPIO_voidSetPinDirection(TFT_AO_PIN, GPIO_OUT_2M_PP);
  GPIO_voidSetPinDirection(TFT_CLK_PIN,GPIO_OUT_50M_PP);
  GPIO_voidSetPinDirection(TFT_AO_PIN, GPIO_OUT_50M_PP);

  /* initialize reset pulse */
  GPIO_voidSetPinValue(TFT_RST_PIN, GPIO_HIGH);
  STK_voidBusyWait(100);
  GPIO_voidSetPinValue(TFT_RST_PIN, GPIO_LOW);
  STK_voidBusyWait(1);
  GPIO_voidSetPinValue(TFT_RST_PIN, GPIO_HIGH);
  STK_voidBusyWait(100);
  GPIO_voidSetPinValue(TFT_RST_PIN, GPIO_LOW);
  STK_voidBusyWait(100);
  GPIO_voidSetPinValue(TFT_RST_PIN, GPIO_HIGH);
  STK_voidBusyWait(120000);
  
  //sleep out command 
  TFT_voidSendCommand(0x11);
  STK_voidBusyWait(150000);

  //color mode command 
  TFT_voidSendCommand(0x3a);
  TFT_voidSendData(0x05);

  //dispaly command 
  TFT_voidSendCommand(0x29);
}

void TFT_voidFillColor(u16 copy_u16Color)
{
  TFT_voidDisplayInit(0,127,0,159);
  for (u16 counter =0 ; counter < 20480 ; counter++) 
  {
    TFT_voidSendData(copy_u16Color);
  }
}

void TFT_voidDisplayImage(const u16 *copy_u16Image)
{
  TFT_voidDisplayInit(0,127,0,159);
  for (u16 counter =0 ; counter < 20480 ; counter++) 
  {
    TFT_voidSendData(copy_u16Image[counter]);
  }
}

void TFT_voidDrawRect(u8 x1, u8 x2, u8 y1, u8 y2, u16 copy_u16Color)
{
  TFT_voidDisplayInit(x1,x2,y1,y2);
  u16 local_u16Size = (x2-x1)*(y2-y1) ;
  for (u16 counter =0 ; counter < local_u16Size ; counter++) 
  {
    TFT_voidSendData(copy_u16Color);
  }
}

static void TFT_voidSendCommand(u16 copy_u16Command)
{
  u16 local_u16Temp ;
  /* set AO to low */ 
  GPIO_voidSetPinValue(TFT_AO_PIN, GPIO_LOW);

  /* send command over SPI */ 
  SPI1_voidSendReceiveSynchronous(copy_u16Command, &local_u16Temp);
}

static void TFT_voidSendData(u16 copy_u16Data)
{
  u16 local_u16Temp ;
  /* set AO to high */ 
  GPIO_voidSetPinValue(TFT_AO_PIN, GPIO_LOW);

  /* send data over SPI */ 
  SPI1_voidSendReceiveSynchronous(copy_u16Data, &local_u16Temp);
}

static void TFT_voidDisplayInit(u8 x1, u8 x2, u8 y1, u8 y2)
{
  /* set X address */ 
  TFT_voidSendCommand(0x2a);
  TFT_voidSendData(0);
  TFT_voidSendData(x1);
  TFT_voidSendData(0);
  TFT_voidSendData(x2);

  /* set X address */ 
  TFT_voidSendCommand(0x2b);
  TFT_voidSendData(0);
  TFT_voidSendData(y1);
  TFT_voidSendData(0);
  TFT_voidSendData(y2);

  /* RAM write */
  TFT_voidSendCommand(0x2c);
}
