#include "abs.h"
#include "speedometer.h"
#include "unity.h"


U8 internGetPort ();
S32 internGetMode ();
int internGetSpeed ();
void internSetCount (S32 count);
void internSetSpeed(S8 speed);


void setUp () {

}


void tearDown () {

}

//Tests if ABS cuts engine power if revs reach 0
//Also that wheel is blocked while brake is activated
void testEngineIsStopped () {
	S8 speed = 20;

	vehicle.vFront = 0;
	internSetSpeed(speed);

	brake();

	TEST_ASSERT_EQUAL(0, internGetSpeed());
	TEST_ASSERT_EQUAL(1, internGetMode());
}

//Tests if ABS applies correct break pressure
//NOTE: values depend on BRAKE_SLIP constant in abs.h
void testBrakeRateLessPower () {
	S8 speed = 100;

	vehicle.vFront = 412;
	vehicle.vBack = 378;
	internSetSpeed(speed);

	brake();

	TEST_ASSERT_EQUAL(87, internGetSpeed());
	TEST_ASSERT_EQUAL(1, internGetMode());
}

//Tests if ABS applies correct break pressure
//NOTE: values depend on BRAKE_SLIP constant in abs.h
void testBrakeRateMorePower () {
	S8 speed = 76;

	vehicle.vFront = 342;
	vehicle.vBack = 216;
	internSetSpeed(speed);

	brake();

	TEST_ASSERT_EQUAL(96, internGetSpeed());
	TEST_ASSERT_EQUAL(1, internGetMode());
}

//Tests if divide by 0 error occurs in math
//NOTE: values depend on BRAKE_SLIP constant in abs.h
void testBrakeRateDivBy0 () {
	S8 speed = 76;

	vehicle.vFront = 20;
	vehicle.vBack = 0;
	internSetSpeed(speed);

	brake();

	//Overflow is handled by controlMotors in controller.c
	TEST_ASSERT_EQUAL(1216, internGetSpeed());
	TEST_ASSERT_EQUAL(1, internGetMode());
}

