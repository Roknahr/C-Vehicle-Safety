#include <math.h>
#include "kernel.h"
#include "kernel_id.h"
#include <stdio.h>
#include "ecrobot_interface.h"


/* Task Declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(InitializeTask);
DeclareTask(TestTask);

/* Definitions */
#define SONAR_SENSOR    NXT_PORT_S1
#define TOUCH_SENSOR    NXT_PORT_S2
#define TEST_COUNT      500


S32 testArray[TEST_COUNT];
U16 testProgress = 0;
float mean = -1;
float standardDeviation = -1;
U8 testStarted = 0;

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ 
    StatusType ercd;

    ercd = SignalCounter(SysTimerCnt);
    if(ercd != E_OK){
        ShutdownOS(ercd);
    }
}

/* Initialize bluetooth connection when NXT is started */
void ecrobot_device_initialize()
{
    ecrobot_init_sonar_sensor(SONAR_SENSOR);
}

/* Run when NXT is shut down */
void ecrobot_device_terminate()
{
    ecrobot_term_sonar_sensor(SONAR_SENSOR);
}

void displayFloat(float val) {
    int decimals;
    display_int(val, 0);
    display_string(",");
    decimals = (int)(val * 100)%100;
    if (decimals < 10)
        display_string("0");
    display_int(decimals, 0);
}

float calculateMean () {
    U16 i;
    S32 sum = 0;

    for (i = 0; i < TEST_COUNT; i++) {
        sum += testArray[i];
    }

    return (float)sum / TEST_COUNT;
}

float calculateSDev () {
    U16 i;
    float sum = 0;

    for (i = 0; i < TEST_COUNT; i++) {
        sum += powf(testArray[i] - mean, 2);
    }

    return sqrtf(sum / (TEST_COUNT - 1));
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : InitializeTask                                                 */
/* Priority: 3                                                              */
/* Type    : EXTENDED TASK                                                  */
/* Schedule: non-preemptive                                                 */
/*--------------------------------------------------------------------------*/
TASK(InitializeTask)
{


    TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : BluetoothTask                                                  */
/* Priority: 2                                                              */
/* Type    : EXTENDED TASK                                                  */
/* Schedule: non-preemptive                                                 */
/*--------------------------------------------------------------------------*/
TASK(TestTask)
{
    S32 measuredValue;

    display_clear(0);
    display_goto_xy(0,2);
    display_string("Start: ");
    display_int(testStarted, 0);
    display_goto_xy(0,3);
    display_string("Tests: ");
    display_int(testProgress, 0);

    if (!testStarted) {
        testStarted = ecrobot_get_touch_sensor(NXT_PORT_S2);
    } 
    else {
        if (testProgress < TEST_COUNT) {
            testArray[testProgress] = ecrobot_get_sonar_sensor(SONAR_SENSOR);
            testProgress++; 
        } 
        else {
            if (mean < 0) {
                mean = calculateMean();
                standardDeviation = calculateSDev();
            }

            display_goto_xy(0,4);
            display_string("Mean: ");
            display_goto_xy(7,4);
            displayFloat(mean, 0);
            display_goto_xy(0,5);
            display_string("SD: ");
            display_goto_xy(7,5);
            displayFloat(standardDeviation, 0);
        }
    }

    display_update();

    TerminateTask();
}



/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : DisplayTask                                                    */
/* Priority: 1                                                              */
/* Type    : EXTENDED TASK                                                  */
/* Schedule: preemptive                                                     */
/*--------------------------------------------------------------------------*/
/*
TASK(DisplayTask)
{
    //display_string("AWESOME!");
    //display_string("HELLO!");
    //display_update();

    

    TerminateTask();
}*/
