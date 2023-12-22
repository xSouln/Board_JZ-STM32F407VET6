//==============================================================================
//header:

#ifndef _REQUEST_CONTROL_COMPONENT_CONFIG_H_
#define _REQUEST_CONTROL_COMPONENT_CONFIG_H_
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
//includes:

#include "Components-Types.h"
//==============================================================================
//macros:


//==============================================================================
//import:


//==============================================================================
//defines:

#define REQUEST_CONTROL_BUFFER_MEM_SECTION __attribute__((section("._user_heap_stack")))
#define REQUEST_CONTROL_BUFFER_SIZE 10
#define REQUEST_CONTROL_PORT CAN_Port2
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif //_REQUEST_CONTROL_COMPONENT_CONFIG_H_
