#include "controller.h"
#include <stdio.h>

S32 _mode;
int _speedVehicle;
S32 _count;
S32 _speedSteering;
S32 _turn;

void controlMotors (S32 speed, S32 mode) {
	_mode = mode;
	_speedVehicle = speed;
}

// Internal mock functions
// For setting and retrieving values

int internGetSpeedVehicle()
{
    return _speedVehicle;
}