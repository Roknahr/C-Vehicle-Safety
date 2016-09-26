
#include "kernel.h"
#include "kernel_id.h"
#include <stdio.h>
#include "ecrobot_interface.h"
#include <math.h>
#include "nxt_interface.h"
#include "speedometer.h"

/* Task Declarations */
DeclareCounter(SysTimerCnt);
// DeclareTask(InitializeTask);
DeclareTask(PrintTask);
DeclareTask(ReadRawDataTask);
DeclareTask(CalculateVehicleSpeedTask);


/* Definitions */


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
    ecrobot_set_RCX_power_source(PORT_3);
    initialiseTickDataArray();
 }

// /* Run when NXT is shut down */
 void ecrobot_device_terminate()
 {
    ecrobot_term_RCX_power_source(PORT_3);
 }


TASK(PrintTask)
{
    displayClear(0);
    displayGotoXY(0,0);
    displayString("Speed value: ");
    displayGotoXY(0,1);
    displayInt(vehicle.velocity * 1000, 0);
    displayUpdate();

    TerminateTask();
}

TASK(ReadRawDataTask)
{
    tickDataArray[arrayCounter] = getAngleSensor();

    displayGotoXY(0,6);
    displayString("Previous data:");
    displayGotoXY(0,7);
    displayInt(convertRawDataToTicks(tickDataArray[arrayCounter]),1);
    displayUpdate();

    arrayCounter = (arrayCounter + 1) % 10;



    TerminateTask();
}

TASK(CalculateVehicleSpeedTask)
{
    vehicle.velocity = (calculateAverageTicks() * WHEEL_DIAMETER * PI) * (1000/*1sek*//40/*scheduler*/);

    TerminateTask();
}
