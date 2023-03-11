/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  4  MAR 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../MCAL/STK/STK_interface.h"

#include "STP_interface.h"
#include "STP_config.h"
#include "STP_private.h"

void STP_voidInit(void)
{
  GPIO_voidSetPinDirection(STP_SERIAL_DATA_PIN, GPIO_OUT_2M_PP);
  GPIO_voidSetPinDirection(STP_SHIFT_CLOCK_PIN, GPIO_OUT_2M_PP);
  GPIO_voidSetPinDirection(STP_STORAGE_CLOCK_PIN, GPIO_OUT_2M_PP);
}

void STP_voidSendData(u8 copy_u8Data)
{
  s8 local_s8Counter ;
  u8 local_u8Bit ;
  for (local_s8Counter = 7 ; local_s8Counter >= 0 ; local_s8Counter--)
  {
    local_u8Bit = GET_BIT(copy_u8Data, local_s8Counter);
    /*send the serial bits */
    GPIO_voidSetPinValue(STP_SERIAL_DATA_PIN, local_u8Bit);
    /*snd pulse to shift clock */
    GPIO_voidSetPinValue(STP_SHIFT_CLOCK_PIN, GPIO_HIGH);
    STK_voidBusyWait(1); //wait 1 Micro Sec 
    GPIO_voidSetPinValue(STP_SHIFT_CLOCK_PIN, GPIO_LOW);
    STK_voidBusyWait(1); //wait 1 Micro Sec 
  }
   /*send pulse to storage clock */
    GPIO_voidSetPinValue(STP_STORAGE_CLOCK_PIN, GPIO_HIGH);
    STK_voidBusyWait(1); //wait 1 Micro Sec 
    GPIO_voidSetPinValue(STP_STORAGE_CLOCK_PIN, GPIO_LOW);
    STK_voidBusyWait(1); //wait 1 Micro Sec 
}
