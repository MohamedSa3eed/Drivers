#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H

//---------------------------------Rigesters Of I2C------------------------------------

// TWI Bit Rate Register 
#define TWBR    *((volatile u8 *)0x20)

// TWI Control Register
#define TWCR    *((volatile u8 *)0x56)
#define TWINT   7 // TWI Interrupt Flag 
#define TWEA    6 // TWI Enable Acknowledge Bit
#define TWSTA   5 // TWI START Condition Bit
#define TWSTO   4 // TWI STOP Condition Bit
#define TWWC    3 // TWI Write Collision Flag
#define TWEN    2 // TWI Enable Bit
#define TWIE    0 // TWI Interrupt Enable

// TWI Status Register
#define TWSR    *((volatile u8 *)0x21)
#define TWPS1   1 // TWI Prescaler Bits
#define TWPS0   0 

// TWI Data Register
#define TWDR    *((volatile u8 *)0x23)

// TWI (Slave) Address Register
#define TWAR    *((volatile u8 *)0x22) 
#define TWGCE   0 // TWI General Call Recognition Enable Bit

//---------------------------------Needed Macros---------------------------------------
#define I2C_MASTER  1
#define I2C_SLAVE   0

#define I2C_ACKNOWLEDGE_BIT_ENABLE   1
#define I2C_ACKNOWLEDGE_BIT_DISABLE  0

#define I2C_INTERRUPT_ENABLE   1
#define I2C_INTERRUPT_DISABLE  0

#define I2C_PRESCALER_1     0
#define I2C_PRESCALER_4     1
#define I2C_PRESCALER_16    2
#define I2C_PRESCALER_64    3

// the Prescaler value must be maped first 
// 0 -> 1 
// 1 -> 4 
// 2 -> 16 
// 3 -> 64 
#define BIT_RATE(I2C_SPEED)  (( (F_CPU / I2C_SPEED) - 16 ) / (2ul * ((1 << I2C_PRESCALER)<<I2C_PRESCALER) ) )

//---------------------------------Status Check---------------------------------------
#define START_CONDITION_SENT                              0x08
#define REPEATED_START_SENT                               0x10
#define SLA_W_SENT_ACK_RECEIVED                           0x18
#define SLA_W_SENT_NO_ACK_RECEIVED                        0x20
#define MASTER_DATA_SENT_ACK_RECEIVED                     0x28
#define MASTER_DATA_SENT_NO_ACK_RECEIVED                  0x30
#define MASTER_ARBITRATION_LOST                           0x38

#define SLA_R_SENT_ACK_RECEIVED                           0x40
#define SLA_R_SENT_NO_ACK_RECEIVED                        0x48
#define MASTER_DATA_RECEIVED_ACK_SENT                     0x50
#define MASTER_DATA_RECEIVED_NO_ACK_SENT                  0x58

#define SLA_W_RECEIVED_ACK_SENT                           0x60
#define SLA_W_RECEIVED_ARBITRATION_LOST_ACK_SENT          0x68
#define GENERAL_CALL_RECEIVED_ACK_SENT                    0x70
#define GENERAL_CALL_RECEIVED_ARBITRATION_LOST_ACK_SENT   0x78
#define SLAVE_DATA_RECEIVED_ACK_SENT                      0x80
#define SLAVE_DATA_RECEIVED_NO_ACK_SENT                   0x88
#define GENERAL_CALL_DATA_RECEIVED_ACK_SENT               0x90
#define GENERAL_CALL_DATA_RECEIVED_NO_ACK_SENT            0x98
#define STOP_OR_REPEATED_START_RECEIVED                   0xA0

#define SLA_R_RECEIVED_ACK_SENT                           0xA8
#define SLA_R_RECEIVED_ARBITRATION_LOST_ACK_SENT          0xB0
#define SLAVE_DATA_TRANSMITTED_ACK_RECEIVED               0xB8
#define SLAVE_DATA_TRANSMITTED_NO_ACK_RECEIVED            0xC0
#define LAST_BYTE_TRANSMITTED_ACK_RECEIVED                0xC8

//---------------------------------Functions Prototypes-------------------------------
/*
 * @breif: This function is responsible for initializing the I2C peripheral.
 *
 * @param: void
 *
 * @return: void
 */
static u8 I2C_GetStatus(void);

#endif // !I2C_PRIVATE_H
