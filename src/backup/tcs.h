#ifndef TCS_H
#define TCS_H

#include "nxt_interface.h"
#include "speedometer.h"

static float TARGET_SLIP_RATIO = 2;
static S32 SPEED_ADJUST = 15;
static float MINIMUM_SPEED_WHILE_TCS = 0.75;

S32 tcs(S32 speed);


#endif