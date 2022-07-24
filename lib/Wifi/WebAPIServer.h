#ifndef WebAPI_h
#define WebAPI_h

//*** ESP32
//#include <WebServer.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "RoombaManager.h"

extern ESP8266WebServer server;

//*** ESP32
//extern WebServer server;

static const int HTTP_SUCCESS  = 200; // actuator task succeeded
static const int HTTP_ACCEPTED = 202; // actuator task started
static const int HTTP_RUNNING  = 204; // busy executing task
static const int HTTP_NOT_NOW  = 405; // task not availbe in current state

static const String FAIL_MSG = "fail - turbo is off";

static RoombaManager * roombaManager;

void SetupRouting();

// api endpoints
void apiWakeUp();

void apiDriveForward();
void apiDriveBackward();
void apiDriveLeft();
void apiDriveRight();
void apiDriveStop();
void apiBrush();
void apiBrushCounter();
void apiBrushStop();
void apiToggleVacuum();

void apiPowerDown();
void apiStartSerial();
void apiStopSerial();
void apiSafeMode();
void apiFullMode();

#endif
