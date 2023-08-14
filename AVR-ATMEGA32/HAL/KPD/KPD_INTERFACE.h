#ifndef KPD_INTERFACE_H
#define KPD_INTERFACE_H

/**
 * @brief Initializes the Keypad (KPD).
 *
 * @return Error state of the KPD initialization.
 */
ES_t KPD_Init(void);

/**
 * @brief Retrieves the pressed key from the Keypad (KPD).
 *
 * @param Copy_pu8Key Pointer to store the pressed key.
 * @return Error state of the KPD operation.
 *         - ES_OK: Operation successful.
 *         - ES_NOK: Operation failed.
 *         - ES_NULL_POINTER: Null pointer argument provided.
 */
ES_t KPD_GetPressedKey(u8 *Copy_pu8Key);

#endif
