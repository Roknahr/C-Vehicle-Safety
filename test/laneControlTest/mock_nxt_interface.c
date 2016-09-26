#include "nxt_interface.h"

U16 _lightSensorRight = 0;
U16 _lightSensorLeft = 0;
U32 _time;
S32 _count = 0;
S32 _countL;
S32 _countR;
S32 _countS;

void internSetLightSensorRight(U16 input)
{
    _lightSensorRight = input;
}

void internSetLightSensorLeft(U16 input)
{
    _lightSensorLeft = input;
}

U16 getLightSensorRight()
{
    return _lightSensorRight;
}

U16 getLightSensorLeft()
{
    return _lightSensorLeft;
}

void initLightSensor ()
{
}

void termLightSensor ()
{
}

void internSetTime (U32 t) {
    _time = t;
}

U32 getSysTime()
{
    return _time;
}

S32 motorGetCount (U8 port_id) {

    if (port_id == LEFT_MOTOR)
        return _countL;
    else if (port_id == RIGHT_MOTOR)
        return _countR;
    else if (port_id == STEERING_MOTOR)
        return _countS;
    else
       return _count;
}

void internSetCount (S32 count) {
    _count = count;
}

void internSetCountLeft (S32 count) {
    _countL = count;
}

void internSetCountRight (S32 count) {
    _countR = count;
}

void internSetCountSteering (S32 count) {
    _countS = count;
}