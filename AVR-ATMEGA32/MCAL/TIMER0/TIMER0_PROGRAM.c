#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERR_STATE.h"

#include "TIMER0_INTERFACE.h"
#include "TIMER0_PRIVATE.h"
#include "TIMER0_CONFIG.h"

static void (*TIMER0_OF_CallBack)(void)  = NULL ;
static void (*TIMER0_CTC_CallBack)(void) = NULL ;

static u8 interval_mode;
static u8 preload;
static u32 NofOvfs_int;
static u32 ConstNofOvfs_int;

void TIMER0_Init()
{
  #if TIMER0_MODE == TIMER_NORMAL 
    CLR_BIT(TCCR0,TCCR0_WGM00);
    CLR_BIT(TCCR0,TCCR0_WGM01);
  #elif TIMER0_MODE == TIMER_CTC
    CLR_BIT(TCCR0,TCCR0_WGM00);
    SET_BIT(TCCR0,TCCR0_WGM01);
  #elif TIMER0_MODE == TIMER_PWM_PHASE_CORRECT
    OCR0 = 0;
    SET_BIT(TCCR0,TCCR0_WGM00);
    CLR_BIT(TCCR0,TCCR0_WGM01);
  #elif TIMER0_MODE == TIMER_FAST_PWM
    OCR0 = 0;
    SET_BIT(TCCR0,TCCR0_WGM00);
    SET_BIT(TCCR0,TCCR0_WGM01);
  #else 
    #error "WRONG TIMER0 MODE"
  #endif 

  #if TIMER0_CLK == TIMER_NO_CLK
    CLR_BIT(TCCR0, TCCR0_CS00);
    CLR_BIT(TCCR0, TCCR0_CS01);
    CLR_BIT(TCCR0, TCCR0_CS02);
  #elif TIMER0_CLK == TIMER_SYS_CLK
    SET_BIT(TCCR0, TCCR0_CS00);
    CLR_BIT(TCCR0, TCCR0_CS01);
    CLR_BIT(TCCR0, TCCR0_CS02);
  #elif TIMER0_CLK == TIMER_CLK_8 
    CLR_BIT(TCCR0, TCCR0_CS00);
    SET_BIT(TCCR0, TCCR0_CS01);
    CLR_BIT(TCCR0, TCCR0_CS02);
  #elif TIMER0_CLK == TIMER_CLK_64
    SET_BIT(TCCR0, TCCR0_CS00);
    SET_BIT(TCCR0, TCCR0_CS01);
    CLR_BIT(TCCR0, TCCR0_CS02);
  #elif TIMER0_CLK == TIMER_CLK_256
    CLR_BIT(TCCR0, TCCR0_CS00);
    CLR_BIT(TCCR0, TCCR0_CS01);
    SET_BIT(TCCR0, TCCR0_CS02);
  #elif TIMER0_CLK == TIMER_CLK_1024
    SET_BIT(TCCR0, TCCR0_CS00);
    CLR_BIT(TCCR0, TCCR0_CS01);
    SET_BIT(TCCR0, TCCR0_CS02);
  #elif TIMER0_CLK == TIMER_EXT_PIN_FALLING_EDGE
    CLR_BIT(TCCR0, TCCR0_CS00);
    SET_BIT(TCCR0, TCCR0_CS01);
    SET_BIT(TCCR0, TCCR0_CS02);
  #elif TIMER0_CLK == TIMER_EXT_PIN_RISING_EDGE
    SET_BIT(TCCR0, TCCR0_CS00);
    SET_BIT(TCCR0, TCCR0_CS01);
    SET_BIT(TCCR0, TCCR0_CS02);
  #else 
    #error "WRONG CLOCK SET FOR TIMER0"
  #endif

  #if TIMER0_OFI == ENABLED
    SET_BIT(TIMSK, TIMSK_TOIE0);
  #elif TIMER0_OFI == DISABLED 
    CLR_BIT(TIMSK,TIMSK_TOIE0);
  #else 
    #error "WRONG OPTION FOR OVF INTERRUPT"
  #endif 

  #if TIMER0_OCI == ENABLED
    SET_BIT(TIMSK, TIMSK_OCIE0);
  #elif TIMER0_OCI == DISABLED 
    CLR_BIT(TIMSK,TIMSK_OCIE0);
  #else 
    #error "WRONG OPTION FOR CTC INTERRUPT"
  #endif 

  #if TIMER0_OC0_PIN_MODE == DISCONECTED
    CLR_BIT(TCCR0, TCCR0_COM00);
    CLR_BIT(TCCR0, TCCR0_COM01);
  #elif TIMER0_OC0_PIN_MODE == TOGGLE_ON_CTC 
    SET_BIT(TCCR0, TCCR0_COM00);
    CLR_BIT(TCCR0, TCCR0_COM01);
  #elif TIMER0_OC0_PIN_MODE == CLEAR_ON_CTC
    CLR_BIT(TCCR0, TCCR0_COM00);
    SET_BIT(TCCR0, TCCR0_COM01);
  #elif TIMER0_OC0_PIN_MODE == SET_ON_CTC
    SET_BIT(TCCR0, TCCR0_COM00);
    SET_BIT(TCCR0, TCCR0_COM01);
  #else 
    #error "WRONG OPTION FOR OC0 PIN"
  #endif
}

