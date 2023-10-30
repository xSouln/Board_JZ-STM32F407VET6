//==============================================================================
//includes:

#include <stdlib.h>
#include "Abstractions/xSystem/xSystem.h"
#include "TemperatureService-Adapter.h"
#include "CAN_Local/Control/CAN_Local-Types.h"
#include "TransferLayer/TransferLayer-Component.h"
//==============================================================================
//defines:


//==============================================================================
//types:


//==============================================================================
//variables:

static uint32_t privateCount;
//==============================================================================
//functions:

static void privateOpenTransferHandler(TemperatureServiceT* service,
		TemperatureServiceAdapterT* adapter,
		volatile CAN_LocalSegmentT* segment)
{
	volatile CAN_LocalPacketOpenTransferRequestT request = { .Value = segment->Data.DoubleWord };

	if (request.ServiceId == service->Base.Id)
	{
		privateCount++;

		CAN_LocalPacketOpenTransferResponseT response;
		response.ServiceId = segment->ExtensionHeader.ServiceId;
		response.Action = request.Action;
		response.Token = request.Token;
		response.Result = 0;

		CAN_LocalSegmentT packet;
		packet.TransferHeader.MessageType = CAN_LocalMessageTypeTransfer;
		packet.TransferHeader.PacketType = CAN_LocalTransferPacketTypeApproveTransfer;
		packet.TransferHeader.Characteristic = service->Base.Info.Type;
		packet.TransferHeader.ServiceId = service->Base.Id;
		packet.TransferHeader.IsEnabled = true;

		packet.Data.DoubleWord = response.Value;
		packet.DataLength = sizeof(response);

		xPortExtendedTransmition(adapter->Port, &packet);
	}
}
//------------------------------------------------------------------------------
static void privateNotificationHandler(TemperatureServiceT* service,
		TemperatureServiceAdapterT* adapter,
		CAN_LocalSegmentT* segment)
{
	CAN_LocalBaseEventPacketT content = { .Value = segment->Data.DoubleWord };

	if (segment->Header.ServiceType == service->Base.Info.Type && content.Id == service->Base.Id)
	{
		xServiceSubscriberListElementT* element = service->Base.Subscribers.Head;

		while (element)
		{
			xServiceSubscriberT* subscriber = element->Value;

			if (subscriber->EventListener)
			{
				subscriber->EventListener((void*)service, subscriber, 0, &content.Content);
			}

			element = element->Next;
		}
	}
}
//------------------------------------------------------------------------------
static void privateHandler(TemperatureServiceT* service)
{
	TemperatureServiceAdapterT* adapter = service->Adapter.Content;

	uint32_t totalTime = xSystemGetTime(service);

	if (adapter->Internal.TimeStamp - totalTime > 500)
	{
		adapter->Internal.TimeStamp = totalTime;

		service->Temperature = 10.0f + (float)(rand() & 0x3fff) / 1000;
	}

	xCircleBufferT* circleBuffer = xPortGetRxCircleBuffer(adapter->Port);

	while (adapter->Internal.RxPacketHandlerIndex != circleBuffer->TotalIndex)
	{
		CAN_LocalSegmentT* segment = xCircleBufferGetElement(circleBuffer, adapter->Internal.RxPacketHandlerIndex);

		if (segment->ExtensionIsEnabled)
		{
			switch((uint8_t)segment->ExtensionHeader.MessageType)
			{
				case CAN_LocalMessageTypeTransfer:
				{
					switch((uint8_t)segment->ExtensionHeader.PacketType)
					{
						case CAN_LocalTransferPacketTypeOpenTransfer:
							privateOpenTransferHandler(service, adapter, segment);
							break;
					}
					break;
				}
			}
		}
		else
		{
			switch((uint8_t)segment->Header.MessageType)
			{
				case CAN_LocalMessageTypeNotification:
				{
					privateNotificationHandler(service, adapter, segment);
					break;
				}
			}
		}

		adapter->Internal.RxPacketHandlerIndex++;
		adapter->Internal.RxPacketHandlerIndex &= circleBuffer->SizeMask;
	}
}
//------------------------------------------------------------------------------
static xResult privateRequestListener(TemperatureServiceT* service, int selector, void* arg)
{
	switch ((uint32_t)selector)
	{

		default : return xResultRequestIsNotFound;
	}

	return xResultAccept;
}
//------------------------------------------------------------------------------
static void privateEventListener(TemperatureServiceT* service, TemperatureServiceAdapterEventSelector selector, void* arg)
{
	//register UsartPortAdapterT* adapter = (UsartPortAdapterT*)port->Adapter;

	switch((int)selector)
	{
		default: return;
	}
}
//==============================================================================
//initializations:

static TemperatureServiceAdapterInterfaceT privateInterface =
{
	.Handler = (TemperatureServiceAdapterHandlerT)privateHandler,

	.RequestListener = (TemperatureServiceAdapterRequestListenerT)privateRequestListener
};
//------------------------------------------------------------------------------
xResult TemperatureServiceAdapterInit(TemperatureServiceT* service,
		TemperatureServiceAdapterT* adapter,
		TemperatureServiceAdapterInitT* init)
{
	if (service && init)
	{
		service->Adapter.Content = adapter;
		service->Adapter.Interface = &privateInterface;
		service->Adapter.Description = nameof(TemperatureServiceAdapterT);

		adapter->Port = init->Port;

		return xResultAccept;
	}
  
  return xResultError;
}
//==============================================================================
