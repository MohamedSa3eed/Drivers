/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  1  MAR 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H

                         //*      this function initialize the channel direction  and sets the addresses of source and destination      
void DMA_voidSetChannelDirection(u8 copy_u8ChannelID, u8 copy_u8Direction, u32 copy_Pu32PAddress , u32 copy_Pu32MAddress);

                         //*      this function initialize the transfer size as well as the size of source and destination       
void DMA_voidSetTransferSize(u8 copy_u8ChannelID, u16 copy_u16NumOfDataRegister, u8 copy_u8PSize, u8 copy_u8MSize);

                         //*      this function starts the data transfer for a specific channel       
void DMA_voidStartTransfer(u8 copy_u8ChannelID);

                         //*      this function stops the data transfer for a specific channel       
void DMA_voidStopTransfer(u8 copy_u8ChannelID);

                         //*      thsi function sets the priority mode , circular mode peripheral increment and memory increment for a specific channel
void DMA_voidSetChannelConfig(u8 copy_u8ChannelID, u8 copy_u8PriorityMode,u8 copy_u8CircularMode, u8 copy_u8PINC, u8 copy_u8MINC);

                         //*      this function enables the DMA interrupt 
void DMA_voidEnableInterrupt(u8 copy_u8ChannelID, u8 copy_u8INT);

                         //*      this function disables the DMA interrupt 
void DMA_voidDisableInterrupt(u8 copy_u8ChannelID, u8 copy_u8INT);

                         //* this function sets the callback function for a specific channel 
void DMA_voidSetCallBack(u8 copy_u8ChannelID, void (*copy_Pvoidfunc)(void));

   //* define channels ID
#define  DMA_CHANNEL1    0 
#define  DMA_CHANNEL2    1 
#define  DMA_CHANNEL3    2 
#define  DMA_CHANNEL4    3 
#define  DMA_CHANNEL5    4 
#define  DMA_CHANNEL6    5 
#define  DMA_CHANNEL7    6 

  //*  define direction  
#define  DMA_MEM2MEM     0 
#define  DMA_P2MEM       1 
#define  DMA_MEM2P       2 

  //*  define size 
#define  DMA_BYTE        0 
#define  DMA_WORD        1 
#define  DMA_DOUBLE_WORD 2 

  //*  define circularity
#define  DMA_CIRCULAR_DISABLED 0 
#define  DMA_CIRCULAR_ENABLED  1 

  //*  define increment 
#define  DMA_INC_DISABLE 0
#define  DMA_INC_ENABLE  1 

  //*  define priority 
#define  DMA_VERY_HIGH   0 
#define  DMA_HIGH        1 
#define  DMA_MEDIUM      2 
#define  DMA_LOW         3 

  //*  define interrupts 
#define  DMA_TEI         0
#define  DMA_HTI         1 
#define  DMA_TCI         2 

#endif // !DMA_INTERFACE_H
