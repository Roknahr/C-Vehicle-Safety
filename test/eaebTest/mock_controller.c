#include "controller.h"
#include <stdio.h>

S32 _mode;
int _speed;
S32 _count;

void controlMotors (S32 speed, S32 mode) {
	_mode = mode;
	_speed = speed;
}

// Internal mock functions
// For setting and retrieving values

void turnDegrees (S32 degrees) {
	//return 0;
}
