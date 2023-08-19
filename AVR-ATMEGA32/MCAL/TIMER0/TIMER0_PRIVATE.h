#ifndef TIMER0_PRIVATE_H
#define TIMER0_PRIVATE_H

// Timer Counter control register for timer 0
#define TCCR0                       *((volatile u8 *)0x53) 
// wave generation mode for timer 0
#define TCCR0_WGM00                 6         
#define TCCR0_WGM01                 3
// clock select for timer 0 (prescaler) 
#define TCCR0_CS00                  0
#define TCCR0_CS01                  1
#define TCCR0_CS02                  2
#define TCCR0_COM01                 5
#define TCCR0_COM00                 4

//  Timer/Counter 0 Register 
#define TCNT0                       *((volatile u8 *)0x52)

//  output compare register for timer/counter 0
#define OCR0                        *((volatile u8 *)0x5C)

//  Timer/Counter 0 Interupt mask register
#define TIMSK                       *((volatile u8 *)0x59)
//  timer/counter 0 overflow interupt enable 
#define TIMSK_TOIE0                 0
//  timer/counter 0 compare match interupt enable
#define TIMSK_OCIE0                 1

// timer/counter interupt flag register 
#define TIFR                        *((volatile u8 *)0x58)
// timer 0 output compare flage
#define TIFR_OCF0                   1
// timer 0 overflow flag 
#define TIFR_TOV0                   0 

//TIMER_MODE
#define	TIMER_NORMAL                1 
#define	TIMER_CTC                   2 
#define	TIMER_PWM_PHASE_CORRECT     3 
#define	TIMER_FAST_PWM              4 

//TIMER_CLK 
#define TIMER_NO_CLK                0
#define TIMER_SYS_CLK               1
#define TIMER_CLK_8                 8
#define TIMER_CLK_64                64
#define TIMER_CLK_256               256
#define TIMER_CLK_1024              1024
#define TIMER_EXT_PIN_FALLING_EDGE  7
#define TIMER_EXT_PIN_RISING_EDGE   8

//TIMER_STATE
#define	ENABLED                     1 
#define	DISABLED                    2 

//The max value of TCNT0
#define REG_MAX                     256

//Modes for ISR
#define TIMER_SINGLE_MODE           1
#define TIMER_PERIODIC_MODE         2
#define TIMER_NO_MODE               3

//OC0 pin mode
#define DISCONECTED                 1
#define TOGGLE_ON_CTC               2
#define CLEAR_ON_CTC                3
#define SET_ON_CTC                  4
#define CLEAR_AT_COUNTING_UP        3
#define SET_AT_COUNTING_UP          4

#endif