ES_t TIMER0_SetPreload(u8 Copy_u8Preload)
{
  ES_t Local_enumErrorState = ES_NOK;
  if (Copy_u8Preload < (u8)REG_MAX) {
    TCNT0 = Copy_u8Preload;
    Local_enumErrorState = ES_OK;
  }
  else {
    Local_enumErrorState = ES_OUT_OF_RANGE;
  }
  return Local_enumErrorState;
}

ES_t TIMER0_SetDuty(u8 Copy_u8DutyCycleValue)
{
  ES_t Local_enumErrorState = ES_NOK;
  if (Copy_u8DutyCycleValue <= 100){
    OCR0 = (Copy_u8DutyCycleValue * (REG_MAX - 1) / 100);
    Local_enumErrorState = ES_OK;
  } 
  else {
    Local_enumErrorState = ES_OUT_OF_RANGE;
  }
  return Local_enumErrorState;
}

ES_t TIMER0_OvfInterruptEnable(void)
{
  SET_BIT(TIMSK, TIMSK_TOIE0);
  return ES_OK;
}

ES_t TIMER0_OvfInterruptDisable(void)
{
  SET_BIT(TIMSK, TIMSK_TOIE0);
  return ES_OK;
}

ES_t TIMER0_CtcInterruptEnable(void)
{
  SET_BIT(TIMSK, TIMSK_OCIE0);
  return ES_OK;
}

ES_t TIMER0_CtcInterruptDisable(void)
{
  SET_BIT(TIMSK, TIMSK_OCIE0);
  return ES_OK;
}

ES_t TIMER0_SetOvfINTCallBack(void (*pfunc)(void))
{
  ES_t Local_enumErrorState = ES_NOK;
	if (pfunc != NULL)
  {
    TIMER0_OF_CallBack = pfunc ; 
    interval_mode = TIMER_NO_MODE ;
    Local_enumErrorState = ES_OK;
  }
  else
  {
    Local_enumErrorState = ES_NULL_POINTER;
  }
  return Local_enumErrorState;
}

ES_t TIMER0_SetCtcINTCallBack(void (*pfunc)(void))
{
  ES_t Local_enumErrorState = ES_NOK;
	if (pfunc != NULL)
  {
		TIMER0_CTC_CallBack = pfunc ;
    Local_enumErrorState = ES_OK;
  }
  else
  {
    Local_enumErrorState = ES_NULL_POINTER;
  }
  return Local_enumErrorState;
}

