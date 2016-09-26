#include "nxt_interface.h"
#include <stdio.h>

U8 _port1;
S32 _mode1;
S32 _speed1;
U8 _port2;
S32 _mode2;
S32 _speed2;
S32 _count = 0;
S32 _countL;
S32 _countR;
U32 _time;

U32 getSysTime()
{
    return _time;
}

S32 motorGetCount (U8 port_id) {
	_port1 = port_id;

    if (port_id == LEFT_MOTOR)
        return _countL;
    else if (port_id == RIGHT_MOTOR)
        return _countR;
    else
	   return _count;
}

U32 readBtPacket(U8 *buf, U32 bufLen) {
    buf[0] = -20;
    buf[1] = -70;
    buf[2] = 1;
    buf[3] = 0;
    return 4;
}

void motorSetSpeed(U8 port, S32 speed, S32 mode){
    if (port == LEFT_MOTOR || port == STEERING_MOTOR) {
        _port1 = port;
        _speed1 = speed;
        _mode1 = mode;
    } else if (port == RIGHT_MOTOR) {
        _port2 = port;
        _speed2 = speed;
        _mode2 = mode;
    }
}

// Internal mock functions
// For setting and retrieving values
U8 internGetPort1 () {
    return _port1;
}

S32 internGetMode1 () {
    return _mode1;
}

S32 internGetSpeed1 () {
	return _speed1;
}

U8 internGetPort2 () {
    return _port2;
}

S32 internGetMode2 () {
    return _mode2;
}

S32 internGetSpeed2 () {
    return _speed2;
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

void internSetTime (U32 t) {
    _time = t;
}