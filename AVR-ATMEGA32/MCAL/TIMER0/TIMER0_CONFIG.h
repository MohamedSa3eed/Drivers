#ifndef TIMER0_CONFIG_H
#define TIMER0_CONFIG_H

// the cpu clock in KHZ
#define CPU_CLK      8000ul       

/*  options for the Timer 0 mode 
 *  1- TIMER_NORMAL
 *  2- TIMER_CTC
 *  3- TIMER_PWM_PHASE_CORRECT
 *  4- TIMER_FAST_PWM
 */
#define TIMER0_MODE TIMER_NORMAL 

/* options for TIMER0 CLOCK 
 * 1- TIMER_NO_CLK
 * 2- TIMER_SYS_CLK
 * 3- TIMER_CLK_8
 * 4- TIMER_CLK_64
 * 5- TIMER_CLK_256
 * 6- TIMER_CLK_1024
 * 7- TIMER_EXT_PIN_FALLING_EDGE
 * 8- TIMER_EXT_PIN_RISING_EDGE 
 */
#define TIMER0_CLK TIMER_CLK_8

/*  options to TIMER INTERUPT 
 *  1- ENABLED
 *  2- DISABLED
 */ 
#define TIMER0_OCI   DISABLED
#define TIMER0_OFI   DISABLED

/* options for OC0 pin 
 * 1- DISCONECTED
 * 2- TOGGLE_ON_CTC             (CTC)
 * 3- CLEAR_ON_CTC              (CTC)
 * 4- SET_ON_CTC                (CTC)
 * 5- CLEAR_AT_COUNTING_UP      (PWM)
 * 6- SET_AT_COUNTING_UP        (PWM)
 */
#define TIMER0_OC0_PIN_MODE DISCONECTED

#endif
