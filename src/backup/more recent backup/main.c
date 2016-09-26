#include "kernel.h"
#include "kernel_id.h"
#include "nxt_interface.h"
#include "controller.h"
#include "datalog.h"
#include "aeb.h"
#include "speedometer.h"
#include "ecrobot_interface.h"
#include "constants.h"
#include "abs.h"
#include "laneControl.h"

/* Task and counter declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(InitializeTask);
DeclareTask(DataLoggingTask);
DeclareTask(AEBTask);
DeclareTask(ControllerTask);
DeclareTask(ABSTask);
DeclareTask(ReadRawDataTask);
DeclareTask(CalculateVehicleSpeedTask);
DeclareTask(LaneControl);
DeclareResource(RES_STEERING_MOTOR);
DeclareResource(RES_OVERRIDE_BT);

static U8 drive = 1;
float brakeVelo = 0;

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
    initRotationSensor();
    initBtConnection();
    initSonarSensor();
    aebInitialise();
    initTurnStruct();
    speedometerInitialise();
    initLightSensor();
}

/* Run when NXT is shut down */
void ecrobot_device_terminate()
{ 
    // nxt_motor_set_speed(PORT, speed, brake on / off)
    motorSetSpeed(STEERING_MOTOR, 0, 1);
    motorSetSpeed(RIGHT_MOTOR, 0, 1);
    motorSetSpeed(LEFT_MOTOR, 0, 1);
    termLightSensor();

    termRotationSensor();
    termBtConnection();
    termSonarSensor();
}

TASK(InitializeTask)
{
    motorSetSpeed(STEERING_MOTOR, 0, 1);
    motorSetSpeed(RIGHT_MOTOR, 0, 1);
    motorSetSpeed(LEFT_MOTOR, 0, 1);

    // nxt_motor_set_count(PORT, count in degrees)
    motorSetCount(STEERING_MOTOR, 0);
    motorSetCount(RIGHT_MOTOR, 0);
    motorSetCount(LEFT_MOTOR, 0);

    TerminateTask();
}

TASK(ControllerTask)
{
    //U8 touch_sensor = ecrobot_get_touch_sensor(NXT_PORT_S4);
    //U16 lightValue = getLightSensorLeft();

    GetResource(RES_OVERRIDE_BT);
    receiveBT();
    ReleaseResource(RES_OVERRIDE_BT);
    
    S32 throttle = -100;// getThrottleAmount();
    S32 steering = getSteeringAmount();
    U8 btnA = getButtonA();
    U8 btnB = getButtonB();

    GetResource(RES_STEERING_MOTOR);
    controlSteering();

    if (aeb.activated == 0)
    {
        controlMotors(throttle, BRAKE_OFF);
    }

    ReleaseResource(RES_STEERING_MOTOR);

    // else 
    // {

    //     if (brakeVelo == 0){
    //         brakeVelo = vehicle.vFront;
    //     }
    //     controlMotors(0, BRAKE_ON);
    // }

    TerminateTask();
}

TASK(ABSTask)
{
    if (drive == 0)
    {
        brake();
    }

    TerminateTask();
}

TASK(DataLoggingTask)
{
    sendData();

    TerminateTask();
}



TASK(AEBTask)
{
    // displayClear(0);
    // displayGotoXY(5,3);
    // displayInt(getSonarSensor(), 0);
    // displayUpdate();

    if(aeb.activated || eaeb.activated)
    {

        // Execute eaeb if it is activated

        if (eaeb.activated)
        {
            executeEAEB();
        }

        // Allow the user to reset aeb / eaeb if it is activated
        U8 btnB = getButtonB();
        if (btnB == BUTTON_PRESSED)
        {
            aebInitialise();
            brakeVelo = 0;
        }
    }
    else
    {
        // Determine if aeb / eaeb should be activated
        float dti = getDistanceToImpact();
        addDistanceToArray(dti);
        runAEB();
    }

    // displayClear(0);
    // displayGotoXY(5,3);
    // displayInt(vehicle.vFront*100, 0);
    // displayGotoXY(5,4);
    // displayInt(getDistanceTravelled(), 0);
    // displayGotoXY(5,5);
    // displayInt(dti*100, 0);
    // displayGotoXY(5,6);
    // displayInt(brakeVelo*100, 0);
    // displayUpdate();

    TerminateTask();
}


TASK(CalculateVehicleSpeedTask)
{
    calculateVelocity();

    TerminateTask();
}


TASK(ReadRawDataTask)
{
    updateSpeedometerData();

    TerminateTask();
}

 TASK(LaneControlTask)
 {
//     /* If sensors are not calibrated, calibrate them */
//     if(calibratedLaneControl != LANE_CONTROL_CALIBRATED)
//     {
//         //displayClear(0);
//         calibrateLaneControlSensor();
//         calibratedLaneControl = LANE_CONTROL_CALIBRATED;
//     }

//     /* Checks for road marking */
//     U8 tempRoadMarking = detectRoadMarking();

//     displayGotoXY(11,0);
//     displayString("Side:");
//     displayGotoXY(11,1);
//     if(tempRoadMarking == 1)
//     {
//         displayString("Left ");
//     }
//     else if(tempRoadMarking == 2)
//     {
//         displayString("Right");
//     }
//     else
//     {
//         displayString("None ");
//     }
//     displayGotoXY(11,3);
//     displayString("ReadR:");
//     displayGotoXY(13,4);
//     displayInt((int)getLightSensorRight(), 0);
//     displayGotoXY(11,5);
//     displayString("ReadL:");
//     displayGotoXY(13,6);
//     displayInt((int)getLightSensorLeft(), 0);
//     displayUpdate();

//     /* If road marking detected, adjust vehicle */
//     if (tempRoadMarking > 0)
//     {
//         GetResource(RES_STEERING_MOTOR);
//         GetResource(RES_OVERRIDE_BT);

//         adjustVehicle(tempRoadMarking);

//         ReleaseResource(RES_OVERRIDE_BT);
//         ReleaseResource(RES_STEERING_MOTOR);
//     }
    
     TerminateTask();
 }