
#include "kernel.h"
#include "kernel_id.h"
#include <stdio.h>
#include "ecrobot_interface.h"


/* Task Declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(InitializeTask);
DeclareTask(DriveTask);

/* Definitions */
#define SPEED_SENSOR       NXT_PORT_S3

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
    ecrobot_set_RCX_power_source(SPEED_SENSOR);
}

/* Run when NXT is shut down */
void ecrobot_device_terminate()
{

    ecrobot_term_RCX_power_source(SPEED_SENSOR);
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : InitializeTask                                                 */
/* Priority: 3                                                              */
/* Type    : EXTENDED TASK                                                  */
/* Schedule: non-preemptive                                                 */
/*--------------------------------------------------------------------------*/

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
    S16 lightValue = ecrobot_get_RCX_sensor(SPEED_SENSOR);

    /* Clear display buffer before filling in new data. 0 = do not update display. */
    display_clear(0);

    /* Display data from gamepad */
    display_goto_xy(0,4);
    display_string("Speed value: ");
    display_goto_xy(0,5);
    display_int(lightValue, 0);
    

    /* Update display from buffer */
    display_update();

    TerminateTask();
}

/*

1st 00.00
1022-1023


2nd 00.45
544-545


3rd 01.15
339


4th 01.45
786

5th 03:00
1022
*/
