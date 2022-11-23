//==============================================================================
#ifndef _COMPONENTS_H
#define _COMPONENTS_H
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif 
//==============================================================================
//includes:

#include "Components_Types.h"
#include "Components_Config.h"
//==============================================================================
//configurations:

#ifdef TERMINAL_COMPONENT_ENABLE
#include "Terminal/Terminal_Component.h"
#endif

#ifdef SERIAL_PORT_COMPONENT_ENABLE
#include "SerialPort/SerialPort_Component.h"
#endif

#ifdef TCP_SERVER_COMPONENT_ENABLE
#include "TCPServer/TCPServer_Component.h"
#endif
//==============================================================================
//functions:

xResult ComponentsInit(void* parent);
void ComponentsTimeSynchronization();
void ComponentsHandler();

void ComponentsEventListener(ComponentObjectBaseT* object, int selector, void* arg, ...);
void ComponentsRequestListener(ComponentObjectBaseT* object, int selector, void* arg, ...);
//==============================================================================
//export:


//==============================================================================
//override:

//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif

