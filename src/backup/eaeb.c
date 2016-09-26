#include "eaeb.h"

#define TURN_DISTANCE 15.0 /* distance to let the vehicle drive while evading */

int turn = 0;
float distance = 0.0;

void runEAEB()
{   
	steer.turnDegreesActivated = 1;

	int degreesToTurn = calculateTurnDegrees(getDistanceToImpact(), aeb.distanceFromPath + VEHICLE_SAFE_ZONE);

	turnDegrees(degreesToTurn); // turn front wheels
    
    while(distance < TURN_DISTANCE)
    {	
	    distance += getDistanceTravelled(); // distance when the evade is first called in cm
	}
	
	turnDegrees(0); // reset wheel position
    brake();

	distance = 0.0; // reset distance travelled

    steer.turnDegreesActivated = 0;
}

int calculateTurnDegrees(float overlap, float distToImpact) 
{
	float ratio = overlap / distToImpact;
	float turnRads = atan(ratio);
	float turnDegrees = (turnRads * 180 / PI) + 1; // +1 makes up for lost precision when casted to int 2.26 => 2

	return (int)turnDegrees;
}
