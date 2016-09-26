#include "m_nxt_interface.h"
#include <stdio.h>

U32 getSysTime()
{
    return _time;
}

U32 sendBtPacket(U8 *buf, U32 bufLen){
	_bufferP = buf;
	_bufLen = bufLen;
    return 0;
}

void internSetTime(U32 time)
{
    _time = time;
}

U8* internGetBufferP () {
	return _bufferP;
}

U32 internGetBufLen () {
	return _bufLen;
}

