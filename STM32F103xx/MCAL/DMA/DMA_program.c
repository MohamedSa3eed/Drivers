/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  1  MAR 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "DMA_interface.h"
#include "DMA_config.h"
#include "DMA_private.h"

static void (*DMA_static_global_ptr[CHANNELS_NUM])(void) = {NULL} ;

                         //*      this function initialize the channel direction  and sets the addresses of source and destination      
void DMA_voidSetChannelDirection(u8 copy_u8ChannelID, u8 copy_u8Direction, u32 copy_Pu32PAddress , u32 copy_Pu32MAddress)
{
  if (copy_u8Direction == DMA_MEM2MEM ) 
  {
    SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 14);
    CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 4);
  }
  else if (copy_u8Direction == DMA_MEM2P) 
  {
    CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 14);
    SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 4);
  }
  else if (copy_u8Direction == DMA_P2MEM) 
  {
    CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 14);
    CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 4);
  }
  else 
  {
    // TODO err handle 
  }
  DMA->CHANNEL[copy_u8ChannelID].CPAR = copy_Pu32PAddress ; 
  DMA->CHANNEL[copy_u8ChannelID].CMAR = copy_Pu32MAddress ; 

}

                         //*      this function initialize the transfer size as well as the size of source and destination       
void DMA_voidSetTransferSize(u8 copy_u8ChannelID, u16 copy_u16NumOfDataRegister, u8 copy_u8PSize, u8 copy_u8MSize)
{
  DMA->CHANNEL[copy_u8ChannelID].CNDTR = copy_u16NumOfDataRegister ; 
  switch (copy_u8PSize) 
  {
    case DMA_BYTE :
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 10);
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 11);
      break;
    case DMA_WORD :
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 10);
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 11);
      break;
    case DMA_DOUBLE_WORD :
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 10);
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 11);
      break;
    default       :  //TODO err handle 
      break ;
  }
  switch (copy_u8MSize) 
  {
    case DMA_BYTE :
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 8);
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 9);
      break;
    case DMA_WORD :
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 8);
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 9);
      break;
    case DMA_DOUBLE_WORD :
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 8);
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 9);
      break;
    default       :  //TODO err handle 
      break ;
  }
}

                         //*      this function starts the data transfer for a specific channel       
void DMA_voidStartTransfer(u8 copy_u8ChannelID)
{
  SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 0);
}

                         //*      this function stops the data transfer for a specific channel       
void DMA_voidStopTransfer(u8 copy_u8ChannelID)
{
  CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 0);
}

                         //*      thsi function sets the priority mode , circular mode peripheral increment and memory increment for a specific channel
void DMA_voidSetChannelConfig(u8 copy_u8ChannelID, u8 copy_u8PriorityMode,u8 copy_u8CircularMode, u8 copy_u8PINC, u8 copy_u8MINC)
{
  switch (copy_u8PriorityMode)
  {
    case DMA_VERY_HIGH :
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 12);
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 13);
      break;
    case DMA_HIGH :
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 12);
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 13);
      break;
    case DMA_MEDIUM :
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 12);
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 13);
      break;
    case DMA_LOW :
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 12);
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 13);
      break;
    default : //TODO 
      break;
  }
  switch (copy_u8CircularMode)
  {
    case DMA_CIRCULAR_ENABLED :
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 5);
      break;
    case DMA_CIRCULAR_DISABLED :
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 5);
      break;
    default : //TODO 
      break;
  }
  switch (copy_u8PINC)
  {
    case DMA_INC_ENABLE :
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 6);
      break;
    case DMA_INC_DISABLE :
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 6);
      break;
      default : //TODO 
      break;
  }
  switch (copy_u8MINC)
  {
    case DMA_INC_ENABLE :
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 7);
      break;
    case DMA_INC_DISABLE :
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 7);
      break;
      default : //TODO 
      break;
  }
}

                         //*      this function enables the DMA interrupt 
void DMA_voidEnableInterrupt(u8 copy_u8ChannelID, u8 copy_u8INT)
{
  switch (copy_u8INT)
  {
    case DMA_TCI : 
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 1); break;
    case DMA_HTI :
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 2); break;
    case DMA_TEI : 
      SET_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 3); break;
    default: //TODO err handle
      break; 
  }
}

                         //*      this function disables the DMA interrupt 
void DMA_voidDisableInterrupt(u8 copy_u8ChannelID, u8 copy_u8INT)
{
  switch (copy_u8INT)
  {
    case DMA_TCI : 
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 1); break;
    case DMA_HTI :
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 2); break;
    case DMA_TEI : 
      CLR_BIT(DMA->CHANNEL[copy_u8ChannelID].CCR, 3); break;
    default:
      break; 
  }
}

                         //* this function sets the callback function for a specific channel 
void DMA_voidSetCallBack(u8 copy_u8ChannelID, void (*copy_Pvoidfunc)(void))
{
  DMA_static_global_ptr[copy_u8ChannelID] = copy_Pvoidfunc ;
}

                         //* static function to clear the interrupt flags for a certain channel 
static void DMA_CLRINTFlags(u8 copy_u8ChannelID)
{
  // the IFCR has 4 continous bits for the interrupt flags 
  // to clear the flag write 1 on its bit  and zero has no effect 

  DMA->IFCR  = (0x0000000f << copy_u8ChannelID *4) ; 

  /*u8 local_flagBit = (copy_u8ChannelID * 4) ;*/
  /*SET_BIT(DMA->IFCR, local_flagBit);*/
  /*SET_BIT(DMA->IFCR, ++local_flagBit);*/
  /*SET_BIT(DMA->IFCR, ++local_flagBit);*/
  /*SET_BIT(DMA->IFCR, ++local_flagBit);*/
}

void DMA1_Channel1_IRQHandler(void) {if(DMA_static_global_ptr[DMA_CHANNEL1] != NULL) DMA_static_global_ptr[DMA_CHANNEL1](); DMA_CLRINTFlags(DMA_CHANNEL1);}
void DMA1_Channel2_IRQHandler(void) {if(DMA_static_global_ptr[DMA_CHANNEL2] != NULL) DMA_static_global_ptr[DMA_CHANNEL2](); DMA_CLRINTFlags(DMA_CHANNEL2);}
void DMA1_Channel3_IRQHandler(void) {if(DMA_static_global_ptr[DMA_CHANNEL3] != NULL) DMA_static_global_ptr[DMA_CHANNEL3](); DMA_CLRINTFlags(DMA_CHANNEL3);}
void DMA1_Channel4_IRQHandler(void) {if(DMA_static_global_ptr[DMA_CHANNEL4] != NULL) DMA_static_global_ptr[DMA_CHANNEL4](); DMA_CLRINTFlags(DMA_CHANNEL4);}
void DMA1_Channel5_IRQHandler(void) {if(DMA_static_global_ptr[DMA_CHANNEL5] != NULL) DMA_static_global_ptr[DMA_CHANNEL5](); DMA_CLRINTFlags(DMA_CHANNEL5);}
void DMA1_Channel6_IRQHandler(void) {if(DMA_static_global_ptr[DMA_CHANNEL6] != NULL) DMA_static_global_ptr[DMA_CHANNEL6](); DMA_CLRINTFlags(DMA_CHANNEL6);}
void DMA1_Channel7_IRQHandler(void) {if(DMA_static_global_ptr[DMA_CHANNEL7] != NULL) DMA_static_global_ptr[DMA_CHANNEL7](); DMA_CLRINTFlags(DMA_CHANNEL7);}
