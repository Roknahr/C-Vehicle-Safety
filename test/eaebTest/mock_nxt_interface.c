#include <stdio.h>
#include "nxt_interface.h"
#include "speedometer.h"

U32 _sysTime;

void motorSetSpeed(U8 port, S32 speed, S32 mode)
{
	
}


S32 _count = 0;

S32 internMotorGetCount()
{
	return _count;
}

void internMotorSetCount(S32 count)
{
	_count = count;
}

U32 getSysTime(){
    return _sysTime;
}

void internSetTime(U32 sysTime){
    _sysTime = sysTime;
}