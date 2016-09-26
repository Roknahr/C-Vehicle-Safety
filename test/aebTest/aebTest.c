#include "aeb.h"
#include "unity.h"

//This function is called before each test function
void setUp () {

}

//This function is called after each test function
void tearDown () {

}

void testAebInitialise() {
    aebInitialise();

    TEST_ASSERT_EQUAL(0, aeb.activated);
    TEST_ASSERT_EQUAL(0, aeb.lastTimeRead);
    TEST_ASSERT_EQUAL(-1, aeb.distanceToObj1);
    TEST_ASSERT_EQUAL(-1, aeb.distanceToObj2);
    TEST_ASSERT_EQUAL(-1, aeb.distanceFromPath);
    TEST_ASSERT_EQUAL(0, aeb.distanceIndex);
}

void testGetBrakeDistance () {
    vehicle.vFront = 2;
    float assumedBrakeDistance = 129;

    TEST_ASSERT_FLOAT_WITHIN(0.1, assumedBrakeDistance, getBrakeDistance());
}

void testGetDistanceTravelled () {
    vehicle.vFront = 4;
    float assumedDistance = 10;

    TEST_ASSERT_FLOAT_WITHIN(0.1, assumedDistance, getDistanceTravelled());
}

void testGetDistanceToObject () {
    U32 assumedDistance = 30;
    internSetDistance(30);
    S32 distance = getSonarSensor();
    TEST_ASSERT_EQUAL(assumedDistance, distance);
}

void testGetDistanceToObject2 () {
    S32 distance = getSonarSensor();
    TEST_ASSERT(distance >= 0 && distance <= 255);
}

void testUpdateDistanceFromPath ()
{
    aebInitialise();


    internSetTime(25); //lastTimeRead
    internSetDistance(16); //distanceToObj1

    float expectedResult = -1;
    float actualResult = updateDistanceFromPath();

    TEST_ASSERT_FLOAT_WITHIN(0.01, expectedResult, actualResult);


    internSetTime(50); //currentTime -> lastTimeRead
    internSetDistance(12); //distanceToObj2 -> distanceToObj1
    vehicle.vFront = 2.4;

    expectedResult = 1; 
    actualResult = updateDistanceFromPath();
  
    TEST_ASSERT_FLOAT_WITHIN(0.01, expectedResult, actualResult);


    internSetTime(75); //currentTime
    internSetDistance(300); //distanceToObj2
    
    expectedResult = -1;
    actualResult = updateDistanceFromPath();

    TEST_ASSERT_FLOAT_WITHIN(0.01, expectedResult, actualResult);
}

void testGetDistanceToImpact () {
    aebInitialise();

    internSetTime(25); //lastTimeRead
    internSetDistance(16); //distanceToObj1

    float expectedResult = -1;
    float actualResult = getDistanceToImpact();

    TEST_ASSERT_FLOAT_WITHIN(0.01, expectedResult, actualResult);


    internSetTime(50); //currentTime
    internSetDistance(12); //distanceToObj2
    vehicle.vFront = 2.4;
    //distanceFromPath = 10,1926

    expectedResult = 6.333317; 
    actualResult = getDistanceToImpact();
  
    TEST_ASSERT_FLOAT_WITHIN(0.01, expectedResult, actualResult);
}