#ifndef LANE_CONTROL_H
#define LANE_CONTROL_H

#include "nxt_interface.h"
#include "eaeb.h"
#include "controller.h"

#define COLOUR_SAFETY 15
#define LEFT_ROADMARKING_VALUE 1
#define RIGHT_ROADMARKING_VALUE 2

extern U8 calibrated;
extern U16 roadMarkingColourRight;
extern U16 roadMarkingColourLeft;
extern U16 floorColourRight;
extern U16 floorColourLeft;

void laneControl();
void calibrateLaneControlSensor();
void calibrateRoadMarkingColour();
void calibrateFloorColour();
U8 detectRoadMarking();
void adjustVehicle(U8 roadMarking);
S32 calculateTurnAngle(U8 roadMarking);

#endif
