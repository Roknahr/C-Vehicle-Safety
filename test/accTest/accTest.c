#include "acc.h"
#include "unity.h"

void setUp () {
    initACCStruck();
}


void tearDown () {

}

void testACC()
{

}


void testConvertDistanceToTime()
{
    vehicle.vFront = 2.0;
    S32 drivenDistance = 100;
    float expectedTime = 0.5;

    float actualTime = convertDistanceToTime(drivenDistance);

    TEST_ASSERT_FLOAT_WITHIN(0.01, expectedTime, actualTime);
}

void testCalculateLeadVehicleVelocity()
{
    vehicle.vFront = 2.0;
    internSetTime(25);
    calculateLeadVehicleVelocity(150);

    internSetTime(1025);
    float actualVelocity = calculateLeadVehicleVelocity(200);

    float expectedVelocity = 2.5;

    TEST_ASSERT_FLOAT_WITHIN(0.01, expectedVelocity, actualVelocity);
}

void testSlowDown()
{
    acc.throttleAmount = 100;
    S32 expectedVelocity = 95;

    slowDown(5);

    S32 actualVelocity = internGetSpeedVehicle();

    TEST_ASSERT_EQUAL(expectedVelocity, actualVelocity);
}

void testSpeedUp()
{
    acc.throttleAmount = 75;
    S32 expectedVelocity = 78;

    speedUp(5);

    S32 actualVelocity = internGetSpeedVehicle();

    TEST_ASSERT_EQUAL(expectedVelocity, actualVelocity);
}

void testMaintainDistanceIncreaseVelocity()
{
    acc.throttleAmount = 75;
    acc.firstDistanceMeasurement = 50;
    acc.secondDistanceMeasurement = 45;
    S32 expectedVelocity = 76;

    maintainDistance();

    S32 actualVelocity = internGetSpeedVehicle();

    TEST_ASSERT_EQUAL(expectedVelocity, actualVelocity);
}

void testMaintainDistanceDecreaseVelocity()
{
    acc.throttleAmount = 75;
    acc.firstDistanceMeasurement = 50;
    acc.secondDistanceMeasurement = 55;
    S32 expectedVelocity = 74;

    maintainDistance();

    S32 actualVelocity = internGetSpeedVehicle();

    TEST_ASSERT_EQUAL(expectedVelocity, actualVelocity);
}
