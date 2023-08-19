/**
 * @file TIMER0_INTERFACE.h
 * @brief This file contains function declarations and documentation for Timer 0 driver.
 */

#ifndef TIMER0_INTERFACE_H
#define TIMER0_INTERFACE_H


/**
 * @brief Initializes Timer 0 based on the specified configuration settings.
 */
void TIMER0_Init(void);

/**
 * @brief Sets the preload value for Timer 0 counter.
 *
 * @param Copy_u8Preload: Preload value to set.
 *
 * @return Error status:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 *         - ES_NULL_POINTER: Null pointer provided.
 */
ES_t TIMER0_SetPreload(u8 Copy_u8Preload);

/**
 * @brief Sets the duty cycle value for PWM mode.
 * 
 * @param Copy_u8DutyCycleValue: Duty cycle value to set.
 *
 * @return Error status:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 *         - ES_NULL_POINTER: Null pointer provided.
 */
ES_t TIMER0_SetDuty(u8 Copy_u8DutyCycleValue);

/**
 * @brief Enables overflow interrupt for Timer 0.
 *
 * @return Error status:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 */
ES_t TIMER0_OvfInterruptEnable(void);

/**
 * @brief Disables overflow interrupt for Timer 0.
 * 
 * @return Error status:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 */
ES_t TIMER0_OvfInterruptDisable(void);

/**
 * @brief Enables compare match interrupt for Timer 0.
 *
 * @return Error status:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 */
ES_t TIMER0_CtcInterruptEnable(void);

/**
 * @brief Disables compare match interrupt for Timer 0.
 *
 * @return Error status:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 */
ES_t TIMER0_CtcInterruptDisable(void);

/**
 * @brief Sets the overflow interrupt callback function for Timer 0.
 *
 * @param pfunc: Function pointer to the callback function.
 *
 * @return Error status:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 *         - ES_NULL_POINTER: Null pointer provided.
 */
ES_t TIMER0_SetOvfINTCallBack(void (*pfunc)(void));

/**
 * @brief Sets the compare match interrupt callback function for Timer 0.
 *
 * @param pfunc: Function pointer to the callback function.
 *
 * @return Error status:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 *         - ES_NULL_POINTER: Null pointer provided.
 */
ES_t TIMER0_SetCtcINTCallBack(void (*pfunc)(void));

/**
 * @brief Provides a busy-wait function to wait for a specified time in milliseconds.
 *
 * @param Copy_u32Time: Time to wait in milliseconds.
 * 
 * @return Error status:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 *         - ES_NULL_POINTER: Null pointer provided.
 */
ES_t TIMER0_BusyWaitms(u32 Copy_u32Time);

/**
 * @brief Provides a busy-wait function to wait for a specified time in microseconds.
 *
 * @param Copy_u32Time: Time to wait in microseconds.
 *
 * @return Error status:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 *         - ES_NULL_POINTER: Null pointer provided.
 */
ES_t TIMER0_BusyWaitus(u32 Copy_u32Time);

/**
 * @brief Configures Timer 0 for asynchronous function execution in periodic mode.
 *
 * @param Copy_u32Time: Time interval for periodic execution.
 * @param Pfunc: Function pointer to the callback function.
 *
 * @return Error status:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 *         - ES_NULL_POINTER: Null pointer provided.
 */
ES_t TIMER0_SetAsyncFunctionPeriodic(u32 Copy_u32Time, void (*Pfunc)(void));

/**
 * @brief Configures Timer 0 for asynchronous function execution in single mode.
 *
 * @param Copy_u32Time: Time interval for single execution.
 * @param Pfunc: Function pointer to the callback function.
 *
 * @return Error status:
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 *         - ES_NULL_POINTER: Null pointer provided.
 */
ES_t TIMER0_SetAsyncFunctionSingle(u32 Copy_u32Time, void (*Pfunc)(void));

/**
 * @brief Halts Timer 0.
 */
void TIMER0_Stop(void);

#endif