ES_t TIMER0_BusyWaitms(u32 Copy_u32Time)
{
  if (Copy_u32Time == 0 ) 
    return ES_OK;
  if (TIMER0_CLK == 0 || CPU_CLK == 0) 
    return ES_NOK;
  CLR_BIT(TIMSK, TIMSK_TOIE0); //disable OVF interrupt
  f32 ovfTime = REG_MAX * ((f32)TIMER0_CLK / CPU_CLK ) ;
  f32 NofOvfs = ((f32)Copy_u32Time / ovfTime ) ;
  u32 NofOvfs_int = (u32)NofOvfs;
  u8 preload  = REG_MAX - ( (NofOvfs - NofOvfs_int) * REG_MAX ) ; 
  if(preload != 0)
  {
    NofOvfs_int++ ;
  }
  TCNT0 = preload ;
  while (NofOvfs_int --) {
    while (GET_BIT(TIFR, TIFR_TOV0) == 0) {
    }
    SET_BIT(TIFR, TIFR_TOV0);
  }
  return ES_OK;
}
ES_t TIMER0_BusyWaitus(u32 Copy_u32Time)
{
  if (Copy_u32Time == 0 ) 
    return ES_OK;
  if (TIMER0_CLK == 0 || CPU_CLK == 0) 
    return ES_NOK;
  CLR_BIT(TIMSK, TIMSK_TOIE0); //disable OVF interrupt
  f32 ovfTime = REG_MAX * ((f32)TIMER0_CLK / CPU_CLK )*1000 ;
  f32 NofOvfs = ((f32)Copy_u32Time / ovfTime ) ;
  u32 NofOvfs_int = (u32)NofOvfs;
  u8 preload  = REG_MAX - ( (NofOvfs - NofOvfs_int) * REG_MAX ) ; 
  if(preload != 0)
  {
    NofOvfs_int++ ;
  }
  TCNT0 = preload ;
  while (NofOvfs_int --) {
    while (GET_BIT(TIFR, TIFR_TOV0) == 0) {
    }
    SET_BIT(TIFR, TIFR_TOV0);
  }
  return ES_OK;
}

ES_t TIMER0_SetAsyncFunctionPeriodic(u32 Copy_u32Time, void (*Pfunc)(void))
{
  if (Copy_u32Time == 0 ) 
    return ES_OK;
  if (TIMER0_CLK == 0 || CPU_CLK == 0) 
    return ES_NOK;
  CLR_BIT(TIMSK, TIMSK_TOIE0); //disable OVF interrupt
  f32 ovfTime = REG_MAX * ((f32)TIMER0_CLK / CPU_CLK ) ;
  f32 NofOvfs = ((f32)Copy_u32Time / ovfTime ) ;
  NofOvfs_int = (u32)NofOvfs;
  preload  = REG_MAX - ( (NofOvfs - NofOvfs_int) * REG_MAX ) ; 
  if(preload != 0)
  {
    NofOvfs_int++ ;
  }
  ConstNofOvfs_int = NofOvfs_int ;
  TIMER0_SetOvfINTCallBack(Pfunc);
  interval_mode = TIMER_PERIODIC_MODE ;
  TCNT0 = preload ;
  SET_BIT(TIMSK, TIMSK_TOIE0); //enable OVF interrupt
  return ES_OK;
}

ES_t TIMER0_SetAsyncFunctionSingle(u32 Copy_u32Time, void (*Pfunc)(void))
{
  if (Copy_u32Time == 0) 
    return ES_OK;
  if (TIMER0_CLK == 0 || CPU_CLK == 0) 
    return ES_NOK;
  CLR_BIT(TIMSK, TIMSK_TOIE0); //disable OVF interrupt
  f32 ovfTime = REG_MAX * ((f32)TIMER0_CLK / CPU_CLK ) ;
  f32 NofOvfs = ((f32)Copy_u32Time / ovfTime ) ;
  NofOvfs_int = (u32)NofOvfs;
  preload  = REG_MAX - ( (NofOvfs - NofOvfs_int) * REG_MAX ) ; 
  if(preload != 0)
  {
    NofOvfs_int++ ;
  }
  ConstNofOvfs_int = NofOvfs_int ;
  TIMER0_SetOvfINTCallBack(Pfunc);
  interval_mode = TIMER_SINGLE_MODE ;
  TCNT0 = preload ;
  SET_BIT(TIMSK, TIMSK_TOIE0); //enable OVF interrupt
  return ES_OK;
}

void TIMER0_Stop(void){
  CLR_BIT(TCCR0, TCCR0_CS00);
  CLR_BIT(TCCR0, TCCR0_CS01);
  CLR_BIT(TCCR0, TCCR0_CS02);
}

void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if(TIMER0_OF_CallBack != NULL)
	{
    if (interval_mode != TIMER_NO_MODE)
    {
      NofOvfs_int -- ;
      if (NofOvfs_int == 0) {
        TIMER0_OF_CallBack();
        TCNT0 = preload ;
        NofOvfs_int = ConstNofOvfs_int;
        if (interval_mode == TIMER_SINGLE_MODE) {
          CLR_BIT(TIMSK, TIMSK_TOIE0); //disable OVF interrupt
        }
      }
    }
    else {
      TIMER0_OF_CallBack();
    }
	}
}

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(TIMER0_CTC_CallBack != NULL)
	{
		TIMER0_CTC_CallBack();
	}
}
