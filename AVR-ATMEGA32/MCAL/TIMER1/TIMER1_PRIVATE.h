#ifndef TIMER0_PRIVATE_H
#define TIMER0_PRIVATE_H

// avr atmega32 has 3 timers
// timer0, timer1, timer2
// this is driver for timer1

// timer1 registers

// timer1 control register A 
#define TCCR1A *((volatile u8*)0x4F) 
#define WGM10     0 // wave generation mode
#define WGM11     1 // wave generation mode
#define FOC1B     2 // force output compare
#define FOC1A     3 // force output compare
#define COM1B0    4 // compare output mode
#define COM1B1    5 // compare output mode
#define COM1A0    6 // compare output mode
#define COM1A1    7 // compare output mode

// timer1 control register B
#define TCCR1B *((volatile u8*)0x4E)
#define CS10      0 // clock select
#define CS11      1 // clock select
#define CS12      2 // clock select
#define WGM12     3 // wave generation mode
#define WGM13     4 // wave generation mode
#define ICES1     6 // input capture edge select
#define ICNC1     7 // input capture noise canceler

// timer1 counter register low byte 
#define TCNT1L *((volatile u8*)0x4C)

// timer1 counter register high byte 
#define TCNT1H *((volatile u8*)0x4D) 

// timer1 output compare register low byte
#define OCR1AL *((volatile u8*)0x4A) 

// timer1 output compare register high byte
#define OCR1AH *((volatile u8*)0x4B) 

// timer1 output compare register low byte
#define OCR1BL *((volatile u8*)0x48)

// timer1 output compare register high byte
#define OCR1BH *((volatile u8*)0x49)

// timer1 input capture register low byte
#define ICR1L *((volatile u8*)0x46)

// timer1 input capture register high byte
#define ICR1H *((volatile u8*)0x47) 

// timer1 interrupt mask register
#define TIMSK *((volatile u8*)0x59)
#define TOIE1     2 // timer overflow interrupt enable
#define OCIE1B    3 // output compare interrupt enable
#define OCIE1A    4 // output compare interrupt enable
#define TICIE1    5 // input capture interrupt enable

// timer1 interrupt flag register 
#define TIFR *((volatile u8*)0x58) 
#define TOV1      2 // timer overflow flag
#define OCF1B     3 // output compare flag
#define OCF1A     4 // output compare flag
#define ICF1      5 // input capture flag

/*------------------Macros for Timer1 Configurations------------------*/

#define TIMER1_NORMAL_MODE                            0
#define TIMER1_PHASE_CORRECT_PWM_8_BIT                1
#define TIMER1_PHASE_CORRECT_PWM_9_BIT                2
#define TIMER1_PHASE_CORRECT_PWM_10_BIT               3
#define TIMER1_CTC_OCR1A                              4
#define TIMER1_FAST_PWM_8_BIT                         5
#define TIMER1_FAST_PWM_9_BIT                         6
#define TIMER1_FAST_PWM_10_BIT                        7
#define TIMER1_PWM_PHASE_AND_FREQUENCY_CORRECT_ICR1   8
#define TIMER1_PWM_PHASE_AND_FREQUENCY_CORRECT_OCR1A  9
#define TIMER1_PWM_PHASE_CORRECT_ICR1                 10
#define TIMER1_PWM_PHASE_CORRECT_OCR1A                11
#define TIMER1_CTC_ICR1                               12
#define TIMER1_FAST_PWM_ICR1                          14
#define TIMER1_FAST_PWM_OCR1A                         15

#define TIMER1_NO_CLOCK                               0
#define TIMER1_NO_PRESCALER                           1
#define TIMER1_PRESCALER_8                            2
#define TIMER1_PRESCALER_64                           3
#define TIMER1_PRESCALER_256                          4
#define TIMER1_PRESCALER_1024                         5
#define TIMER1_EXTERNAL_CLOCK_FALLING                 6
#define TIMER1_EXTERNAL_CLOCK_RISING                  7

#define TIMER1_DISCONNECTED                           0
#define TIMER1_TOGGLE_ON_CTC                          1
#define TIMER1_CLEAR_ON_CTC                           2
#define TIMER1_SET_ON_CTC                             3
#define TIMER1_CLEAR_AT_COUNTING_UP                   2
#define TIMER1_SET_AT_COUNTING_UP                     3

#define TIMER1_DISABLE                                0
#define TIMER1_ENABLE                                 1

#define TIMER1_ICES1_FALLING                          0
#define TIMER1_ICES1_RISING                           1

#define TIMER1_DISABLE_INTERRUPT                      0
#define TIMER1_ENABLE_INTERRUPT                       1

/*------------------Functions Prototypes for Timer1------------------*/

/*
 * @brief: this function sets the Timer1 mode.
 *
 * @param void.
 *
 * @return void.
 *
 */
static void TIMER1_SelectMode(void);

/*
 * @brief: this function sets the Timer1 prescaler.
 *
 * @param void.
 *
 * @return void.
 *
 */
static void TIMER1_SelectPrescaler(void);

/*
 * @brief: this function sets the Timer1 output compare pin mode.
 *
 * @param void.
 *
 * @return void.
 *
 */
static void TIMER1_SelectOC1_Mode(void);

/*
 * @brief: this function sets the Timer1 input capture noise canceler.
 *
 * @param void.
 *
 * @return void.
 *
 */
static void TIMER1_SelectICNC1_Mode(void);

/*
 * @brief: this function sets the Timer1 input capture edge select.
 *
 * @param void.
 *
 * @return void.
 *
 */
static void TIMER1_SelectICES1_Mode(void);

/*
 * @brief: this function sets the Timer1 interrupt enable.
 *
 * @param void.
 *
 * @return void.
 *
 */
static void TIMER1_SelectInterrupt(void);

#endif
