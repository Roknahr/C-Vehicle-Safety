#ifndef AEB_H
#define AEB_H

#include "speedometer.h"
#include <math.h>
#include "nxt_interface.h"
#include "constants.h"
#include "eaeb.h"

typedef struct AEBStruct
{
    U8  activated;
    U8  distanceIndex;
    U32 lastTimeRead;
    S32 distanceToObj1;
    S32 distanceToObj2;
    float distanceFromPath;
    float distances[SAMPLE_COUNT];
} AEBStruct;
AEBStruct aeb;

void aebInitialise();

float getBrakeDistance ();

float getDistanceTravelled();

int updateDistanceFromPath();

float getDistanceToImpact();

void runAEB();

void addDistanceToArray(float item);

float fakePow(float vFront, int fakePow);

float fakeAcos(float x);

float fakeSin(float x);

#endif
