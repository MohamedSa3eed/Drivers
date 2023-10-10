#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERR_STATE.h"

#include "TIMER1_INTERFACE.h"
#include "TIMER1_PRIVATE.h"
#include "TIMER1_CONFIG.h"

void (*TIMER1_OVF_CallBack)(void) = NULL;
void (*TIMER1_CTCA_CallBack)(void) = NULL;
void (*TIMER1_CTCB_CallBack)(void) = NULL;
void (*TIMER1_ICU_CallBack)(void) = NULL;

void TIMER1_Init(void){
  TIMER1_SelectMode();
  TIMER1_SelectPrescaler();
  TIMER1_SelectInterrupt();
  TIMER1_SelectOC1_Mode();
  TIMER1_SelectICNC1_Mode();
  TIMER1_SelectICES1_Mode();
}

void TIMER1_Start(void){
  SET_BIT(TCCR1B,CS10);
}

void TIMER1_Stop(void){
  CLR_BIT(TCCR1B,CS10);
  CLR_BIT(TCCR1B,CS11);
  CLR_BIT(TCCR1B,CS12);
}

ES_t TIMER1_SetDutyCycle(u8 Copy_u8DutyCylce)
{
  if(Copy_u8DutyCylce > 100)
  {
    return ES_OUT_OF_RANGE;
  }
  u16 Local_u16DutyCycle = (Copy_u8DutyCylce * TIMER1_MAX / 100 ) ;
  return TIMER1_SetCompareValueA(Local_u16DutyCycle);
}
ES_t TIMER1_SetPreloadedValue(u16 Copy_u16PreloadedValue){
  ES_t Local_ErrorState = ES_NOK;
  if(Copy_u16PreloadedValue <= 0xFFFF){
    TCNT1H = (u8)(Copy_u16PreloadedValue>>8);
    TCNT1L = (u8)Copy_u16PreloadedValue;
    Local_ErrorState = ES_OK;
  }
  else{
    Local_ErrorState = ES_OUT_OF_RANGE;
  }
  return Local_ErrorState;
}

ES_t TIMER1_SetCompareValueA(u16 Copy_u16CompareValueA){
  ES_t Local_ErrorState = ES_NOK;
  if(Copy_u16CompareValueA <= 0xFFFF){
    OCR1AH = (u8)(Copy_u16CompareValueA>>8);
    OCR1AL = (u8)Copy_u16CompareValueA;
    Local_ErrorState = ES_OK;
  }
  else{
    Local_ErrorState = ES_OUT_OF_RANGE;
  }
  return Local_ErrorState;
}

ES_t TIMER1_SetCompareValueB(u16 Copy_u16CompareValueB){
  ES_t Local_ErrorState = ES_NOK;
  if(Copy_u16CompareValueB <= 0xFFFF){
    OCR1BH = (u8)(Copy_u16CompareValueB>>8);
    OCR1BL = (u8)Copy_u16CompareValueB;
    Local_ErrorState = ES_OK;
  }
  else{
    Local_ErrorState = ES_OUT_OF_RANGE;
  }
  return Local_ErrorState;
}

ES_t TIMER1_SetInputCaptureValue(u16 Copy_u16InputCaptureValue){
  ES_t Local_ErrorState = ES_NOK;
  if(Copy_u16InputCaptureValue <= 0xFFFF){
    ICR1H = (u8)(Copy_u16InputCaptureValue>>8);
    ICR1L = (u8)Copy_u16InputCaptureValue;
    Local_ErrorState = ES_OK;
  }
  else{
    Local_ErrorState = ES_OUT_OF_RANGE;
  }
  return Local_ErrorState;
}

void TIMER1_EnableOVFInterrupt(void){
  SET_BIT(TIMSK,TOIE1);
}

void TIMER1_EnableCTCAInterrupt(void){
  SET_BIT(TIMSK,OCIE1A);
}

void TIMER1_EnableCTCBInterrupt(void){
  SET_BIT(TIMSK,OCIE1B);
}

void TIMER1_EnableICUInterrupt(void){
  SET_BIT(TIMSK,TICIE1);
}

void TIMER1_DisableOVFInterrupt(void){
  CLR_BIT(TIMSK,TOIE1);
}

