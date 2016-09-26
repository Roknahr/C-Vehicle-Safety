#include "speedometer.h"


void speedometerInitialise(){
    int i; 

    vehicle.backLastTime = 0;
    vehicle.frontLastTime = 0;
    vehicle.vFront = 0;
    vehicle.vBack  = 0;
    vehicle.vBackRounds = 0;
    vehicle.vFrontRounds = 0;
    tickCounter.oldIndexFront = 0;
    tickCounter.newIndexFront = -1;
    tickCounter.oldIndexBack = 0;
    tickCounter.newIndexBack = -1;

    for (i = 0; i < TICK_ARRAY_SIZE; i++) {
        tickCounter.frontDegreesArray[i] = 0;
        tickCounter.backDegreesArray[i] = 0;
    }

    //initialiseTickDataArray();
}

void updateSpeedometerData()
{

    S16 rawData = getRotationSensor();
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

    addToArrayFront(rotationSensor.ticks * (360 / 16.0));
    addToArrayBack(-motorGetCount(PORT_B));
}

void calculateVelocity()
{
    // TODO: We should not rely upon the task being executed within every 40 ms. This should be dynamic and adjusted by the counter

    /* BackWheel speedometer */
    S32 degreeDiffBack = tickCounter.backDegreesArray[tickCounter.newIndexBack] 
                            - tickCounter.backDegreesArray[tickCounter.oldIndexBack];
    float degreePerMsBack = degreeDiffBack / 250.0;
    float roundsPerSecBack = (degreePerMsBack * 1000) / 360.0;
    float metersPerSecondBack = roundsPerSecBack * WHEEL_CIRC * GEAR_RATIO;
    vehicle.vBack = metersPerSecondBack;

    /* FrontWheel speedometer */
    float degreeDiff = tickCounter.frontDegreesArray[tickCounter.newIndexFront] 
                        - tickCounter.frontDegreesArray[tickCounter.oldIndexFront];
    float degreePerMs = degreeDiff / 250.0;
    float roundsPerSec = (degreePerMs * 1000) / 360.0;
    vehicle.vFront = roundsPerSec * WHEEL_CIRC;

}

void addToArrayFront(float item){
    tickCounter.newIndexFront = tickCounter.oldIndexFront;
    tickCounter.oldIndexFront = (tickCounter.oldIndexFront+1) % TICK_ARRAY_SIZE;
    tickCounter.frontDegreesArray[tickCounter.newIndexFront] = item;
}

void addToArrayBack(S32 item){
    tickCounter.newIndexBack = tickCounter.oldIndexBack;
    tickCounter.oldIndexBack = (tickCounter.oldIndexBack+1) % TICK_ARRAY_SIZE;
    tickCounter.backDegreesArray[tickCounter.newIndexBack] = item;
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

/*
void initialiseTickDataArray()
{
    U8 j = 0;

    for(j = 0; j <= 9 ; j = j + 1)
    {
        tickDataArray[j] = 0;
    }
}

void setFrontWheelVelocity(){
    if (speedometerInitialised == 0) return;

    U32 currentTime = getSysTime();

    if (vehicle.frontLastTime == 0){
        vehicle.vFrontRounds  = averageTicksInRounds();
        vehicle.frontLastTime = currentTime;
    } else if (currentTime - vehicle.frontLastTime >= SPEED_TIME_BETWEEN_READINGS) {
        
        float newRounds = averageTicksInRounds();

        float roundsSinceLastReading = newRounds - vehicle.vFrontRounds;

        float roundsPerMin = roundsSinceLastReading / (currentTime - vehicle.frontLastTime) * MS_PER_MIN;

        vehicle.vFront = roundsPerMin * WHEEL_CIRC * SEC_PER_MIN;
        
        vehicle.frontLastTime = 0;
    }
}

float averageTicksInRounds()
{
    float averageNumberOfTicks = 0;
    S16 totalNumberOfTicks = 0;
    U16 i = 0;

    for(i = 1; i <= arrayCounter; i = i + 1)
    {
        totalNumberOfTicks = totalNumberOfTicks + ((4 + (convertRawDataToTicks(tickDataArray[i]) - convertRawDataToTicks(tickDataArray[i-1]))) % 4);
    }

    averageNumberOfTicks = totalNumberOfTicks / 9.0;

    return averageNumberOfTicks / TICKS_PER_ROUND;
}



float getMaxMotorRotationSpeedInRounds(){
    S32 leftCount = motorGetCount(LEFT_MOTOR);
    S32 rightCount = motorGetCount(RIGHT_MOTOR);
    S32 max;

    if (leftCount > rightCount){
        max = leftCount;
    } else {
        max = rightCount;
    }

    return degreesToRounds(max);
}

float degreesToRounds(S32 degrees){
    return degrees / 360.0;
}

float getVelocityMS(float roundsPerMin){
    float result = (roundsPerMin * GEAR_RATIO * WHEEL_CIRC) / SEC_PER_MIN;

    return result;
}

void setBackWheelVelocity(){
    // speedometer module has not been initialised -> Short circuit
    if (speedometerInitialised == 0) return;

    U32 currentTime = getSysTime();

    if (vehicle.backLastTime == 0){
        vehicle.vBackRounds  = getMaxMotorRotationSpeedInRounds();
        vehicle.backLastTime = currentTime;
    } else if (currentTime - vehicle.backLastTime >= SPEED_TIME_BETWEEN_READINGS) {
        
        float newRounds = getMaxMotorRotationSpeedInRounds();

        float roundsSinceLastReading = newRounds - vehicle.vBackRounds;

        float roundsPerMin = roundsSinceLastReading / (currentTime - vehicle.backLastTime) * MS_PER_MIN;

        vehicle.vBack = getVelocityMS(roundsPerMin);
        
        vehicle.backLastTime = 0;
        motorSetCount(LEFT_MOTOR, 0);
        motorSetCount(RIGHT_MOTOR, 0);
    }

*/
    
/*
    float ticksPerSec = motorGetCount(RIGHT_MOTOR) * (1000 / (currentTime - vehicle.backLastTime));
    float roundsPerSeconds = (ticksPerSec / 360);
    float metersPerSecond = roundsPerSeconds * WHEEL_CIRC;
    vehicle.vBack = metersPerSecond;

    vehicle.backLastTime = currentTime;
    motorSetCount(RIGHT_MOTOR, 0);
    motorSetCount(LEFT_MOTOR, 0);
}

*/
