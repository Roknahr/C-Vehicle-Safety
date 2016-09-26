#include "ecrobot_interface.h"
#include "nxt_interface.h"

/* Motor */
S32 motorGetCount(U8 port){
    return nxt_motor_get_count(port);
}

void motorSetCount(U8 port, int count){
    nxt_motor_set_count(port, count);
}

void motorSetSpeed(U8 port, S32 speed, S32 mode){
    nxt_motor_set_speed(port, speed, mode);
}

/* Bluetooth */


U32 sendBtPacket(U8 *buf, U32 bufLen){
    return ecrobot_send_bt_packet(buf, bufLen);
}

U32 readBtPacket(U8 *buf, U32 bufLen) {
    return ecrobot_read_bt_packet(buf, bufLen);
}

U32 getSysTime()
{
	return systick_get_ms();
}

void initBtConnection(){
    ecrobot_init_bt_connection();
}

void termBtConnection(){
    ecrobot_term_bt_connection();
}

/* LCD Display */
void displayUpdate() {
    display_update();
}

void displayClear(U32 updateToo) {
    display_clear(updateToo);
}

void displayGotoXY(int x, int y){
    display_goto_xy(x, y);
}

void displayString(const char *str){
    display_string(str);
}

void displayInt(int val, U32 places){
    display_int(val, places);
}

/* Ultrasonic */
/*
S32 getSonarSensor(){
    ecrobot_get_sonar_sensor(SONAR_SENSOR);
}

void termSonarSensor(){
    ecrobot_term_sonar_sensor(SONAR_SENSOR);
}

void initSonarSensor(){
    ecrobot_init_sonar_sensor(SONAR_SENSOR);
}
*/

/* Anglesensor */
S16 getAngleSensor(){
    return ecrobot_get_RCX_sensor(PORT_3);
}

void termAngleSensor(){
    ecrobot_term_RCX_power_source(PORT_3);
}

void initAngleSensor(){
    ecrobot_set_RCX_power_source(PORT_3);
}
