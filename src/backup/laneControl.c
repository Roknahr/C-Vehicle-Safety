#include "laneControl.h"

U16 roadMarkingColourRight = 0;
U16 roadMarkingColourLeft = 0;
U16 floorColourRight = 0;
U16 floorColourLeft = 0;

void laneControl () 
{
    U8 tempRoadMarking = detectRoadMarking();

    if (tempRoadMarking > 0)
    {
        adjustVehicle(tempRoadMarking);
    }
}

//Adskilt funktion - Skal kun køres 1 gang!
void calibrateLaneControlSensor ()
{
        //wait button press
        calibrateRoadMarkingColour();
        //wait button press
        calibrateFloorColour();    
}

void calibrateRoadMarkingColour ()
{
    roadMarkingColourRight = getLightSensorRight();
    //wait button press
    roadMarkingColourLeft = getLightSensorLeft();
}

void calibrateFloorColour ()
{
    floorColourRight = getLightSensorRight();
    //wait button press
    floorColourLeft = getLightSensorLeft();
}

U8 detectRoadMarking () 
{
    if (getLightSensorLeft() >= (roadMarkingColourLeft - COLOUR_SAFETY) && getLightSensorLeft() <= (roadMarkingColourLeft + COLOUR_SAFETY))
    {
        return LEFT_ROADMARKING_VALUE;
    }
    else if (getLightSensorRight() >= (roadMarkingColourRight - COLOUR_SAFETY) && getLightSensorRight() <= (roadMarkingColourRight + COLOUR_SAFETY))
    {
        return RIGHT_ROADMARKING_VALUE;
    }
    else
    {
        return 0;
    }
}

void adjustVehicle (U8 roadMarking)
{
    S32 turnAngle = calculateTurnAngle(roadMarking);;

    if(turnAngle != 0)
    {
        turnDegreesActivated = 1;

        turnDegrees(turnAngle);

        turnDegreesActivated = 0;
    }

}

//Skal udvides med bedre algoritme til udregning af turnAngle.
S32 calculateTurnAngle(U8 roadMarking)
{
    if (roadMarking == LEFT_ROADMARKING_VALUE)
    {
        //Lav bedre algoritme
        return -40;
    }
    else if (roadMarking == RIGHT_ROADMARKING_VALUE)
    {
        //Lav bedre algoritme
        return 40;
    }
    else
    {
        return 0;
    }


}