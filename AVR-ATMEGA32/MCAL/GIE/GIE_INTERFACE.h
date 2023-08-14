#ifndef GIE_INTERFACE_H 
#define GIE_INTERFACE_H

/**
 * @brief Enables the global interrupt enable.
 *
 * This function enables the global interrupt enable (GIE) flag, allowing interrupts to occur.
 *
 * @return Error state of the global interrupt enable operation.
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 */
ES_t GIE_Enable(void);

/**
 * @brief Disables the global interrupt enable.
 *
 * This function disables the global interrupt enable (GIE) flag, preventing interrupts from occurring.
 *
 * @return Error state of the global interrupt disable operation.
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 */
ES_t GIE_Disable(void);

#endif 
