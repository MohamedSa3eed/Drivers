#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERR_STATE.h"

#include "SPI_INTERFCAE.h"
#include "SPI_CONFIG.h"
#include "SPI_PRIVATE.h"

static void (*SPI_CallBackFunc) (void) = NULL;

void SPI_Init(void){
#if SPI_MODE == SPI_MASTER 
  SET_BIT(SPCR, SPCR_MSTR);
  DDR_SPI = (1<<MOSI)|(1<<SS)|(1<<SCK);  /* Set MOSI, SS and SCK output, all others input */
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
  #else 
    #error "WRONG SPI_PRESCALER OPTION"
  #endif 
#elif SPI_MODE == SPI_SLAVE
  CLR_BIT(SPCR, SPCR_MSTR);
  DDR_SPI = (1<<MISO);                /* Set MISO output, all others input */
#else 
  #error "WRONG SPI_MODE OPTION"
#endif

#if SPI_DATA_ORDER == SPI_MSB 
  CLR_BIT(SPCR, SPCR_DORD);
#elif SPI_DATA_ORDER == SPI_LSB
  SET_BIT(SPCR, SPCR_DORD);
#else 
  #error "WRONG SPI_MSB OPTION" 
#endif

#if SPI_CLK_POLARITY == SPI_LEADING_EDGE_RISING 
  CLR_BIT(SPCR, SPCR_CPOL);
#elif SPI_CLK_POLARITY == SPI_LEADING_EDGE_FALLING
  SET_BIT(SPCR, SPCR_CPOL);
#else 
  #error "WRONG SPI_CLK_POLARITY OPTION" 
#endif 

#if SPI_CLK_PHASE == SPI_LEADING_EDGE_SETUP 
  SET_BIT(SPCR, SPCR_CPHA);
#elif SPI_CLK_PHASE == SPI_LEADING_EDGE_SAMPLE
  CLR_BIT(SPCR, SPCR_CPHA);
#else 
  #error "WRONG SPI_CLK_PHASE OPTION" 
#endif 

#if SPI_INTERRUPT == SPI_DISABLED 
  CLR_BIT(SPCR, SPCR_SPIE);
#elif SPI_INTERRUPT == SPI_ENABLED
  SET_BIT(SPCR, SPCR_SPIE);
#else 
  #error "WRONG SPI_INTERRUPT OPTION" 
#endif 
SET_BIT(SPCR, SPCR_SPE);   /* enable SPI */
}

ES_t SPI_TransmitRecieveData(u8 *Copy_pu8Data){
  /* Start transmission */
  SPDR = *Copy_pu8Data ;
  /* Wait for transmission complete */
  u8 Local_u8Check;
  while(1){
    Local_u8Check = ((SPSR>>6)&0x03);
    if(Local_u8Check == 0x03 || Local_u8Check == 0x01) // if collision error 
      return ES_NOK;
    if(Local_u8Check == 0x02) // if transmission complete
      break;
  }
  *Copy_pu8Data = SPDR;
  return ES_OK;
}

ES_t SPI_SetCallBack(void (*pfunc) (void)){
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

void __vector_12(void) __attribute__((signal));
void __vector_12(void){
  if (SPI_CallBackFunc != NULL)
    SPI_CallBackFunc();
}
