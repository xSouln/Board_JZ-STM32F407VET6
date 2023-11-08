//==============================================================================
//header:

#ifndef _CAN_LOCAL_COMPONENT_H_
#define _CAN_LOCAL_COMPONENT_H_
//==============================================================================
#ifdef __cplusplus
extern "C" {
#endif
//==============================================================================
//includes:

#include "Peripherals/CAN/xCAN.h"
#include "CAN_Local-ComponentConfig.h"
//==============================================================================
//defines:


//==============================================================================
//macros:


//==============================================================================
//functions:

xResult CAN_LocalComponentInit(void* parent);

void CAN_LocalComponentHandler();
void CAN_LocalComponentTimeSynchronization();
//==============================================================================
//import:


//==============================================================================
//export:

extern xPortT CAN_LocalPorts[CAN_LOCAL_PORTS_COUNT];

#ifdef CAN_LOCAL1_ENABLE
#define CAN_Local1 CAN_LocalPorts[CAN_LOCAL1]
#endif

#ifdef CAN_LOCAL2_ENABLE
#define CAN_Local2 CAN_LocalPorts[CAN_LOCAL2]
#endif

#define CAN_LocalPort CAN_Local1
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif //_CAN_LOCAL_COMPONENT_H_
