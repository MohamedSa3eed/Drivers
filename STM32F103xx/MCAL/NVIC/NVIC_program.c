/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  13 FEB 2023                                           */
/* Version      :  V01                                                  */
/************************************************************************/

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_config.h"
#include "NVIC_private.h"

u8 NVIC_u8EnableInterrupt (u8 copy_u8IntNumber)
{
  u8 state ;
  if (copy_u8IntNumber <=31) 
  {
    NVIC_ISER0 = (1 << copy_u8IntNumber);
    state = 0;
  }
  else if (copy_u8IntNumber <=59)
  {
    copy_u8IntNumber -= 8;
    NVIC_ISER1 = (1 << copy_u8IntNumber);
    state = 0;
  }
  else
  {
    state = 1;
  }
  return state;
}

u8 NVIC_u8DisableInterrupt (u8 copy_u8IntNumber)
{
  u8 state ;
  if (copy_u8IntNumber <=31) 
  {
    NVIC_ICER0 = (1 << copy_u8IntNumber);
    state = 0;
  }
  else if (copy_u8IntNumber <=59)
  {
    copy_u8IntNumber -= 8;
    NVIC_ICER1 = (1 << copy_u8IntNumber);
    state = 0;
  }
  else
  {
    state = 1;
  }
  return state;
}

u8 NVIC_SetPendingFlag (u8 copy_u8IntNumber)
{
  u8 state ;
  if (copy_u8IntNumber <=31) 
  {
    NVIC_ISPR0 = (1 << copy_u8IntNumber);
    state = 0;
  }
  else if (copy_u8IntNumber <=59)
  {
    copy_u8IntNumber -= 8;
    NVIC_ISPR1 = (1 << copy_u8IntNumber);
    state = 0;
  }
  else
  {
    state = 1;
  }
  return state;
}

u8 NVIC_ClearPendingFlag (u8 copy_u8IntNumber)
{
  u8 state ;
  if (copy_u8IntNumber <=31) 
  {
    NVIC_ICPR0 = (1 << copy_u8IntNumber);
    state = 0;
  }
  else if (copy_u8IntNumber <=59)
  {
    copy_u8IntNumber -= 8;
    NVIC_ICPR1 = (1 << copy_u8IntNumber);
    state = 0;
  }
  else
  {
    state = 1;
  }
  return state;
}

s8 NVIC_s8GetActiveFlag (u8 copy_u8IntNumber)
{
  u8 local_u8Result ;
  if (copy_u8IntNumber <=31) 
  {
    local_u8Result = GET_BIT(NVIC_IABR0, copy_u8IntNumber);
  }
  else if (copy_u8IntNumber <=59)
  {
    copy_u8IntNumber -= 8;
    local_u8Result = GET_BIT(NVIC_IABR1, copy_u8IntNumber);
  }
  else
  {
    return -1 ;
  }
  return local_u8Result;
}

void NVIC_voidSetPriority(s8 copy_s8IntNumber ,u32 copy_u32PriorityMode , u8 copy_u8GroupPriority ,u8 copy_u8SubPriority)
{
  SCB_AIRCR = copy_u32PriorityMode ;
  u8 local_u8Priority = copy_u8SubPriority | (copy_u8GroupPriority << (copy_u32PriorityMode - 0x05fa0300)/0x100);
  //core peripherals
  //TODO

  //external peripherals 
  if (copy_s8IntNumber >= 0 && copy_s8IntNumber <60)
  {
    NVIC_IPR[copy_s8IntNumber] = local_u8Priority << 4 ;
  }
}
