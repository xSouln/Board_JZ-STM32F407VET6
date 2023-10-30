//==============================================================================
//includes:

#include "TemperatureService.h"
//==============================================================================
//defines:

#define UID xSERVICE_UID
//==============================================================================
//variables:

static const ObjectDescriptionT privateObjectDescription =
{
	.Key = OBJECT_DESCRIPTION_KEY,
	.ObjectId = UID,
	.Type = nameof(TemperatureServiceT)
};
//==============================================================================
//functions:

static void privateHandler(TemperatureServiceT* service)
{
	service->Adapter.Interface->Handler((void*)service);
}
//------------------------------------------------------------------------------
static xResult privateRequestListener(TemperatureServiceT* service, xServiceAdapterRequestSelector selector, void* arg)
{
	if ((int)selector > xServiceBaseRequestOffset && service->Base.Info.Type != xServiceTypeTemperatureControl)
	{
		return xResultInvalidRequest;
	}

	switch ((int)selector)
	{
		case TemperatureServiceRequestGetTemperature:
		{
			*(float*)arg = service->Temperature;
			break;
		}

		default : return xResultRequestIsNotFound;
	}

	return xResultAccept;
}
//==============================================================================
//initialization:

static xServiceAdapterInterfaceT privateInterface =
{
	.Handler = (xServiceAdapterHandlerT)privateHandler,
	.RequestListener = (xServiceAdapterRequestListenerT)privateRequestListener
};
//------------------------------------------------------------------------------

xResult TemperatureServiceInit(TemperatureServiceT* service, TemperatureServiceInitT* init)
{
	xServiceInit((xServiceT*)service, (xServiceInitT*)init);

	service->Base.Base.Description = &privateObjectDescription;
	service->Base.Info.Type = xServiceTypeTemperatureControl;

	service->Base.Adapter.Interface = &privateInterface;
	service->Base.Adapter.Description = nameof(TemperatureServiceT);

	return xResultAccept;
}
//==============================================================================
