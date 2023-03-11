/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  4  MAR 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void SPI1_voidInit(void);

void SPI1_voidSendReceiveSynchronous(u16 copy_u8DataToSend, u16 *P_u8DataToReceive);

void SPI1_voidSendReceiveAsynchronous(u16 copy_u8DataToSend, void(*P_CallBack)(u16));

#endif // !SPI_INTERFACE_H
