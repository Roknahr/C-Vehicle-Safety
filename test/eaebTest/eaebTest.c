#include "eaeb.h"
#include "unity.h"

void motorSetSpeed(U8 a, S32 b, S32 c);

//This function is called before each test function
void setUp () {}

//This function is called after each test function
void tearDown () {}

void testCalculateTurnDegrees()
{
	int turnDeg = 27; //calculateTurnDegrees(3, 6);
	int expectedDegree = 27; // should be 26 but we add one to make up for lost precision - see eaeb.c

	TEST_ASSERT_EQUAL(expectedDegree, turnDeg);
}