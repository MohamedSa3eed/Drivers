#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERR_STATE.h"

#include "UART_INTERFACE.h"
#include "UART_CONFIG.h"
#include "UART_PRIVATE.h"

static void (*TransmitCompleteInterruptCallBack) (void) = NULL ;
static void (*RecieveCompleteInterruptCallBack)  (void) = NULL ;
static void (*DataRegisterEmptyInterruptCallBack)(void) = NULL ;

ES_t UART_Init(u32 Copy_u32BaudRate, UART_DataBits_t Copy_enumDataBits, UART_Parity_t Copy_enumParity, UART_StopBit_t Copy_enumStopBits, UART_DoubleSpeed_t Copy_enumDoubleSpeed)
{
  /* Check for range of arguments */
  if (!(Copy_enumDataBits >= UART_5BIT_DATA || Copy_enumDataBits <= UART_8BIT_DATA || Copy_enumDataBits == UART_9BIT_DATA)) 
    return ES_OUT_OF_RANGE;
  if (!(Copy_enumParity == UART_PARITY_DISABLED || Copy_enumParity == UART_PARITY_ODD || Copy_enumParity == UART_PARITY_EVEN))
    return ES_OUT_OF_RANGE;
  if (!(Copy_enumDoubleSpeed == UART_DOUBLE_SPEED_ON || Copy_enumDoubleSpeed == UART_DOUBLE_SPEED_OFF)) 
    return ES_OUT_OF_RANGE;
  /* Set baud rate */
  Copy_u32BaudRate *= (Copy_enumDoubleSpeed+1);
  u16 Local_u16UBRRValue = ((CPU_FREQ / (16 * Copy_u32BaudRate))-1) ;
  if(Local_u16UBRRValue > UBRR_MAX)
    return ES_OUT_OF_RANGE;
  UBRRH = (u8)(Local_u16UBRRValue>>8);
  UBRRL = (u8)Local_u16UBRRValue;
  /* Set the double speed option */
  UCSRA |= (Copy_enumDoubleSpeed<<UCSRA_U2X);
  /* Enable receiver and transmitter */
  UCSRB = (1<<UCSRB_RXEN)|(1<<UCSRB_TXEN);
  /* Set frame format: data bits, stop bits, parity mode */
  if (Copy_enumDataBits == UART_9BIT_DATA) {
    SET_BIT(UCSRB, UCSRB_UCSZ2);
    Copy_enumDataBits = UART_8BIT_DATA;
  }
    UCSRC = (1<<UCSRC_URSEL)|(Copy_enumStopBits<<UCSRC_USBS)|(Copy_enumDataBits<<UCSRC_UCSZ0)|(Copy_enumParity<<UCSRC_UPM0);
  return ES_OK;
}

ES_t UART_EnableTransmitUnit(void){
  SET_BIT(UCSRB, UCSRB_TXEN);
  return ES_OK;
}

ES_t UART_DisableTransmitUnit(void){
  CLR_BIT(UCSRB, UCSRB_TXEN);
  return ES_OK;
}

ES_t UART_EnableRecieveUnit(void){
  SET_BIT(UCSRB, UCSRB_RXEN);
  return ES_OK;
}

ES_t UART_DisableRecieveUnit(void){
  CLR_BIT(UCSRB, UCSRB_RXEN);
  return ES_OK;
}

ES_t UART_SetTransmitCompleteInterruptCallBack(void(*Pfunc)(void)){
  if (Pfunc == NULL) 
    return ES_NULL_POINTER;
  TransmitCompleteInterruptCallBack = Pfunc;
  return ES_OK;
}

ES_t UART_SetRecieveCompleteInterruptCallBack(void(*Pfunc)(void)){
  if (Pfunc == NULL) 
    return ES_NULL_POINTER;
  RecieveCompleteInterruptCallBack = Pfunc;
  return ES_OK;
}

ES_t UART_SetDataRegisterEmptyInterruptCallBack(void(*Pfunc)(void)){
  if (Pfunc == NULL) 
    return ES_NULL_POINTER;
  DataRegisterEmptyInterruptCallBack = Pfunc;
  return ES_OK;
}

ES_t UART_TransmitCompleteInterruptEnable(void){
  SET_BIT(UCSRB, UCSRB_TXCIE);
  return ES_OK;
}

ES_t UART_RecieveCompleteInterruptEnable(void){
  SET_BIT(UCSRB, UCSRB_RXCIE);
  return ES_OK;
}

ES_t UART_DataRegisterEmptyInterruptEnable(void){
  SET_BIT(UCSRB, UCSRB_UDRIE);
  return ES_OK;
}

