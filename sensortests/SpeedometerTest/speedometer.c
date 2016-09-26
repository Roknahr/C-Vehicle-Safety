#include "speedometer.h"
#include "nxt_interface.h"



void initialiseTickDataArray()
{
    U8 j = 0;

    for(j = 0; j <= 9 ; j = j + 1)
    {
        tickDataArray[j] = 0;
    }
}
//TASK
/*void saveTickDataToArray()
{
    tickDataArray[arrayCounter] = getAngleSensor();
    arrayCounter = (arrayCounter + 1) % 10;
}*/

//Skal køres hver 5. gang saveTickDataToArray køres.
//TASK
/*void calculateVehicleSpeed()
{
    vehicle.velocity = calculateAverageTicks() * WHEEL_DIAMETER * PI * (LARGE_GEAR / SMALL_GEAR);
}*/

float calculateAverageTicks()
{
    float averageNumberOfTicks = 0;
    S16 totalNumberOfTicks = 0;
    U16 i = 0;

    for(i = 1; i <= 9; i = i + 1)
    {
        totalNumberOfTicks = totalNumberOfTicks + ((4 + (convertRawDataToTicks(tickDataArray[i]) - convertRawDataToTicks(tickDataArray[i-1]))) % 4);
    }
    
    displayGotoXY(0,3);
    displayString("Total Ticks:");
    displayGotoXY(0,4);
    displayInt(totalNumberOfTicks,2);

    averageNumberOfTicks = totalNumberOfTicks / 9.0;

    totalNumberOfTicks = 0;

    return averageNumberOfTicks;
}

S16 convertRawDataToTicks(S16 rawData)
{
    if(950 < rawData && rawData < 1050)
    {
        return 1;
    }
    else if(500 < rawData && rawData < 575)
    {
        return 2;
    }
    else if (300 < rawData && rawData < 400)
    {
        return 3;
    }
    else if (700 < rawData && rawData < 850)
    {
        return 4;
    }
    else
    {
        //ERROR
    }
}
