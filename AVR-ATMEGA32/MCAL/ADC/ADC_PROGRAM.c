#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERR_STATE.h"

#include "ADC_INTERFACE.h"
#include "ADC_CONFIG.h"
#include "ADC_PRIVATE.h"

static void (*CallBackfunc) (void) = NULL ;

ES_t ADC_SetPrescaler(u8 Copy_u8Prescaler)
{
  ES_t Local_enumErrorState = ES_NOK;
  switch (Copy_u8Prescaler) {
    case ADC_PRESCALER_2:
      CLR_BIT(ADCSRA, ADCSRA_ADPS0);
      CLR_BIT(ADCSRA, ADCSRA_ADPS1);
      CLR_BIT(ADCSRA, ADCSRA_ADPS2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_PRESCALER_4:
      CLR_BIT(ADCSRA, ADCSRA_ADPS0);
      SET_BIT(ADCSRA, ADCSRA_ADPS1);
      CLR_BIT(ADCSRA, ADCSRA_ADPS2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_PRESCALER_8:
      SET_BIT(ADCSRA, ADCSRA_ADPS0);
      SET_BIT(ADCSRA, ADCSRA_ADPS1);
      CLR_BIT(ADCSRA, ADCSRA_ADPS2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_PRESCALER_16:
      CLR_BIT(ADCSRA, ADCSRA_ADPS0);
      CLR_BIT(ADCSRA, ADCSRA_ADPS1);
      SET_BIT(ADCSRA, ADCSRA_ADPS2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_PRESCALER_32:
      SET_BIT(ADCSRA, ADCSRA_ADPS0);
      CLR_BIT(ADCSRA, ADCSRA_ADPS1);
      SET_BIT(ADCSRA, ADCSRA_ADPS2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_PRESCALER_64:
      CLR_BIT(ADCSRA, ADCSRA_ADPS0);
      SET_BIT(ADCSRA, ADCSRA_ADPS1);
      SET_BIT(ADCSRA, ADCSRA_ADPS2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_PRESCALER_128:
      SET_BIT(ADCSRA, ADCSRA_ADPS0);
      SET_BIT(ADCSRA, ADCSRA_ADPS1);
      SET_BIT(ADCSRA, ADCSRA_ADPS2);
      Local_enumErrorState = ES_OK;
      break;
    default:
      Local_enumErrorState = ES_OUT_OF_RANGE;
      break;
  }
  return Local_enumErrorState ;
}

ES_t ADC_SetVref(u8 Copy_u8Vref)
{
  ES_t Local_enumErrorState = ES_NOK;
  switch (Copy_u8Vref) {
    case ADC_AREF:
      CLR_BIT(ADMUX, ADMUX_REFS0);
      CLR_BIT(ADMUX, ADMUX_REFS1);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_AVCC:
      SET_BIT(ADMUX, ADMUX_REFS0);
      CLR_BIT(ADMUX, ADMUX_REFS1);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_INTERNAL:
      SET_BIT(ADMUX, ADMUX_REFS0);
      SET_BIT(ADMUX, ADMUX_REFS1);
      Local_enumErrorState = ES_OK;
      break;
    default:
      Local_enumErrorState = ES_OUT_OF_RANGE;
  }
  return Local_enumErrorState;
}

ES_t ADC_init(u8 Copy_u8Prescaler, u8 Copy_u8Vref)
{
  ES_t Local_enumErrorState = ES_NOK;
  CLR_BIT(ADMUX, ADMUX_ADLAR);
  SET_BIT(ADCSRA, ADCSRA_ADEN);
  Local_enumErrorState = ADC_SetVref(Copy_u8Vref);
  if (Local_enumErrorState != ES_OK)
    return Local_enumErrorState ;
  Local_enumErrorState = ADC_SetPrescaler(Copy_u8Prescaler);
  return Local_enumErrorState ;
}

ES_t ADC_InterruptEnable(void)
{
  SET_BIT(ADCSRA, ADCSRA_ADIE);
  return ES_OK;
}

ES_t ADC_InterruptDisable(void)
{
  CLR_BIT(ADCSRA, ADCSRA_ADIE);
  return ES_OK;
}

ES_t ADC_SetCallBack(void (*func) (void))
{
  ES_t Local_enumErrorState = ES_NOK;
  if (func != NULL) {
    CallBackfunc  = func ;
    Local_enumErrorState = ES_OK;
  }
  else {
    return ES_NULL_POINTER; 
  }
  return Local_enumErrorState;
}

void __vector_16 (void) __attribute__ ((signal));
void __vector_16 (void)
{
  if (CallBackfunc != NULL) 
    CallBackfunc();
}

ES_t ADC_terminate(void)
{
  CLR_BIT(ADCSRA, ADCSRA_ADEN);
  return ES_OK;
}

ES_t ADC_StartConversion(void)
{
  SET_BIT(ADCSRA, ADCSRA_ADSC);
  return ES_OK;
}

ES_t ADC_SetAutoTrigger(u8 Copy_u8Trigger)
{
  ES_t Local_enumErrorState = ES_NOK;
  SET_BIT(ADCSRA, ADCSRA_ADATE);
  switch (Copy_u8Trigger) {
    case ADC_FREE_RUNNING:
      CLR_BIT(SFIOR, SFIOR_ADT0);
      CLR_BIT(SFIOR, SFIOR_ADT1);
      CLR_BIT(SFIOR, SFIOR_ADT2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_ANALOG_CMP:
      SET_BIT(SFIOR, SFIOR_ADT0);
      CLR_BIT(SFIOR, SFIOR_ADT1);
      CLR_BIT(SFIOR, SFIOR_ADT2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_EXT_INT0:
      CLR_BIT(SFIOR, SFIOR_ADT0);
      SET_BIT(SFIOR, SFIOR_ADT1);
      CLR_BIT(SFIOR, SFIOR_ADT2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_TMR0_CMP_MATCH:
      SET_BIT(SFIOR, SFIOR_ADT0);
      SET_BIT(SFIOR, SFIOR_ADT1);
      CLR_BIT(SFIOR, SFIOR_ADT2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_TMR0_OVF:
      CLR_BIT(SFIOR, SFIOR_ADT0);
      CLR_BIT(SFIOR, SFIOR_ADT1);
      SET_BIT(SFIOR, SFIOR_ADT2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_TMR1_CMP_MATCH_B:
      SET_BIT(SFIOR, SFIOR_ADT0);
      CLR_BIT(SFIOR, SFIOR_ADT1);
      SET_BIT(SFIOR, SFIOR_ADT2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_TMR1_OVF:
      CLR_BIT(SFIOR, SFIOR_ADT0);
      SET_BIT(SFIOR, SFIOR_ADT1);
      SET_BIT(SFIOR, SFIOR_ADT2);
      Local_enumErrorState = ES_OK;
      break;
    case ADC_TMR1_CAPTURE_EVENT:
      SET_BIT(SFIOR, SFIOR_ADT0);
      SET_BIT(SFIOR, SFIOR_ADT1);
      SET_BIT(SFIOR, SFIOR_ADT2);
      Local_enumErrorState = ES_OK;
      break;
    default:
      Local_enumErrorState = ES_OUT_OF_RANGE;
  }
  return Local_enumErrorState;
}

ES_t ADC_DisableAutoTrigger(void)
{
  CLR_BIT(ADCSRA, ADCSRA_ADATE);
  return ES_OK;
}

ES_t ADC_GetResult(u16 *Copy_pu8Result)
{
  *Copy_pu8Result = ADCR;
  return ES_OK;
}

ES_t ADC_GetResultPolling(u16 *Copy_pu8Result)
{
  while (GET_BIT(ADCSRA, ADCSRA_ADIF)) {

  }
  SET_BIT(ADCSRA, ADCSRA_ADIF);
  *Copy_pu8Result = ADCR;
  return ES_OK;
}
