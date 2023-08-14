#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

/**
 * @brief Initializes the LCD display.
 *
 * @return Error state of the LCD operation. Returns:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.*
 */
ES_t LCD_Init(void);

/**
 * @brief Writes a command to the LCD display.
 *
 * @param Command The command to be written.
 * @return Error state of the LCD operation. Returns:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.*
 */
ES_t LCD_WriteCommand(u8 Command);

/**
 * @brief Writes data to the LCD display.
 *
 * @param Data The data to be written.
 * @return Error state of the LCD operation. Returns:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.*
 */
ES_t LCD_WriteData(u8 Data);

/**
 * @brief Writes a signed integer number to the LCD display.
 *
 * @param Number The number to be written.
 * @return Error state of the LCD operation. Returns:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.*
 */
ES_t LCD_WriteDigits(s32 Number);

/**
 * @brief Writes a null-terminated string to the LCD display.
 *
 * @param String Pointer to the string to be written.
 * @return Error state of the LCD operation. Returns:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.*
 *         - ES_NULL_POINTER: argument is null 
 */
ES_t LCD_WriteString(char *String);

/**
 * @brief Sets the cursor position on the LCD display.
 *
 * @param X_Pos X position (0 or 1) of the cursor.
 * @param Y_Pos Y position (0-15) of the cursor.
 * @return Error state of the LCD operation. Returns:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.*
 */
ES_t LCD_GoToXY(u8 X_Pos, u8 Y_Pos);

/**
 * @brief Writes a special character to the LCD display.
 *
 * @param Special_Character Pointer to the special character data.
 * @param CGRAM_Index Index of the character in the CGRAM (0-7).
 * @param X_Pos X position (0 or 1) of the character.
 * @param Y_Pos Y position (0-15) of the character.
 * @return Error state of the LCD operation. Returns:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.*
 *         - ES_NULL_POINTER: argument is null 
 */
ES_t LCD_WriteSpecial(u8 *Special_Character, u8 CGRAM_Index, u8 X_Pos, u8 Y_Pos);

#endif
