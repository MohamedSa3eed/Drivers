/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  17 FEB 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "AFIO_interface.h"
#include "AFIO_private.h"
#include "AFIO_config.h"

void AFIO_voidSetEXTILineConfig(u8 copy_u8Line , u8 copy_u8Config)
{
  u8 local_u8RegIndex ;
  if (copy_u8Line < 4)
  {
    local_u8RegIndex = 0 ;
  }
  else if (copy_u8Line < 8)
  {
    local_u8RegIndex = 1 ;  
    copy_u8Line -= 4 ;
  }
  else if (copy_u8Line < 12)
  {
    local_u8RegIndex = 2 ;  
    copy_u8Line -= 8 ;
  }
  else if (copy_u8Line < 16)
  {
    local_u8RegIndex = 3 ;  
    copy_u8Line -= 12 ;
  }

  AFIO->EXTICR[local_u8RegIndex]  &= ~((0b1111) << (copy_u8Line * 4));
  AFIO->EXTICR[local_u8RegIndex]  |=  ((copy_u8Config) << (copy_u8Line*4));
}
