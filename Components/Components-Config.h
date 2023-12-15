//==============================================================================
#ifndef _COMPONENTS_CONFIG_H_
#define _COMPONENTS_CONFIG_H_
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif 
//==============================================================================
//includes:

#include "Registers/registers.h"
//==============================================================================
//defines:

#define FREERTOS_HEAP_SECTION __attribute__((section(".ccmram")))

#define LWIP_ENABLE 0
#define MQTT_ENABLE 0
//==============================================================================
//macros:

extern int RTOS_FreeHeapSize;
extern int RTOS_ComponentsTaskStackWaterMark;
//==============================================================================
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif //_COMPONENTS_CONFIG_H_
