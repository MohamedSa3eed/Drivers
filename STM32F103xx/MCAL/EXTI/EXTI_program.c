/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  1  MAR 2023                                          */
/* Version      :  V02                                                  */
/************************************************************************/

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

static void (*EXTI_static_global_ptr[16])(void) = {NULL} ;

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
  
    case EXTI_RISING_EDGE  :  SET_BIT(EXTI->RTSR, copy_u8Line);  
                              CLR_BIT(EXTI->FTSR, copy_u8Line);  break;
    case EXTI_FALLING_EDGE :  SET_BIT(EXTI->FTSR, copy_u8Line);  
                              CLR_BIT(EXTI->RTSR, copy_u8Line);  break;
    case EXTI_ON_CHANGE    :  SET_BIT(EXTI->RTSR, copy_u8Line); 
                              SET_BIT(EXTI->FTSR, copy_u8Line);  break;
    default                :   break;
  }
  EXTI_voidEnableEXTI(copy_u8Line);
}

void EXTI_voidSetCallBack(u8 copy_u8Line ,void (*copy_ptr)(void))
{
  EXTI_static_global_ptr[copy_u8Line] = copy_ptr ;
}

// excuting the ISR and setting pr to clear the interrupt flag
void EXTI0_IRQHandler (void){if(EXTI_static_global_ptr[EXTI_LINE0]  != NULL ){ EXTI_static_global_ptr[EXTI_LINE0]() ;} SET_BIT(EXTI->PR,EXTI_LINE0) ;}
void EXTI1_IRQHandler (void){if(EXTI_static_global_ptr[EXTI_LINE1]  != NULL ){ EXTI_static_global_ptr[EXTI_LINE1]() ;} SET_BIT(EXTI->PR,EXTI_LINE1) ;}
void EXTI2_IRQHandler (void){if(EXTI_static_global_ptr[EXTI_LINE2]  != NULL ){ EXTI_static_global_ptr[EXTI_LINE2]() ;} SET_BIT(EXTI->PR,EXTI_LINE2) ;}
void EXTI3_IRQHandler (void){if(EXTI_static_global_ptr[EXTI_LINE3]  != NULL ){ EXTI_static_global_ptr[EXTI_LINE3]() ;} SET_BIT(EXTI->PR,EXTI_LINE3) ;}
void EXTI4_IRQHandler (void){if(EXTI_static_global_ptr[EXTI_LINE4]  != NULL ){ EXTI_static_global_ptr[EXTI_LINE4]() ;} SET_BIT(EXTI->PR,EXTI_LINE4) ;}
void EXTI5_IRQHandler (void){if(EXTI_static_global_ptr[EXTI_LINE5]  != NULL ){ EXTI_static_global_ptr[EXTI_LINE5]() ;} SET_BIT(EXTI->PR,EXTI_LINE5) ;}
void EXTI6_IRQHandler (void){if(EXTI_static_global_ptr[EXTI_LINE6]  != NULL ){ EXTI_static_global_ptr[EXTI_LINE6]() ;} SET_BIT(EXTI->PR,EXTI_LINE6) ;}
void EXTI7_IRQHandler (void){if(EXTI_static_global_ptr[EXTI_LINE7]  != NULL ){ EXTI_static_global_ptr[EXTI_LINE7]() ;} SET_BIT(EXTI->PR,EXTI_LINE7) ;}
void EXTI8_IRQHandler (void){if(EXTI_static_global_ptr[EXTI_LINE8]  != NULL ){ EXTI_static_global_ptr[EXTI_LINE8]() ;} SET_BIT(EXTI->PR,EXTI_LINE8) ;}
void EXTI9_IRQHandler (void){if(EXTI_static_global_ptr[EXTI_LINE9]  != NULL ){ EXTI_static_global_ptr[EXTI_LINE9]() ;} SET_BIT(EXTI->PR,EXTI_LINE9) ;}
void EXTI10_IRQHandler(void){if(EXTI_static_global_ptr[EXTI_LINE10] != NULL ){ EXTI_static_global_ptr[EXTI_LINE10]();} SET_BIT(EXTI->PR,EXTI_LINE10);}
void EXTI11_IRQHandler(void){if(EXTI_static_global_ptr[EXTI_LINE11] != NULL ){ EXTI_static_global_ptr[EXTI_LINE11]();} SET_BIT(EXTI->PR,EXTI_LINE11);}
void EXTI12_IRQHandler(void){if(EXTI_static_global_ptr[EXTI_LINE12] != NULL ){ EXTI_static_global_ptr[EXTI_LINE12]();} SET_BIT(EXTI->PR,EXTI_LINE12);}
void EXTI13_IRQHandler(void){if(EXTI_static_global_ptr[EXTI_LINE13] != NULL ){ EXTI_static_global_ptr[EXTI_LINE13]();} SET_BIT(EXTI->PR,EXTI_LINE13);}
void EXTI14_IRQHandler(void){if(EXTI_static_global_ptr[EXTI_LINE14] != NULL ){ EXTI_static_global_ptr[EXTI_LINE14]();} SET_BIT(EXTI->PR,EXTI_LINE14);}
void EXTI15_IRQHandler(void){if(EXTI_static_global_ptr[EXTI_LINE15] != NULL ){ EXTI_static_global_ptr[EXTI_LINE15]();} SET_BIT(EXTI->PR,EXTI_LINE15);}
