#ifndef TIMER0_CONFIG_H
#define TIMER0_CONFIG_H

// the cpu clock in KHZ
#define CPU_CLK      8000ul       

// timer1 modes
/* 
 * options: 
 *          TIMER1_NORMAL_MODE
 *          TIMER1_PHASE_CORRECT_PWM_8_BIT
 *          TIMER1_PHASE_CORRECT_PWM_9_BIT
 *          TIMER1_PHASE_CORRECT_PWM_10_BIT
 *          TIMER1_CTC_OCR1A
 *          TIMER1_FAST_PWM_8_BIT
 *          TIMER1_FAST_PWM_9_BIT
 *          TIMER1_FAST_PWM_10_BIT
 *          TIMER1_PWM_PHASE_AND_FREQUENCY_CORRECT_ICR1
 *          TIMER1_PWM_PHASE_AND_FREQUENCY_CORRECT_OCR1A
 *          TIMER1_PWM_PHASE_CORRECT_ICR1
 *          TIMER1_PWM_PHASE_CORRECT_OCR1A
 *          TIMER1_CTC_ICR1
 *          TIMER1_FAST_PWM_ICR1
 *          TIMER1_FAST_PWM_OCR1A
 */
#define TIMER1_MODE  TIMER1_NORMAL_MODE

// timer1 prescaler
/* 
 * options: 
 *          TIMER1_NO_CLOCK
 *          TIMER1_NO_PRESCALER
 *          TIMER1_PRESCALER_8
 *          TIMER1_PRESCALER_64
 *          TIMER1_PRESCALER_256
 *          TIMER1_PRESCALER_1024
 *          TIMER1_EXTERNAL_CLOCK_FALLING
 *          TIMER1_EXTERNAL_CLOCK_RISING
 */
#define TIMER1_PRESCALER  TIMER1_NO_PRESCALER

// timer1 output compare pin mode 
/* 
 * options: 
 *          TIMER1_DISCONNECTED
 *          TIMER1_TOGGLE_ON_CTC          (CTC)
 *          TIMER1_CLEAR_ON_CTC           (CTC)
 *          TIMER1_SET_ON_CTC             (CTC)
 *          TIMER1_CLEAR_AT_COUNTING_UP   (PWM)
 *          TIMER1_SET_AT_COUNTING_UP     (PWM)
 */
#define TIMER1_OC1A_MODE  TIMER1_DISCONNECT
#define TIMER1_OC1B_MODE  TIMER1_DISCONNECT

// timer1 input capture noise canceler
/* 
 * options: 
 *          TIMER1_DISABLE
 *          TIMER1_ENABLE
 */
#define TIMER1_ICNC1_MODE TIMER1_ICNC1_DISABLE

// timer1 input capture edge select
/* 
 * options: 
 *          TIMER1_ICES1_FALLING
 *          TIMER1_ICES1_RISING
 */
#define TIMER1_ICES1_MODE TIMER1_ICES1_FALLING

// timer1 interrupt enable
/* 
 * options: 
 *          TIMER1_ENABLE_INTERRUPT
 *          TIMER1_DISABLE_INTERRUPT
 */
#define TIMER1_OVF_INTERRUPT  TIMER1_DISABLE_INTERRUPT
#define TIMER1_CTCA_INTERRUPT TIMER1_DISABLE_INTERRUPT
#define TIMER1_CTCB_INTERRUPT TIMER1_DISABLE_INTERRUPT
#define TIMER1_ICU_INTERRUPT  TIMER1_DISABLE_INTERRUPT

#endif
