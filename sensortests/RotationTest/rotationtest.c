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
#define ROTATION_SENSOR  NXT_PORT_S3
#define MOTOR            NXT_PORT_C
#define REV_COUNT        500
#define TEST_COUNT       10


typedef struct RotationSensor
{
    S16 ticks;
    S16 secondToLastTick;
    S16 lastTick;
} RotationSensor;
RotationSensor rotationSensor;

float motorRevCount;
float sensorRevCount;
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
    ecrobot_set_RCX_power_source(ROTATION_SENSOR);
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

S16 convertRawDataToTicks(S16 rawData)
{
    if(950 < rawData && rawData < 1050)
    {
        return 0;
    }
    else if(500 < rawData && rawData < 575)
    {
        return 1;
    }
    else if (300 < rawData && rawData < 400)
    {
        return 2;
    }
    else if (700 < rawData && rawData < 850)
    {
        return 3;
    }
    else
    {
        return -1;
    }

    //TODO: Error handling for out of bounds input?
}

void updateSpeedometerData()
{
    S16 rawData = ecrobot_get_RCX_sensor(ROTATION_SENSOR);
    S16 currentTick = convertRawDataToTicks(rawData);

    // Handling bad data from rotation sensor
    if (currentTick == -1)
    {
        currentTick = rotationSensor.lastTick;
    }

    // TODO: CREATE UNIT TEST
    // TODO: Credit to other group in the report!
    if((currentTick+2) % 4 == rotationSensor.secondToLastTick)
    {
        if ((currentTick+1) % 4 == rotationSensor.lastTick)
        {
            rotationSensor.ticks++;
            rotationSensor.secondToLastTick = rotationSensor.lastTick;
        }
        else if ((currentTick+3) % 4 == rotationSensor.lastTick)
        {
            rotationSensor.ticks--;
            rotationSensor.secondToLastTick = rotationSensor.lastTick;
        }
    }
    rotationSensor.lastTick = currentTick;
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
    nxt_motor_set_count(MOTOR, 0);
    rotationSensor.ticks = 0;
    rotationSensor.secondToLastTick = 0;
    rotationSensor.lastTick = 0;
    testStarted = 0;
    motorRevCount = 0;
    sensorRevCount = 0;
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
    display_string("Motor:  ");
    displayFloat(motorRevCount);
    display_goto_xy(0,4);
    display_string("Sensor: ");
    displayFloat(sensorRevCount);

    if (!testStarted) {
        testStarted = ecrobot_is_ENTER_button_pressed();
    } 
    else {
        if (testProgress == TEST_COUNT) {
            nxt_motor_set_speed(MOTOR, 0, 0);
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
        else if (motorRevCount < REV_COUNT) {
            nxt_motor_set_speed(MOTOR, 100, 1);
            updateSpeedometerData();
            motorRevCount = (nxt_motor_get_count(MOTOR) / 360.0) * 5;
            sensorRevCount = rotationSensor.ticks / 16.0;
        } 
        else {
            nxt_motor_set_speed(MOTOR, 0, 1);
            systick_wait_ms(1000);
            testResults[testProgress] = sensorRevCount;
            testProgress++;
            nxt_motor_set_count(MOTOR, 0);
            rotationSensor.ticks = 0;
            rotationSensor.secondToLastTick = 0;
            rotationSensor.lastTick = 0;
            sensorRevCount = 0;
            motorRevCount = 0;
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
