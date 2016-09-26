#ifndef NXT_INTERFACE_H
#define NXT_INTERFACE_H

#include "mytypes.h"

#define SONAR_SENSOR PORT_1;
#define LIGHT_SENSOR PORT_2;
#define ANGLE_SENSOR PORT_3;

typedef enum {
	PORT_A,
	PORT_B,
	PORT_C
}MY_MOTOR_PORT_T;

typedef enum {
	PORT_1,
	PORT_2,
	PORT_3,
	PORT_4
}MY_SENSOR_PORT_T;

S32 motorGetCount(U8 port);

void motorSetCount(U8 port, int count);

void motorSetSpeed(U8 port, S32 speed, S32 mode);

U32 sendBtPacket(U8 *buf, U32 bufLen);

U32 readBtPacket(U8 *buf, U32 bufLen);

U32 getSysTime();

void initBtConnection();

void termBtConnection();

/* LCD Display */
void displayUpdate();

void displayClear(U32 updateToo);

void displayGotoXY(int x, int y);

void displayString(const char *str);

void displayInt(int val, U32 places);

/* Ultrasonic */
S32 getSonarSensor();

void initSonarSensor();

void termSonarSensor();

/* AngleSensor */
S16 getAngleSensor();

void termAngleSensor();

void initAngleSensor();

#endif
