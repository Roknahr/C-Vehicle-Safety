#ifndef EAEB_H
#define EAEB_H

#include <math.h> // used for trig functions
#include "constants.h"
#include "nxt_interface.h"
#include "controller.h"
#include "aeb.h"
#include "abs.h"

typedef struct EAEBStruct
{
    U8  activated;
    float distance;
} EAEBStruct;
EAEBStruct eaeb;

int calculateTurnDegrees(float overlap, float distToImpact);

void executeEAEB();

#endif
