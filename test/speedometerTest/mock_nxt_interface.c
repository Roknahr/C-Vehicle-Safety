#include <stdio.h>
#include "nxt_interface.h"
#include "speedometer.h"

U32 _lastTime;
S32 internal_motor1;
S32 internal_motor2;
S16 _rawData;

S32 motorGetCount(U8 port){
    if (port == PORT_C){
        return internal_motor1;
    } else {
        return internal_motor2;
    }
}

void motorSetCount(U8 port, int count){
    if (port == PORT_C){
        internal_motor1 = count;
    } else {
        internal_motor2 = count;
    }
}

void setInternalMotor(U8 port, U32 speed){
    if (port == PORT_C){
        internal_motor1 = speed;
    } else {
        internal_motor2 = speed;
    }
}


U32 getSysTime(){
    return _lastTime;
}

S16 getRotationSensor(){
    return _rawData;
}

U32 internGetTime(){
    return _lastTime;
}

void internSetTime(U32 lastTime){
    _lastTime = lastTime;
}

void internSetRawData (U16 rawData){
    _rawData = rawData;
}
