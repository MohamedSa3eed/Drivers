#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

/**
 * @file ADC_Interface.h
 * @brief This is an interface file for the ADC (Analog-to-Digital Converter) module.
 */

/**
 * @defgroup ADC_channels ADC Channels
 * @{
 */
#define ADC_CH0                  0x00 /**< ADC channel 0 */
#define ADC_CH1                  0x01 /**< ADC channel 1 */
#define ADC_CH2                  0x02 /**< ADC channel 2 */
#define ADC_CH3                  0x03 /**< ADC channel 3 */
#define ADC_CH4                  0x04 /**< ADC channel 4 */
#define ADC_CH5                  0x05 /**< ADC channel 5 */
#define ADC_CH6                  0x06 /**< ADC channel 6 */
#define ADC_CH7                  0x07 /**< ADC channel 7 */
/** @} */

/**
 * @defgroup ADC_reference ADC Reference Voltages
 * @{
 */
#define ADC_AREF                 0 /**< External reference voltage (AREF) */
#define ADC_AVCC                 1 /**< AVCC reference voltage */
#define ADC_INTERNAL             2 /**< Internal reference voltage */
/** @} */

/**
 * @defgroup ADC_prescaler ADC Prescaler
 * @{
 */
#define ADC_PRESCALER_2          1  /**< ADC clock divided by 2 */
#define ADC_PRESCALER_4          2  /**< ADC clock divided by 4 */
#define ADC_PRESCALER_8          3  /**< ADC clock divided by 8 */
#define ADC_PRESCALER_16         4  /**< ADC clock divided by 16 */
#define ADC_PRESCALER_32         5  /**< ADC clock divided by 32 */
#define ADC_PRESCALER_64         6  /**< ADC clock divided by 64 */
#define ADC_PRESCALER_128        7  /**< ADC clock divided by 128 */
/** @} */

/**
 * @defgroup ADC_trigger ADC Trigger Sources
 * @{
 */
#define ADC_FREE_RUNNING         1  /**< Free running mode */
#define ADC_ANALOG_CMP           2  /**< Analog Comparator */
#define ADC_EXT_INT0             3  /**< External Interrupt 0 */
#define ADC_TMR0_CMP_MATCH       4  /**< Timer/Counter0 Compare Match */
#define ADC_TMR0_OVF             5  /**< Timer/Counter0 Overflow */
#define ADC_TMR1_CMP_MATCH_B     6  /**< Timer/Counter1 Compare Match B */
#define ADC_TMR1_OVF             7  /**< Timer/Counter1 Overflow */
#define ADC_TMR1_CAPTURE_EVENT   8  /**< Timer/Counter1 Capture Event */
/** @} */

/**
 * @defgroup ADC_trigger ADC Trigger Sources
 * @{
 */
#define ADC_ADJUST_LEFT          1  /**< Adjust result to left */ 
#define ADC_ADJUST_RIGHT         2  /**< Adjust result to right */ 
/** @} */

/**
 * @brief Initializes the ADC module with the specified prescaler and reference voltage.
 *
 * This function initializes the ADC module with the given prescaler and reference voltage.
 * It configures the ADC clock frequency and reference voltage source.
 *
 * @param Copy_u8Prescaler The prescaler value. Use one of the ADC_PRESCALER_X constants.
 * @param Copy_u8Vref The reference voltage. Use one of the ADC_AREF, ADC_AVCC, or ADC_INTERNAL constants.
 * @param Copy_u8AdjustResult The Adjust result. Use one of ADC_ADJUST_LEFT, ADC_ADJUST_RIGHT constants.
 * @return Error status. Possible values: ES_OK (0) for success, ES_OUT_OF_RANGE (1) for invalid parameter values.
 */
ES_t ADC_init(u8 Copy_u8Prescaler, u8 Copy_u8Vref, u8 Copy_u8AdjustResult);

/**
 * @brief Enables the ADC module.
 *
 * This function enables the ADC module.
 *
 * @return Error status. Possible values: ES_OK (0) for success.
 */
ES_t ADC_Enable(void);

/**
 * @brief This function selects the ADC channel.
 *
 *the function clears the MUX[4..0] bits in the ADMUX register and then sets them to the desired channel number.
 *
 * @param Copy_u8Channel The ADC channel to set. Use one of the ADC_CHX constants.
 * @return Error status. Possible values: ES_OK (0) for success, ES_OUT_OF_RANGE (1) for invalid parameter values.
 */
