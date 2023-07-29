//==============================================================================
//includes:

#include "Components.h"
//==============================================================================
//defines:

//==============================================================================
//variables:

int FreeRTOS_MallocErrorCount = 0;
//==============================================================================
//functions:

void FreeRTOS_MallocTracer(void* mem, int size)
{
	if (mem == NULL)
	{
		FreeRTOS_MallocErrorCount++;
	}
}
//==============================================================================
