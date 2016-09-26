#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "nxt_interface.h"
#include "abs.h"

enum {
    BRAKE_OFF,
    BRAKE_ON
};

enum {
    BUTTON_RELEASED,
    BUTTON_PRESSED
};

typedef struct ControllerStruct{
    S32 steeringAmount;
    S32 throttleAmount;
    U8 buttonA;
    U8 buttonB;
} ControllerStruct;
ControllerStruct controller;

S8 appliedPower;
S32 appliedMode;
S32 appliedSteering;

void receiveBT();
void controlSteering();
void controlMotors (S32 speed, S32 mode);
S8 getSteeringAmount();
S8 getThrottleAmount();
U8 getButtonA();
U8 getButtonB();
void initTurnStruct();
void turnDegrees(S32 degrees);

typedef struct TurnStruct
{
	S32 turnDegrees;
	S8 turnDegreesActivated;
} TurnStruct;
TurnStruct steer;

#endif
