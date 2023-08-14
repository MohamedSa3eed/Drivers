#include </usr/avr/include/avr/delay.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERR_STATE.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "LCD_INTERFACE.h"
#include "LCD_CONFIG.h"
#include "LCD_PRIVATE.h"

#if CONNECTION == _8_PINS
ES_t LCD_Init(void)
{
  ES_t Local_enumErrorState = ES_NOK ;
	Local_enumErrorState = DIO_SetPinDirection(GPORT,RS,OUTPUT);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinDirection(GPORT,EN,OUTPUT);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinDirection(GPORT,RW,OUTPUT);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPortDirection(LCD_PORT,PORT_OUTPUT); //all high
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(100);  //delay from data sheet
	Local_enumErrorState = LCD_WriteCommand(function_set_2Lines);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(1);
	Local_enumErrorState = LCD_WriteCommand(dispaly_on);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(1);
	Local_enumErrorState = LCD_WriteCommand(clear);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(2);
	Local_enumErrorState = LCD_WriteCommand(entry_mode);
  return Local_enumErrorState ;
}
ES_t LCD_WriteCommand(u8 Command)
{
  ES_t Local_enumErrorState = ES_NOK ;
	DIO_SetPinValue(GPORT , RS ,LOW);  //RS
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	DIO_SetPinValue(GPORT , RW ,LOW);  //R/W 
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	DIO_SetPinValue(GPORT,EN,HIGH);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	DIO_SetPortValue(LCD_PORT,Command);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(1);
	DIO_SetPinValue(GPORT,EN,LOW);
  return Local_enumErrorState ;
}
ES_t LCD_WriteData(u8 Data)
{
  ES_t Local_enumErrorState = ES_NOK ;
	Local_enumErrorState = DIO_SetPinValue(GPORT , RS ,HIGH);  //RS
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(GPORT , RW ,LOW);  //R/W 
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(GPORT,EN,HIGH);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPortValue(LCD_PORT,Data);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(1);
	Local_enumErrorState = DIO_SetPinValue(GPORT,EN,LOW);
  return Local_enumErrorState;
}

#elif CONNECTION==_4_PINS
 u8 init_flag = 0;
ES_t LCD_Init(void)
{
  ES_t Local_enumErrorState = ES_NOK ;
	Local_enumErrorState = DIO_SetPinDirection(GPORT,RS,OUTPUT);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinDirection(GPORT,RW,OUTPUT);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinDirection(GPORT,EN,OUTPUT);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPortDirection(LCD_PORT,LAST_4OUTPUT);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(100);
	Local_enumErrorState = LCD_WriteCommand(function_set);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = LCD_WriteCommand(function_set);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = LCD_WriteCommand(function_set_2Lines);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	init_flag =1 ;
	_delay_ms(1);
	Local_enumErrorState = LCD_WriteCommand(dispaly_on);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(1);
	Local_enumErrorState = LCD_WriteCommand(clear);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(2);
	Local_enumErrorState = LCD_WriteCommand(entry_mode);
  return Local_enumErrorState ;
}

void LCD_WriteCommand(u8 Command)
{
  ES_t Local_enumErrorState = ES_NOK ;
	Local_enumErrorState = DIO_SetPinValue(GPORT , RS ,LOW);  //RS
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(GPORT , RW ,LOW);  //R/W 
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(GPORT , EN ,HIGH);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN4 ,GET_BIT(Command,4));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN5 ,GET_BIT(Command,5));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN6 ,GET_BIT(Command,6));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN7 ,GET_BIT(Command,7));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(1);
	Local_enumErrorState = DIO_SetPinValue(GPORT,EN,LOW);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	if(init_flag==1)
	{
	_delay_ms(1);
	Local_enumErrorState = DIO_SetPinValue(GPORT , EN ,HIGH);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN4 ,GET_BIT(Command,0));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN5 ,GET_BIT(Command,1));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN6 ,GET_BIT(Command,2));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN7 ,GET_BIT(Command,3));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(1);
	Local_enumErrorState = DIO_SetPinValue(GPORT,EN,LOW);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
  _delay_ms(2);
	}
  return Local_enumErrorState ;
}

