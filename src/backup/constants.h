#ifndef CONSTANTS_H
#define CONSTANTS_H

#define LEFT_MOTOR          PORT_C
#define RIGHT_MOTOR         PORT_B
#define STEERING_MOTOR      PORT_A

#define SONAR_SENSOR 		PORT_1
#define LIGHT_SENSOR_LEFT   PORT_2
#define ROTATION_SENSOR 	PORT_3
#define LIGHT_SENSOR_RIGHT  PORT_4

#define STEERING_LIMIT          40 				/* Degree */
#define STEERING_P_GAIN          2 				/* Proportional gain */
#define MAX_SPEED_FW           100 				/* Max speed forwards */ 
#define MAX_SPEED_BW          -100 				/* Max speed backwards */ 
#define ARRAY_SIZE               4
#define VEHICLE_WIDTH           15 				/* Half of the actual width + safe zone*/
#define JOYSTICK_LASH			10 				/* dead zone of joystick - 0.1 on C# side */

/* AEB Constants */
#define COEF_OF_FRICTION            0.158
#define STD_GRAVITY                 9.80665     /* meter / seconds ^ 2 */
#define AEB_TIME_BETWEEN_READINGS   25          /* in milliseconds */
#define MS_PER_SEC                  1000.0      /* milliseconds */
#define BRAKE_SAFE_ZONE             20          /* in cm */
#define SONAR_ERROR_MARGIN          4           /* in cm */
#define SAMPLE_COUNT                5           /* number of samples taken for the error correction array */
#define CM_PER_M                    100         /* number of centimetres per meter */

/* EAEB constants */
#define VEHICLE_SAFE_ZONE 			5 			/* 5 cm safe zone */

#endif
