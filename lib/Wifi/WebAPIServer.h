#ifndef WebAPI_h
#define WebAPI_h

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "RoombaManager.h"

#define HTTP_REST_PORT 80
#define WEB_SSID "BruceBanner"
#define WEB_PASS "1000Shots"

extern ESP8266WebServer server;

static const int HTTP_SUCCESS  = 200; // actuator task succeeded
static const int HTTP_ACCEPTED = 202; // actuator task started
static const int HTTP_RUNNING  = 204; // busy executing task
static const int HTTP_NOT_NOW  = 405; // task not availbe in current state

static const String FAIL_MSG = "fail - turbo is off";

static RoombaManager * roombaManager;

void Connect();
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
void apiToggleVacuum();

void apiPowerDown();
void apiStartSerial();
void apiStopSerial();
void apiSafeMode();
void apiFullMode();

#endif
