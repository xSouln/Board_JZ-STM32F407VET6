//==============================================================================
//includes:

#include "LocalDevice-Component.h"
#include "Components.h"

#include "Abstractions/xDevice/Communication/xDeviceControl-RxTransactions.h"
#include "Services/Temperature/Adapters/TemperatureService-Adapter.h"
#include "Adapters/LocalDevice-Adapter.h"
//==============================================================================
//defines:

#define TASK_STACK_SIZE 0x300

#define LOCAL_DEVICE_ID 598745
#define TEMPERATURE_SERVICE1_ID 32545
#define TEMPERATURE_SERVICE2_ID 32546
//==============================================================================
//import:


//==============================================================================
//variables:

static TaskHandle_t taskHandle;
static StaticTask_t taskBuffer;
static StackType_t taskStack[TASK_STACK_SIZE];

TemperatureServiceT TemperatureService1;
TemperatureServiceT TemperatureService2;

xDeviceT LocalDevice;
//==============================================================================
//functions:

static void privateServiceEventListener(xServiceT* service, xServiceAdapterEventSelector selector, void* arg)
{
	switch ((int)selector)
	{
		default: break;
	}
}
//------------------------------------------------------------------------------
static void privateDeviceEventListener(xDeviceT* object, xDeviceEventSelector selector, void* arg)
{
	switch ((int)selector)
	{
		default: break;
	}
}
//------------------------------------------------------------------------------
static void privateTask(void* arg)
{
	vTaskDelay(pdMS_TO_TICKS(1000));

	while (true)
	{
		xDeviceHandler(&LocalDevice);

		vTaskDelay(pdMS_TO_TICKS(1));
	}
}
//------------------------------------------------------------------------------
void LocalDeviceComponentHandler()
{

}
//------------------------------------------------------------------------------
void LocalDeviceComponentTimeSynchronization()
{

}
//==============================================================================
//initializations:

static LocalDeviceAdapterT privateLocalDeviceAdapter;

static TemperatureServiceAdapterT privateTemperatureServiceAdapter1;
static TemperatureServiceAdapterT privateTemperatureServiceAdapter2;
//------------------------------------------------------------------------------
static xTerminalObjectT privateTerminalObject =
{
	.Requests = xDeviceControlRxRequests,
	.Object = (void*)&LocalDevice
};
//==============================================================================
//initialization:

xResult LocalDeviceComponentInit(void* parent)
{
	TemperatureServiceAdapterInitT temperatureServiceAdapterInit;
	TemperatureServiceAdapterInit(&TemperatureService1, &privateTemperatureServiceAdapter1, &temperatureServiceAdapterInit);
	TemperatureServiceAdapterInit(&TemperatureService2, &privateTemperatureServiceAdapter2, &temperatureServiceAdapterInit);

	TemperatureServiceInitT temperatureServiceInit;
	temperatureServiceInit.Base.EventListener = (void*)privateServiceEventListener;

	temperatureServiceInit.Base.Id = TEMPERATURE_SERVICE1_ID;
	TemperatureServiceInit(&TemperatureService1, &temperatureServiceInit);

	temperatureServiceInit.Base.Id = TEMPERATURE_SERVICE2_ID;
	TemperatureServiceInit(&TemperatureService2, &temperatureServiceInit);

	LocalDeviceAdapterInitT deviceAdapterInit;
	LocalDeviceAdapterInit(&LocalDevice, &privateLocalDeviceAdapter, &deviceAdapterInit);

	xDeviceInitT deviceInit = { 0 };
	deviceInit.Parent = parent;
	deviceInit.Id = LOCAL_DEVICE_ID;
	deviceInit.EventListener = (void*)privateDeviceEventListener;
	xDeviceInit(&LocalDevice, &deviceInit);

	xDeviceAddService(&LocalDevice, (xServiceT*)&TemperatureService1);
	xDeviceAddService(&LocalDevice, (xServiceT*)&TemperatureService2);

	TerminalAddObject(&privateTerminalObject);

	taskHandle =
				xTaskCreateStatic(privateTask, // Function that implements the task.
									"device control task", // Text name for the task.
									TASK_STACK_SIZE, // Number of indexes in the xStack array.
									NULL, // Parameter passed into the task.
									osPriorityNormal, // Priority at which the task is created.
									taskStack, // Array to use as the task's stack.
									&taskBuffer);

	return xResultAccept;
}
//==============================================================================
