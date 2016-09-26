#include "nxt_interface.h"

void internSetTime(U32 time);
U8* internGetBufferP();
U32 internGetBufLen();

U32 _time;
U8 *_bufferP;
U32 _bufLen;
