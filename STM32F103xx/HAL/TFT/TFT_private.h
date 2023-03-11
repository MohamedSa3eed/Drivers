/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  7  MAR 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef TFT_PRIVATE_H
#define TFT_PRIVATE_H

static void TFT_voidSendCommand(u16 copy_u16Command);

static void TFT_voidSendData(u16 copy_u16Data);

static void TFT_voidDisplayInit(u8 x1, u8 x2, u8 y1, u8 y2);

#endif // !TFT_PRIVATE_H
