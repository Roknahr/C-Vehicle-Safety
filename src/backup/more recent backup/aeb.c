#include "aeb.h"

void aebInitialise(){
    aeb.activated = 0;
    eaeb.activated = 0;
    eaeb.distance = 0;
    aeb.lastTimeReadPath = 0;
    aeb.lastTimeReadDist = 0;
    aeb.distanceToObj1 = -1;
    aeb.distanceToObj2 = -1;
    aeb.distanceFromPath = -1;
    aeb.distanceIndex = 0;

    int i;
    for(i = 0; i < SAMPLE_COUNT; i++){
        aeb.distances[i] = -1;
    }
}

float getBrakeDistance () {
    float brakeDistance = (pow(vehicle.vFront,2) / (2 * COEF_OF_FRICTION * STD_GRAVITY)) * CM_PER_M;

    return brakeDistance;
}

float getDistanceTravelled () {

    U32 currentTime = getSysTime();

    float timeBetweenReadings = currentTime - aeb.lastTimeReadDist;
    aeb.lastTimeReadDist = currentTime;

    float distance = vehicle.vFront * (timeBetweenReadings / MS_PER_SEC) * CM_PER_M;

    return distance;
}

int updateDistanceFromPath() {

    U32 currentTime = getSysTime();

    int result = -1;
    //  fetch the first distance to distanceToObj1
    //  update variable for when distance was last read
    //  return -1 to indicate no distance was calculated
    
    if (aeb.lastTimeReadPath == 0)
    {
        aeb.distanceToObj1 = getSonarSensor();
        aeb.lastTimeReadPath = currentTime;
        result = -1;
    }
    else if (currentTime - aeb.lastTimeReadPath >= AEB_TIME_BETWEEN_READINGS)
    {
        //  time since last read is above or equal TIME_BETWEEN_READINGS
        //  read new distance, calculate distanceTravelled
        //  reset the variable for when distance was last read
        //  return distance form object
        
        aeb.distanceToObj2 = getSonarSensor();
        
        if (aeb.distanceToObj2 < 255)
        {
            float distanceTravelled = getDistanceTravelled();

            float angleToObj2 = acos((pow(aeb.distanceToObj2,2) + pow(distanceTravelled,2) - pow(aeb.distanceToObj1,2)) / (2 * aeb.distanceToObj2 * distanceTravelled));

            aeb.distanceFromPath = aeb.distanceToObj2 * sin(PI - angleToObj2);

            aeb.distanceToObj1 = aeb.distanceToObj2;
            aeb.lastTimeReadPath = currentTime;

            if(aeb.distanceFromPath <= VEHICLE_WIDTH)
            {
                result = 1;
            }
        }
    }

    return result;
}

/*
float updateDistanceFromPath() {

    U32 currentTime = getSysTime();

    float result = -1;
    //  fetch the first distance to distanceToObj1
    //  update variable for when distance was last read
    //  return -1 to indicate no distance was calculated
    
    if (aeb.lastTimeRead == 0){
        aeb.distanceToObj1 = getSonarSensor();
        aeb.lastTimeRead = currentTime;
        result = -1;
    } else if (currentTime - aeb.lastTimeRead >= AEB_TIME_BETWEEN_READINGS) {
        //  time since last read is above or equal TIME_BETWEEN_READINGS
        //  read new distance, calculate distanceTravelled
        //  reset the variable for when distance was last read
        //  return distance form object
        
        aeb.distanceToObj2 = getSonarSensor();
        float distanceTravelled = fakePow(getDistanceTravelled(),2);

        float D = fakePow(fakePow(aeb.distanceToObj1,2) + distanceTravelled - fakePow(aeb.distanceToObj2,2),2);

        result = sqrt(fakePow(aeb.distanceToObj1,2)-(D/(4 * distanceTravelled)));

        aeb.distanceToObj1 = aeb.distanceToObj2;
        // reset variable for when distance was last read
        aeb.lastTimeRead = currentTime;
        aeb.distanceFromPath = result;
    }

    if (aeb.distanceToObj2 > 254){
        result = -1;
    }

    return result;
}
*/

float getDistanceToImpact(){
    float result;
    if (updateDistanceFromPath() > -1)
    {
        result = sqrt(pow(aeb.distanceToObj2,2) - pow(aeb.distanceFromPath,2));
    }
    else
    {
        result = -1;
    }
    return result;
}

void runAEB()
{
        //If the vehicle is not moving, don't do anything.
        if (vehicle.vFront < 0.01)
            return;

         int i;
         U8 criticalDistance = 0;
         U8 veryCritical = 0;

        float brakeDistance = getBrakeDistance() + SONAR_ERROR_MARGIN;

        for (i = 0; i < SAMPLE_COUNT; i++)
        {   
            if((aeb.distances[i] <= brakeDistance) && aeb.distances[i] > -1)
            {   
                veryCritical++; // used to activate EAEB
            }  
            else if ((aeb.distances[i] <= (brakeDistance + BRAKE_SAFE_ZONE)) && aeb.distances[i] > -1)
            {
                criticalDistance++;
            }

        }

        if (criticalDistance >= 2)
        {
            aeb.activated = 1;  // diable user control of the throttle
            brake();
        }
        else if(veryCritical >= 2)
        {
            // activate EAEB
            aeb.activated = 1;  // diable user control of the throttle
            eaeb.activated = 1; // disable user control of steering
        }
}

void addDistanceToArray(float item){
    aeb.distances[aeb.distanceIndex] = item;
    aeb.distanceIndex = (aeb.distanceIndex + 1) % SAMPLE_COUNT;
}
