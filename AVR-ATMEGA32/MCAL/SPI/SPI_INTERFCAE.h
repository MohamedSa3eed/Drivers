#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

/**
 * @brief Initialize the SPI module with the specified configuration.
 */
void SPI_Init(void);

/**
 * @brief Transmit and receive a byte of data in Master mode.
 *
 * @param Copy_pu8Data Pointer to the data to be transmitted and to store the received data.
 * @return Error status: ES_OK if successful, ES_NOK if there is a collision error during transmission.
 */
ES_t SPI_TransmitRecieveData(u8 *Copy_pu8Data);

/**
 * @brief Set the callback function to be executed upon SPI interrupt.
 *
 * @param pfunc Pointer to the callback function.
 * @return Error status: ES_OK if successful, ES_NULL_POINTER if pfunc is NULL.
 */
ES_t SPI_SetCallBack(void (*pfunc) (void));

/**
 * @brief Enable the SPI interrupt.
 * @return Error status: ES_OK if successful.
 */
ES_t SPI_InterruptEnable(void);

/**
 * @brief Disable the SPI interrupt.
 * @return Error status: ES_OK if successful.
 */
ES_t SPI_InterruptDisable(void);

#endif // !SPI_INTERFACE_H
