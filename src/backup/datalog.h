#ifndef DATALOG_H
#define DATALOG_H

#include "nxt_interface.h"
#include "controller.h"
#include "speedometer.h"
#define PACKETSIZE 13

U8* createDatalogArray();

void sendData();

#endif
