#include </usr/avr/include/avr/delay.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "LCD_INTERFACE.h"
#include "LCD_CONFIG.h"
#include "LCD_PRIVATE.h"

#if CONNECTION == _8_PINS
void LCD_Init(void)
{
	DIO_SetPinDirection(GPORT,RS,OUTPUT);
	DIO_SetPinDirection(GPORT,EN,OUTPUT);
	DIO_SetPinDirection(GPORT,RW,OUTPUT);
	DIO_SetPortDirection(LCD_PORT,PORT_OUTPUT); //all high
	_delay_ms(100);  //delay from data sheet
	LCD_WriteCommand(function_set_2Lines);
	_delay_ms(1);
	LCD_WriteCommand(dispaly_on);
	_delay_ms(1);
	LCD_WriteCommand(clear);
	_delay_ms(2);
	LCD_WriteCommand(entry_mode);

}
void LCD_WriteCommand(u8 Command)
{
	DIO_SetPinValue(GPORT , RS ,LOW);  //RS
	DIO_SetPinValue(GPORT , RW ,LOW);  //R/W 
	DIO_SetPinValue(GPORT,EN,HIGH);
	DIO_SetPortValue(LCD_PORT,Command);
	_delay_ms(1);
	DIO_SetPinValue(GPORT,EN,LOW);

}
void LCD_WriteData(u8 Data)
{
	DIO_SetPinValue(GPORT , RS ,HIGH);  //RS
	DIO_SetPinValue(GPORT , RW ,LOW);  //R/W 
	DIO_SetPinValue(GPORT,EN,HIGH);
	DIO_SetPortValue(LCD_PORT,Data);
	_delay_ms(1);
	DIO_SetPinValue(GPORT,EN,LOW);

}
#elif CONNECTION==_4_PINS
 u8 init_flag = 0;
void LCD_Init(void)
{
	DIO_SetPinDirection(GPORT,RS,OUTPUT);
	DIO_SetPinDirection(GPORT,RW,OUTPUT);
	DIO_SetPinDirection(GPORT,EN,OUTPUT);
	DIO_SetPortDirection(LCD_PORT,LAST_4OUTPUT);
	_delay_ms(100);
	LCD_WriteCommand(function_set);
	LCD_WriteCommand(function_set);
	LCD_WriteCommand(function_set_2Lines);
	init_flag =1 ;
	_delay_ms(1);
	LCD_WriteCommand(dispaly_on);
	_delay_ms(1);
	LCD_WriteCommand(clear);
	_delay_ms(2);
	LCD_WriteCommand(entry_mode);

}

void LCD_WriteCommand(u8 Command)
{
	DIO_SetPinValue(GPORT , RS ,LOW);  //RS
	DIO_SetPinValue(GPORT , RW ,LOW);  //R/W 
	DIO_SetPinValue(GPORT , EN ,HIGH);
	DIO_SetPinValue(LCD_PORT ,PIN4 ,GET_BIT(Command,4));
	DIO_SetPinValue(LCD_PORT ,PIN5 ,GET_BIT(Command,5));
	DIO_SetPinValue(LCD_PORT ,PIN6 ,GET_BIT(Command,6));
	DIO_SetPinValue(LCD_PORT ,PIN7 ,GET_BIT(Command,7));
	_delay_ms(1);
	DIO_SetPinValue(GPORT,EN,LOW);
	if(init_flag==1)
	{
	_delay_ms(1);
	DIO_SetPinValue(GPORT , EN ,HIGH);
	DIO_SetPinValue(LCD_PORT ,PIN4 ,GET_BIT(Command,0));
	DIO_SetPinValue(LCD_PORT ,PIN5 ,GET_BIT(Command,1));
	DIO_SetPinValue(LCD_PORT ,PIN6 ,GET_BIT(Command,2));
	DIO_SetPinValue(LCD_PORT ,PIN7 ,GET_BIT(Command,3));
	_delay_ms(1);
	DIO_SetPinValue(GPORT,EN,LOW);
        _delay_ms(2);
	}
}

void LCD_WriteData(u8 Data)
{
	DIO_SetPinValue(GPORT , RS ,HIGH);  //RS
	DIO_SetPinValue(GPORT , RW ,LOW);  //R/W 
	DIO_SetPinValue(GPORT , EN ,HIGH);
	DIO_SetPinValue(LCD_PORT ,PIN4 ,GET_BIT(Data,4));
	DIO_SetPinValue(LCD_PORT ,PIN5 ,GET_BIT(Data,5));
	DIO_SetPinValue(LCD_PORT ,PIN6 ,GET_BIT(Data,6));
	DIO_SetPinValue(LCD_PORT ,PIN7 ,GET_BIT(Data,7));
	_delay_ms(1);
	DIO_SetPinValue(GPORT,EN,LOW);
	_delay_ms(1);
	DIO_SetPinValue(GPORT , EN ,HIGH);
	DIO_SetPinValue(LCD_PORT ,PIN4 ,GET_BIT(Data,0));
	DIO_SetPinValue(LCD_PORT ,PIN5 ,GET_BIT(Data,1));
	DIO_SetPinValue(LCD_PORT ,PIN6 ,GET_BIT(Data,2));
	DIO_SetPinValue(LCD_PORT ,PIN7 ,GET_BIT(Data,3));
	_delay_ms(1);
	DIO_SetPinValue(GPORT,EN,LOW);
        _delay_ms(2);
}

#else 
       #error   "WRONG CONNECTION"

#endif
void LCD_WriteString(char *String)
{
	u8 i =0;
	while(String[i] != '\0')
	{
		LCD_WriteData(String[i]);
		i++;
	}
}

void LCD_GoToXY(u8 X_Pos,u8 Y_Pos)
{
	u8 Local_Adress ;
	if(X_Pos == 0 )
	{
		Local_Adress = Y_Pos ;
	}
	else if (X_Pos == 1)
	{
		Local_Adress = Y_Pos + 0x40 ;
	}
	LCD_WriteCommand(Local_Adress+128);   // + 0x80
}

void LCD_WriteDigits(s32 Number)
{
	u32 remainder;
	u8 LocalArrOfDigits[10]={0};
	u8 index =0 ;
	if(Number == 0)
	{
		LCD_WriteData('0');
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
			LCD_WriteData(LocalArrOfDigits[index]+'0');
			index--;
		}
		LCD_WriteData(LocalArrOfDigits[0]+'0');
	}
	else if (Number<0)
	{
		LCD_WriteData('-');
		LCD_WriteDigits(-Number);
	}

}
void LCD_WriteSpecial(u8 * Special_Character,u8 CGRAM_Index,u8 X_Pos ,u8 Y_Pos )
{
	LCD_GoToXY(X_Pos, Y_Pos);
	LCD_WriteData(CGRAM_Index);
	u8 Local_Adress= CGRAM_Index*8  ;
        SET_BIT(Local_Adress,6); //from data sheet
	LCD_WriteCommand(Local_Adress); //start writting in CGRAM
	for (u8 Local_Index = 0; Local_Index < 8; Local_Index++) {
		LCD_WriteData(Special_Character[Local_Index]);
	}
	LCD_WriteCommand(return_to_0x00_in_DDRAM);
}
