#include "aeb.h"
#include <stdio.h>

void aebInitialise(){
    aeb.activated = 0;
    aeb.lastTimeRead = 0;
    aeb.distanceToObj1 = -1;
    aeb.distanceToObj2 = -1;
    aeb.distanceFromPath = -1;
    aeb.distanceIndex = 0;

    int i;
    for(i = 0; i < SAMPLE_COUNT; i++){
        aeb.distances[i] = -1;
    }
}

float fakePow(float vFront, int fakePow)
{
    int i = 0;
    float res = vFront;

    for(i = 1; i < fakePow; i++)
    {
        res *= vFront;
    }

    return res;
}

float fakeAcos(float x) 
{
   return (-0.69813170079773212 * x * x - 0.87266462599716477) * x + 1.5707963267948966;
}

float fakeSin(float x)
{
  float res=0, pow=x, fact=1;
  for(int i=0; i<5; ++i)
  {
    res+=pow/fact;
    pow*=x*x;
    fact*=(2*(i+1))*(2*(i+1)+1);
  }

  return res;
}

float getBrakeDistance () {
    float brakeDistance = fakePow(vehicle.vFront,2) / (2 * COEF_OF_FRICTION * STD_GRAVITY) * CM_PER_M;

    return brakeDistance;
}

float getDistanceTravelled () {
    float distance = vehicle.vFront * (AEB_TIME_BETWEEN_READINGS / MS_PER_SEC);

    return distance * CM_PER_M;
}

int updateDistanceFromPath() {

    U32 currentTime = getSysTime();

    int result = -1;
    //  fetch the first distance to distanceToObj1
    //  update variable for when distance was last read
    //  return -1 to indicate no distance was calculated
    
    if (aeb.lastTimeRead == 0)
    {
        aeb.distanceToObj1 = getSonarSensor();
        aeb.lastTimeRead = currentTime;
        result = -1;
    }
    else if (currentTime - aeb.lastTimeRead >= AEB_TIME_BETWEEN_READINGS)
    {
        //  time since last read is above or equal TIME_BETWEEN_READINGS
        //  read new distance, calculate distanceTravelled
        //  reset the variable for when distance was last read
        //  return distance form object
        
        aeb.distanceToObj2 = getSonarSensor();
        
        if (aeb.distanceToObj2 < 255)
        {
            float distanceTravelled = getDistanceTravelled();

            float angleToObj2 = fakeAcos((fakePow(aeb.distanceToObj2,2) + fakePow(distanceTravelled,2) - fakePow(aeb.distanceToObj1,2)) / (2 * aeb.distanceToObj2 * distanceTravelled));

            aeb.distanceFromPath = aeb.distanceToObj2 * (fakeSin(PI - angleToObj2));

            aeb.distanceToObj1 = aeb.distanceToObj2;
            aeb.lastTimeRead = currentTime;

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
        result = sqrt(fakePow(aeb.distanceToObj2,2) - fakePow(aeb.distanceFromPath,2));
    }
    else
    {
        result = -1;
    }
    return result;
}

void runAEB()
{
         int i;
         U8 criticalDistance = 0;
         U8 veryCritical = 0;

        float brakeDistance = getBrakeDistance();

        /*if (impact <= (brakeDistance + BRAKE_SAFE_ZONE + SONAR_ERROR_MARGIN) && impact > -1)
        {
            aeb.activated = 1;
        }*/

        for (i = 0; i < SAMPLE_COUNT; i++)
        {     
            if ((aeb.distances[i] <= (brakeDistance + BRAKE_SAFE_ZONE + SONAR_ERROR_MARGIN)) && aeb.distances[i] > -1){
                criticalDistance++;
            }else if((aeb.distances[i] <= (brakeDistance + SONAR_ERROR_MARGIN)) && aeb.distances[i] > -1)
            {   
                veryCritical++; // used to activate EAEB
            }
        }

        if (criticalDistance >= 2)
        {
            aeb.activated = 1;
        }else if(veryCritical >= 2)
        {
            // activate EAEB
            aeb.activated = 1; // diable user control of the vehicle
            runEAEB();
        }
}

void addDistanceToArray(float item){
    aeb.distances[aeb.distanceIndex] = item;
    aeb.distanceIndex = (aeb.distanceIndex + 1) % SAMPLE_COUNT;
}
