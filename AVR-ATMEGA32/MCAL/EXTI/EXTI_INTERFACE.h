#include "../../LIB/STD_TYPES.h"
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

// INT_NUM
#define	EXTI_INT0  0
#define	EXTI_INT1  1
#define	EXTI_INT2  2


/* this function initializes INT0 */
void EXTI_INT0_Init(void);


/* this function initializes INT1 */
void EXTI_INT1_Init(void);

/* this function initializes INT2 */
void EXTI_INT2_Init(void);

// this function takes a pointer to a function to execute it in ISR 
void EXTI_CallBackFunction(void (*fun)(void) ,u8 INT_Num );

void EXTI_SetTrigger(u8 Trigger);

void EXTI_Disable_INT(u8 INT_Num);
#endif
