#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

/**
 * @brief Enumeration for UART parity settings.
 */
typedef enum {
  UART_PARITY_DISABLED = 0,  /**< No parity */
  UART_PARITY_EVEN = 2,      /**< Even parity */
  UART_PARITY_ODD = 3        /**< Odd parity */
} UART_Parity_t;

/**
 * @brief Enumeration for UART stop bit settings.
 */
typedef enum {
  UART_STOP_BIT_1 = 0,  /**< 1 stop bit */
  UART_STOP_BIT_2 = 1   /**< 2 stop bits */
} UART_StopBit_t;

/**
 * @brief Enumeration for UART data bit settings.
 */
typedef enum {
  UART_5BIT_DATA = 0,  /**< 5 data bits */
  UART_6BIT_DATA = 1,  /**< 6 data bits */
  UART_7BIT_DATA = 2,  /**< 7 data bits */
  UART_8BIT_DATA = 3,  /**< 8 data bits */
  UART_9BIT_DATA = 7   /**< 9 data bits */
} UART_DataBits_t;

/**
 * @brief Enumeration for UART double-speed mode settings.
 */
typedef enum {
  UART_DOUBLE_SPEED_OFF = 1,  /**< Double-speed mode disabled */
  UART_DOUBLE_SPEED_ON = 0    /**< Double-speed mode enabled */
} UART_DoubleSpeed_t;

/**
 * @brief Initialize the UART module with specified parameters.
 *
 * @param Copy_u32BaudRate   Baud rate for UART communication.
 * @param Copy_enumDataBits  Number of data bits.
 * @param Copy_enumParity    Parity setting.
 * @param Copy_enumStopBits  Number of stop bits.
 * @param Copy_enumDoubleSpeed Double-speed mode setting.
 * @return ES_OK if successful, ES_OUT_OF_RANGE if input values are invalid.
 */
ES_t UART_Init(u32 Copy_u32BaudRate, UART_DataBits_t Copy_enumDataBits, UART_Parity_t Copy_enumParity, UART_StopBit_t Copy_enumStopBits, UART_DoubleSpeed_t Copy_enumDoubleSpeed);

/**
 * @brief Enable the transmit unit of the UART module.
 * @return ES_OK if successful.
 */
ES_t UART_EnableTransmitUnit(void);

/**
 * @brief Disable the transmit unit of the UART module.
 * @return ES_OK if successful.
 */
ES_t UART_DisableTransmitUnit(void);

/**
 * @brief Enable the receive unit of the UART module.
 * @return ES_OK if successful.
 */
ES_t UART_EnableRecieveUnit(void);

/**
 * @brief Disable the receive unit of the UART module.
 * @return ES_OK if successful.
 */
ES_t UART_DisableRecieveUnit(void);

/**
 * @brief Set the callback function for the transmit complete interrupt.
 *
 * @param Pfunc Pointer to the callback function.
 * @return ES_OK if successful, ES_NULL_POINTER if Pfunc is NULL.
 */
ES_t UART_SetTransmitCompleteInterruptCallBack(void (*Pfunc)(void));

/**
 * @brief Set the callback function for the receive complete interrupt.
 *
 * @param Pfunc Pointer to the callback function.
 * @return ES_OK if successful, ES_NULL_POINTER if Pfunc is NULL.
 */
ES_t UART_SetRecieveCompleteInterruptCallBack(void (*Pfunc)(void));

/**
 * @brief Set the callback function for the data register empty interrupt.
 *
 * @param Pfunc Pointer to the callback function.
 * @return ES_OK if successful, ES_NULL_POINTER if Pfunc is NULL.
 */
ES_t UART_SetDataRegisterEmptyInterruptCallBack(void (*Pfunc)(void));

/**
 * @brief Enable the transmit complete interrupt.
 * @return ES_OK if successful.
 */
ES_t UART_TransmitCompleteInterruptEnable(void);

/**
 * @brief Enable the receive complete interrupt.
 * @return ES_OK if successful.
 */
ES_t UART_RecieveCompleteInterruptEnable(void);

/**
 * @brief Enable the data register empty interrupt.
 * @return ES_OK if successful.
 */
ES_t UART_DataRegisterEmptyInterruptEnable(void);

/**
 * @brief Disable the transmit complete interrupt.
 * @return ES_OK if successful.
 */
ES_t UART_TransmitCompleteInterruptDisable(void);

/**
 * @brief Disable the receive complete interrupt.
 * @return ES_OK if successful.
 */
ES_t UART_RecieveCompleteInterruptDisable(void);

/**
 * @brief Disable the data register empty interrupt.
 * @return ES_OK if successful.
 */
ES_t UART_DataRegisterEmptyInterruptDisable(void);

/**
 * @brief Transmit an 8-bit data over UART.
 *
 * @param Copy_u8Data 8-bit data to be transmitted.
 * @return ES_OK if successful.
 */
ES_t UART_Transmit8BitData(u8 Copy_u8Data);

/**
 * @brief Receive an 8-bit data from UART.
 *
 * @param Copy_pu8Data Pointer to store the received data.
 * @return ES_OK if successful, ES_NULL_POINTER if Copy_pu8Data is NULL, ES_NOK if error occurred.
 */
ES_t UART_Recieve8BitData(u8 *Copy_pu8Data);

/**
 * @brief Transmit a 9-bit data over UART.
 *
 * @param Copy_u16Data 9-bit data to be transmitted.
 * @return ES_OK if successful.
 */
ES_t UART_Transmit9BitData(u16 Copy_u16Data);

/**
 * @brief Receive a 9-bit data from UART.
 *
 * @param Copy_pu16Data Pointer to store the received data.
 * @return ES_OK if successful, ES_NULL_POINTER if Copy_pu16Data is NULL, ES_NOK if error occurred.
 */
ES_t UART_Recieve9BitData(u16 *Copy_pu16Data);

/**
 * @brief Transmit a string over UART.
 *
 * @param Copy_pu8String Pointer to the string data to be transmitted.
 * @return ES_OK if successful, ES_NULL_POINTER if Copy_pu8String is NULL.
 */
ES_t UART_TransmitString(u8 *Copy_pu8String);

/**
 * @brief Receive a string from UART.
 *
 * @param Copy_pu8String Array to store the received data.
 * @return ES_OK if successful, ES_NULL_POINTER if Copy_pu8String is NULL, ES_NOK if error occurred.
 */
ES_t UART_RecieveString(u8 *Copy_pu8String);

#endif // !UART_INTERFACE_H
