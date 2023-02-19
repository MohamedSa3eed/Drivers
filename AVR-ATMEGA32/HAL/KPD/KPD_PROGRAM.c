#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "KPD_INTERFACE.h"
#include "KPD_CONFIG.h"
#include "KPD_PRIVATE.h"

void KPD_Init(void)
{
  //initialize columns
  DIO_SetPinDirection(KPD_PORT, KPD_COLUMN0_PIN , HIGH);
  DIO_SetPinDirection(KPD_PORT, KPD_COLUMN1_PIN , HIGH);
  DIO_SetPinDirection(KPD_PORT, KPD_COLUMN2_PIN , HIGH);
  DIO_SetPinDirection(KPD_PORT, KPD_COLUMN3_PIN , HIGH);

  //initialize rows
  DIO_SetPinDirection(KPD_PORT, KPD_ROW0_PIN , INPUT);
  DIO_SetPinDirection(KPD_PORT, KPD_ROW1_PIN , INPUT);
  DIO_SetPinDirection(KPD_PORT, KPD_ROW2_PIN , INPUT);
  DIO_SetPinDirection(KPD_PORT, KPD_ROW3_PIN , INPUT);

  //make all pins high 
  DIO_SetPortDirection(KPD_PORT, PORT_HIGH);
}

u8 KPD_GetPressedKey(void)
{
		u8 Local_PressedKey = KPD_NOT_PRESSED ; //indication value for not pressing
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
				u8 value = DIO_GetPinValue(KPD_PORT, Local_RowPinsArr[row_index]);
				// check if current switch is pressed (low value)
				if(value == LOW)
				{
					Local_PressedKey = Local_KPDArr[row_index][col_index] ;  //pressed value

					// busy waiting until switch is released     human takes 250ms to press the switch
					while (value == LOW )
					{
						value =  DIO_GetPinValue(KPD_PORT, Local_RowPinsArr[row_index]);   //refreshing the value
					}
					return Local_PressedKey ;
				}
			}
			// deactivate the current column with high
			DIO_SetPinValue(KPD_PORT, Local_ColPinsArr[col_index], HIGH);
		}
	return Local_PressedKey;
}
