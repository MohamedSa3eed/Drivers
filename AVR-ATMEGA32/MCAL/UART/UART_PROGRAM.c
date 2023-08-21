#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERR_STATE.h"

#include "UART_INTERFACE.h"
#include "UART_CONFIG.h"
#include "UART_PRIVATE.h"

ES_t UART_Init(u32 Copy_u32BaudRate, UART_StopBit_t Copy_enumStopBit, UART_Parity_t Copy_enumParity, UART_DoubleSpeed_t Copy_enumDoubleSpeed)
{
  ES_t Local_enumErrorState = ES_NOK;

  return Local_enumErrorState;
}

ES_t UART_TransmitData(u8 Copy_u8Data)
{
  ES_t Local_enumErrorState = ES_NOK;

  return Local_enumErrorState;
}

ES_t UART_RecieveData(u8 *Copy_pu8Data)
{
  ES_t Local_enumErrorState = ES_NOK;

  return Local_enumErrorState;
}
