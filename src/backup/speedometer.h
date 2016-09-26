#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "nxt_interface.h"
#include "controller.h"
#include "aeb.h"

#define PI                              3.14159
#define SMALL_GEAR                      8
#define LARGE_GEAR                      40
#define WHEEL_DIAMETER                  0.082   /* Wheel size is in m. */
#define SEC_PER_MIN                     60      /* seconds */
#define MS_PER_MIN                      60000   /* milliseconds */
#define GEAR_RATIO                      5       /* LARGE_GEAR / SMALL_GEAR */
#define WHEEL_CIRC                      0.25761 /* WHEEL_DIAMETER*PI */
#define SPEED_TIME_BETWEEN_READINGS     10      /* milliseconds */
#define TICKS_PER_ROUND                 16      /* ticks per round on rotation sensor */
#define TICK_ARRAY_SIZE                 50      /* Size of tick history arrays*/

typedef struct VehicleStruct
{
    U32 backLastTime;
    U32 frontLastTime;
    float vFront;  // real velocity
    float vBack; // applied velocity
    float vBackRounds;
    float vFrontRounds;
} VehicleStruct;
VehicleStruct vehicle;

typedef struct TickCounter
{
    float frontDegreesArray[TICK_ARRAY_SIZE];
    S32 backDegreesArray[TICK_ARRAY_SIZE];
    U8 oldIndexFront;
    U8 newIndexFront;
    U8 oldIndexBack;
    U8 newIndexBack;
} TickCounter;
TickCounter tickCounter;

/*
static S16 tickDataArray[100];
static U8 arrayCounter = 0;
*/

void speedometerInitialise();

void updateSpeedometerData();

void calculateVelocity();

void addToArrayFront(float item);

void addToArrayBack(S32 item);

S16 convertRawDataToTicks(S16 rawData);

//void initialiseTickDataArray();

//void saveTickDataToArray();

//void calculateVehicleSpeed();

//void setFrontWheelVelocity();

//float averageTicksInRounds();

//float getMaxMotorRotationSpeedInRounds();

//float degreesToRounds(S32 degrees);

//float getVelocityMS(float roundsPerMin);

//void setBackWheelVelocity();

#endif
