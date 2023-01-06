//==============================================================================
//includes:

#include "SureFlap_Device.h"
#include "SureFlap_ZigbeePackets.h"
#include "SureFlap_Tcp.h"
#include <stdio.h>
//==============================================================================
//defines:


//==============================================================================
//variables:


//==============================================================================
//functions:

void SureFlapDeviceDataReceiver(SureFlapT* hub, SureFlapDeviceT* device)
{
	xResult result = xResultError;

	char data[SUREFLAP_SERVER_MESSAGE_BUFFER_SIZE];
	int data_size = 0;

	static uint8_t server_msg_index = 0;

	// we can do a sanity check here as we know that we only receive packets
	// of type T_MESSAGE. Because we know that T_MESSAGE contains a length, and
	// so does RECEIVED_PACKET, we can check for consistency:

	if((hub->Zigbee.RxPacket.Header.PacketLength - 21) != hub->Zigbee.RxPacket.Payload[2])
	{
		return;
	}

	SureFlapZigbeeMessageT* message = (SureFlapZigbeeMessageT*)hub->Zigbee.RxPacket.Payload;
	uint16_t register_number = (uint16_t)((message->Payload[1] & 0xff) + (message->Payload[0] << 8));
	uint16_t length = (uint16_t)((message->Payload[3] & 0xff) + (message->Payload[2] << 8));

	switch(message->Command)
	{
		case SUREFLAP_ZIGBEE_COMMAND_GET_REG:
			data_size = sprintf(data,
								"%d %d %d",
								SUREFLAP_TCP_MSG_GET_REG_RANGE,
								register_number,
								length);
			break;

		// Device sending one or more registers to the server
		case SUREFLAP_ZIGBEE_COMMAND_SET_REG:
			// arguments are MSG_REG_VALUES_INDEX_ADDED index reg_address num_of_registers val1 val2 val3 etc.
			// here we screen out time update COMMAND_SET_REG messages if hub_debug_mode bit 2 is not set.
			// Bit 7 of payload[6] = minutes is set if the device is requesting the server to send the time.
			// These messages need to be sent. Otherwise hourly time messages get discarded
			// and the only time messages sent are the ones generated by the hub based on the device awake messages.
			// Don't know what is going on here. Removing this allows the Hourly messgaes to get through,
			// which they do with Hub1...?!?!
			// if ( ((registerNumber==33&&length==3&&(rx_message->payload[6]<128)) || (registerNumber==634&&length==16)) &&
			// (hub_debug_mode!=HUB_SEND_TIME_UPDATES_FROM_DEVICES))  //discard PET DOOR hourly messages unless send time bit is set
			// {
			// discard message
			// } else if( MOVEMENT_DUMMY_REGISTER == registerNumber)

			// This is a Pet Door Movement event, which is a group of registers sent atomically. Length is assumed to be correct!
			if(register_number == SUREFLAP_ZIGBEE_MOVEMENT_DUMMY_REGISTER)
			{
				data_size = sprintf(data, "%d", SUREFLAP_TCP_MSG_MOVEMENT_EVENT);

				// build string containing list of values
				for(int i = 0; i < length; i++)
				{
					data_size += sprintf(data + data_size," %02x", message->Payload[i + 4]);
				}
			}
			else
			{
				data_size = sprintf((char *)data,
						"%d %d %d %d",
						SUREFLAP_TCP_MSG_REG_VALUES_INDEX_ADDED,
						server_msg_index++,
						register_number,
						length);

				// build string containing list of values
				for(int i = 0; i < length; i++)
				{
					data_size += sprintf(data + data_size, " %02x", message->Payload[i + 4]);
				}
			}
			break;

		// Device is sending a single Thalamus format message
		case SUREFLAP_ZIGBEE_COMMAND_THALAMUS:
			// arguments are MSG_HUB_THALAMUS va1 val2 val3 etc.
			data_size = sprintf((char *)data, "%d", SUREFLAP_TCP_MSG_HUB_THALAMUS);

			// build string containing list of values
			for(int i = 0; i < message->Length - SUREFLAP_ZIGBEE_MESSAGE_OVERHEAD; i++)
			{
				data_size += sprintf(data + data_size," %02x", message->Payload[i]);
			}
			break;

		case SUREFLAP_ZIGBEE_COMMAND_THALAMUS_MULTIPLE:
			// arguments are MSG_HUB_THALAMUS va1 val2 val3 etc.
			data_size = sprintf((char *)data, "%d", SUREFLAP_TCP_MSG_HUB_THALAMUS_MULTIPLE);

			// build string containing list of values
			for(int i = 0; i < message->Length - SUREFLAP_ZIGBEE_MESSAGE_OVERHEAD; i++)
			{
				data_size += sprintf(data + data_size," %02x", message->Payload[i]);
			}
			break;
	}

	if (data_size)
	{
		result = SureFlapTcpAddToServerBuffer(&hub->Tcp, device->Status.MAC_Address, data, data_size);
	}
}
//==============================================================================