ES_t UART_TransmitCompleteInterruptDisable(void){
  CLR_BIT(UCSRB, UCSRB_TXCIE);
  return ES_OK;
}

ES_t UART_RecieveCompleteInterruptDisable(void){
  CLR_BIT(UCSRB, UCSRB_RXCIE);
  return ES_OK;
}

ES_t UART_DataRegisterEmptyInterruptDisable(void){
  CLR_BIT(UCSRB, UCSRB_UDRIE);
  return ES_OK;
}

ES_t UART_Transmit8BitData(u8 Copy_u8Data)
{
  /* Wait for empty transmit buffer */
  while (!(GET_BIT(UCSRA, UCSRA_UDRE)));
  /* Put data into buffer, sends the data */
  UDR = Copy_u8Data;
  return ES_OK;
}

ES_t UART_Recieve8BitData(u8 *Copy_pu8Data)
{
  if (Copy_pu8Data == NULL)
    return ES_NULL_POINTER;
  /* Wait for data to be received */
  while (!(GET_BIT(UCSRA, UCSRA_RXC)));
  /* If error */
  if (GET_BIT(UCSRA, UCSRA_FE) || GET_BIT(UCSRA, UCSRA_PE) || GET_BIT(UCSRA, UCSRA_DOR))
    return ES_NOK;
  /* Get and return received data from buffer */
  *Copy_pu8Data = UDR;
  return ES_OK;
}

ES_t UART_Transmit9BitData(u16 Copy_u16Data)
{
  /* Wait for empty transmit buffer */
  while (!(GET_BIT(UCSRA, UCSRA_UDRE)));
  /* Copy 9th bit to TXB8 */
  CLR_BIT(UCSRB, UCSRB_TXB8);
  if (GET_BIT(Copy_u16Data, 8))
    SET_BIT(UCSRB, UCSRB_TXB8);
  /* Put data into buffer, sends the data */
  UDR = (u8)Copy_u16Data;
  return ES_OK;
}

ES_t UART_Recieve9BitData(u16 *Copy_pu16Data)
{
  if (Copy_pu16Data == NULL) 
    return ES_NULL_POINTER;
  u8 Local_u8ResH, Local_u8ResL;
  /* Wait for data to be received */
  while (!(GET_BIT(UCSRA, UCSRA_RXC))) ;
  /* If error */
  if (GET_BIT(UCSRA, UCSRA_FE) || GET_BIT(UCSRA, UCSRA_PE) || GET_BIT(UCSRA, UCSRA_DOR))
    return ES_NOK;
  /* Get the 9 bits and store them */
  Local_u8ResH = GET_BIT(UCSRB, UCSRB_RXB8);
  Local_u8ResL = UDR;
  *Copy_pu16Data = ((Local_u8ResH << 8) | Local_u8ResL);
  return ES_OK;
}

ES_t UART_TransmitString(u8 *Copy_pu8String){
  if (Copy_pu8String == NULL)
    return ES_NULL_POINTER;
  u8 *Local_Pu8ptr = Copy_pu8String;
  while (*Local_Pu8ptr != '\0') {
    UART_Transmit8BitData(*Local_Pu8ptr);
    Local_Pu8ptr++;
  }
  UART_Transmit8BitData('\0');
  return ES_OK;
}

ES_t UART_RecieveString(u8 *Copy_pu8String){
  ES_t Local_enumErrorState = ES_NOK;
  u8 Local_u8Char;
  u32 Local_u32Itrator=0;
  if (Copy_pu8String == NULL)
    return ES_NULL_POINTER;
  do {
    Local_enumErrorState = UART_Recieve8BitData(&Local_u8Char); 
    if (Local_enumErrorState != ES_OK)
      return Local_enumErrorState;
    Copy_pu8String[Local_u32Itrator] = Local_u8Char;
    Local_u32Itrator++;
    if (Local_u8Char == '\0' || Local_u8Char == '\t' || Local_u8Char == '\n') {
      break; 
    }
  }while (1);
  return ES_OK;
}

void __vector_15(void) __attribute__((signal,used));
void __vector_15(void){
  if(TransmitCompleteInterruptCallBack!=NULL)
      TransmitCompleteInterruptCallBack();
}

void __vector_14(void) __attribute__((signal,used));
void __vector_14(void){
  if(DataRegisterEmptyInterruptCallBack!=NULL)
      DataRegisterEmptyInterruptCallBack();
}

void __vector_13(void) __attribute__((signal,used));
void __vector_13(void){
  if(RecieveCompleteInterruptCallBack!=NULL)
      RecieveCompleteInterruptCallBack();
}
