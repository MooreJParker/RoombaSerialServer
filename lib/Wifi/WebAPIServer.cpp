#include "WebAPIServer.h"

//*** ESP32
//#include <WiFi.h>

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "defs/RoombaDefs.h"
#include "defs/RoombaUtils.h"
#include "ByteUtils.h"

ESP8266WebServer server(80);

//*** ESP32
//WebServer server(80);

// JSON data buffer
static const int H_RESULT_COUNT = 500;
const size_t capacity = JSON_ARRAY_SIZE(H_RESULT_COUNT) + JSON_OBJECT_SIZE(1) + H_RESULT_COUNT * JSON_OBJECT_SIZE(6);
StaticJsonDocument<capacity> jsonDoc;

/// Define paths for api calls and corresponding response methods
void SetupRouting()
{
    roombaManager = new RoombaManager();

    if ( WiFi.isConnected() )
    {
        server.on( "/driveForward", apiDriveForward );
        server.on( "/driveBackward", apiDriveBackward);
        server.on( "/driveLeft", apiDriveLeft );
        server.on( "/driveRight", apiDriveRight );
        server.on( "/driveStop", apiDriveStop );
        server.on( "/brush", apiBrush );
        server.on( "/brushCounter", apiBrushCounter );
        server.on( "/brushStop", apiBrushStop );
        server.on( "/toggleVacuum", apiToggleVacuum );

        server.on( "/powerDown", apiPowerDown );
        server.on( "/wakeUp", apiWakeUp );
        server.on( "/startSerial", apiStartSerial );
        server.on( "/stopSerial", apiStopSerial );
        server.on( "/safeMode", apiSafeMode );
        server.on( "/fullMode", apiFullMode );

        server.begin();
        Serial.println( "WebAPI Server Setup" );
    }
}

void apiDriveForward()
{
    // static DriveCommand drive = { 146, speed, speed };
    // SendDriveCommand( &drive );

    Serial.println( "Drive Forward" );

    roombaManager->Accelerate();
    server.send( HTTP_SUCCESS, "text/plain", "" );
}

void apiDriveBackward()
{
    // static DriveCommand drive = { 146, nspeed, nspeed };
    // SendDriveCommand( &drive );

    Serial.println( "Drive Backward" );

    roombaManager->Decelerate();
    server.send( HTTP_SUCCESS, "text/plain", "" );
}

void apiDriveLeft()
{
    // static DriveCommand drive = { 146, speed, 00 };
    // SendDriveCommand( &drive );
    server.send( HTTP_SUCCESS, "text/plain", "" );
}

void apiDriveRight()
{
    // static DriveCommand drive = { 146, 00, speed };
    // SendDriveCommand( &drive );
    server.send( HTTP_SUCCESS, "text/plain", "" );
}

void apiDriveStop()
{
    static const uint8_t stopData[5] = { DRIVE_PWM_COMMAND, 0x00, 0x00, 0x00, 0x00 };
    Serial2.write( stopData, 5 );
    server.send( HTTP_SUCCESS, "text/plain", "Drive Stop" );
}

void apiWakeUp()
{
    server.send( HTTP_SUCCESS, "text/plain", "Wake Up" );
    roombaManager->Wake();
}

void apiPowerDown()
{
    Serial2.write( POWER_DOWN_COMMAND );
    server.send( HTTP_SUCCESS, "text/plain", "Power Down" );
}

void apiStartSerial()
{
    Serial2.write( START_SCI_COMMAND );
    delay( 500 );

    Serial2.write( FULL_MODE_COMMAND );

    server.send( HTTP_SUCCESS, "text/plain", "Start Serial" );
}

void apiStopSerial()
{
    Serial2.write( STOP_SCI_COMMAND );
    server.send( HTTP_SUCCESS, "text/plain", "Stop Serial" );
}

void apiSafeMode()
{
    Serial2.write( SAFE_MODE_COMMAND );
    server.send( HTTP_SUCCESS, "text/plain", "Safe Mode" );
}

void apiFullMode()
{
    Serial2.write( FULL_MODE_COMMAND );
    server.send( HTTP_SUCCESS, "text/plain", "Full Mode" );
}

void apiBrush()
{
    // static const uint8_t motorData[2] = { MOTORS_COMMAND, 1 };
    // static const uint8_t stopData[2] =  { MOTORS_COMMAND, 0x00 };

    // Serial2.write( motorData, 2 );
    // delay( brushDelay );

    // Serial2.write( stopData, 2 );

    server.send( HTTP_SUCCESS, "text/plain", "Brush Clockwise" );
}

void apiBrushCounter()
{
    // static const uint8_t motorData[2] = { MOTORS_COMMAND, 9 };
    // static const uint8_t stopData[2] =  { MOTORS_COMMAND, 0x00 };

    // Serial2.write( motorData, 2 );
    // delay( brushDelay );

    // Serial2.write( stopData, 2 );

    server.send( HTTP_SUCCESS, "text/plain", "Brush Counter-Clockwise" );
}

void apiBrushStop()
{
    // static const uint8_t stopData[2] =  { MOTORS_COMMAND, 0x00 };
    // Serial2.write( stopData, 2 );
    server.send( HTTP_SUCCESS, "text/plain", "Brush Stop" );
}

void apiToggleVacuum()
{
    // static const uint8_t startData[2] =  { MOTORS_COMMAND, 0x06 };
    // static const uint8_t stopData[2] =  { MOTORS_COMMAND, 0x00 };
    // Serial2.write( stopData, 2 );
    server.send( HTTP_SUCCESS, "text/plain", "Start Vacuum" );
}
