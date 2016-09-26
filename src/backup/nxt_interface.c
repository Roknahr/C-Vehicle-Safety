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

U32 getSysTime(){
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

void initSonarSensor(){
    ecrobot_init_sonar_sensor(SONAR_SENSOR);
}

S32 getSonarSensor(){
    return ecrobot_get_sonar_sensor(SONAR_SENSOR);
}

void termSonarSensor(){
    ecrobot_term_sonar_sensor(SONAR_SENSOR);
}

/* Rotation sensor */
S16 getRotationSensor(){
    return ecrobot_get_RCX_sensor(ROTATION_SENSOR);
}

void termRotationSensor(){
    ecrobot_term_RCX_power_source(ROTATION_SENSOR);
}

void initRotationSensor(){
    rotationSensor.ticks = 0;
    rotationSensor.secondToLastTick = 0;
    rotationSensor.lastTick = 0;
    ecrobot_set_RCX_power_source(ROTATION_SENSOR);
}

/* Light sensor */

void initLightSensor ()
{
    ecrobot_set_light_sensor_active(LIGHT_SENSOR_RIGHT);
    ecrobot_set_light_sensor_active(LIGHT_SENSOR_LEFT);
}

void termLightSensor ()
{
    ecrobot_set_light_sensor_inactive(LIGHT_SENSOR_RIGHT);
    ecrobot_set_light_sensor_inactive(LIGHT_SENSOR_LEFT);
}

U16 getLightSensorRight ()
{
    return ecrobot_get_light_sensor(LIGHT_SENSOR_RIGHT);
}

U16 getLightSensorLeft ()
{
    return ecrobot_get_light_sensor(LIGHT_SENSOR_LEFT);
}
