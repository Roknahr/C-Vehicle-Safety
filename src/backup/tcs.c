#include "tcs.h"
#include <math.h>


S32 tcs(S32 speed){
    if(fabs(vehicle.vBack) > MINIMUM_SPEED_WHILE_TCS)
    {
        if((vehicle.vBack > 0 && vehicle.vFront > 0) || 
           (vehicle.vBack < 0 && vehicle.vFront < 0) ||
           (vehicle.vBack == 0 && vehicle.vFront == 0)){
            if(fabs(vehicle.vBack) > (fabs(vehicle.vFront) * TARGET_SLIP_RATIO))
            {
                if(speed > SPEED_ADJUST)
                {
                    speed = speed - SPEED_ADJUST;
                }
                else
                {
                    speed = speed / 2;
                }
            }
        }
        else{
            if((fabs(vehicle.vBack) + fabs(vehicle.vFront)) > (fabs(vehicle.vFront) * TARGET_SLIP_RATIO))
            {
                if(speed > SPEED_ADJUST)
                {
                    speed = speed - SPEED_ADJUST;
                }
                else
                {
                    speed = speed / 2;
                }
            }
        }
    }
    else
    {
        //DO NOTHING - speed = speed;
    }
    return speed;
}