#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERR_STATE.h"

#include "I2C_INTERFACE.h"
#include "I2C_CONFIG.h"
#include "I2C_PRIVATE.h"

void I2C_Init(void)
{
#if I2C_MODE == I2C_MASTER 
 TWSR = I2C_PRESCALER; // Prescaler 
 TWBR = BIT_RATE(I2C_SPEED); // Bit Rate
 TWCR = (I2C_ADDRESS<<1) | (1<<TWEN); // Set MCU Address and the Globla Call 
 SET_BIT(TWCR, TWINT); // Clear Flag
 SET_BIT(TWCR, TWEN); // Enable I2C
#elif I2C_MODE == I2C_SLAVE
 TWCR = (I2C_ADDRESS<<1) | (1<<TWEN); // Set MCU Address and the Globla Call 
 SET_BIT(TWCR, TWINT); // Clear Flag
 SET_BIT(TWCR, TWEN); // Enable I2C
#else 
 #error "Wrong I2C Mode"
#endif 
}
