/*****************************************************************************
*
* SUREFLAP CONFIDENTIALITY & COPYRIGHT NOTICE
*
* Copyright � 2013-2021 Sureflap Limited.
* All Rights Reserved.
*
* All information contained herein is, and remains the property of Sureflap 
* Limited.
* The intellectual and technical concepts contained herein are proprietary to
* Sureflap Limited. and may be covered by U.S. / EU and other Patents, patents 
* in process, and are protected by copyright law.
* Dissemination of this information or reproduction of this material is 
* strictly forbidden unless prior written permission is obtained from Sureflap 
* Limited.
*
* Filename: ResetHandler.c   
* Author:   
* Purpose:  Miscellaneous Reset related functions
*           
**************************************************************************/

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_src.h"
#include "fsl_common.h"
#include "hermes.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "resetHandler.h"
#include "temperature.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
* Code
******************************************************************************/
// Private functions
void SRC_ClearResetStatusFlags(SRC_Type *base, uint32_t flags);
void print_reset_cause(uint32_t value);

void DisplayResetStatus(void)
{    
	uint32_t flags;
	flags = SRC_GetResetStatusFlags(SRC);    
	SRC_ClearResetStatusFlags(SRC, flags);    
	print_reset_cause(flags);   

}

void SRC_ClearResetStatusFlags(SRC_Type *base, uint32_t flags)
{
    uint32_t tmp32 = base->SRSR;

    if (0U != (SRC_SRSR_TSR_MASK & flags))
    {
        tmp32 &= ~SRC_SRSR_TSR_MASK; /* Write 0 to clear. */
    }

    if (0U != (SRC_SRSR_W1C_BITS_MASK & flags))
    {
        tmp32 |= (SRC_SRSR_W1C_BITS_MASK & flags); /* Write 1 to clear. */
    }

    base->SRSR = tmp32;
}

void print_reset_cause(uint32_t value)
{
 	uint32_t temperature;
  	uint8_t i;
	
	char *reset_reasons[] = {"Power up", \
							 "CPU Lockup", \
							 "csu", \
							 "User", \
							 "Watchdog", \
							 "JTAG", \
							 "JTAG software", \
							 "Watchdog 3", \
							 "Temperature"};

	if((SRC_SRSR_WDOG_RST_B_MASK&value)!=0)
	{
		zprintf(CRITICAL_IMPORTANCE,"Watchdog reset!\r\n");
	}

	zprintf(LOW_IMPORTANCE,"Reset cause(s): ");

	if( 0 == value)
	{
		zprintf(LOW_IMPORTANCE," None");
	}
	else
	{
		value = value << 1;
		for (i=0; i<9; i++)
		{
			value = value >> 1;		
			if (1 == (value & 1))
			{
				zprintf(LOW_IMPORTANCE,"%s ",reset_reasons[i]);
			}
		}
	}
	zprintf(LOW_IMPORTANCE,"\r\n");
	
	if (1 == (value & 1))
	{
		temperature = get_temperature();
		zprintf(LOW_IMPORTANCE,"Die temperature: %dC\r\n",temperature);
	}
}

