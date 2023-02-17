/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  17 FEB 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"


void EXTI_voidInit(void)
{
  #if       EXTI_MODE == EXTI_RISING_EDGE
    SET_BIT((EXTI->RTSR), EXTI_LINE);
  #elif     EXTI_MODE == EXTI_FALLING_EDGE
    SET_BIT((EXTI->FTSR), EXTI_LINE);
  #elif     ECTI_MODE == EXTI_ON_CHANGE
  #else     #error "Wrong Mode or Line"
  #endif
}

void EXTI_voidEnableEXTI(u8 copy_u8Line)
{
  SET_BIT(EXTI->IMR, copy_u8Line);
}

void EXTI_voidDisableEXTI(u8 copy_u8Line)
{
  CLR_BIT(EXTI->IMR, copy_u8Line);
}

void EXTI_voidSWTriggerEXTI(u8 copy_u8Line)
{
  SET_BIT(EXTI->SWIER, copy_u8Line);
}

void EXTI_voidSetSignalLatch(u8 copy_u8Line , u8 copu_u8Mode)
{
  switch (copu_u8Mode) {
  
    case EXTI_RISING_EDGE  :  SET_BIT(EXTI->RTSR, copy_u8Line);  break;
    case EXTI_FALLING_EDGE :  SET_BIT(EXTI->FTSR, copy_u8Line);  break;
    case EXTI_ON_CHANGE    :  SET_BIT(EXTI->RTSR, copy_u8Line); 
                              SET_BIT(EXTI->FTSR, copy_u8Line);  break;
    default                :   break;
  }


}
