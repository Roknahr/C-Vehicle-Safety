#include "controller.h"
#include "unity.h"
#include "datalog.h"
#include "m_nxt_interface.h"

//This function is called before each test function
void setUp () {

}

//This function is called after each test function
void tearDown () {

}

void testCreateDatalogArray1 () 
{
    /* 13 bytes for the data logging array */

    U32 time = 2216; // 4 bytes for time cell
    vehicle.vFront = 0.4; // 2 bytes for front wheel degree change 
    vehicle.vBack = 0.4; // 2 bytes for back wheel degree change 
    appliedPower = 100; // 1 byte for applied power
    appliedSteering = -120; // 4 bytes for applied steering

    internSetTime(time);

    unsigned char * arrayData = createDatalogArray();

    U32 *t = &arrayData[0];
    S16 *fdeg = &arrayData[4];
    S16 *bdeg = &arrayData[6];
    S8 *powa = &arrayData[8];
    S32 *steer = &arrayData[9];

    // Tests
    TEST_ASSERT_EQUAL_UINT32(time, *t);
    TEST_ASSERT_EQUAL_INT16((S16)(vehicle.vFront * 100), *fdeg);
    TEST_ASSERT_EQUAL_INT16((S16)(vehicle.vBack * 100), *bdeg);
    TEST_ASSERT_EQUAL_INT8(appliedPower, *powa);
    TEST_ASSERT_EQUAL_INT32(appliedSteering, *steer);

}

void testCreateDatalogArray2 () 
{
    /* 13 bytes for the data logging array */

    U32 time = 100; // 4 bytes for time cell
    vehicle.vFront = 1.2; // 2 bytes for front wheel degree change 
    vehicle.vBack = 1.345; // 2 bytes for back wheel degree change 
    appliedPower = -50; // 1 byte for applied power
    appliedSteering = 60; // 4 bytes for applied steering

    internSetTime(time);

    unsigned char * arrayData = createDatalogArray();

    U32 *t = &arrayData[0];
    S16 *fdeg = &arrayData[4];
    S16 *bdeg = &arrayData[6];
    S8 *powa = &arrayData[8];
    S32 *steer = &arrayData[9];

    // Tests
    TEST_ASSERT_EQUAL_UINT32(time, *t);
    TEST_ASSERT_EQUAL_INT16((S16)(vehicle.vFront * 100), *fdeg);
    TEST_ASSERT_EQUAL_INT16((S16)(vehicle.vBack * 100), *bdeg);
    TEST_ASSERT_EQUAL_INT8(appliedPower, *powa);
    TEST_ASSERT_EQUAL_INT32(appliedSteering, *steer);

}

void testSendData () 
{
    /* 13 bytes for the data logging array */

    U32 time = 100; // 4 bytes for time cell
    vehicle.vFront = 1200; // 2 bytes for front wheel degree change 
    vehicle.vBack = 1345; // 2 bytes for back wheel degree change 
    appliedPower = -50; // 1 byte for applied power
    appliedSteering = 60; // 4 bytes for applied steering
    int i;

    internSetTime(time);

    U8 *sentData = createDatalogArray();

    sendData();

    U8 *recievedData = internGetBufferP();
    
    //Must be equal to current packet length
    TEST_ASSERT_EQUAL(13, internGetBufLen());

    TEST_ASSERT_EQUAL_UINT8_ARRAY(sentData, recievedData, internGetBufLen());
}

