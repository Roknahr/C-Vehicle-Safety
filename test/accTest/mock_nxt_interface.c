#include <stdio.h>
#include "nxt_interface.h"
#include "speedometer.h"

S32 _distance;
U32 _lastTime;

S32 getSonarSensor(){
    return _distance;
}

U32 getSysTime(){
    return _lastTime;
}

void internSetDistance(S32 dist){
    _distance = dist;
}

void internSetTime(U32 lastTime){
    _lastTime = lastTime;
}

void internSetVelocity(float velocity){
    vehicle.vFront = velocity;

}

S32 internGetDistance(){
    return _distance;
}

U32 internGetTime(){
    return _lastTime;
}

float internGetVelocity(){
    return vehicle.vFront;
}
