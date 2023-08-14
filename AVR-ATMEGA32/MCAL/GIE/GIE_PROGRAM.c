#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERR_STATE.h"
#include "GIE_CONFIG.h"
#include "GIE_INTERFACE.h"
#include "GIE_PRIVATE.h"

ES_t GIE_Enable()
{
  SET_BIT(SREG, SREG_EN);
  return ES_OK;
}

ES_t GIE_Disable()
{
	 CLR_BIT(SREG, SREG_EN);
   return ES_OK;
}
