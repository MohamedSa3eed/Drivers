#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#include "../../LIB/STD_TYPES.h"

enum PORT
{
 PORTA = 0 ,
 PORTB = 1 ,
 PORTC = 2 ,
 PORTD = 3
};

enum PIN 
{
 PIN0 = 0 ,
 PIN1 = 1 ,
 PIN2 = 2 ,
 PIN3 = 3 ,
 PIN4 = 4 ,
 PIN5 = 5 ,
 PIN6 = 6 ,
 PIN7 = 7
};

enum DIRECTION 
{
 INPUT  = 0 ,
 OUTPUT = 1
};

enum VALUE
{
 LOW  = 0 ,
 HIGH = 1 
};

enum PORT_VALUE
{
	PORT_LOW  = 0 ,
	PORT_HIGH = 0xFF ,
	LAST_4HIGH = 0xf0
};
enum PORT_DIRECTION
{
	PORT_INPUT  = 0 ,
	PORT_OUTPUT = 0xff , 
	LAST_4OUTPUT = 0xf0
};

void DIO_SetPinDirection( u8 Port , u8 Pin , u8 Direction);
void DIO_SetPinValue    ( u8 Port , u8 Pin ,u8 Value);
u8   DIO_GetPinValue    ( u8 Port , u8 Pin);

void DIO_SetPortDirection (u8 Port , u8 Direction );
void DIO_SetPortValue     (u8 Port , u8 Value);
u8   DIO_GetPortValue     (u8 Port);

#endif 
