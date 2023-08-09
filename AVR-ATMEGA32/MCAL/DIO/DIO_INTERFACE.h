#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

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
 HIGH = 1 ,
 FLOAT = 2,
 PULL_UP = 3
};

enum PORT_VALUE
{
	PORT_LOW  = 0 ,
	PORT_HIGH = 0xFF ,
	LAST_4HIGH = 0xf0 ,
	FIRIST_4HIGH = 0x0f
};

enum PORT_DIRECTION
{
	PORT_INPUT  = 0 ,
	PORT_OUTPUT = 0xff , 
	LAST_4OUTPUT = 0xf0 ,
	FIRIST_4OUTPUT = 0x0f
};

/**
 * @brief Sets the direction of a specific pin in a given port.
 *
 * This function is used to set the direction (input or output) of a specific pin
 * in a specified port of a microcontroller.
 *
 * @param Copy_u8Port: The port to which the pin belongs. It can be one of the following values:
 *                     - PORTA
 *                     - PORTB
 *                     - PORTC
 *                     - PORTD
 * @param Copy_u8Pin: The pin number whose direction will be set. It can be a value from PIN0 to PIN7.
 * @param Copy_u8Direction: The desired direction for the pin. It can be one of the following values:
 *                          - INPUT: Set the pin as an input.
 *                          - OUTPUT: Set the pin as an output.
 *
 * @return ES_t: An enumeration of type ES_t representing the error state of the function.
 *               - ES_OK: The function executed successfully.
 *               - ES_OUT_OF_RANGE: The provided port or direction is out of range.
 *               - ES_NOK: An unknown error occurred during execution.
 */
ES_t DIO_SetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);

/**
 * @brief Sets the value of a specific pin in a given port.
 *
 * This function is used to set the value (logic level) of a specific pin in a specified
 * port of a microcontroller.
 *
 * @param Copy_u8Port: The port to which the pin belongs. It can be one of the following values:
 *                     - PORTA
 *                     - PORTB
 *                     - PORTC
 *                     - PORTD
 * @param Copy_u8Pin: The pin number whose value will be set. It can be a value from PIN0 to PIN7.
 * @param Copy_u8Value: The desired value for the pin. It can be one of the following values:
 *                      - LOW: Set the pin to logic low (0V).
 *                      - FLOAT: Set the pin to floating state (disconnected from internal pull-up or pull-down resistors).
 *                      - HIGH: Set the pin to logic high (Vcc).
 *                      - PULL_UP: Set the pin to logic high (Vcc) and enable the internal pull-up resistor.
 *
 * @return ES_t: An enumeration of type ES_t representing the error state of the function.
 *               - ES_OK: The function executed successfully.
 *               - ES_OUT_OF_RANGE: The provided port or value is out of range.
 *               - ES_NOK: An unknown error occurred during execution.
 */
ES_t  DIO_SetPinValue    ( u8 Copy_u8Port , u8 Copy_u8Pin ,u8 Copy_u8Value);

/**
 * @brief Retrieves the value of a specific pin in a given port.
 *
 * This function is used to retrieve the value (logic level) of a specific pin in a specified
 * port of a microcontroller.
 *
 * @param Copy_u8Port: The port to which the pin belongs. It can be one of the following values:
 *                     - PORTA
 *                     - PORTB
 *                     - PORTC
 *                     - PORTD
 * @param Copy_u8Pin: The pin number whose value will be retrieved. It can be a value from PIN0 to PIN7.
 * @param Copy_pu8Value: Pointer to a variable where the retrieved pin value will be stored.
 *                      The value can be one of the following:
 *                      - 0: Logic low (0V).
 *                      - 1: Logic high (Vcc).
 *
 * @return ES_t: An enumeration of type ES_t representing the error state of the function.
 *               - ES_OK: The function executed successfully.
 *               - ES_OUT_OF_RANGE: The provided port is out of range.
 *               - ES_NULL_POINTER: The provided pointer is NULL.
 *               - ES_NOK: An unknown error occurred during execution.
 */
ES_t  DIO_GetPinValue    ( u8 Copy_u8Port , u8 Copy_u8Pin ,u8 *Copy_pu8Value);

/**
 * @brief Toggles the value of a specific pin in a given port.
 *
 * This function is used to toggle (invert) the value of a specific pin in a specified
 * port of a microcontroller. If the pin was previously logic high, it will be set to logic low,
 * and if it was previously logic low, it will be set to logic high.
 *
 * @param Copy_u8Port: The port to which the pin belongs. It can be one of the following values:
 *                     - PORTA
 *                     - PORTB
 *                     - PORTC
 *                     - PORTD
 * @param Copy_u8Pin: The pin number to be toggled. It can be a value from PIN0 to PIN7.
 *
 * @return ES_t: An enumeration of type ES_t representing the error state of the function.
 *               - ES_OK: The function executed successfully.
 *               - ES_OUT_OF_RANGE: The provided port or pin number is out of range.
 *               - ES_NOK: An unknown error occurred during execution.
 */
