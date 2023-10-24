//==============================================================================
#ifndef _USART_PORTS_COMPONENT_CONFIG_H_
#define _USART_PORTS_COMPONENT_CONFIG_H_
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif 
//==============================================================================
//includes:

#include "Components-Types.h"
#include "Peripherals/xUSART/xUSART-Types.h"
//==============================================================================
//import:

//==============================================================================
//defines:

//#define SERIAL1_ENABLE
//#define SERIAL2_ENABLE
#define SERIAL3_ENABLE
//#define SERIAL4_ENABLE
//#define SERIAL5_ENABLE
#define SERIAL6_ENABLE
//------------------------------------------------------------------------------

enum
{
#ifdef SERIAL1_ENABLE
	SERIAL1,
#endif

#ifdef SERIAL2_ENABLE
	SERIAL2,
#endif

#ifdef SERIAL3_ENABLE
	SERIAL3,
#endif

#ifdef SERIAL4_ENABLE
	SERIAL4,
#endif

#ifdef SERIAL5_ENABLE
	SERIAL5,
#endif

#ifdef SERIAL6_ENABLE
	SERIAL6,
#endif

	SERIAL_PORTS_COUNT
};
//------------------------------------------------------------------------------

#ifdef SERIAL1_ENABLE
extern DMA_HandleTypeDef hdma_usart1_rx;

#define SERIAL1_RX_CIRCLE_BUF_SIZE_MASK 0x1ff
#define SERIAL1_RX_OBJECT_BUF_SIZE 0x1ff
#define SERIAL1_TX_CIRCLE_BUF_SIZE_MASK 0x3ff
#define SERIAL1_REG USART1
#define SERIAL2_PORT_NUMBER xUSART1
#define SERIAL1_RX_DMA hdma_usart1_rx
#endif

#ifdef SERIAL2_ENABLE
extern DMA_HandleTypeDef hdma_usart2_rx;

#define SERIAL2_RX_CIRCLE_BUF_SIZE_MASK 0x1ff
#define SERIAL2_RX_OBJECT_BUF_SIZE 0x1ff
#define SERIAL2_TX_CIRCLE_BUF_SIZE_MASK 0x3ff
#define SERIAL2_REG USART2
#define SERIAL2_PORT_NUMBER xUSART2
#define SERIAL2_RX_DMA hdma_usart2_rx
#endif

#ifdef SERIAL3_ENABLE
extern DMA_HandleTypeDef hdma_usart3_rx;

#define SERIAL3_RX_CIRCLE_BUF_SIZE_MASK 0xff
#define SERIAL3_RX_OBJECT_BUF_SIZE 0x1ff
#define SERIAL3_TX_CIRCLE_BUF_SIZE_MASK 0x3ff
#define SERIAL3_REG USART3
#define SERIAL3_PORT_NUMBER xUSART3
#define SERIAL3_RX_DMA hdma_usart3_rx
#endif

#ifdef SERIAL4_ENABLE
#define SERIAL4_RX_CIRCLE_BUF_SIZE_MASK 0x1ff
#define SERIAL4_RX_OBJECT_BUF_SIZE 0x1ff
#define SERIAL4_TX_CIRCLE_BUF_SIZE_MASK 0x3ff
#define SERIAL4_REG USART4
#define SERIAL4_PORT_NUMBER xUSART4
#define SERIAL4_RX_DMA hdma_usart4_rx
#endif

#ifdef SERIAL5_ENABLE
#define SERIAL5_RX_CIRCLE_BUF_SIZE_MASK 0x1ff
#define SERIAL5_RX_OBJECT_BUF_SIZE 0x1ff
#define SERIAL5_TX_CIRCLE_BUF_SIZE_MASK 0x3ff
#define SERIAL5_REG USART5
#define SERIAL5_PORT_NUMBER xUSART5
#define SERIAL5_RX_DMA hdma_usart5_rx
#endif

#ifdef SERIAL6_ENABLE
extern DMA_HandleTypeDef hdma_usart6_rx;

#define SERIAL6_RX_CIRCLE_BUF_SIZE_MASK 0xff
#define SERIAL6_RX_OBJECT_BUF_SIZE 0x1ff
#define SERIAL6_TX_CIRCLE_BUF_SIZE_MASK 0x3ff
#define SERIAL6_REG USART6
#define SERIAL6_PORT_NUMBER xUSART6
#define SERIAL6_RX_DMA hdma_usart6_rx
#endif

#define DEBUG_SERIAL_PORT_DEFAULT_NUMBER SERIAL3
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif //_USART_PORTS_COMPONENT_CONFIG_H_