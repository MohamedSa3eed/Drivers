#include "../../LIB/STD_TYPES.h"
#include "../../LIB//BIT_MATH.h"
#include "EXTI_INTERFACE.h"
#include "EXTI_CONFIG.h"
#include "EXTI_PRIVATE.h"


static void (*INT_CallBack[3]) (void)= {NULL ,NULL ,NULL};

void EXTI_INT0_Init(void)
{
	/*check for the INT0_STATE */
     #if INT0_STATE == ENABLED

	SET_BIT(GICR,GICR_INT0);

	/*check for the INT0_SENSE */
      #if INT0_SENSE == LOW_LEVEL	
	
	CLR_BIT(MCUCR,ISC00);
	CLR_BIT(MCUCR,ISC01);

      #elif INT0_SENSE == ON_CHANGE
     SET_BIT(MCUCR,ISC00);
	 CLR_BIT(MCUCR,ISC01);

      #elif INT0_SENSE == FALLING_EDGE

	CLR_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC01);

      #elif INT0_SENSE == RISING_EDGE
      
    SET_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC01);

      #else 
	#error "WRONG SENSE FOR INT0"
	
      #endif


     #elif INT0_STATE == DISABLED

	CLR_BIT(GICR,GICR_INT0);

     #else 
        #error "WRONG STATE FOR INT0"

     #endif

}
void EXTI_INT1_Init(void)
{
	/*check for the INT1_STATE */
     #if INT1_STATE == ENABLED

	SET_BIT(GICR,GICR_INT1);

	/*check for the INT1_SENSE */
      #if INT1_SENSE == LOW_LEVEL	
	
	CLR_BIT(MCUCR,ISC10);
	CLR_BIT(MCUCR,ISC11);

      #elif INT1_SENSE == ON_CHANGE
        SET_BIT(MCUCR,ISC10);
	CLR_BIT(MCUCR,ISC11);

      #elif INT1_SENSE == FALLING_EDGE

	CLR_BIT(MCUCR,ISC10);
	SET_BIT(MCUCR,ISC11);

      #elif INT1_SENSE == RISING_EDGE
      
    SET_BIT(MCUCR,ISC10);
	SET_BIT(MCUCR,ISC11);

      #else 
         #error "WRONG SENSE FOR INT1"
	
      #endif


     #elif INT1_STATE == DISABLED

	CLR_BIT(GICR,GICR_INT1);

     #else
	#error "WRONG STATE FOR INT1"

     #endif

}
void EXTI_INT2_Init(void)
{
	/*check for the INT2_STATE */
     #if INT2_STATE == ENABLED

	  SET_BIT(GICR,GICR_INT2);

	/*check for the INT2_SENSE */
      #if INT2_SENSE == FALLING_EDGE

       CLR_BIT(MCUCSR,ISC2);

      #elif INT2_SENSE == RISING_EDGE
      
       SET_BIT(MCUCSR,ISC2);

      #else 
       #error "WRONG SENSE FOR INT2"
	
      #endif


     #elif INT2_STATE == DISABLED

	CLR_BIT(GICR,GICR_INT2);

     #else 
	#error "WRONG STATE FOR INT2"

     #endif

}
void EXTI_CallBackFunction(void (*fun)(void) ,u8 INT_Num )
{
	if(fun != NULL)
       INT_CallBack[INT_Num] = fun ;
}
void __vector_1 (void) __attribute__ ((signal));
void __vector_1 (void)
{
	if (INT_CallBack[EXTI_INT0] != NULL)
	{
		INT_CallBack[EXTI_INT0]();
	}
}
void __vector_2 (void) __attribute__ ((signal));
void __vector_2 (void)
{
	if (INT_CallBack[EXTI_INT1] != NULL)
	{
		INT_CallBack[EXTI_INT1]();
	}
}
void __vector_3 (void) __attribute__ ((signal));
void __vector_3 (void)
{
	if (INT_CallBack[EXTI_INT2] != NULL)
	{
		INT_CallBack[EXTI_INT2]();
	}
}

void EXTI_Disable_INT(u8 INT_Num)
{
	switch (INT_Num) {
		case EXTI_INT0 :
			{ 
			     CLR_BIT(GICR,GICR_INT0);
				break;
			}
		case EXTI_INT1 :
			{ 
			     CLR_BIT(GICR,GICR_INT1);
				break;
			}
		case EXTI_INT2 :
			{ 
			     CLR_BIT(GICR,GICR_INT2);
				break;
			}

	}
}
void EXTI_SetTrigger(u8 Trigger)
{

      switch (Trigger) {
      case LOW_LEVEL :	
	
	{CLR_BIT(MCUCR,ISC00);
	CLR_BIT(MCUCR,ISC01);
	break;
	}
      
	case ON_CHANGE:
      {
        SET_BIT(MCUCR,ISC00);
	CLR_BIT(MCUCR,ISC01);
	break;
      }
	case FALLING_EDGE :
      {
	CLR_BIT(MCUCR,ISC00);
      	SET_BIT(MCUCR,ISC01);
	break;
      }
	case RISING_EDGE:
      {
        SET_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC01);
	break;
      }
}
}
