#ifndef TIMER0_INTERFACE_H
#define TIMER0_INTERFACE_H


// timer1 initialization
/*
 * @brief: this function initializes timer1.
 *
 * @param void.
 *
 * @return void.
 */
void TIMER1_Init(void);

// timer1 set duty cycle
/*
 * @brief: this function sets the duty cycle of timer1.
 *
 * @param u16 Copy_u8DutyCycle: the duty cycle to be set.
 *
 * @return ES_t: Error Status.
 *               ES_OK: if no error occured.
 *               ES_OUT_OF_RANGE: if the duty cycle is out of range.
 *               ES_NOK: if unknown error occured.
 *
 */
ES_t TIMER1_SetDutyCycle(u16 Copy_u16DutyCycle);

// timer1 set preloaded value
/*
 * @brief: this function sets the preloaded value of timer1.
 *
 * @param u16 Copy_u16PreloadedValue: the preloaded value to be set.
 *
 * @return ES_t: Error Status.
 *               ES_OK: if no error occured.
 *               ES_OUT_OF_RANGE: if the preloaded value is out of range.
 *               ES_NOK: if unknown error occured.
 *
 */
ES_t TIMER1_SetPreloadedValue(u16 Copy_u16PreloadedValue);

// timer1 set compare value
/*
 * @brief: this function sets the compare value of timer1.
 *
 * @param u16 Copy_u16CompareValue: the compare value to be set.
 *
 * @return ES_t: Error Status.
 *               ES_OK: if no error occured.
 *               ES_OUT_OF_RANGE: if the compare value is out of range.
 *               ES_NOK: if unknown error occured.
 *
 */
ES_t TIMER1_SetCompareValueA(u16 Copy_u16CompareValue);
ES_t TIMER1_SetCompareValueB(u16 Copy_u16CompareValueB);

// timer1 set input capture value
/*
 * @brief: this function sets the input capture value of timer1.
 *
 * @param u16 Copy_u16InputCaptureValue: the input capture value to be set.
 *
 * @return ES_t: Error Status.
 *               ES_OK: if no error occured.
 *               ES_OUT_OF_RANGE: if the input capture value is out of range.
 *               ES_NOK: if unknown error occured.
 *
 */
ES_t TIMER1_SetInputCaptureValue(u16 Copy_u16InputCaptureValue);

// timer1 set overflow value
/*
 * @brief: this function sets the overflow value of timer1.
 *
 * @param u16 Copy_u16OverflowValue: the overflow value to be set.
 *
 * @return ES_t: Error Status.
 *               ES_OK: if no error occured.
 *               ES_OUT_OF_RANGE: if the overflow value is out of range.
 *               ES_NOK: if unknown error occured.
 *
 */
ES_t TIMER1_SetOverflowValue(u16 Copy_u16OverflowValue);

// set interrupt callback function for timer1 overflow interrupt
/*
 * @brief: this function sets the callback function for timer1 overflow interrupt.
 *
 * @param void (*Copy_ptr)(void): pointer to the callback function.
 *
 * @return ES_t: Error Status.
 *               ES_OK: if no error occured.
 *               ES_NUL: if the pointer is null.
 *               ES_NOK: if unknown error occured.
 *
 */
ES_t TIMER1_SetOverflowCallBack(void (*Copy_ptr)(void));

// set interrupt callback function for timer1 compare match A interrupt
/*
 * @brief: this function sets the callback function for timer1 compare match A interrupt.
 *
 * @param void (*Copy_ptr)(void): pointer to the callback function.
 *
 * @return ES_t: Error Status.
 *               ES_OK: if no error occured.
 *               ES_NUL: if the pointer is null.
 *               ES_NOK: if unknown error occured.
 *
 */
ES_t TIMER1_SetCompareMatchACallBack(void (*Copy_ptr)(void));

// set interrupt callback function for timer1 compare match B interrupt
/*
 * @brief: this function sets the callback function for timer1 compare match B interrupt.
 *
 * @param void (*Copy_ptr)(void): pointer to the callback function.
 *
 * @return ES_t: Error Status.
 *               ES_OK: if no error occured.
 *               ES_NUL: if the pointer is null.
 *               ES_NOK: if unknown error occured.
 *
 */
ES_t TIMER1_SetCompareMatchBCallBack(void (*Copy_ptr)(void));

// set interrupt callback function for timer1 input capture interrupt
/*
 * @brief: this function sets the callback function for timer1 input capture interrupt.
 *
 * @param void (*Copy_ptr)(void): pointer to the callback function.
 *
 * @return ES_t: Error Status.
 *               ES_OK: if no error occured.
 *               ES_NUL: if the pointer is null.
 *               ES_NOK: if unknown error occured.
 *
 */
ES_t TIMER1_SetInputCaptureCallBack(void (*Copy_ptr)(void));

// timer1 start
/*
 * @brief: this function starts timer1.
 *
 * @param void.
 *
 * @return void.
 */
void TIMER1_Start(void);

// timer1 stop
/*
 * @brief: this function stops timer1.
 *
 * @param void.
 *
 * @return void.
 */
void TIMER1_Stop(void);

// timer1 set ovf interrupt enable
/*
 * @brief: this function enables timer1 overflow interrupt.
 *
 * @param void.
 *
 * @return void.
 *
 */
void TIMER1_EnableOVFInterrupt(void);
void TIMER1_EnableCTCAInterrupt(void);
void TIMER1_EnableCTCBInterrupt(void);
void TIMER1_EnableICUInterrupt(void);

// timer1 set interrupt disable
/*
 * @brief: this function disables timer1 overflow interrupt.
 *
 * @param void.
 *
 * @return void.
 *
 */
void TIMER1_DisableOVFInterrupt(void);
void TIMER1_DisableCTCAInterrupt(void);
void TIMER1_DisableCTCBInterrupt(void);
void TIMER1_DisableICUInterrupt(void);

#endif
