#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "nxt_interface.h"

#define PI              3.14159
#define SMALL_GEAR      8
#define LARGE_GEAR      40
#define WHEEL_DIAMETER  0.082 /* Wheel size is in m. */

S16 tickDataArray[10];
U8 arrayCounter = 0;

typedef struct VehicleStruct
{
    float velocity;
} VehicleStruct;

VehicleStruct vehicle;

void initialiseTickDataArray();

void saveTickDataToArray();

void calculateVehicleSpeed();

float calculateAverageTicks();

S16 convertRawDataToTicks(S16 rawData);


#endif
