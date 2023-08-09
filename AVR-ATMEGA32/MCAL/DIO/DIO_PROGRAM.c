#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h" 
#include "../../LIB/ERR_STATE.h"
#include "DIO_INTERFACE.h"
#include "DIO_PRIVATE.h"

ES_t DIO_SetPinDirection(u8 Copy_u8Port ,u8 Copy_u8Pin ,u8 Copy_u8Direction)
{
  ES_t Local_enuErorrState = ES_NOK ;
  if (Copy_u8Pin < 8 && Copy_u8Pin >= 0)
  {
    switch (Copy_u8Port)
    {
      case PORTA :
        Local_enuErorrState = ES_OK ;
        if (Copy_u8Direction == INPUT)
        {
          CLR_BIT(DDRA_REG , Copy_u8Pin);
        }
        else if (Copy_u8Direction == OUTPUT)
        {
          SET_BIT(DDRA_REG , Copy_u8Pin);
        }
        else 
        {
          Local_enuErorrState = ES_OUT_OF_RANGE ;
        }
        break;
      case PORTB :
        Local_enuErorrState = ES_OK ;
        if (Copy_u8Direction == INPUT)
        {
          CLR_BIT(DDRB_REG , Copy_u8Pin );
        }
        else if (Copy_u8Direction == OUTPUT)
        {
          SET_BIT(DDRB_REG , Copy_u8Pin);
        }
        else 
        {
          Local_enuErorrState = ES_OUT_OF_RANGE ;
        }
        break;
      case PORTC :
        Local_enuErorrState = ES_OK ;
        if (Copy_u8Direction == INPUT)
        {
          CLR_BIT(DDRC_REG , Copy_u8Pin );
        }
        else if (Copy_u8Direction == OUTPUT)
        {
          SET_BIT(DDRC_REG , Copy_u8Pin);
        }
        else 
        {
          Local_enuErorrState = ES_OUT_OF_RANGE ;
        }
        break;
      case PORTD :
        Local_enuErorrState = ES_OK ;
        if (Copy_u8Direction == INPUT)
        {
          CLR_BIT(DDRD_REG , Copy_u8Pin );
        }
        else if (Copy_u8Direction == OUTPUT)
        {
          SET_BIT(DDRD_REG , Copy_u8Pin);
        }
        else 
        {
          Local_enuErorrState = ES_OUT_OF_RANGE ;
        }
        break;
      default: 
        Local_enuErorrState = ES_OUT_OF_RANGE ;
        break;
    }
  }
  else 
  {
    Local_enuErorrState = ES_OUT_OF_RANGE ;
  }
  return Local_enuErorrState ;
}

ES_t DIO_SetPinValue(u8 Copy_u8Port ,u8 Copy_u8Pin ,u8 Copy_u8Value)
{
  ES_t Local_enuErorrState = ES_NOK ;
  if (Copy_u8Pin < 8 && Copy_u8Pin >= 0)
  {
    switch (Copy_u8Port)
    {
      case PORTA :
        Local_enuErorrState = ES_OK ;
        if (Copy_u8Value == LOW || Copy_u8Value == FLOAT)
        {
          CLR_BIT(PORTA_REG , Copy_u8Pin);
        }
        else if (Copy_u8Value == HIGH || Copy_u8Value == PULL_UP)
        {
          SET_BIT(PORTA_REG , Copy_u8Pin);
        }
        else 
        {
          Local_enuErorrState = ES_OUT_OF_RANGE ;
        }
        break;
      case PORTB :
        Local_enuErorrState = ES_OK ;
        if (Copy_u8Value == LOW || Copy_u8Value == FLOAT)
        {
          CLR_BIT(PORTB_REG , Copy_u8Pin );
        }
        else if (Copy_u8Value == HIGH || Copy_u8Value == PULL_UP)
        {
          SET_BIT(PORTB_REG , Copy_u8Pin);
        }
        else 
        {
          Local_enuErorrState = ES_OUT_OF_RANGE ;
        }
        break;
      case PORTC :
        Local_enuErorrState = ES_OK ;
        if (Copy_u8Value == LOW || Copy_u8Value == FLOAT)
        {
          CLR_BIT(PORTC_REG , Copy_u8Pin );
        }
        else if (Copy_u8Value == HIGH || Copy_u8Value == PULL_UP)
        {
          SET_BIT(PORTC_REG , Copy_u8Pin);
        }
        else 
        {
          Local_enuErorrState = ES_OUT_OF_RANGE ;
        }
        break;
      case PORTD :
        Local_enuErorrState = ES_OK ;
        if (Copy_u8Value == LOW || Copy_u8Value == FLOAT)
        {
          CLR_BIT(PORTD_REG , Copy_u8Pin );
        }
        else if (Copy_u8Value == HIGH || Copy_u8Value == PULL_UP)
        {
          SET_BIT(PORTD_REG , Copy_u8Pin);
        }
        else 
        {
          Local_enuErorrState = ES_OUT_OF_RANGE ;
        }
        break;
      default:
        Local_enuErorrState = ES_OUT_OF_RANGE ;
        break;
    }
  }
  else 
  {
    Local_enuErorrState = ES_OUT_OF_RANGE ;
  }
  return Local_enuErorrState ;
}

