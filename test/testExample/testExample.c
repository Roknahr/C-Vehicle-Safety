#include "testExampleSrc.h"
#include "unity.h"


U8 intern_get_port ();
S32 intern_get_mode ();
S8 intern_get_speed ();
void intern_set_count (S32 count);

//This function is called before each test function
void setUp () {

}

//This function is called after each test function
void tearDown () {

}

//These are test functions. Their name MUST start with "test"!
void testRunEngine () {
	U8 port = PORT_A;
	S32 mode = 1;
	S8 speed = 50;

	runEngine (port, mode, speed);
	TEST_ASSERT_EQUAL(port, intern_get_port()); 
	TEST_ASSERT_EQUAL(mode, intern_get_mode()); 
	TEST_ASSERT_EQUAL(speed, intern_get_speed()); 
}

void testReadEngine () {
	int port = PORT_A;
	int count = 200;

	intern_set_count(count);
	int input = readEngine (port);
	TEST_ASSERT_EQUAL(port, intern_get_port());
	TEST_ASSERT_EQUAL(count, input);
}
