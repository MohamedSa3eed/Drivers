#include "../../LIB/STD_TYPES.h"
#include "../../LIB//ERR_STATE.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "KPD_INTERFACE.h"
#include "KPD_CONFIG.h"
#include "KPD_PRIVATE.h"

ES_t KPD_Init(void)
{
  ES_t Local_u8ErrorState = ES_NOK ;
  //initialize columns
  Local_u8ErrorState = DIO_SetPinDirection(KPD_PORT, KPD_COLUMN0_PIN , HIGH);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }
  Local_u8ErrorState = DIO_SetPinDirection(KPD_PORT, KPD_COLUMN1_PIN , HIGH);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }
  Local_u8ErrorState = DIO_SetPinDirection(KPD_PORT, KPD_COLUMN2_PIN , HIGH);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }
  Local_u8ErrorState = DIO_SetPinDirection(KPD_PORT, KPD_COLUMN3_PIN , HIGH);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }

  //initialize rows
  Local_u8ErrorState = DIO_SetPinDirection(KPD_PORT, KPD_ROW0_PIN , INPUT);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }
  Local_u8ErrorState = DIO_SetPinDirection(KPD_PORT, KPD_ROW1_PIN , INPUT);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }
  Local_u8ErrorState = DIO_SetPinDirection(KPD_PORT, KPD_ROW2_PIN , INPUT);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }
  Local_u8ErrorState = DIO_SetPinDirection(KPD_PORT, KPD_ROW3_PIN , INPUT);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }

  //make all pins high 
  Local_u8ErrorState = DIO_SetPortValue(KPD_PORT, PORT_HIGH);
  return Local_u8ErrorState ;
}

ES_t KPD_GetPressedKey(u8 *Copy_pu8Key)
{
  ES_t Local_u8ErrorState = ES_NOK ;
  u8 Local_PressedKey = KPD_NOT_PRESSED ; //indication value for not pressing
  u8 Local_pu8Value ;
  u8 row_index , col_index ;   //for iteration
  u8 Local_ColPinsArr[KPD_COLUMNS]={ KPD_COLUMN0_PIN , KPD_COLUMN1_PIN , KPD_COLUMN2_PIN , KPD_COLUMN3_PIN };
  u8 Local_RowPinsArr[KPD_ROWS]={ KPD_ROW0_PIN , KPD_ROW1_PIN , KPD_ROW2_PIN , KPD_ROW3_PIN };
  u8 Local_KPDArr[KPD_ROWS][KPD_COLUMNS] = KPD_VALUES ;
  for(col_index =0;col_index<KPD_COLUMNS;col_index ++)
  {
    // activate current column with low
    DIO_SetPinValue(KPD_PORT, Local_ColPinsArr[col_index], LOW);
    for(row_index=0 ; row_index<KPD_ROWS;row_index ++)
    {
      // read the value of current row (current switch)
      Local_u8ErrorState = DIO_GetPinValue(KPD_PORT, Local_RowPinsArr[row_index], &Local_pu8Value);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      // check if current switch is pressed (low value)
      if(Local_pu8Value == LOW)
      {
        Local_PressedKey = Local_KPDArr[row_index][col_index] ;  //pressed value
        // busy waiting until switch is released     human takes 250ms to press the switch
        while (Local_pu8Value == LOW )
        {
          Local_u8ErrorState =  DIO_GetPinValue(KPD_PORT, Local_RowPinsArr[row_index], &Local_pu8Value);   //refreshing the value
          if (Local_u8ErrorState != ES_OK) {
            return Local_u8ErrorState ;
          }
        }
        *Copy_pu8Key = Local_PressedKey ;
        return Local_u8ErrorState ;
      }
    }
    // deactivate the current column with high
    Local_u8ErrorState = DIO_SetPinValue(KPD_PORT, Local_ColPinsArr[col_index], HIGH);
    if (Local_u8ErrorState != ES_OK) {
      return Local_u8ErrorState ;
    }
  }
  *Copy_pu8Key = Local_PressedKey ;
  return Local_u8ErrorState ;
}
