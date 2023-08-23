#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERR_STATE.h"

#include "SPI_INTERFCAE.h"
#include "SPI_CONFIG.h"
#include "SPI_PRIVATE.h"

static void (*SPI_CallBackFunc) (void) = NULL;

void SPI_Init(void){
SET_BIT(SPCR, SPCR_SPE);
#if SPI_MODE == SPI_MASTER 
  SET_BIT(SPCR, SPCR_MSTR);
  DDR_SPI = (1<<MOSI)|(1<<SS)|(1<<SCK);  /* Set MOSI, SS and SCK output, all others input */
#elif SPI_MODE == SPI_SLAVE
  CLR_BIT(SPCR, SPCR_MSTR);
  DDR_SPI = (1<<DD_MISO);                /* Set MISO output, all others input */
#endif

#if SPI_PRESCALER == SPI_PRESCALER_2 
  CLR_BIT(SPCR, SPCR_SPR0);
  CLR_BIT(SPCR, SPCR_SPR1);
  SET_BIT(SPSR, SPSR_SPI2X);
#elif SPI_PRESCALER == SPI_PRESCALER_4
  CLR_BIT(SPCR, SPCR_SPR0);
  CLR_BIT(SPCR, SPCR_SPR1);
  CLR_BIT(SPSR, SPSR_SPI2X);
#elif SPI_PRESCALER == SPI_PRESCALER_8
  SET_BIT(SPCR, SPCR_SPR0);
  CLR_BIT(SPCR, SPCR_SPR1);
  SET_BIT(SPSR, SPSR_SPI2X);
#elif SPI_PRESCALER == SPI_PRESCALER_16
  SET_BIT(SPCR, SPCR_SPR0);
  CLR_BIT(SPCR, SPCR_SPR1);
  CLR_BIT(SPSR, SPSR_SPI2X);
#elif SPI_PRESCALER == SPI_PRESCALER_32
  CLR_BIT(SPCR, SPCR_SPR0);
  SET_BIT(SPCR, SPCR_SPR1);
  SET_BIT(SPSR, SPSR_SPI2X);
#elif SPI_PRESCALER == SPI_PRESCALER_64
  CLR_BIT(SPCR, SPCR_SPR0);
  SET_BIT(SPCR, SPCR_SPR1);
  CLR_BIT(SPSR, SPSR_SPI2X);
#elif SPI_PRESCALER == SPI_PRESCALER_128
  SET_BIT(SPCR, SPCR_SPR0);
  SET_BIT(SPCR, SPCR_SPR1);
  CLR_BIT(SPSR, SPSR_SPI2X);
#endif 

#if SPI_DATA_ORDER == SPI_MSB 
  CLR_BIT(SPCR, SPCR_DORD);
#elif SPI_DATA_ORDER == SPI_LSB
  SET_BIT(SPCR, SPCR_DORD);
#endif

#if SPI_CLK_POLARITY == SPI_LEADING_EDGE_RISING 
  CLR_BIT(SPCR, SPCR_CPOL);
#elif SPI_CLK_POLARITY == SPI_LEADING_EDGE_FALLING
  SET_BIT(SPCR, SPCR_CPOL);
#endif 

#if SPI_CLK_PHASE == SPI_LEADING_EDGE_SETUP 
  SET_BIT(SPCR, SPCR_CPHA);
#elif SPI_CLK_PHASE == SPI_LEADING_EDGE_SAMPLE
  CLR_BIT(SPCR, SPCR_CPHA);
#endif 

#if SPI_INTERRUPT == SPI_DISABLED 
  CLR_BIT(SPCR, SPCR_SPIE);
#elif SPI_INTERRUPT == SPI_ENABLED
  SET_BIT(SPCR, SPCR_SPIE);
#endif 
}

ES_t SPI_TransmitRecieveData(u8 *Copy_pu8Data){
  /* Start transmission */
  SPDR = *Copy_pu8Data ;
  /* Wait for transmission complete */
  u8 Local_u8Check;
  while(1){
    Local_u8Check = ((SPSR>>6)&0x11);
    if(Local_u8Check == 0x11 || Local_u8Check == 0x01) // if collision error 
      return ES_NOK;
    if(Local_u8Check == 0x10) // if transmission complete
      break;
  }
  *Copy_pu8Data = SPDR;
  return ES_OK;
}

ES_t SPI_SetCasllBack(void (*pfunc) (void)){
  if (pfunc==NULL)
    return ES_NULL_POINTER;
  SPI_CallBackFunc = pfunc;
  return ES_OK;
}

ES_t SPI_InterruptEnable(void){
  SET_BIT(SPCR, SPCR_SPIE);
  return ES_OK;
}

ES_t SPI_InterruptDisable(void){
  CLR_BIT(SPCR, SPCR_SPIE);
  return ES_OK;
}
