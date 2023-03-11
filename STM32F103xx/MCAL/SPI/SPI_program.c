/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  4  MAR 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "../GPIO/GPIO_interface.h"

#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"


void SPI1_voidInit(void)
{
  //********   SPI selsction **********//
  #if    SPI1_MASTER_OR_SLAVE == SPI_MASTER
    SET_BIT(SPI1->CR1, 2); 
    SET_BIT(SPI1->CR1, 8);
  #elif  SPI1_MASTER_OR_SLAVE == SPI_SLAVE 
    CLR_BIT(SPI1->CR1, 2); 
  #endif /* if SPI1_MASTER_OR_SLAVE */

  //********   SPI clock phase **********//
  #if    SPI1_CLK_PHA == SPI_SEND_FIRST 
    SET_BIT(SPI1->CR1, 0); 
  #elif  SPI1_CLK_PHA == SPI_RECEIVE_FIRST
    CLR_BIT(SPI1->CR1, 0); 
  #endif /* if SPI1_CLK_PHA */

  //********   SPI clock polarity **********//
  #if    SPI1_CLK_POL == SPI_HIGH
    SET_BIT(SPI1->CR1, 1); 
  #elif  SPI1_CLK_POL == SPI_LOW 
    CLR_BIT(SPI1->CR1, 1); 
  #endif /* if SPI1_CLK_POL */

  //********   SPI clock **********//
  #if    SPI1_FPCLK == SPI_FPCLK_2
    CLR_BIT(SPI1->CR1, 3); 
    CLR_BIT(SPI1->CR1, 4); 
    CLR_BIT(SPI1->CR1, 5); 
  #elif  SPI1_FPCLK == SPI_FPCLK_4 
    SET_BIT(SPI1->CR1, 3); 
    CLR_BIT(SPI1->CR1, 4); 
    CLR_BIT(SPI1->CR1, 5); 
  #elif  SPI1_FPCLK == SPI_FPCLK_8 
    CLR_BIT(SPI1->CR1, 3); 
    SET_BIT(SPI1->CR1, 4); 
    CLR_BIT(SPI1->CR1, 5); 
  #elif  SPI1_FPCLK == SPI_FPCLK_16 
    SET_BIT(SPI1->CR1, 3); 
    SET_BIT(SPI1->CR1, 4); 
    CLR_BIT(SPI1->CR1, 5); 
  #elif  SPI1_FPCLK == SPI_FPCLK_32 
    CLR_BIT(SPI1->CR1, 3); 
    CLR_BIT(SPI1->CR1, 4); 
    SET_BIT(SPI1->CR1, 5); 
  #elif  SPI1_FPCLK == SPI_FPCLK_64 
    SET_BIT(SPI1->CR1, 3); 
    CLR_BIT(SPI1->CR1, 4); 
    SET_BIT(SPI1->CR1, 5); 
  #elif  SPI1_FPCLK == SPI_FPCLK_128
    CLR_BIT(SPI1->CR1, 3); 
    SET_BIT(SPI1->CR1, 4); 
    SET_BIT(SPI1->CR1, 5); 
  #elif  SPI1_FPCLK == SPI_FPCLK_256
    SET_BIT(SPI1->CR1, 3); 
    SET_BIT(SPI1->CR1, 4); 
    SET_BIT(SPI1->CR1, 5); 
  #endif /* if SPI1_FPCLK */

  //********   SPI enable **********//
  #if    SPI1_ENABLE == SPI_ENABLED
    SET_BIT(SPI1->CR1, 6); 
  #elif  SPI1_ENABLE == SPI_DISABLED
    CLR_BIT(SPI1->CR1, 6); 
  #endif /* if SPI1_ENABLE */
  
  //********   SPI data order **********//
  #if    SPI1_DATA_ORDER == SPI_LSB_FIRST
    SET_BIT(SPI1->CR1, 7); 
  #elif  SPI1_DATA_ORDER == SPI_MSB_FIRST
    CLR_BIT(SPI1->CR1, 7); 
  #endif /* if SPI1_DATA_ORDER */
  
  //********   SPI slave management **********//
  #if    SPI1_SLAVE_MANAGEMENT == SPI_SOFTWARE
    SET_BIT(SPI1->CR1, 9); 
  #elif  SPI1_SLAVE_MANAGEMENT == SPI_HARDWARE
    CLR_BIT(SPI1->CR1, 9); 
  #endif /* if SPI1_SLAVE_MANAGEMENT */

  //********   SPI data frame format **********//
  #if    SPI1_DATA_FRAME_FORMAT == SPI_BYTE
    SET_BIT(SPI1->CR1, 11); 
  #elif  SPI1_DATA_FRAME_FORMAT == SPI_WORD
    CLR_BIT(SPI1->CR1, 11); 
  #endif /* if SPI1_DATA_FRAME_FORMAT */
  GPIO_voidSetPinDirection( SPI1_SLAVE_PIN, GPIO_OUT_50M_PP);
}

void SPI1_voidSendReceiveSynchronous(u16 copy_u16DataToSend, u16 *P_u16DataToReceive)
{
  #if SPI1_SLAVE_MANAGEMENT == SPI_SOFTWARE 
  //* enable the SS pin for slave *//
  GPIO_voidSetPinValue( SPI1_SLAVE_PIN, GPIO_LOW);
  #endif //SPI1_SLAVE_MANAGEMENT 

  // send data  ( put the value in data register )
  SPI1->DR = copy_u16DataToSend ;

  // wait untill sending done  (untill busy flag set to 0)
  while (GET_BIT(SPI1->SR, 7) == 0 ) ;

  //receive the data 
  *P_u16DataToReceive = SPI1->DR ;

  #if SPI1_SLAVE_MANAGEMENT == SPI_SOFTWARE 
  //* disable the SS pin for slave *//
  GPIO_voidSetPinValue( SPI1_SLAVE_PIN, GPIO_HIGH);
  #endif //SPI1_SLAVE_MANAGEMENT 
}

void SPI1_voidSendReceiveAsynchronous(u16 copy_u16DataToSend, void(*P_CallBack)(u16))
{
  #if SPI1_SLAVE_MANAGEMENT == SPI_SOFTWARE 
  //* enable the SS pin for slave *//
  GPIO_voidSetPinValue( SPI1_SLAVE_PIN, GPIO_LOW);
  #endif //SPI1_SLAVE_MANAGEMENT 

  // send data  ( put the value in data register )
  SPI1->DR = copy_u16DataToSend ;
  
  //receive the data 
  SPI1_static_global_ptr = P_CallBack ;
}

void SPI1_IRQHandler(void)
{
  SPI1_static_global_ptr(SPI1->DR);
  
  #if SPI1_SLAVE_MANAGEMENT == SPI_SOFTWARE 
  //* disable the SS pin for slave *//
  GPIO_voidSetPinValue( SPI1_SLAVE_PIN, GPIO_HIGH);
  #endif //SPI1_SLAVE_MANAGEMENT 
}
