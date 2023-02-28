/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  24 FEB 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

// initialize SysTick 
void STK_voidInit(void);

// makes the processor stuck for a certain time 
void STK_voidBusyWait(u32 copy_u32Ticks);

// fire interrupt after a certain time 
void STK_voidSetIntervalSingle(u32 copy_u32Ticks , void (*copy_ptr)(void));
// fire interrupt after a certain periodic time 
void STK_voidSetIntervalperiodic(u32 copy_u32Ticks , void (*copy_ptr)(void));

// stop the timer 
void STK_voidStopInterval(void);

// return the elapsed time 
u32  STK_u32GetElapsedTime(void);

// return the remaining time 
u32  STK_u32GetRemainingTime(void);

#endif // !STK_INTERFACE_H
