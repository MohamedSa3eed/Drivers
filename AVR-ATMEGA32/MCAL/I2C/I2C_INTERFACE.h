#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERR_STATE.h"

//------------------------------------------Needed Macros------------------------------------------------//
//I2C Operations
#define I2C_WRITE   0 
#define I2C_READ    1 

//------------------------------------------Function Prototypes------------------------------------------//

/*
 * @breif: This function is responsible for initializing the I2C peripheral.
 *
 * @param: void
 *
 * @return: void
 */
void I2C_Init(void);

/*
 * @breif: This function is responsible for sending a start condition on the I2C bus.
 *
 * @param: void
 *
 * @return: ES_OK -> if the start condition is sent successfully. 
 */
ES_t I2C_StartCondition(void);

/*
 * @breif: This function is responsible for sending a repeated start condition on the I2C bus.
 *
 * @param: void
 *
 * @return: ES_OK -> if the repeated start condition is sent successfully. 
 */
ES_t I2C_RepeatedStartCondition(void);

/*
 * @breif: This function is responsible for sending a stop condition on the I2C bus.
 *
 * @param: void
 *
 * @return: ES_OK -> if the stop condition is sent successfully. 
 */
ES_t I2C_StopCondition(void);

/*
 * @breif: This function is responsible for sending a byte on the I2C bus.
 *
 * @param: u8 Copy_u8Data -> the byte to be sent.
 *
 * @return: ES_OK -> if the byte is sent successfully. 
 *          ES_NOK -> if the slave address is not sent successfully.
 */
ES_t I2C_MasterSendData(u8 Copy_u8Data);

/*
 * @breif: This function is responsible for receiving a byte on the I2C bus.
 *
 * @param: u8 *Copy_pu8Data -> pointer to the variable that will hold the received byte.
 *
 * @return: ES_OK -> if the byte is received successfully. 
 *          ES_NOK -> if the slave address is not sent successfully.
 *          ES_NULL_POINTER -> if the pointer is null.
 */
ES_t I2C_MasterReceiveData(u8 *Copy_pu8Data);

/*
 * @breif: This function is responsible for sending a byte on the I2C bus.
 *
 * @param: u8 Copy_u8Data -> the byte to be sent.
 *
 * @return: ES_OK -> if the byte is sent successfully. 
 *          ES_NOK -> if the slave address is not sent successfully.
 */
ES_t I2C_SlaveSendData(u8 Copy_u8Data);

/*
 * @breif: This function is responsible for receiving a byte on the I2C bus.
 *
 * @param: u8 *Copy_pu8Data -> pointer to the variable that will hold the received byte.
 *
 * @return: ES_OK -> if the byte is received successfully. 
 *          ES_NOK -> if the slave address is not sent successfully.
 *          ES_NULL_POINTER -> if the pointer is null.
 */
ES_t I2C_SlaveReceiveData(u8 *Copy_pu8Data);

/*
 * @breif: This function is responsible for sending the slave address and the operation on the I2C bus.
 *
 * @param: u8 Copy_u8Address -> the slave address to be sent.
 *         u8 Copy_u8Operation -> the operation to be sent.
 *
 * @return: ES_OK -> if the slave address is sent successfully. 
 *          ES_NOK -> if the slave address is not sent successfully.
 *          ES_OUT_OF_RANGE -> if the slave address is out of range or wrong operation is sent.
 */
ES_t I2C_SendSlaveAddress(u8 Copy_u8Address, u8 Copy_u8Operation);

/*
 * @breif: This function is responsible for checking the slave address on the I2C bus.
 *
 * @param: void
 *
 * @return: ES_OK -> if the slave address is sent successfully. 
 *          ES_NOK -> if the slave address is not sent successfully.
 */
ES_t I2C_CheckSlaveAddress(void);

/*
 * @breif: This function is responsible for setting the call back function of I2C ISR.
 *         The call back function will be called when the I2C ISR is fired.
 *
 * @param: void (*Copy_ptr)(void) -> pointer to the call back function.
 *
 * @return: ES_OK -> if the call back function is set successfully.
 *          ES_NOK -> if the call back function is not set successfully.
 *          ES_NULL_POINTER -> if the pointer is null.
 */
ES_t I2C_SetCallBack(void (*Copy_ptr)(void));

#endif // !I2C_INTERFACE_H
