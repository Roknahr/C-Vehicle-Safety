
#include "kernel.h"
#include "kernel_id.h"
#include <stdio.h>
#include "ecrobot_interface.h"


/* Task Declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(InitializeTask);
DeclareTask(DriveTask);

/* Definitions */
#define MOTOR_RIGHT        NXT_PORT_B
#define MOTOR_LEFT         NXT_PORT_C
#define LIGHT_SENSOR       NXT_PORT_S3

static U8 drive = 1;

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
    ecrobot_set_light_sensor_active(LIGHT_SENSOR);
}

/* Run when NXT is shut down */
void ecrobot_device_terminate()
{
    nxt_motor_set_speed(MOTOR_RIGHT, 0, 1);
    nxt_motor_set_speed(MOTOR_LEFT, 0, 1);
    ecrobot_set_light_sensor_inactive(LIGHT_SENSOR);
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
    // nxt_motor_set_speed(PORT, speed, brake / float)
    nxt_motor_set_speed(MOTOR_RIGHT, 0, 1);
    nxt_motor_set_speed(MOTOR_LEFT, 0, 1);

    // nxt_motor_set_count(PORT, count in degrees)
    nxt_motor_set_count(MOTOR_RIGHT, 0);
    nxt_motor_set_count(MOTOR_LEFT, 0);


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
TASK(DriveTask)
{
    U16 lightValue = ecrobot_get_light_sensor(LIGHT_SENSOR);
    U8 touch_sensor = ecrobot_get_touch_sensor(NXT_PORT_S4);

    /* Clear display buffer before filling in new data. 0 = do not update display. */
    display_clear(0);

    /* Display data from gamepad */
    display_goto_xy(0,4);
    display_string("Light value: ");
    display_int(lightValue, 0);
    
    display_goto_xy(0,5);
    display_string("STATUS: ");

    if (touch_sensor == 1){
        drive = 1;
    }

    /* Throttle control */
    if (lightValue < 680 && drive == 1)
    {
        nxt_motor_set_speed(MOTOR_RIGHT, -100, 0);
        nxt_motor_set_speed(MOTOR_LEFT, -100, 0);

        display_string("DRIVE!!!");
    }
    else
    {
        drive = 0;
        nxt_motor_set_speed(MOTOR_RIGHT, 0, 1);
        nxt_motor_set_speed(MOTOR_LEFT, 0, 1);
        display_string("BRAKE!!! ");
    }

    /* Update display from buffer */
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
