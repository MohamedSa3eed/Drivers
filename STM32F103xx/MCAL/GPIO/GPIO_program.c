/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  8 FEB 2023                                           */
/* Version      :  V01                                                  */
/************************************************************************/

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

void GPIO_voidSetPinDirection(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Mode)
{
  switch (copy_u8Port) 
  {
    case GPIOA :
                  if (copy_u8Pin < 8 )
                  {
                      GPIOA_CRL &= ~ ((0b1111) << (copy_u8Pin *4 ));
                      GPIOA_CRL |=   ((copy_u8Mode) << (copy_u8Pin *4 ));
                  }
                  else if (copy_u8Pin <16) 
                  {
                      copy_u8Pin -= 8 ;
                      GPIOA_CRH &= ~ ((0b1111) << (copy_u8Pin *4 ));
                      GPIOA_CRH |=   ((copy_u8Mode) << (copy_u8Pin *4 ));
                  }
                  else 
                  {
                      /*#error ("Wrong Pin\n")*/
                  }
                  break;
    case GPIOB :
                  if (copy_u8Pin < 8 )
                  {
                      GPIOB_CRL &= ~ ((0b1111) << (copy_u8Pin *4 ));
                      GPIOB_CRL |=   ((copy_u8Mode) << (copy_u8Pin *4 ));
                  }
                  else if (copy_u8Pin <16) 
                  {
                      copy_u8Pin -= 8 ;
                      GPIOB_CRH &= ~ ((0b1111) << (copy_u8Pin *4 ));
                      GPIOB_CRH |=   ((copy_u8Mode) << (copy_u8Pin *4 ));
                  }
                  else 
                  {
                      /*#error ("Wrong Pin\n")*/
                  }
                  break;
    case GPIOC :
                  if (copy_u8Pin < 8 )
                  {
                      GPIOC_CRL &= ~ ((0b1111) << (copy_u8Pin *4 ));
                      GPIOC_CRL |=   ((copy_u8Mode) << (copy_u8Pin *4 ));
                  }
                  else if (copy_u8Pin <16) 
                  {
                      copy_u8Pin -= 8 ;
                      GPIOC_CRH &= ~ ((0b1111) << (copy_u8Pin *4 ));
                      GPIOC_CRH |=   ((copy_u8Mode) << (copy_u8Pin *4 ));
                  }
                  else 
                  {
                      /*#error ("Wrong Pin\n")*/
                  }
                  break;
    default    : 
                  /*#error ("Wrong Port\n")*/
                  break;
  }
}

void GPIO_voidSetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value)
{
  switch (copy_u8Port) 
  {
    case GPIOA :
                  if (copy_u8Value == GPIO_HIGH)
                  {
                      SET_BIT(GPIOA_ODR, copy_u8Pin);
                  }
                  else if (copy_u8Value == GPIO_LOW) 
                  {
                      CLR_BIT(GPIOA_ODR, copy_u8Pin);
                  }
                  else 
                  {
                      /*#error ("Wrong Value\n")*/
                  }
                  break;
    case GPIOB :
                  if (copy_u8Value == GPIO_HIGH)
                  {
                      SET_BIT(GPIOB_ODR, copy_u8Pin);
                  }
                  else if (copy_u8Value == GPIO_LOW) 
                  {
                      CLR_BIT(GPIOB_ODR, copy_u8Pin);
                  }
                  else 
                  {
                      /*#error ("Wrong Value\n")*/
                  }
                  break;
    case GPIOC :
                  if (copy_u8Value == GPIO_HIGH)
                  {
                      SET_BIT(GPIOC_ODR, copy_u8Pin);
                  }
                  else if (copy_u8Value == GPIO_LOW) 
                  {
                      CLR_BIT(GPIOC_ODR, copy_u8Pin);
                  }
                  else 
                  {
                      /*#error ("Wrong Value\n")*/
                  }
                  break;
    default    : 
                  /*#error ("Wrong Port\n")*/
                  break;
  }
}

u8   GPIO_u8GetPinValue(u8 copy_u8Port , u8 copy_u8Pin)
{
  u8 local_u8Value = 0;
  switch (copy_u8Port) 
  {
    case GPIOA :
                  local_u8Value = GET_BIT(GPIOA_IDR , copy_u8Pin);
                  break;
    case GPIOB :
                  local_u8Value = GET_BIT(GPIOB_IDR , copy_u8Pin);
                  break;
    case GPIOC :
                  local_u8Value = GET_BIT(GPIOC_IDR , copy_u8Pin);
                  break;
    default    : 
                  /*#error ("Wrong Port\n")*/
                  break;
  }
    return local_u8Value;
}
