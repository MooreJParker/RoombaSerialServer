#include "WebAPIServer.h"

#include "defs/RoombaDefs.h"
#include "defs/RoombaUtils.h"
#include "ByteUtils.h"

ESP8266WebServer server( HTTP_REST_PORT );

void Connect()
{
    WiFi.mode( WIFI_STA );
    WiFi.begin( WEB_SSID, WEB_PASS );
    Serial.println( "" );

    // Wait for connection
    while ( WiFi.status() != WL_CONNECTED )
    {
        delay(500);
        Serial.print(".");
    }
    Serial.print( "IP address: " );
    Serial.println( WiFi.localIP() );
    
    // Activate mDNS this is used to be able to connect to the server
    // with local DNS hostmane esp8266.local
    if ( MDNS.begin( "roombaBot" ) )
    {
        Serial.println( "MDNS responder started" );
    }

    SetupRouting();
    
    // Start server
    server.begin();
    Serial.println("HTTP server started");
}

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

void apiWakeUp()
{
    roombaManager->Wake();

    server.send( HTTP_SUCCESS, "text/plain", "Wake Up" );
}

void apiDriveForward()
{
    roombaManager->Accelerate();
    server.send( HTTP_SUCCESS, "text/plain", "" );
}

void apiDriveBackward()
{
    roombaManager->Decelerate();
    server.send( HTTP_SUCCESS, "text/plain", "" );
}

void apiDriveLeft()
{
    roombaManager->TurnLeft();
    server.send( HTTP_SUCCESS, "text/plain", "" );
}

void apiDriveRight()
{
    roombaManager->TurnRight();
    server.send( HTTP_SUCCESS, "text/plain", "" );
}

void apiDriveStop()
{
    roombaManager->StopMotion();
    server.send( HTTP_SUCCESS, "text/plain", "Drive Stop" );
}

void apiBrush()
{
    roombaManager->BrushClock();
    server.send( HTTP_SUCCESS, "text/plain", "Brush Clockwise" );
}

void apiBrushCounter()
{
    roombaManager->BrushCounterClock();
    server.send( HTTP_SUCCESS, "text/plain", "Brush Counter-Clockwise" );
}

void apiToggleVacuum()
{
    roombaManager->ToggleVacuum();
    server.send( HTTP_SUCCESS, "text/plain", "Start Vacuum" );
}

void apiPowerDown()
{
    roombaManager->PowerDown();
    server.send( HTTP_SUCCESS, "text/plain", "Power Down" );
}

void apiStartSerial()
{
    roombaManager->StartSerial();
    server.send( HTTP_SUCCESS, "text/plain", "Start Serial" );
}

void apiStopSerial()
{
    roombaManager->StopSerial();
    server.send( HTTP_SUCCESS, "text/plain", "Stop Serial" );
}

void apiSafeMode()
{
    roombaManager->SafeMode();
    server.send( HTTP_SUCCESS, "text/plain", "Safe Mode" );
}

void apiFullMode()
{
    roombaManager->FullMode();
    server.send( HTTP_SUCCESS, "text/plain", "Full Mode" );
}
