/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  24 FEB 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

// pointer for callback
static void (*STK_static_global_ptr) (void)  =  NULL ;

// variable for interval mode
static u8 STK_u8IntervalMode ;

void STK_voidInit(void)
{
    #if STK_CLK_SOURCE == AHB 
      SET_BIT(STK->STK_CTRL, STK_CTRL_CLK_SOURCE);
    #elif STK_CLK_SOURCE == AHB_8  
      CLR_BIT(STK->CTRL, STK_CTRL_CLK_SOURCE);
    #endif /* if STK_INT == ENABLED  */
}

void STK_voidBusyWait(u32 copy_u32Ticks)
{
  //load value into timer 
  STK->LOAD = copy_u32Ticks ;
  STK->VAL  = 0 ;

  //start timer 
  SET_BIT(STK->CTRL,STK_CTRL_ENABLE);

  //wait till flag is raised
  while (GET_BIT(STK->CTRL, STK_CTRL_COUNT_FLAG) == 0 ) 
   ;
  //stop timer
  CLR_BIT(STK->CTRL,STK_CTRL_ENABLE);
  STK->LOAD = 0 ;
  STK->VAL  = 0 ;
}

void STK_voidSetIntervalSingle(u32 copy_u32Ticks , void (*copy_ptr)(void))
{
  //stop timer
  CLR_BIT(STK->CTRL,STK_CTRL_ENABLE);
  STK->VAL  = 0 ;

  //load value into timer
  STK->LOAD = copy_u32Ticks ;
  
  // start timer
  SET_BIT(STK->CTRL,STK_CTRL_ENABLE);
  
  // set interval mode 
  STK_u8IntervalMode = STK_SINGLE_INTERVAL ;
  
  //set the callback
  STK_static_global_ptr = copy_ptr ;

  //enable interrupt 
  SET_BIT(STK->CTRL, STK_CTRL_TICK_INT);
}

void STK_voidSetIntervalperiodic(u32 copy_u32Ticks , void (*copy_ptr)(void))
{
  //stop timer
  CLR_BIT(STK->CTRL,STK_CTRL_ENABLE);
  STK->VAL  = 0 ;

  //load value into timer
  STK->LOAD = copy_u32Ticks ;

  // start timer
  SET_BIT(STK->CTRL,STK_CTRL_ENABLE);

  // set interval mode 
  STK_u8IntervalMode = STK_PERIODIC_INTERVAL ;
  
  //set the callback
  STK_static_global_ptr = copy_ptr ;

  //enable interrupt 
  SET_BIT(STK->CTRL, STK_CTRL_TICK_INT);
}

void STK_voidStopInterval(void)
{
  //disable interrupt 
  CLR_BIT(STK->CTRL, STK_CTRL_TICK_INT);

  //stop timer 
  CLR_BIT(STK->CTRL, STK_CTRL_ENABLE);
  STK->LOAD=0 ;
  STK->VAL = 0 ;
}

u32  STK_u32GetElapsedTime(void)
{
  return ((STK->LOAD) - (STK->VAL));
}

u32  STK_u32GetRemainingTime(void)
{
  return STK->VAL ;
}

void SysTick_Handler(void)
{
  u8 local_u8Temp ;

	if (STK_u8IntervalMode == STK_SINGLE_INTERVAL)
	{
		/* disable STK interrupt */
		CLR_BIT(STK->CTRL, STK_CTRL_TICK_INT);
	
		/* stop timer */
		CLR_BIT(STK->CTRL, STK_CTRL_ENABLE);
		STK -> LOAD = 0;
		STK -> VAL  = 0;
	}

  //execute the callback
  STK_static_global_ptr();

  // clearing the flag (by reading it)
  local_u8Temp = GET_BIT(STK->CTRL, STK_CTRL_COUNT_FLAG);
}