ES_t DIO_GetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8 *Copy_pu8Value)
{
  ES_t Local_enuErorrState = ES_NOK ;
  if(Copy_pu8Value != NULL)
  {
    if (Copy_u8Pin < 8 && Copy_u8Pin >= 0)
    {
      switch (Copy_u8Port)
      {
        case PORTA :
          *Copy_pu8Value = GET_BIT(PINA_REG , Copy_u8Pin);
          Local_enuErorrState = ES_OK ;
          break;
        case PORTB :
          *Copy_pu8Value = GET_BIT(PINB_REG , Copy_u8Pin);
          Local_enuErorrState = ES_OK ;
          break;
        case PORTC :
          *Copy_pu8Value = GET_BIT(PINC_REG , Copy_u8Pin);
          Local_enuErorrState = ES_OK ;
          break;
        case PORTD :
          *Copy_pu8Value = GET_BIT(PIND_REG , Copy_u8Pin);
          Local_enuErorrState = ES_OK ;
          break;
        default: 
          Local_enuErorrState = ES_OUT_OF_RANGE ;
      }
    }
    else 
    {
      Local_enuErorrState = ES_OUT_OF_RANGE ;
    }
  }
  else 
  {
    Local_enuErorrState = ES_NULL_POINTER ;
  }
  return Local_enuErorrState ;
}

ES_t DIO_TogglePin(u8 Copy_u8Port, u8 Copy_u8Pin)
{
  ES_t Local_enuErorrState = ES_NOK ;
  if (Copy_u8Pin < 8 && Copy_u8Pin >= 0)
  {
    switch (Copy_u8Port)
    {
      case PORTA :
        Local_enuErorrState = ES_OK ;
        TOG_BIT(PORTA_REG, Copy_u8Pin);
        break;
      case PORTB :
        Local_enuErorrState = ES_OK ;
        TOG_BIT(PORTB_REG, Copy_u8Pin);
        break;
      case PORTC :
        Local_enuErorrState = ES_OK ;
        TOG_BIT(PORTC_REG, Copy_u8Pin);
        break;
      case PORTD :
        Local_enuErorrState = ES_OK ;
        TOG_BIT(PORTD_REG, Copy_u8Pin);
        break;
      default :
        Local_enuErorrState = ES_OUT_OF_RANGE ;
        break;
    }
  }
  else 
  {
    Local_enuErorrState = ES_OUT_OF_RANGE ;
  }
  return Local_enuErorrState ;
}

ES_t DIO_SetPortDirection (u8 Copy_u8Port , u8 Copy_u8Direction)
{
  ES_t Local_enuErorrState = ES_NOK ;
	switch (Copy_u8Port)
	{
    case PORTA : 
      DDRA_REG = Copy_u8Direction ;
      Local_enuErorrState = ES_OK ;
      break;
    case PORTB : 
      DDRB_REG = Copy_u8Direction ;
      Local_enuErorrState = ES_OK ;
      break;
    case PORTC : 
      DDRC_REG = Copy_u8Direction ;
      Local_enuErorrState = ES_OK ;
      break;
    case PORTD : 
      DDRD_REG = Copy_u8Direction ;
      Local_enuErorrState = ES_OK ;
      break;
    default:
      Local_enuErorrState = ES_OUT_OF_RANGE ;
      break;
	}
  return Local_enuErorrState ;
}

ES_t DIO_SetPortValue(u8 Copy_u8Port , u8 Copy_u8Value)
{
  ES_t Local_enuErorrState = ES_NOK ;
	switch (Copy_u8Port)
	{
    case PORTA : 
      PORTA_REG = Copy_u8Value ;
      Local_enuErorrState = ES_OK ;
      break;
    case PORTB : 
      PORTB_REG = Copy_u8Value ;
      Local_enuErorrState = ES_OK ;
      break;
    case PORTC : 
      PORTC_REG = Copy_u8Value ;
      Local_enuErorrState = ES_OK ;
      break;
    case PORTD : 
      PORTD_REG = Copy_u8Value ;
      Local_enuErorrState = ES_OK ;
      break;
    default:
      Local_enuErorrState = ES_OUT_OF_RANGE ;
      break;
	}
  return Local_enuErorrState ;
}

ES_t   DIO_GetPortValue     (u8 Copy_u8Port , u8 *Copy_pu8Value)
{
  ES_t Local_enuErorrState = ES_NOK ;
  if (Copy_pu8Value != NULL)
  {
    switch (Copy_u8Port)
    {
      case PORTA :
        *Copy_pu8Value = PINA_REG ;
        Local_enuErorrState = ES_OK ;
        break;
      case PORTB :
        *Copy_pu8Value = PINB_REG ;
        Local_enuErorrState = ES_OK ;
        break;
      case PORTC :
        *Copy_pu8Value = PINC_REG ;
        Local_enuErorrState = ES_OK ;
        break;
      case PORTD :
        *Copy_pu8Value = PIND_REG ;
        Local_enuErorrState = ES_OK ;
        break;
      default:
        Local_enuErorrState = ES_OUT_OF_RANGE ;
        break;
    }
  }
  else 
  {
    Local_enuErorrState = ES_NULL_POINTER ;
  }
  return Local_enuErorrState ;
}

ES_t DIO_TogglePort(u8 Copy_u8Port)
{
  ES_t Local_enuErorrState = ES_NOK ;
  switch (Copy_u8Port) 
  {
    case PORTA :
      PORTA_REG = ~PORTA_REG ;
      Local_enuErorrState = ES_OK ;
      break;
    case PORTB :
      PORTB_REG = ~PORTB_REG ;
      Local_enuErorrState = ES_OK ;
      break;
    case PORTC :
      PORTC_REG = ~PORTC_REG ;
      Local_enuErorrState = ES_OK ;
      break;
    case PORTD :
      PORTD_REG = ~PORTD_REG ;
      Local_enuErorrState = ES_OK ;
      break;
    default:
      Local_enuErorrState = ES_OUT_OF_RANGE ;
      break;
  }
  return Local_enuErorrState ;
}
