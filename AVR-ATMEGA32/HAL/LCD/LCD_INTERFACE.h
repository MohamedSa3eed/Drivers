#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

void LCD_Init(void);
void LCD_WriteCommand(u8 Command);
void LCD_WriteData(u8 Data);
void LCD_WriteDigits(s32 Number);
void LCD_WriteString(char *String);
void LCD_GoToXY(u8 X_Pos,u8 Y_Pos);
void LCD_WriteSpecial(u8 * Special_Character,u8 CGRAM_Index,u8 X_Pos ,u8 Y_Pos );

#endif