ES_t DIO_TogglePin(u8 Copy_u8Port, u8 Copy_u8Pin);

/**
 * @brief Sets the direction of all pins in a given port.
 *
 * This function is used to set the direction (input or output) of all pins in a specified
 * port of a microcontroller.
 *
 * @param Copy_u8Port: The port for which the pins' direction will be set. It can be one of the following values:
 *                     - PORTA
 *                     - PORTB
 *                     - PORTC
 *                     - PORTD
 * @param Copy_u8Direction: The desired direction for the port. It can be one of the following values from the PORT_DIRECTION enum:
 *                          - PORT_INPUT: Set all pins in the port as inputs.
 *                          - PORT_OUTPUT: Set all pins in the port as outputs.
 *                          - LAST_4OUTPUT: Set the last 4 pins in the port as outputs and the rest as inputs.
 *                          - FIRST_4OUTPUT: Set the first 4 pins in the port as outputs and the rest as inputs.
 *
 * @return ES_t: An enumeration of type ES_t representing the error state of the function.
 *               - ES_OK: The function executed successfully.
 *               - ES_OUT_OF_RANGE: The provided port or direction is out of range.
 *               - ES_NOK: An unknown error occurred during execution.
 */
ES_t  DIO_SetPortDirection (u8 Copy_u8Port , u8 Copy_u8Direction );

/**
 * @brief Sets the value of a specific pin in a given port.
 *
 * This function is used to set the value (logic level) of a specific pin in a specified
 * port of a microcontroller.
 *
 * @param Copy_u8Port: The port to which the pin belongs. It can be one of the following values:
 *                     - PORTA
 *                     - PORTB
 *                     - PORTC
 *                     - PORTD
 * @param Copy_u8Value: The desired value for the pin. It can be one of the following values from the PORT_VALUE enum:
 *                      - PORT_LOW: Set the pin to logic low (0V).
 *                      - PORT_HIGH: Set the pin to logic high (Vcc).
 *                      - LAST_4HIGH: Set the last 4 pins in the port to logic high and the rest to logic low.
 *                      - FIRST_4HIGH: Set the first 4 pins in the port to logic high and the rest to logic low.
 *
 * @return ES_t: An enumeration of type ES_t representing the error state of the function.
 *               - ES_OK: The function executed successfully.
 *               - ES_OUT_OF_RANGE: The provided port or value is out of range.
 *               - ES_NOK: An unknown error occurred during execution.
 */
ES_t  DIO_SetPortValue     (u8 Copy_u8Port , u8 Copy_u8Value);

/**
 * @brief Retrieves the value of all pins in a given port.
 *
 * This function is used to retrieve the value (logic level) of all pins in a specified
 * port of a microcontroller.
 *
 * @param Copy_u8Port: The port from which the pin values will be retrieved. It can be one of the following values:
 *                     - PORTA
 *                     - PORTB
 *                     - PORTC
 *                     - PORTD
 * @param Copy_pu8Value: Pointer to a variable where the retrieved port value will be stored.
 *
 * @return ES_t: An enumeration of type ES_t representing the error state of the function.
 *               - ES_OK: The function executed successfully.
 *               - ES_OUT_OF_RANGE: The provided port is out of range.
 *               - ES_NULL_POINTER: The provided pointer is NULL.
 *               - ES_NOK: An unknown error occurred during execution.
 */
ES_t  DIO_GetPortValue     (u8 Copy_u8Port , u8 *Copy_pu8Value);

/**
 * @brief Toggles the value of all pins in a given port.
 *
 * This function is used to toggle (invert) the value of all pins in a specified
 * port of a microcontroller. If a pin was previously logic high, it will be set to logic low,
 * and if it was previously logic low, it will be set to logic high.
 *
 * @param Copy_u8Port: The port for which the pins' values will be toggled. It can be one of the following values:
 *                     - PORTA
 *                     - PORTB
 *                     - PORTC
 *                     - PORTD
 *
 * @return ES_t: An enumeration of type ES_t representing the error state of the function.
 *               - ES_OK: The function executed successfully.
 *               - ES_OUT_OF_RANGE: The provided port is out of range.
 *               - ES_NOK: An unknown error occurred during execution.
 */
ES_t DIO_TogglePort(u8 Copy_u8Port);

#endif 
