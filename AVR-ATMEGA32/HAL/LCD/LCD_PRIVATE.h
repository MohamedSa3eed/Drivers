#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H


#define	_8_PINS  1
#define	_4_PINS  2

#if CONNECTION == _8_PINS

#define function_set_2Lines     0x38
#define function_set_1line      0x30

#elif CONNECTION == _4_PINS

#define function_set            0x20 //this command used twice then choose one of the next 2 commands
				     //according to the data sheet
#define function_set_2Lines     0x80
#define function_set_1line      0xc0

#endif
#endif 
