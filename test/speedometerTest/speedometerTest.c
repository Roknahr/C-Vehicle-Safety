#include "speedometer.h"
#include "unity.h"


void setUp () {

}


void tearDown () {

}

void testConvertRawDataToTicks0()
{
    S16 rawData = 1000;
    S16 tick = convertRawDataToTicks(rawData);

    TEST_ASSERT_EQUAL(0, tick);
}

void testConvertRawDataToTicks1()
{
    S16 rawData = 550;
    S16 tick = convertRawDataToTicks(rawData);

    TEST_ASSERT_EQUAL(1, tick);
}

void testConvertRawDataToTicks2()
{
    S16 rawData = 350;
    S16 tick = convertRawDataToTicks(rawData);

    TEST_ASSERT_EQUAL(2, tick);
}

void testConvertRawDataToTicks3()
{
    S16 rawData = 800;
    S16 tick = convertRawDataToTicks(rawData);

    TEST_ASSERT_EQUAL(3, tick);
}

void testConvertRawDataToTicksBadData()
{
    S16 rawData = 1;
    S16 tick = convertRawDataToTicks(rawData);

    TEST_ASSERT_EQUAL(-1, tick);
}

void testUpdateSpeedometerDataForward()
{
    S16 oldTicksFront = 10;
    Sensor.ticks = oldTicksFront;
    Sensor.secondToLastTick = 1;
    Sensor.lastTick = 0;
    S16 rawData = 800;
    internSetRawData(rawData);
    S32 ticksBack = -822;
    motorSetCount(PORT_B, ticksBack);

    updateSpeedometerData();

    TEST_ASSERT_EQUAL(0, Sensor.secondToLastTick);
    TEST_ASSERT_EQUAL(3, Sensor.lastTick);
    TEST_ASSERT_EQUAL(oldTicksFront+1, Sensor.ticks);
    TEST_ASSERT_EQUAL(Sensor.ticks * (360/16.0), tickCounter.frontDegreesArray[tickCounter.newIndexFront]);
    TEST_ASSERT_EQUAL(-ticksBack, tickCounter.backDegreesArray[tickCounter.newIndexBack]);
}

void testUpdateSpeedometerDataBackward()
{
    S16 oldTicksFront = 126;
    rotationSensor.ticks = oldTicksFront;
    rotationSensor.secondToLastTick = 2;
    rotationSensor.lastTick = 3;
    S16 rawData = 1000;
    internSetRawData(rawData);
    S32 ticksBack = -10;
    motorSetCount(PORT_B, ticksBack);

    updateSpeedometerData();

    TEST_ASSERT_EQUAL(3, rotationSensor.secondToLastTick);
    TEST_ASSERT_EQUAL(0, rotationSensor.lastTick);
    TEST_ASSERT_EQUAL(oldTicksFront-1, rotationSensor.ticks);
    TEST_ASSERT_EQUAL(rotationSensor.ticks * (360/16.0), tickCounter.frontDegreesArray[tickCounter.newIndexFront]);
    TEST_ASSERT_EQUAL(-ticksBack, tickCounter.backDegreesArray[tickCounter.newIndexBack]);
}

void testUpdateSpeedometerDataStopped()
{
    S16 oldTicksFront = 95;
    rotationSensor.ticks = oldTicksFront;
    rotationSensor.secondToLastTick = 1;
    rotationSensor.lastTick = 0;
    S16 rawData = 1000;
    internSetRawData(rawData);
    S32 ticksBack = 100;
    motorSetCount(PORT_B, ticksBack);

    updateSpeedometerData();

    TEST_ASSERT_EQUAL(1, rotationSensor.secondToLastTick);
    TEST_ASSERT_EQUAL(0, rotationSensor.lastTick);
    TEST_ASSERT_EQUAL(oldTicksFront, rotationSensor.ticks);
    TEST_ASSERT_EQUAL(rotationSensor.ticks * (360/16.0), tickCounter.frontDegreesArray[tickCounter.newIndexFront]);
    TEST_ASSERT_EQUAL(-ticksBack, tickCounter.backDegreesArray[tickCounter.newIndexBack]);
}

void testAddToArrayFront () {
    tickCounter.newIndexFront = 48;
    tickCounter.oldIndexFront = 49;
    addToArrayFront(200.0);

    TEST_ASSERT_EQUAL(200.0, tickCounter.frontDegreesArray[tickCounter.newIndexFront]);
    TEST_ASSERT_EQUAL(49, tickCounter.newIndexFront);
    TEST_ASSERT_EQUAL(0, tickCounter.oldIndexFront);
}

void testAddToArrayBack () {
    tickCounter.newIndexBack = 48;
    tickCounter.oldIndexBack = 49;
    addToArrayBack(200.0);

    TEST_ASSERT_EQUAL(200.0, tickCounter.backDegreesArray[tickCounter.newIndexBack]);
    TEST_ASSERT_EQUAL(49, tickCounter.newIndexBack);
    TEST_ASSERT_EQUAL(0, tickCounter.oldIndexBack);
}

void testCalculateVelocity () {
    tickCounter.newIndexBack = 0;
    tickCounter.oldIndexBack = 1;
    tickCounter.newIndexFront = 0;
    tickCounter.oldIndexFront = 1;

    tickCounter.backDegreesArray[tickCounter.newIndexBack] = 2200;
    tickCounter.backDegreesArray[tickCounter.oldIndexBack] = 2150;
    tickCounter.frontDegreesArray[tickCounter.newIndexFront] = 1500;
    tickCounter.frontDegreesArray[tickCounter.oldIndexFront] = 1475;

    calculateVelocity ();

    TEST_ASSERT_FLOAT_WITHIN(0.000001, 0.715583, vehicle.vBack);
    TEST_ASSERT_FLOAT_WITHIN(0.000001, 0.071558, vehicle.vFront);
}
