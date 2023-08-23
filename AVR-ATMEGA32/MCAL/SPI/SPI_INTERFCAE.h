#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void SPI_Init(void);

ES_t SPI_TransmitRecieveData(u8 *Copy_pu8Data);

ES_t SPI_SetCasllBack(void (*pfunc) (void));

ES_t SPI_InterruptEnable(void);

ES_t SPI_InterruptDisable(void);

#endif // !SPI_INTERFACE_H