ES_t ADC_SelectChannel(u8 Copy_u8Channel);

/**
 * @brief Enables the ADC conversion complete interrupt.
 *
 * This function enables the ADC conversion complete interrupt to trigger an interrupt
 * when an ADC conversion is complete.
 *
 * @return Error status. Possible values: ES_OK (0) for success.
 */
ES_t ADC_InterruptEnable(void);

/**
 * @brief Disables the ADC conversion complete interrupt.
 *
 * This function disables the ADC conversion complete interrupt.
 *
 * @return Error status. Possible values: ES_OK (0) for success.
 */
ES_t ADC_InterruptDisable(void);

/**
 * @brief Sets the callback function to be called when an ADC conversion is complete.
 *
 * This function sets the callback function that will be called when an ADC conversion is complete.
 * The callback function should have a void return type and no parameters.
 *
 * @param func Pointer to the callback function.
 * @return Error status. Possible values: ES_OK (0) for success, ES_NULL_POINTER (2) if the function pointer is NULL.
 */
ES_t ADC_SetCallBack(void (*func) (void));

/**
 * @brief Starts a single ADC conversion.
 *
 * This function starts a single ADC conversion.
 *
 * @return Error status. Possible values: ES_OK (0) for success.
 */
ES_t ADC_StartConversion(void);

/**
 * @brief Gets the result of the last ADC conversion.
 *
 * This function retrieves the result of the last ADC conversion and stores it in the provided pointer.
 *
 * @param Copy_pu16Result Pointer to store the ADC result.
 * @return Error status. Possible values: ES_OK (0) for success, ES_NULL_POINTER (2) if the result pointer is NULL.
 */
ES_t ADC_GetResult(u16 *Copy_pu16Result);

/**
 * @brief Gets the result of the last ADC conversion by polling the conversion complete flag.
 *
 * This function polls the conversion complete flag and retrieves the result of the last ADC conversion.
 *
 * @param Copy_pu16Result Pointer to store the ADC result.
 * @return Error status. Possible values: ES_OK (0) for success, ES_NULL_POINTER (2) if the result pointer is NULL.
 */
ES_t ADC_GetResultPolling(u16 *Copy_pu16Result);

/**
 * @brief Gets the result of the last ADC conversion.
 *
 * This function retrieves the result of the last ADC conversion and stores it in the provided pointer.
 *
 * @param Copy_pu8Result Pointer to store the ADC result.
 * @return Error status. Possible values: ES_OK (0) for success, ES_NULL_POINTER (2) if the result pointer is NULL.
 */
ES_t ADC_GetHighResult(u8 *Copy_pu8Result);

/**
 * @brief Gets the result of the last ADC conversion by polling the conversion complete flag.
 *
 * This function polls the conversion complete flag and retrieves the result of the last ADC conversion.
 *
 * @param Copy_pu8Result Pointer to store the ADC result.
 * @return Error status. Possible values: ES_OK (0) for success, ES_NULL_POINTER (2) if the result pointer is NULL.
 */
ES_t ADC_GetHighResultPolling(u8 *Copy_pu8Result);

/**
 * @brief Sets the auto-trigger source for ADC conversion.
 *
 * This function sets the auto-trigger source for ADC conversion.
 *
 * @param Copy_u8Trigger The auto-trigger source. Use one of the ADC_TRIGGER_X constants.
 * @return Error status. Possible values: ES_OK (0) for success, ES_OUT_OF_RANGE (1) for an invalid trigger source.
 */
ES_t ADC_SetAutoTrigger(u8 Copy_u8Trigger);

/**
 * @brief Disables the auto-trigger feature for ADC conversion.
 *
 * This function disables the auto-trigger feature for ADC conversion.
 *
 * @return Error status. Possible values: ES_OK (0) for success.
 */
ES_t ADC_DisableAutoTrigger(void);

/**
 * @brief Terminates the ADC module.
 *
 * This function terminates the ADC module and performs any necessary cleanup.
 *
 * @return Error status. Possible values: ES_OK (0) for success.
 */
ES_t ADC_terminate(void);

#endif // !ADC_INTERFACE_H
