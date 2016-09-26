#include "abs.h"
#include "controller.h"
#define BRAKE_SLIP 0.2

static S32 currentSpeed;

//Slows down the vehicle at a rate optimizing braking distance
//If vehicle is stationary it applies brake mode to the motors
void brake() {
	/*
	int newPower = 0;
	if (vehicle.vFront < 0.1) {				// 0.1 used because FLOAT == FLOAT can be imprecise
		controlMotors (0, 1);
	} else {
		newPower = calculateNewPower();
		controlMotors (newPower, 1);
	}*/

	// currentSpeed = appliedPower;

    
	// if (isLocked() == 1)
	// {
	// 	float decreaseSpeedPercent = getThrottleAmount() / 100;
	// 	controlMotors(currentSpeed * decreaseSpeedPercent, 1); 
	// } else {
	// 	motorSetSpeed(LEFT_MOTOR, 0, 1);
	// 	motorSetSpeed(RIGHT_MOTOR, 0, 1);
	// }

		motorSetSpeed(LEFT_MOTOR, 0, 1);
		motorSetSpeed(RIGHT_MOTOR, 0, 1);

}
//Calculates the now power to be applied to the motors
//	in relation to the current revolution speed of
//	the front and back wheels.
/*int calculateNewPower() {
	int backDegPrSecCorrected; // used to prevent division by zero

	//Prevent division by zero
	if (vehicle.vBack == 0) 
		backDegPrSecCorrected = 0.001;
	else
		backDegPrSecCorrected = vehicle.vBack;

	float powerRatio = -((BRAKE_SLIP *  vehicle.vFront) - vehicle.vFront) / backDegPrSecCorrected;

	displayClear(0);
	displayGotoXY(0, 4);
	displayInt(powerRatio*100, 0);
	displayUpdate();

	int result = (powerRatio * appliedPower);

	return result;
}*/

U8 isLocked() {
	//Prevent division by zero
	U8 locked = 0;
	float brakeSlip = 0.3;
	if (fabs(vehicle.vFront) > 0.0) {
		float slipRatio = (vehicle.vFront - vehicle.vBack) / vehicle.vFront;
		if (slipRatio > brakeSlip){
			locked = 1;
		}
	}

	return locked;
}
