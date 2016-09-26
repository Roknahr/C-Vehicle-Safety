#include "tcs.h"
#include "speedometer.h"
#include "unity.h"
/*
  Det antages at TCS funktionen foregår før appliedPower verifikation i controlMotors funktionen.
  Således vil det ikke være muligt for speed at blive negativ.
*/


//This function is called before each test function
void setUp () {

}

//This function is called after each test function
void tearDown () {

}

void printValues(S32 speed){
    printf("vBack: %f\n", vehicle.vBack);
    printf("vFront: %f\n", vehicle.vFront);
    printf("Speed: %d\n", speed);
}

//Det antages at speed bliver nedsat med 15, hvis hjulet slipper.
void testLowerSpeedWhenSlipping () {
    vehicle.vBack = 1.76;
    vehicle.vFront = 0.4;
    S32 speed = 100;
    S32 expectedSpeed = speed - SPEED_ADJUST;

    speed = tcs(speed);

    TEST_ASSERT_EQUAL(expectedSpeed, speed);
}

void testLowerSpeedWhenBothReverse () {
    vehicle.vBack = -1.76;
    vehicle.vFront = -0.4;
    S32 speed = 100;
    S32 expectedSpeed = speed - SPEED_ADJUST;

    speed = tcs(speed);

    TEST_ASSERT_EQUAL(expectedSpeed, speed);
}

void testLowerSpeedWhenBackReverse () {
    vehicle.vBack = -1.76;
    vehicle.vFront = 1.4;
    S32 speed = 100;
    S32 expectedSpeed = speed - SPEED_ADJUST;

    speed = tcs(speed);

    TEST_ASSERT_EQUAL(expectedSpeed, speed);
}

void testLowerSpeedWhenFrontReverse () {
    vehicle.vBack = 1.76;
    vehicle.vFront = -0.4;
    S32 speed = 100;
    S32 expectedSpeed = speed - SPEED_ADJUST;

    speed = tcs(speed);

    TEST_ASSERT_EQUAL(expectedSpeed, speed);
}




//Det antages at der ikke bliver ændret på hastigheden, da der er intet slip.

void testRemainSpeedWhenNotSlipping(){
    vehicle.vBack = 1.76;
    vehicle.vFront = 1.1;
    S8 speed = 100;
    S8 expectedSpeed = speed;

    speed = tcs(speed);

    TEST_ASSERT_EQUAL(expectedSpeed, speed);
}


void testRemainSpeedWhenNotSlippingBothReverse(){
    vehicle.vBack = -1.76;
    vehicle.vFront = -1.1;
    S8 speed = 100;
    S8 expectedSpeed = speed;

    speed = tcs(speed);

    TEST_ASSERT_EQUAL(expectedSpeed, speed);
}

//Antaget at MINIMUM_SPEED_WHILE_TCS = 0.05;
void testRemainSpeedWhenNotSlippingBackReverse(){
    vehicle.vBack = -0.1;
    vehicle.vFront = 0.3;
    S8 speed = 100;
    S8 expectedSpeed = speed;

    speed = tcs(speed);

    TEST_ASSERT_EQUAL(expectedSpeed, speed);
}

//Antaget at MINIMUM_SPEED_WHILE_TCS = 0.05;
void testRemainSpeedWhenNotSlippingFrontReverse(){
    vehicle.vBack = 0.1;
    vehicle.vFront = -0.3;
    S8 speed = 100;
    S8 expectedSpeed = speed;

    speed = tcs(speed);

    TEST_ASSERT_EQUAL(expectedSpeed, speed);
}


void testRemainSpeedWhenBraking(){
    vehicle.vBack = 0.85;
    vehicle.vFront = 2.1;
    S8 speed = 100;
    S8 expectedSpeed = speed;

    speed = tcs(speed);

    TEST_ASSERT_EQUAL(expectedSpeed, speed);
}


void testRemainSpeedWhenBrakingNegative(){
    vehicle.vBack = -0.85;
    vehicle.vFront = -2.1;
    S8 speed = 100;
    S8 expectedSpeed = speed;

    speed = tcs(speed);

    TEST_ASSERT_EQUAL(expectedSpeed, speed);
}



/*
//Det antages at der kan ske fejl pga. floats upræcision, hvis testen fejler.
void testRemainSpeedWhenSlipEqualMaxTargetSlip(){
    S32 frontWheelRotationDegree = 400;
    S32 backWheelRotationDegree = frontWheelRotationDegree * 1.05;
    S8 speed = 100;
    S8 expectedSpeed = speed;

    speed = tcs(frontWheelRotationDegree, backWheelRotationDegree, speed);

    TEST_ASSERT_EQUAL(expectedSpeed, speed);
}


//Det antages at der kan ske fejl pga. floats upræcision, hvis testen fejler.
void testLowerSpeedWhenStartAccelerating(){
    S32 frontWheelRotationDegree = 0;
    S32 backWheelRotationDegree = 65;
    S8 speed = 65;
    S8 expectedSpeed = speed - 15;

    speed = tcs(frontWheelRotationDegree, backWheelRotationDegree, speed);

    TEST_ASSERT_EQUAL(expectedSpeed, speed);
}
*/