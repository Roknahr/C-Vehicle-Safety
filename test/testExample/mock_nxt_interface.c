#include "nxt_interface.h"
#include <stdio.h>

U8 _port;
S32 _mode;
S8 _speed;
S32 _count;

void set_motor_speed (U8 port_id, S32 mode, S8 speed) {
	_port = port_id;
	_mode = mode;
	_speed = speed;
}

S32 get_motor_count (U8 port_id) {
	_port = port_id;
	return _count;
}



// Internal mock functions
// For setting and retrieving values
U8 intern_get_port () {
	return _port;
}

S32 intern_get_mode () {
	return _mode;
}

S8 intern_get_speed () {
	return _speed;
}

void intern_set_count (S32 count) {
	_count = count;
}

