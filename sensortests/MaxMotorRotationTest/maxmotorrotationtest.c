
#include "kernel.h"
#include "kernel_id.h"
#include <stdio.h>
#include "ecrobot_interface.h"
#include <math.h>


/* Task Declarations */
DeclareCounter(SysTimerCnt);
// DeclareTask(InitializeTask);
DeclareTask(DriveTask);

/* Definitions */
#define MOTOR_RIGHT        NXT_PORT_B
#define MOTOR_LEFT         NXT_PORT_C

S32 i = 0;

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

// /* Run when NXT is shut down */
 void ecrobot_device_terminate()
 {
     nxt_motor_set_speed(MOTOR_RIGHT, 0, 1);
     nxt_motor_set_speed(MOTOR_LEFT, 0, 1);
 }

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : InitializeTask                                                 */
/* Priority: 3                                                              */
/* Type    : EXTENDED TASK                                                  */
/* Schedule: non-preemptive                                                 */
/*--------------------------------------------------------------------------*/
/*TASK(InitializeTask)
{
    // nxt_motor_set_speed(PORT, speed, brake / float)
    nxt_motor_set_speed(MOTOR_RIGHT, 0, 1);
    nxt_motor_set_speed(MOTOR_LEFT, 0, 1);

    // nxt_motor_set_count(PORT, count in degrees)
    nxt_motor_set_count(MOTOR_RIGHT, 0);
    nxt_motor_set_count(MOTOR_LEFT, 0);


    TerminateTask();
}*/
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

    nxt_motor_set_speed(MOTOR_RIGHT, -100, 0);
    nxt_motor_set_speed(MOTOR_LEFT, -100, 0);
    S32 motorAngleRightTotal = ecrobot_get_motor_rev(MOTOR_RIGHT);
    S32 motorAngleLeftTotal = ecrobot_get_motor_rev(MOTOR_LEFT);
    double motorAngleRightDecimal = motorAngleRightTotal / 360;
    double motorAngleLeftDecimal = motorAngleLeftTotal / 360;
    S32 motorAngleRightDisplayInt = 0;
    S32 motorAngleRightDisplayDec = 0;
    S32 motorAngleLeftDisplayInt = 0;
    S32 motorAngleLeftDisplayDec = 0;

    i = i + 1;
    if(i>0){
        motorAngleRightDecimal = motorAngleRightDecimal/i;
        motorAngleRightDisplayInt = floor(motorAngleRightDecimal);
        motorAngleRightDisplayDec = floor(fmod(motorAngleRightDecimal,1.00)*1000);
        motorAngleLeftDecimal = motorAngleLeftDecimal/i;
        motorAngleLeftDisplayInt = floor(motorAngleLeftDecimal);
        motorAngleLeftDisplayDec = floor(fmod(motorAngleLeftDecimal,1.00)*1000);
    }
    /* Clear display buffer before filling in new data. 0 = do not update display. */
    display_clear(0);

    /* Display data from gamepad */
  /*  display_goto_xy(0,0);
    display_string("Iteration: ");*/
    display_goto_xy(0,0);
    display_int(i, 0);
    display_goto_xy(0,1);
    display_string("Right value: ");
    display_goto_xy(0,2);
    display_int(motorAngleRightTotal, 0);
    display_goto_xy(0,3);
    display_int(motorAngleRightDisplayInt, 0);
    display_int(motorAngleRightDisplayDec, 5);
    display_goto_xy(0,5);
    display_string("Left value: ");
    display_goto_xy(0,6);
    display_int(motorAngleLeftTotal, 0);
    display_goto_xy(0,7);
    display_int(motorAngleLeftDisplayInt, 0);
    display_int(motorAngleLeftDisplayDec, 5);


    // nxt_motor_set_speed(MOTOR_RIGHT, -100, 0);
    // nxt_motor_set_speed(MOTOR_LEFT, -100, 0);

    /* Update display from buffer */
    display_update();

    TerminateTask();
}
