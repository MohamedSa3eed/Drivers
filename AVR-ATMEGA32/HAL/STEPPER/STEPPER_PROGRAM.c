#include "../../LIB/STD_TYPES.h"
#include "../../LIB/ERR_STATE.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "STEPPER_INTERFACE.h"
#include "STEPPER_CONFIG.h"
#include </usr/avr/include/avr/delay.h>

ES_t STEPPER_Init(void)
{
  ES_t Local_u8ErrorState = ES_NOK ;
  Local_u8ErrorState =	DIO_SetPinDirection(STEPPER_BLUE_PIN,OUTPUT);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }
  Local_u8ErrorState =	DIO_SetPinDirection(STEPPER_PINK_PIN,OUTPUT);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }
  Local_u8ErrorState =	DIO_SetPinDirection(STEPPER_YELLOW_PIN,OUTPUT);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }
  Local_u8ErrorState =	DIO_SetPinDirection(STEPPER_ORANGE_PIN,OUTPUT);
  return Local_u8ErrorState ;
}

ES_t STEPPER_FullStep(void)
{
  ES_t Local_u8ErrorState = ES_NOK ;
	u8 Local_pu8Value ;
  Local_u8ErrorState = DIO_GetPortValue(STEPPER_PORT , &Local_pu8Value);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }
	switch (Local_pu8Value) {
		case 0b00000000 :
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_BLUE_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
    case 0b00000001:
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_PINK_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
      break;
		case 0b00000010:
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_YELLOW_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
    case 0b00000100 :
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_ORANGE_PIN, HIGH);
			_delay_ms(5);
			break;
		case 0b00001000 :
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_BLUE_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
	}
  return Local_u8ErrorState ;
}

ES_t STEPPER_HalfStvoidep(void)
{
  ES_t Local_u8ErrorState = ES_NOK ;
  u8 Local_pu8Value ;
  Local_u8ErrorState = DIO_GetPortValue(STEPPER_PORT , &Local_pu8Value);
  if (Local_u8ErrorState != ES_OK) {
    return Local_u8ErrorState ;
  }
  switch (Local_pu8Value) 
  {
		case 0b00000000 :
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_BLUE_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =	DIO_SetPinValue(STEPPER_ORANGE_PIN, HIGH);
			_delay_ms(5);
			break;
    case 0b00001001:
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_BLUE_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
      break;
		case 0b00000001:
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_BLUE_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_PINK_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
    case 0b00000011 :
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_PINK_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
		case 0b00000010 :
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_PINK_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_YELLOW_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
    case 0b00000110 :
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_YELLOW_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
    case 0b00000100 :
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_YELLOW_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_ORANGE_PIN, HIGH);
			_delay_ms(5);
			break;
    case 0b00001100 :
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_ORANGE_PIN, HIGH);
			_delay_ms(5);
			break;
    case 0b00001000 :
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_BLUE_PIN, HIGH);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
      if (Local_u8ErrorState != ES_OK) {
        return Local_u8ErrorState ;
      }
      Local_u8ErrorState =  DIO_SetPinValue(STEPPER_ORANGE_PIN, HIGH);
			_delay_ms(5);
			break;
	}
  return Local_u8ErrorState ;
}