ES_t LCD_WriteData(u8 Data)
{
  ES_t Local_enumErrorState = ES_NOK ;
	Local_enumErrorState = DIO_SetPinValue(GPORT , RS ,HIGH);  //RS
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(GPORT , RW ,LOW);  //R/W 
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(GPORT , EN ,HIGH);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN4 ,GET_BIT(Data,4));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN5 ,GET_BIT(Data,5));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN6 ,GET_BIT(Data,6));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN7 ,GET_BIT(Data,7));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(1);
	Local_enumErrorState = DIO_SetPinValue(GPORT,EN,LOW);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(1);
	Local_enumErrorState = DIO_SetPinValue(GPORT , EN ,HIGH);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN4 ,GET_BIT(Data,0));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN5 ,GET_BIT(Data,1));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN6 ,GET_BIT(Data,2));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = DIO_SetPinValue(LCD_PORT ,PIN7 ,GET_BIT(Data,3));
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	_delay_ms(1);
	Local_enumErrorState = DIO_SetPinValue(GPORT,EN,LOW);
  _delay_ms(2);
  return Local_enumErrorState ;
}

#else 
       #error   "WRONG CONNECTION"

#endif

ES_t LCD_WriteString(char *String)
{
  ES_t Local_enumErrorState = ES_NOK ;
  if (String == NULL) {
    return ES_NULL_POINTER;
  }
	u8 i =0;
	while(String[i] != '\0')
	{
		Local_enumErrorState = LCD_WriteData(String[i]);
    if (Local_enumErrorState != ES_OK) {
      return Local_enumErrorState ;
    }
		i++;
	}
  return Local_enumErrorState ;
}

ES_t LCD_GoToXY(u8 X_Pos,u8 Y_Pos)
{
  ES_t Local_enumErrorState = ES_NOK ;
	u8 Local_Adress ;
	if(X_Pos == 0)
	{
		Local_Adress = Y_Pos ;
    Local_enumErrorState = LCD_WriteCommand(Local_Adress+128);   // + 0x80
	}
	else if(X_Pos == 1)
	{
		Local_Adress = Y_Pos + 0x40 ;
    Local_enumErrorState = LCD_WriteCommand(Local_Adress+128);   // + 0x80
	}
  else 
  {
    Local_enumErrorState = ES_OUT_OF_RANGE ; 
  }
  return Local_enumErrorState;
}

ES_t LCD_WriteDigits(s32 Number)
{
  ES_t Local_enumErrorState = ES_NOK ;
	u32 remainder;
	u8 LocalArrOfDigits[10]={0};
	u8 index =0 ;
	if(Number == 0)
	{
		Local_enumErrorState = LCD_WriteData('0');
	}
	else if(Number>0)
	{
		while(Number!=0)
		{
			remainder = Number % 10 ;
			LocalArrOfDigits[index]=remainder ;
			Number =Number/ 10 ;
			index++;
		}
		index -- ;
		while(index>0)
		{
			Local_enumErrorState = LCD_WriteData(LocalArrOfDigits[index]+'0');
      if (Local_enumErrorState != ES_OK) {
        return Local_enumErrorState ;
      }
			index--;
		}
		Local_enumErrorState = LCD_WriteData(LocalArrOfDigits[0]+'0');
	}
	else if (Number<0)
	{
		Local_enumErrorState = LCD_WriteData('-');
    if (Local_enumErrorState != ES_OK) {
      return Local_enumErrorState ;
    }
		Local_enumErrorState = LCD_WriteDigits(-Number);
	}
  return Local_enumErrorState ;
}

ES_t LCD_WriteSpecial(u8 * Special_Character,u8 CGRAM_Index,u8 X_Pos ,u8 Y_Pos )
{
  ES_t Local_enumErrorState = ES_NOK ;
  if (Special_Character == NULL) {
    return ES_NULL_POINTER;
  }
	Local_enumErrorState = LCD_GoToXY(X_Pos, Y_Pos);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	Local_enumErrorState = LCD_WriteData(CGRAM_Index);
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	u8 Local_Adress= CGRAM_Index*8  ;
        SET_BIT(Local_Adress,6); //from data sheet
	Local_enumErrorState = LCD_WriteCommand(Local_Adress); //start writting in CGRAM
  if (Local_enumErrorState != ES_OK) {
    return Local_enumErrorState ;
  }
	for (u8 Local_Index = 0; Local_Index < 8; Local_Index++) {
		Local_enumErrorState = LCD_WriteData(Special_Character[Local_Index]);
    if (Local_enumErrorState != ES_OK) {
      return Local_enumErrorState ;
    }
	}
	Local_enumErrorState = LCD_WriteCommand(return_to_0x00_in_DDRAM);
  return Local_enumErrorState;
}
