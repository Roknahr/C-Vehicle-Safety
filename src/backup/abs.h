#ifndef ABS_H
#define ABS_H
#include "controller.h"
#include "speedometer.h"
#include "nxt_interface.h"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Contains a single function that slows down the engines,    *
* braking the engines at an optimal ratio.                   *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Slows down the vehicle at a rate optimizing braking distance
//If vehicle is stationary it applies brake mode to the motors
void brake();
U8 isLocked();//TODO: Move this prototype to abs.c, as it is a private helper function

#endif
