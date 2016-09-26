#include "kernel.h"
#include "kernel_id.h"
#include "nxt_interface.h"
#include "controller.h"
#include "datalog.h"
#include "aeb.h"
#include "speedometer.h"
#include "ecrobot_interface.h"
#include "constants.h"

/* Task and counter declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(InitializeTask);
DeclareTask(ControllerTask);
DeclareTask(ABSTask);
DeclareTask(DataLoggingTask);
DeclareTask(AEBTask);
DeclareTask(ReadRawDataTask);
DeclareTask(CalculateVehicleSpeedTask);


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
    motorSetSpeed(STEERING_MOTOR, 0, BRAKE_ON);
    motorSetSpeed(RIGHT_MOTOR, 0, BRAKE_ON);
    motorSetSpeed(LEFT_MOTOR, 0, BRAKE_ON);
    termLightSensor();

    termRotationSensor();
    termBtConnection();
    termSonarSensor();
}

TASK(InitializeTask)
{
    motorSetSpeed(STEERING_MOTOR, 0, BRAKE_ON);
    motorSetSpeed(RIGHT_MOTOR, 0, BRAKE_ON);
    motorSetSpeed(LEFT_MOTOR, 0, BRAKE_ON);

    // nxt_motor_set_count(PORT, count in degrees)
    motorSetCount(STEERING_MOTOR, 0);
    motorSetCount(RIGHT_MOTOR, 0);
    motorSetCount(LEFT_MOTOR, 0);

    TerminateTask();
}

TASK(DataLoggingTask)
{
    sendData();

    TerminateTask();
}

TASK(ControllerTask)
{
    //U8 touch_sensor = ecrobot_get_touch_sensor(NXT_PORT_S4);
    U16 lightValue = getLightSensorLeft();

    receiveBT();

    S32 throttle = -100;//getThrottleAmount();
    S32 steering = getSteeringAmount();
    U8 btnA = getButtonA();
    U8 btnB = getButtonB();



 /* 
    displayGotoXY(2,1);
    displayString("Throttle: ");
    displayInt(throttle, 0);
    displayGotoXY(2,2);
    displayString("Steering: ");
    displayInt(steering, 0);
    displayGotoXY(4,3);
    displayString("btnA: ");
    displayInt(btnA, 0);
    displayGotoXY(4,4);
    displayString("btnB: ");
    displayInt(btnB, 0);
    displayUpdate();
*/
    /* Display data from gamepad */
  
    // displayClear(0);
    // display_goto_xy(0,4);
    // display_string("Light value: ");
    // display_int(lightValue, 0);
    
    // displayGotoXY(2,5);
    // displayString("ABS: ");
    // displayInt(getThrottleAmount(), 0);
    

    controlSteering();


    if (aeb.activated == 0)
    {
        controlMotors(throttle, BRAKE_OFF);
    }
    else 
    {

        if (brakeVelo == 0){
            brakeVelo = vehicle.vFront;
        }
        controlMotors(0, BRAKE_ON);
    }



    // displayGotoXY(2,6);
    // if (touch_sensor == BUTTON_PRESSED){
    //     drive = 1;
    //     brakeVelo = 0;
    // }
     
    // if (lightValue > 600 && drive == 1)
    // {
    //     controlMotors(throttle, BRAKE_OFF);
    // } else {
    //     if (brakeVelo == 0)
    //         brakeVelo = vehicle.vFront;

    //     drive = 0;
    // }

    //displayInt(brakeVelo*100, 0);

    //displayUpdate();

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

TASK(AEBTask)
{
    U8 touch_sensor = ecrobot_get_touch_sensor(NXT_PORT_S4);
    if (touch_sensor == BUTTON_PRESSED){
        aebInitialise();
        brakeVelo = 0;
    }

    //float dti = 0.0;
    float dti = getDistanceToImpact();
    addDistanceToArray(dti);
    runAEB();

    displayClear(0);
    displayGotoXY(5,3);
    displayInt(vehicle.vFront*100, 0);
    displayGotoXY(5,4);
    displayInt(pow(3,3), 0); //displayInt(aeb.activated, 0);
    displayGotoXY(5,5);
    displayInt(dti*100, 0);
    displayGotoXY(5,6);
    displayInt(brakeVelo*100, 0);
    displayUpdate();

    TerminateTask();
}

TASK(ReadRawDataTask)
{
    updateSpeedometerData();

    TerminateTask();
}

TASK(CalculateVehicleSpeedTask)
{
    calculateVelocity();

    TerminateTask();
}