void TIMER1_DisableCTCAInterrupt(void){
  CLR_BIT(TIMSK,OCIE1A);
}

void TIMER1_DisableCTCBInterrupt(void){
  CLR_BIT(TIMSK,OCIE1B);
}

void TIMER1_DisableICUInterrupt(void){
  CLR_BIT(TIMSK,TICIE1);
}

ES_t TIMER1_SetOverflowCallBack(void (*Copy_PtrToFunc)(void)){
  ES_t Local_ErrorState = ES_NOK;
  if(Copy_PtrToFunc != NULL){
    TIMER1_OVF_CallBack = Copy_PtrToFunc;
    Local_ErrorState = ES_OK;
  }
  else{
    Local_ErrorState = ES_NULL_POINTER;
  }
  return Local_ErrorState;
}

ES_t TIMER1_SetCTCACallBack(void (*Copy_PtrToFunc)(void)){
  ES_t Local_ErrorState = ES_NOK;
  if(Copy_PtrToFunc != NULL){
    TIMER1_CTCA_CallBack = Copy_PtrToFunc;
    Local_ErrorState = ES_OK;
  }
  else{
    Local_ErrorState = ES_NULL_POINTER;
  }
  return Local_ErrorState;
}

ES_t TIMER1_SetCTCBCallBack(void (*Copy_PtrToFunc)(void)){
  ES_t Local_ErrorState = ES_NOK;
  if(Copy_PtrToFunc != NULL){
    TIMER1_CTCB_CallBack = Copy_PtrToFunc;
    Local_ErrorState = ES_OK;
  }
  else{
    Local_ErrorState = ES_NULL_POINTER;
  }
  return Local_ErrorState;
}

ES_t TIMER1_SetICUCallBack(void (*Copy_PtrToFunc)(void)){
  ES_t Local_ErrorState = ES_NOK;
  if(Copy_PtrToFunc != NULL){
    TIMER1_ICU_CallBack = Copy_PtrToFunc;
    Local_ErrorState = ES_OK;
  }
  else{
    Local_ErrorState = ES_NULL_POINTER;
  }
  return Local_ErrorState;
}

void __vector_9(void) __attribute__((signal));
void __vector_9(void){
  if(TIMER1_OVF_CallBack != NULL){
    TIMER1_OVF_CallBack();
  }
}

void __vector_7(void) __attribute__((signal));
void __vector_7(void){
  if(TIMER1_CTCA_CallBack != NULL){
    TIMER1_CTCA_CallBack();
  }
}

void __vector_6(void) __attribute__((signal));
void __vector_6(void){
  if(TIMER1_CTCB_CallBack != NULL){
    TIMER1_CTCB_CallBack();
  }
}

void __vector_5(void) __attribute__((signal));
void __vector_5(void){
  if(TIMER1_ICU_CallBack != NULL){
    TIMER1_ICU_CallBack();
  }
}

