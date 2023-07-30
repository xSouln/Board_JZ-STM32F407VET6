//==============================================================================
#ifndef _X_USART_CONFIG_H_
#define _X_USART_CONFIG_H_
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
//includes:

#include "Registers/registers.h"
//==============================================================================
//defines:

#define USART1_ENABLE 1

//------------------------------------------------------------------------------

typedef enum
{
#if USART1_BASE && USART1_ENABLE
	xUSART1,
#endif

#if USART2_BASE && USART2_ENABLE
	xUSART2,
#endif

#if USART3_BASE && USART3_ENABLE
	xUSART3,
#endif

#if USART4_BASE && USART4_ENABLE
	xUSART4,
#endif

#if USART5_BASE && USART5_ENABLE
	xUSART5,
#endif

#if USART6_BASE && USART6_ENABLE
	xUSART6,
#endif

	xUSART_MAX_NUMBER_OF_PORTS

} xUSART_Numbers;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif //_X_USART_CONFIG_H_
