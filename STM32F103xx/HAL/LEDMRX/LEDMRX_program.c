/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  25 FEB 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../MCAL/STK/STK_interface.h"

#include "LEDMRX_interface.h"
#include "LEDMRX_config.h"
#include "LEDMRX_private.h"

static u8 colPinArr [COL_NUM] = COL_PINS ;
static u8 colPortArr[COL_NUM] = COL_PORTS ;
static u8 rowPortArr[ROW_NUM] = ROW_PORTS ;
static u8 rowPinArr [ROW_NUM] = ROW_PINS ;

void LEDMRX_voidInit(void)
{
  //initialize the led matrix pins
  for (u8 it = 0  ; it < 8 ; it++) {
    GPIO_voidSetPinDirection(rowPortArr[it], rowPinArr[it], GPIO_OUT_2M_PP);
    GPIO_voidSetPinDirection(colPortArr[it], colPinArr[it], GPIO_OUT_2M_PP);
  }
}

void LEDMRX_voidDisplay(u8 *copy_u8Data)
{
  // Disable all columns 
  for (u8 col = 0 ; col < COL_NUM ; col++) {
    GPIO_voidSetPinValue(colPortArr[col], colPinArr[col], GPIO_HIGH);
  }
  for (u8 col =0 ; col < COL_NUM ; col++) {
    for (u8 row = 0; row < ROW_NUM ; row++) {
      //set the data values for each row 
      u8 localu8Bit = GET_BIT(copy_u8Data[col],row);
      GPIO_voidSetPinValue(rowPortArr[row], rowPinArr[row], localu8Bit);
    }
    //activate the cloumn
    GPIO_voidSetPinValue(colPortArr[col], colPinArr[col], GPIO_LOW);
    
    //delay  2.5 ms
    STK_voidBusyWait(2500) ;

    //disable the column 
    GPIO_voidSetPinValue(colPortArr[col], colPinArr[col], GPIO_HIGH);
  }
}
