#include "controller.h"

float rev_pr_sec_left = 1;
float rev_pr_sec_right = 1;
S32 lastRevLeft = 0;
S32 lastRevRight = 0;
U32 oldTime = 0;
float factor = 1.0F;


void receiveBT(){
    static U8 btReceiveBuf[ARRAY_SIZE];

    readBtPacket(btReceiveBuf, ARRAY_SIZE);

    controller.steeringAmount = (S8) btReceiveBuf[0];
    controller.throttleAmount = (S8) btReceiveBuf[1];
    controller.throttleAmount *= -1; /* Invert this number, to go in the right direction*/
    controller.buttonA        = btReceiveBuf[2];
    controller.buttonB        = btReceiveBuf[3];
}

void controlMotors (S32 speed, S32 mode) {
    if (speed > MAX_SPEED_FW) 
        appliedPower = MAX_SPEED_FW;
    else if (speed < MAX_SPEED_BW)
        appliedPower = MAX_SPEED_BW;
    else
        appliedPower = speed;

    U32 currentTime  = getSysTime();
    S32 newRevLeft   = motorGetCount(LEFT_MOTOR);
    S32 newRevRight  = motorGetCount(RIGHT_MOTOR);
    rev_pr_sec_left  = newRevLeft / (float)(currentTime - oldTime);
    rev_pr_sec_right = newRevRight / (float)(currentTime - oldTime);

    factor = fabs(rev_pr_sec_left / rev_pr_sec_right);
    if (factor > 1)
    {
        motorSetSpeed(LEFT_MOTOR, (S32)(appliedPower * fabs(rev_pr_sec_right / rev_pr_sec_left)), mode);
        motorSetSpeed(RIGHT_MOTOR, appliedPower, mode);
    }
    else
    {
        motorSetSpeed(LEFT_MOTOR, appliedPower, mode);
        motorSetSpeed(RIGHT_MOTOR, (S32)(appliedPower * factor ), mode);
    }

    
/*
    displayClear(0);

    displayGotoXY(0,4);
    displayString("Left:  ");
    displayInt(newRevLeft, 0);
    
    displayGotoXY(0,5);
    displayString("Right: ");
    displayInt(newRevRight, 0);

    displayGotoXY(0,6);
    displayString("Factor: ");
    displayInt(newRevLeft-newRevRight, 0);

    displayUpdate();
*/
    oldTime = currentTime;
    lastRevLeft = newRevLeft;
    lastRevRight = newRevRight;
}

void controlSteering(){
    S32 steeringAngle;
    S32 steeringErr;
    S8 steeringAmountAdjusted;

    if(steer.turnDegreesActivated == 0) // don't turn while another task is using the motor for turning
    {
        // 10 corresponds to 0.1 on the C# side - this is the dead zone of the joystick
        if(controller.steeringAmount < JOYSTICK_LASH && controller.steeringAmount > -JOYSTICK_LASH)
        {
            steeringAmountAdjusted = 0;
        }else
        {
            steeringAmountAdjusted = controller.steeringAmount;
        }
    }
    else
    {
        steeringAmountAdjusted = steer.turnDegrees;
    }

    /* steering control */
    steeringAngle = motorGetCount(STEERING_MOTOR);
    steeringErr = (STEERING_LIMIT * steeringAmountAdjusted) / 100 - steeringAngle;
    
    appliedSteering = STEERING_P_GAIN * steeringErr;
    
    motorSetSpeed(STEERING_MOTOR, appliedSteering, 1);
    
}

S8 getSteeringAmount(){
    return controller.steeringAmount;
}

S8 getThrottleAmount(){
    return controller.throttleAmount;
}

U8 getButtonA(){
    return controller.buttonA;
}

U8 getButtonB(){
    return controller.buttonB;
}

void turnDegrees(S32 degrees) // remember to set turnDegreeActivated = 1 before and  = 0 after call!
{

    float deg = degrees;

    if(deg > 40)
    {
        deg = 40;
    }
    else if(deg < -40)
    {
        deg = -40;
    }

    steer.turnDegrees = (S32)(deg * 2.5);
}

void initTurnStruct()
{
    steer.turnDegrees = 0;
    steer.turnDegreesActivated = 0;
}