static void TIMER1_SelectMode(void){
  #if TIMER1_MODE == TIMER1_NORMAL_MODE
    CLR_BIT(TCCR1A,WGM10);
    CLR_BIT(TCCR1A,WGM11);
    CLR_BIT(TCCR1B,WGM12);
    CLR_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_8_BIT
    SET_BIT(TCCR1A,WGM10);
    CLR_BIT(TCCR1A,WGM11);
    CLR_BIT(TCCR1B,WGM12);
    CLR_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_9_BIT
    CLR_BIT(TCCR1A,WGM10);
    SET_BIT(TCCR1A,WGM11);
    CLR_BIT(TCCR1B,WGM12);
    CLR_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_10_BIT
    SET_BIT(TCCR1A,WGM10);
    SET_BIT(TCCR1A,WGM11);
    CLR_BIT(TCCR1B,WGM12);
    CLR_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_CTC_OCR1A_TOP
    CLR_BIT(TCCR1A,WGM10);
    CLR_BIT(TCCR1A,WGM11);
    SET_BIT(TCCR1B,WGM12);
    CLR_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_FAST_PWM_8_BIT
    SET_BIT(TCCR1A,WGM10);
    CLR_BIT(TCCR1A,WGM11);
    SET_BIT(TCCR1B,WGM12);
    CLR_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_FAST_PWM_9_BIT
    CLR_BIT(TCCR1A,WGM10);
    SET_BIT(TCCR1A,WGM11);
    SET_BIT(TCCR1B,WGM12);
    CLR_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_FAST_PWM_10_BIT
    SET_BIT(TCCR1A,WGM10);
    SET_BIT(TCCR1A,WGM11);
    SET_BIT(TCCR1B,WGM12);
    CLR_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1
    CLR_BIT(TCCR1A,WGM10);
    CLR_BIT(TCCR1A,WGM11);
    CLR_BIT(TCCR1B,WGM12);
    SET_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A
    SET_BIT(TCCR1A,WGM10);
    CLR_BIT(TCCR1A,WGM11);
    CLR_BIT(TCCR1B,WGM12);
    SET_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1
    CLR_BIT(TCCR1A,WGM10);
    SET_BIT(TCCR1A,WGM11);
    CLR_BIT(TCCR1B,WGM12);
    SET_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A
    SET_BIT(TCCR1A,WGM10);
    SET_BIT(TCCR1A,WGM11);
    CLR_BIT(TCCR1B,WGM12);
    SET_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_CTC_ICR1
    CLR_BIT(TCCR1A,WGM10);
    CLR_BIT(TCCR1A,WGM11);
    SET_BIT(TCCR1B,WGM12);
    SET_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_FAST_PWM_ICR1
    CLR_BIT(TCCR1A,WGM10);
    SET_BIT(TCCR1A,WGM11);
    SET_BIT(TCCR1B,WGM12);
    SET_BIT(TCCR1B,WGM13);
  #elif TIMER1_MODE == TIMER1_FAST_PWM_OCR1A
    SET_BIT(TCCR1A,WGM10);
    SET_BIT(TCCR1A,WGM11);
    SET_BIT(TCCR1B,WGM12);
    SET_BIT(TCCR1B,WGM13);
  #else
    #error "Wrong Mode Choice"
  #endif
}

static void TIMER1_SelectPrescaler(void){
  #if TIMER1_PRESCALER == TIMER1_NO_CLOCK
    CLR_BIT(TCCR1B,CS10);
    CLR_BIT(TCCR1B,CS11);
    CLR_BIT(TCCR1B,CS12);
  #elif TIMER1_PRESCALER == TIMER1_NO_PRESCALER
    SET_BIT(TCCR1B,CS10);
    CLR_BIT(TCCR1B,CS11);
    CLR_BIT(TCCR1B,CS12);
  #elif TIMER1_PRESCALER == TIMER1_PRESCALER_8
    CLR_BIT(TCCR1B,CS10);
    SET_BIT(TCCR1B,CS11);
    CLR_BIT(TCCR1B,CS12);
  #elif TIMER1_PRESCALER == TIMER1_PRESCALER_64
    SET_BIT(TCCR1B,CS10);
    SET_BIT(TCCR1B,CS11);
    CLR_BIT(TCCR1B,CS12);
  #elif TIMER1_PRESCALER == TIMER1_PRESCALER_256
    CLR_BIT(TCCR1B,CS10);
    CLR_BIT(TCCR1B,CS11);
    SET_BIT(TCCR1B,CS12);
  #elif TIMER1_PRESCALER == TIMER1_PRESCALER_1024
    SET_BIT(TCCR1B,CS10);
    CLR_BIT(TCCR1B,CS11);
    SET_BIT(TCCR1B,CS12);
  #elif TIMER1_PRESCALER == TIMER1_EXTERNAL_CLOCK_FALLING
    CLR_BIT(TCCR1B,CS10);
    SET_BIT(TCCR1B,CS11);
    SET_BIT(TCCR1B,CS12);
  #elif TIMER1_PRESCALER == TIMER1_EXTERNAL_CLOCK_RISING
    SET_BIT(TCCR1B,CS10);
    SET_BIT(TCCR1B,CS11);
    SET_BIT(TCCR1B,CS12);
  #else
    #error "Wrong Prescaler Choice"
  #endif
}

