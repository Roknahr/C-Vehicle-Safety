#include "laneControl.h"
#include "eaeb.h"
#include "controller.h"
#include "unity.h"

U16 RoadMarkingRight = 750;
U16 RoadMarkingLeft = 748;
U16 FloorRight = 650;
U16 FloorLeft = 638;


//This function is called before each test function
void setUp ()
{
    initLightSensor();
}

//This function is called after each test function
void tearDown ()
{
    termLightSensor();
}

// Tests if road marking is detected for
// right sensor
void testDetectRoadMarkingRight ()
{
    // Expected value is return value
    // from detectRoadMarking function
    U16 expectedRoadMarkingRight = 2;

    internSetLightSensorRight(RoadMarkingRight);
    internSetLightSensorLeft(RoadMarkingLeft);

    calibrateRoadMarkingColour();

    internSetLightSensorLeft(FloorLeft);

    TEST_ASSERT_EQUAL(expectedRoadMarkingRight, detectRoadMarking());
}

// Tests if road marking is detected for
// left sensor
void testDetectRoadMarkingLeft ()
{
    // Expected value is return value
    // from detectRoadMarking function
    U16 expectedRoadMarkingLeft = 1;

    internSetLightSensorRight(RoadMarkingRight);
    internSetLightSensorLeft(RoadMarkingLeft);

    calibrateRoadMarkingColour();

    internSetLightSensorRight(FloorRight);

    TEST_ASSERT_EQUAL(expectedRoadMarkingLeft, detectRoadMarking());
}

// Tests if no road marking is detected
// for both sensors
void testDetectNoRoadMarking ()
{
    // Expected value is return value
    // from detectRoadMarking function
    U16 expectedNoRoadMarking = 0;

    internSetLightSensorRight(RoadMarkingRight);
    internSetLightSensorLeft(RoadMarkingLeft);

    calibrateRoadMarkingColour();

    internSetLightSensorLeft(FloorLeft);
    internSetLightSensorRight(FloorRight);

    TEST_ASSERT_EQUAL(expectedNoRoadMarking, detectRoadMarking());
}

// Test if readings from light sensors are saved
// Tests calibrateRoadMarkingColour and calibrateFloorColour
void testCalibrateRoadMarkingReadings ()
{
    // Expected values are light values from the sensor
    U16 expectedRoadMarkingRight = RoadMarkingRight;
    U16 expectedRoadMarkingLeft = RoadMarkingLeft;
    U16 expectedFloorRight = FloorRight;
    U16 expectedFloorLeft = FloorLeft;
    
    internSetLightSensorRight(expectedRoadMarkingRight);
    internSetLightSensorLeft(expectedRoadMarkingLeft);

    calibrateRoadMarkingColour();

    internSetLightSensorRight(expectedFloorRight);
    internSetLightSensorLeft(expectedFloorLeft);

    calibrateFloorColour();

    TEST_ASSERT_EQUAL(expectedRoadMarkingRight, colour.roadMarkingRight);
    TEST_ASSERT_EQUAL(expectedRoadMarkingLeft, colour.roadMarkingLeft);
    TEST_ASSERT_EQUAL(expectedFloorRight, colour.floorRight);
    TEST_ASSERT_EQUAL(expectedFloorLeft, colour.floorLeft);
}

void testEmptyArray()
{
    U8 expectedArray[ARRAY_SIZE];
    U8 actualArray[ARRAY_SIZE];
    int i = 0;
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        expectedArray[i] = 0;
        actualArray[i] = i;
    }

    emptyArray(actualArray);

    for (i = 0; i < ARRAY_SIZE; i++)
    {
        TEST_ASSERT_EQUAL(expectedArray[i], actualArray[i]);
    }
}