#include "controller.h"
#include "unity.h"
#include "stdio.h"

//This function is called before each test function
void setUp () {
    internSetTime(0);
    controlMotors(0, 0);
}

//This function is called after each test function
void tearDown () {

}

void testReceiveBT () {
    /* Control variables */
    S32 _steeringAmount = -20;
    S32 _throttleAmount = 70;
    U8  _buttonA = 1;
    U8  _buttonB = 0;

    receiveBT();

    TEST_ASSERT_EQUAL(_steeringAmount, getSteeringAmount());
    TEST_ASSERT_EQUAL(_throttleAmount, getThrottleAmount());
    TEST_ASSERT_EQUAL(_buttonA, getButtonA());
    TEST_ASSERT_EQUAL(_buttonB, getButtonB());

}


void testControlSteering () {
    controller.steeringAmount = 100;
    S32 expectedSpeed = 80;
    int brakeMode = 1;
    int count = 0;

    controlSteering();

    TEST_ASSERT_EQUAL(STEERING_MOTOR, internGetPort1());
    TEST_ASSERT_EQUAL(expectedSpeed, internGetSpeed1());
    TEST_ASSERT_EQUAL(brakeMode, internGetMode1());
}

void testControlSteeringTurnDeg () {
    /* Tests that controlSteering() reads data from
       steer.turnDegrees if steer.turnDegreesActivated = 1*/
    controller.steeringAmount = 100;
    S32 expectedSpeed = -80;

    steer.turnDegreesActivated = 1;
    turnDegrees(-40);
    controlSteering();
    steer.turnDegreesActivated = 0;

    TEST_ASSERT_EQUAL(expectedSpeed, internGetSpeed1());
}

void testControlSteeringsLash () {
    controller.steeringAmount = 8;
    S32 count = 0;

    internSetCount(count);

    controlSteering();

    TEST_ASSERT_EQUAL(0, appliedSteering);
}

void testControlMotorsGoodParams () {
    int speed = 100;
    S32 mode = 1;
    U32 t = 15;
    S32 countL = 1435;
    S32 countR = 1508;

    internSetTime(t);
    internSetCountLeft(countL);
    internSetCountRight(countR);

    controlMotors (speed, mode);

    TEST_ASSERT_EQUAL(speed, internGetSpeed1());
    TEST_ASSERT_EQUAL(mode, internGetMode1());
    TEST_ASSERT_FLOAT_WITHIN(1, speed * 0.9515, internGetSpeed2());
    TEST_ASSERT_EQUAL(mode, internGetMode2());
}

void testControlMotorsHighSpeed () {
    int speed = 1216;
    S32 mode = 1;
    U32 t = 22;
    S32 countL = 1202;
    S32 countR = 1097;

    internSetTime(t);
    internSetCountLeft(countL);
    internSetCountRight(countR);

    controlMotors (speed, mode);

    TEST_ASSERT_EQUAL(100 * 0.9126, internGetSpeed1());
    TEST_ASSERT_EQUAL(mode, internGetMode1());
    TEST_ASSERT_EQUAL(100, internGetSpeed2());
    TEST_ASSERT_EQUAL(mode, internGetMode2());
}

void testControlMotorsLowSpeed () {
    int speed = -110;
    S32 mode = 1;
    U32 t = 8;
    S32 countL = 792;
    S32 countR = 1008;

    internSetTime(t);
    internSetCountLeft(countL);
    internSetCountRight(countR);

    controlMotors (speed, mode);

    TEST_ASSERT_EQUAL(-100, internGetSpeed1());
    TEST_ASSERT_EQUAL(mode, internGetMode1());
    TEST_ASSERT_FLOAT_WITHIN(1, -100 * 0.7857, internGetSpeed2());
    TEST_ASSERT_EQUAL(mode, internGetMode2());
}

void testTurnDegreesUnder()
{
    turnDegrees(-60);

    S32 deg = steer.turnDegrees;

    TEST_ASSERT_EQUAL(-100, deg);
}

void testTurnDegreesOver()
{
    turnDegrees(60);

    S32 deg = steer.turnDegrees;

    TEST_ASSERT_EQUAL(100, deg);
}

void testTurnDegreesOn()
{
    turnDegrees(30);

    S32 deg = steer.turnDegrees;

    TEST_ASSERT_EQUAL(75, deg); // 75 because multiplied with 2.5 in controller.c implmentation
}

void testTurnDegreesAlreadyTurnedPos()
{
    internSetCount(30);
    steer.turnDegreesActivated = 1;
    turnDegrees(30);
    controlSteering();
    S32 deg = internGetSpeed1();
    steer.turnDegreesActivated = 0;

    TEST_ASSERT_EQUAL(0, deg); // 75 because multiplied with 2.5 in controller.c implmentation
}

void testTurnDegreesAlreadyTurnedNeg()
{
    internSetCount(-40);
    steer.turnDegreesActivated = 1;
    turnDegrees(-40);
    controlSteering();
    S32 deg = internGetSpeed1();
    steer.turnDegreesActivated = 0;

    TEST_ASSERT_EQUAL(0, deg); // 75 because multiplied with 2.5 in controller.c implmentation
}