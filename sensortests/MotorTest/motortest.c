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
#define MOTOR_LEFT  NXT_PORT_C
#define MOTOR_RIGHT NXT_PORT_B
#define REV_COUNT   1000
#define TEST_COUNT  10


float motorLeftRevCount;
float motorRightRevCount;
U8 testStarted;
U16 testProgress;
float testResults[TEST_COUNT];
float mean;
float standardDeviation;

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
}

/* Run when NXT is shut down */
void ecrobot_device_terminate()
{
}

void displayFloat(float val) {
    int decimals;
    if (val < 0){
        val = -val;
        display_string("-");
    }
    display_int(val, 0);
    display_string(",");
    decimals = (int)(val * 100)%100;
    if (decimals < 10)
        display_string("0");
    display_int(decimals, 0);
}

float calculateMean () {
    U16 i;
    U32 sum = 0;

    for (i = 0; i < TEST_COUNT; i++) {
        sum += testResults[i];
    }

    return (float)sum / TEST_COUNT;
}

float calculateSDev () {
    U16 i;
    float sum = 0;

    for (i = 0; i < TEST_COUNT; i++) {
        sum += powf(testResults[i] - mean, 2);
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
    nxt_motor_set_count(MOTOR_LEFT, 0);
    nxt_motor_set_count(MOTOR_RIGHT, 0);
    testStarted = 0;
    motorLeftRevCount = 0;
    motorRightRevCount = 0;
    testProgress = 0;
    mean = -1;
    standardDeviation = -1;

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
    display_clear(0);
    display_goto_xy(0,2);
    display_string("Progr:  ");
    display_int(testProgress, 0);
    display_goto_xy(0,3);
    display_string("MotorL: ");
    displayFloat(motorLeftRevCount);
    display_goto_xy(0,4);
    display_string("MotorR: ");
    displayFloat(motorRightRevCount);

    if (!testStarted) {
        testStarted = ecrobot_is_ENTER_button_pressed();
    } 
    else {
        if (testProgress == TEST_COUNT) {
            nxt_motor_set_speed(MOTOR_LEFT, 0, 0);
            nxt_motor_set_speed(MOTOR_RIGHT, 0, 0);
            if (mean < 0) {
                mean = calculateMean();
                standardDeviation = calculateSDev();
            }

            display_goto_xy(0, 5);
            display_string("Mean:   ");
            displayFloat(mean);
            display_goto_xy(0, 6);
            display_string("SD:     ");
            displayFloat(standardDeviation);
        }
        else if (motorLeftRevCount < REV_COUNT) {
            nxt_motor_set_speed(MOTOR_LEFT, 100, 1);
            nxt_motor_set_speed(MOTOR_RIGHT, 100, 1);
            motorLeftRevCount = nxt_motor_get_count(MOTOR_LEFT);
            motorRightRevCount = nxt_motor_get_count(MOTOR_RIGHT);
        } 
        else {
            nxt_motor_set_speed(MOTOR_LEFT, 0, 1);
            nxt_motor_set_speed(MOTOR_RIGHT, 0, 1);
            systick_wait_ms(1000);
            testResults[testProgress] = motorRightRevCount;
            testProgress++;
            nxt_motor_set_count(MOTOR_LEFT, 0);
            nxt_motor_set_count(MOTOR_RIGHT, 0);
            motorLeftRevCount = 0;
            motorRightRevCount = 0;
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
