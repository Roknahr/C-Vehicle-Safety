#include "eaeb.h"

int turn = 0;
float distance = 0.0;

void executeEAEB()
{   
	// prevents user from steering while the EAEB is running
	steer.turnDegreesActivated = 1;
 
 	// brake while the distance to the object ahead is more than 35 centimeter
 	brake();

 	float distanceToImpact = getDistanceToImpact();
 	// busy wait while braking
	if(distanceToImpact != -1 && distanceToImpact < BRAKE_WAIT_DIST)
	{
		// release brake from wheels allowing them to float
	    controlMotors(0, BRAKE_OFF);

	    // turn the fixed amount of degrees on the front wheels
	    turnDegrees(MAX_LEFT_TURN);

	    // turn for TURN_DISTANCE distance
	    if(eaeb.distance < TURN_DISTANCE)
	    {	
		    eaeb.distance += 1; //getDistanceTravelled();
		        displayClear(0);
		        displayGotoXY(5,3);
		        displayInt(eaeb.distance, 0);
		        displayGotoXY(5,4);
		        displayInt(666, 0);
		        displayUpdate();
		}
		else
		{

		        displayClear(0);
		        displayGotoXY(5,3);
		        displayInt(eaeb.distance, 0);
		        displayGotoXY(5,4);
		        displayInt(777, 0);
		        displayUpdate();
			// reset distance travelled
			eaeb.distance = 0.0;

			// reset wheel position
			turnDegrees(0);

			// float for 10 centimeters to straighten up the vehicles path
			if(eaeb.distance < 10)
   			{	
	   			eaeb.distance += getDistanceTravelled();
			}
			else
			{
			    brake();

			 	// reset distance travelled
				eaeb.distance = 0.0;

				// allow the user to steer again
			    steer.turnDegreesActivated = 0;
			}
		}
    }
}

/*
calculateTurnDegrees could be called with parameters getDistanceToImpact(), aeb.distanceFromPath + VEHICLE_SAFE_ZONE.
That approach was tried and should work in theory, but didn't work in practice. Therefore another implementation was chosen.
The function is still in the source code if there is made a decision to try to make the orignal solution work.
*/


/*
int calculateTurnDegrees(float overlap, float distToImpact) 
{
	float ratio = overlap / distToImpact;
	float turnRads = atan(ratio);
	float turnDegrees = (turnRads * 180 / PI) + 1; // +1 makes up for lost precision when casted to int 2.26 => 2


	return (int)turnDegrees;
}*/
