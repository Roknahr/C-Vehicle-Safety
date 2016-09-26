#include "datalog.h"
#include <string.h>

U8* createDatalogArray() 
{
	static U8 dataArray[PACKETSIZE];
	
	U32 time = getSysTime();
	S16 vFront = vehicle.vFront * 100; //Turn value into int, to avoid complications of sending float values via Bluetooth
	S16 vBack = vehicle.vBack * 100;

	memcpy(&dataArray[0], &time, sizeof(U32));					// 4 bytes
	memcpy(&dataArray[4], &vFront, sizeof(S16));				// 2 bytes
	memcpy(&dataArray[6], &vBack, sizeof(S16));					// 2 bytes
	memcpy(&dataArray[8], &appliedPower, sizeof(S8));			// 1 byte
	memcpy(&dataArray[9], &appliedSteering, sizeof(S32));		// 4 bytes
																// = 13 bytes

	return dataArray;
}

void sendData() 
{
	U8 *dataArray = createDatalogArray();
    sendBtPacket(dataArray, PACKETSIZE);
}
