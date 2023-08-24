#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

// SPI Control Register
#define SPCR       *((volatile u8 *)0x2D)
#define SPCR_SPIE  7     // SPI Interrupt Enable 
#define SPCR_SPE   6     // SPI Enable
#define SPCR_DORD  5     // Data Order
#define SPCR_MSTR  4     // Master/Slave Select
#define SPCR_CPOL  3     // Clock Polarity
#define SPCR_CPHA  2     // Clock Phase
// SPI Clock Rate Select 1 and 0
#define SPCR_SPR1  1 
#define SPCR_SPR0  0 

// SPI Status Register
#define SPSR       *((volatile u8 *)0x2E)
#define SPSR_SPIF  7     // SPI Interrupt Flag
#define SPSR_WCOL  6     // Write COLlision Flag
#define SPSR_SPI2X 0     // Double SPI Speed Bit

// SPI Data Register
#define SPDR       *((volatile u8 *)0x2F)

#define DDR_SPI    *((volatile u8*)0x37)
#define MISO       6
#define MOSI       5
#define SS         4
#define SCK        7

// options for SPI_MODE
#define SPI_MASTER 0
#define SPI_SLAVE  1

// options for SPI_DATA_ORDER
#define  SPI_MSB   0
#define  SPI_LSB   1

// options for SPI_CLK_POLARITY
#define  SPI_LEADING_EDGE_RISING  0
#define  SPI_LEADING_EDGE_FALLING 1

// options for SPI_CLK_PHASE
#define  SPI_LEADING_EDGE_SAMPLE 0
#define  SPI_LEADING_EDGE_SETUP 1

// options for SPI_PRESCALER
#define  SPI_PRESCALER_2    0
#define  SPI_PRESCALER_4    1
#define  SPI_PRESCALER_8    2
#define  SPI_PRESCALER_16   3
#define  SPI_PRESCALER_32   4
#define  SPI_PRESCALER_64   5
#define  SPI_PRESCALER_128  6

// options for SPI_INTERRUPT
#define  SPI_ENABLED  0
#define  SPI_DISABLED 1

#endif // !SPI_PRIVATE_H
