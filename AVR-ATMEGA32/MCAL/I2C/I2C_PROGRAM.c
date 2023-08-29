#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERR_STATE.h"

#include "I2C_INTERFACE.h"
#include "I2C_CONFIG.h"
#include "I2C_PRIVATE.h"

static void (*I2C_CallBack)(void) = NULL;

void I2C_Init(void)
{
  #if I2C_MODE == I2C_MASTER 
   TWSR = I2C_PRESCALER; // Prescaler 
   TWBR = BIT_RATE(I2C_SPEED); // Bit Rate
   TWAR = (I2C_ADDRESS<<1) | (1<<TWGCE); // Set MCU Address and the Globla Call 
   SET_BIT(TWCR, TWINT); // Clear Flag
   SET_BIT(TWCR, TWEN); // Enable I2C
  #elif I2C_MODE == I2C_SLAVE
   TWAR = (I2C_ADDRESS<<1) | (1<<TWGCE); // Set MCU Address and the Globla Call 
   SET_BIT(TWCR, TWINT); // Clear Flag
   SET_BIT(TWCR, TWEN); // Enable I2C
  #else 
   #error "Wrong I2C Mode"
  #endif 
  #if I2C_INTERRUPT == I2C_INTERRUPT_ENABLE
   SET_BIT(TWCR, TWIE); // Enable Interrupt 
  #elif I2C_INTERRUPT == I2C_INTERRUPT_DISABLE 
   CLR_BIT(TWCR, TWIE); // Disable Interrupt 
  #else 
   #error "Wrong I2C Interrupt Mode"
  #endif 
  #if I2C_ACKNOWLEDGE == I2C_ACKNOWLEDGE_ENABLE
   SET_BIT(TWCR, TWEA); // Enable Acknowledge 
  #elif I2C_ACKNOWLEDGE == I2C_ACKNOWLEDGE_DISABLE 
   CLR_BIT(TWCR, TWEA); // Disable Acknowledge 
  #else 
   #error "Wrong I2C Acknowledge Mode"
  #endif 
}

ES_t I2C_StartCondition(void){
  ES_t Local_Error = ES_NOK;
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); // Start Condition
  while(!GET_BIT(TWCR, TWINT)); // Wait until flag is set
  if(I2C_GetStatus() == START_CONDITION_SENT)
    Local_Error = ES_OK;
  /*CLR_BIT(TWCR, TWSTA); // Clear Start Condition*/
  return Local_Error;
}

ES_t I2C_RepeatedStartCondition(void){
  ES_t Local_Error = ES_NOK;
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); // Start Condition
  while(!GET_BIT(TWCR, TWINT)); // Wait until flag is set
  if(I2C_GetStatus() == REPEATED_START_SENT)
    Local_Error = ES_OK;
  return Local_Error;
}

ES_t I2C_StopCondition(void){
  TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN); // Stop Condition
  while(!GET_BIT(TWCR, TWINT)); // Wait until flag is set
  return ES_OK;
}

ES_t I2C_MasterSendData(u8 Copy_u8Data){
  ES_t Local_Error = ES_NOK;
  TWDR = Copy_u8Data; // Send Data
  SET_BIT(TWCR, TWINT); // Clear flag
  while(!GET_BIT(TWCR, TWINT)); // Wait until flag is set
  if(I2C_GetStatus() == MASTER_DATA_SENT_ACK_RECEIVED)
    Local_Error = ES_OK;
  return Local_Error;
}

ES_t I2C_MasterReceiveData(u8 *Copy_pu8Data){
  ES_t Local_Error = ES_NOK;
  SET_BIT(TWCR, TWINT); // Clear flag
  while(!GET_BIT(TWCR, TWINT)); // Wait until flag is set
  if(I2C_GetStatus() == MASTER_DATA_RECEIVED_ACK_SENT){
    *Copy_pu8Data = TWDR;
    Local_Error = ES_OK;
  }
  return Local_Error;
}

ES_t I2C_SlaveSendData(u8 Copy_u8Data){
  ES_t Local_Error = ES_NOK;
  TWDR = Copy_u8Data; // Send Data
  SET_BIT(TWCR, TWINT); // Clear flag
  while(!GET_BIT(TWCR, TWINT)); // Wait until flag is set
  if(I2C_GetStatus() == SLAVE_DATA_TRANSMITTED_ACK_RECEIVED)
    Local_Error = ES_OK;
  return Local_Error;
}

ES_t I2C_SlaveReceiveData(u8 *Copy_pu8Data){
  ES_t Local_Error = ES_NOK;
  SET_BIT(TWCR, TWINT); // Clear flag
  while(!GET_BIT(TWCR, TWINT)); // Wait until flag is set
  if(I2C_GetStatus() == SLAVE_DATA_RECEIVED_ACK_SENT){
    *Copy_pu8Data = TWDR;
    Local_Error = ES_OK;
  }
  return Local_Error;
}

ES_t I2C_SendSlaveAddress(u8 Copy_u8Address, u8 Copy_u8Operation){
  ES_t Local_Error = ES_NOK;
  TWDR = (Copy_u8Address<<1) | Copy_u8Operation; // Send Address
  SET_BIT(TWCR, TWINT); // Clear flag
  while(!GET_BIT(TWCR, TWINT)); // Wait until flag is set
  if(I2C_GetStatus() == SLA_W_SENT_ACK_RECEIVED && Copy_u8Operation == I2C_WRITE) 
    Local_Error = ES_OK;
  else if(I2C_GetStatus() == SLA_R_SENT_ACK_RECEIVED && Copy_u8Operation == I2C_READ) 
    Local_Error = ES_OK;
  return Local_Error;
}

ES_t I2C_CheckSlaveAddress(void){
  ES_t Local_Error = ES_NOK;
  SET_BIT(TWCR, TWINT); // Clear flag
  while(!GET_BIT(TWCR, TWINT)); // Wait until flag is set
  if(I2C_GetStatus() ==  SLA_R_RECEIVED_ACK_SENT || I2C_GetStatus() == SLA_W_RECEIVED_ACK_SENT)
    Local_Error = ES_OK;
  return Local_Error;
}

ES_t I2C_SetCallBack(void (*Copy_ptr)(void)){
  ES_t Local_Error = ES_NOK;
  if(Copy_ptr != NULL){
    I2C_CallBack = Copy_ptr;
    Local_Error = ES_OK;
  }
  else{
    Local_Error = ES_NULL_POINTER;
  }
  return Local_Error;
}

void __vector_19(void) __attribute__((signal));
void __vector_19(void){
  if (I2C_CallBack != NULL)
    I2C_CallBack();
}

static u8 I2C_GetStatus(void){
  u8 Local_Status = 0;
  Local_Status = TWSR & 0xF8;
  return Local_Status;
}
