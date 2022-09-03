#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "GIE_CONFIG.h"
#include "GIE_INTERFACE.h"
#include "GIE_PRIVATE.h"

void GIE_Enable()
{
       SET_BIT(SREG, SREG_EN);
}

void GIE_Disable()
{
	CLR_BIT(SREG, SREG_EN);
}
