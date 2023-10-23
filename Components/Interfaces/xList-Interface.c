//==============================================================================
//includes:

#include "Common/xList.h"
//==============================================================================
//variables:


//==============================================================================
//functions:

void xListLock(xListT* list)
{
	if (list->Content)
	{
		xSemaphoreTake(list->Content, portMAX_DELAY);
	}
}
//------------------------------------------------------------------------------
void xListUnLock(xListT* list)
{
	if (list->Content)
	{
		xSemaphoreGive(list->Content);
	}
}
//==============================================================================
