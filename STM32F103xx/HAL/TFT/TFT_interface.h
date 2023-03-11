/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  7  MAR 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H

void TFT_voidInit(void);

void TFT_voidDisplayImage(const u16 *copy_u16Image);

void TFT_voidFillColor(u16 copy_u16Color);

void TFT_voidDrawRect(u8 x1, u8 x2, u8 y1, u8 y2, u16 copy_u16Color);

#endif // !TFT_INTERFACE_H
