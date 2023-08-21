#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H
#include "../../LIB/ERR_STATE.h"
typedef enum {
  UART_PARITY_DISABLED = 0,
  UART_PARITY_ODD = 1,
  UART_PARITY_EVEN = 2
} UART_Parity_t;

typedef enum {
  UART_STOP_BIT_1 = 0,
  UART_STOP_BIT_2 = 1
} UART_StopBit_t;

typedef enum{ 
  UART_5BIT_DATA = 0,
  UART_6BIT_DATA = 1,
  UART_7BIT_DATA = 2,
  UART_8BIT_DATA = 3,
  UART_9BIT_DATA = 4
} UART_DataBits_t ;

typedef enum{
  UART_DOUBLE_SPEED_ON = 0,
  UART_DOUBLE_SPEED_OFF = 1
} UART_DoubleSpeed_t;

ES_t UART_Init(u32 Copy_u32BaudRate, UART_StopBit_t Copy_enumStopBit, UART_Parity_t Copy_enumParity, UART_DoubleSpeed_t Copy_enumDoubleSpeed);

ES_t UART_TransmitData(u8 Copy_u8Data);

ES_t UART_RecieveData(u8 *Copy_pu8Data);

#endif // !UART_INTERFACE_H