static void TIMER1_SelectInterrupt(void){
  #if TIMER1_OVF_INTERRUPT == TIMER1_ENABLE_INTERRUPT
    SET_BIT(TIMSK,TOIE1);
  #elif TIMER1_OVF_INTERRUPT == TIMER1_DISABLE_INTERRUPT
    CLR_BIT(TIMSK,TOIE1);
  #else
    #error "Wrong OVF Interrupt Choice"
  #endif
  
  #if TIMER1_CTCA_INTERRUPT == TIMER1_ENABLE_INTERRUPT
    SET_BIT(TIMSK,OCIE1A);
  #elif TIMER1_CTCA_INTERRUPT == TIMER1_DISABLE_INTERRUPT
    CLR_BIT(TIMSK,OCIE1A);
  #else
    #error "Wrong CTCA Interrupt Choice"
  #endif

  #if TIMER1_CTCB_INTERRUPT == TIMER1_ENABLE_INTERRUPT
    SET_BIT(TIMSK,OCIE1B);
  #elif TIMER1_CTCB_INTERRUPT == TIMER1_DISABLE_INTERRUPT
    CLR_BIT(TIMSK,OCIE1B);
  #else
    #error "Wrong CTCB Interrupt Choice"
  #endif

  #if TIMER1_ICU_INTERRUPT == TIMER1_ENABLE_INTERRUPT
    SET_BIT(TIMSK,TICIE1);
  #elif TIMER1_ICU_INTERRUPT == TIMER1_DISABLE_INTERRUPT
    CLR_BIT(TIMSK,TICIE1);
  #else
    #error "Wrong ICU Interrupt Choice"
  #endif
}

static void TIMER1_SelectOC1_Mode(void){
  #if TIMER1_OC1A_MODE == TIMER1_DISCONNECTED
    CLR_BIT(TCCR1A,COM1A0);
    CLR_BIT(TCCR1A,COM1A1);
  #elif TIMER1_OC1A_MODE == TIMER1_TOGGLE_ON_CTC
    SET_BIT(TCCR1A,COM1A0);
    CLR_BIT(TCCR1A,COM1A1);
  #elif TIMER1_OC1A_MODE == TIMER1_CLEAR_ON_CTC
    CLR_BIT(TCCR1A,COM1A0);
    SET_BIT(TCCR1A,COM1A1);
  #elif TIMER1_OC1A_MODE == TIMER1_SET_ON_CTC
    SET_BIT(TCCR1A,COM1A0);
    SET_BIT(TCCR1A,COM1A1);
  #else
    #error "Wrong OC1A Mode Choice"
  #endif

  #if TIMER1_OC1B_MODE == TIMER1_DISCONNECTED
    CLR_BIT(TCCR1A,COM1B0);
    CLR_BIT(TCCR1A,COM1B1);
  #elif TIMER1_OC1B_MODE == TIMER1_TOGGLE_ON_CTC
    SET_BIT(TCCR1A,COM1B0);
    CLR_BIT(TCCR1A,COM1B1);
  #elif TIMER1_OC1B_MODE == TIMER1_CLEAR_ON_CTC
    CLR_BIT(TCCR1A,COM1B0);
    SET_BIT(TCCR1A,COM1B1);
  #elif TIMER1_OC1B_MODE == TIMER1_SET_ON_CTC
    SET_BIT(TCCR1A,COM1B0);
    SET_BIT(TCCR1A,COM1B1);
  #else
    #error "Wrong OC1B Mode Choice"
  #endif
}

static void TIMER1_SelectICNC1_Mode(void){
  #if TIMER1_ICNC1_MODE == TIMER1_DISABLE
    CLR_BIT(TCCR1B,ICNC1);
  #elif TIMER1_ICNC1_MODE == TIMER1_ENABLE
    SET_BIT(TCCR1B,ICNC1);
  #else
    #error "Wrong ICNC1 Mode Choice"
  #endif
}

static void TIMER1_SelectICES1_Mode(void){
  #if TIMER1_ICES1_MODE == TIMER1_ICES1_FALLING
    CLR_BIT(TCCR1B,ICES1);
  #elif TIMER1_ICES1_MODE == TIMER1_ICES1_RISING
    SET_BIT(TCCR1B,ICES1);
  #else
    #error "Wrong ICES1 Mode Choice"
  #endif
}
