/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  4 FEB 2023                                           */
/* Version      :  V01                                                  */
/************************************************************************/
#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "./RCC_interface.h"
#include "./RCC_private.h"
#include "./RCC_config.h"

void RCC_voidInitSysClock(void)
{
  #if    RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
          RCC_CR = 0x00010000 ;  // Enable HSE with no bypass 
  #elif  RCC_CLOCK_TYPE == RCC_HSE_RC 
          RCC_CR = 0x00050000 ;  // Enable HSE with bypass
  #elif  RCC_CLOCK_TYPE == RCC_HSI 
          RCC_CR = 0x00000081 ;  // Enable HSI with Trimming = 0 
  #elif  RCC_CLOCK_TYPE == RCC_PLL
         #if    RCC_PLL_INPUT == RCC_PLL_HSI_DIV_2

         #elif  RCC_PLL_INPUT == RCC_PLL_HSE_DIV_2

         #elif  RCC_PLL_INPUT == RCC_PLL_HSE 

         #endif 

  #else
           #error ("Wrong Clock Type\n")  
  
  #endif /* if RCC_CLOCK_TYPE */

}

void RCC_voidEnableClock(u8 Copy_u8Bus , u8 Copy_u8Periphral)
{
  if (Copy_u8Bus <= 31) 
  {
    switch (Copy_u8Periphral) 
    {
      case   RCC_AHB  :   SET_BIT(RCC_AHBENR, Copy_u8Periphral);   break;
      case   RCC_APB1 :   SET_BIT(RCC_APB1ENR, Copy_u8Periphral);  break;
      case   RCC_APB2 :   SET_BIT(RCC_APB2ENR, Copy_u8Periphral);  break;
      default         :   #error ("Bus not found\n")               break; 
    }
  }
  else 
  {
    #error ("Periphral not found\n")
  }
}
void RCC_voidDisableClock(u8 Copy_u8Bus , u8 Copy_u8Periphral)
{
  if (Copy_u8Bus <= 31) 
  {
    switch (Copy_u8Periphral) 
    {
      case   RCC_AHB  :   CLR_BIT(RCC_AHBENR, Copy_u8Periphral);   break;
      case   RCC_APB1 :   CLR_BIT(RCC_APB1ENR, Copy_u8Periphral);  break;
      case   RCC_APB2 :   CLR_BIT(RCC_APB2ENR, Copy_u8Periphral);  break;
      default         :   #error ("Bus not found\n")               break; 
    }
  }
  else 
  {
    #error ("Periphral not found\n")
  }
}
