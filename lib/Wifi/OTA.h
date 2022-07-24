#include <Arduino.h>

//*** ESP32
// #include <WiFi.h>
// #include <HTTPClient.h>

#include <IPAddress.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

bool wifiConnected = false;

#define SECONDS 1000

const String HomeWifiSSID = "BruceBanner";
const String HomeWifiPass = "1000Shots";
bool DeviceIsHome = false;

void OTASetup()
{
    unsigned long max = 10 * SECONDS;
    unsigned long t = millis();
    Serial.println( WiFi.macAddress() );

    WiFi.disconnect();
    WiFi.persistent(false);

    int n = WiFi.scanNetworks();
    Serial.println( "Wifi scan done" );

    // No networks found...
    if (n == 0)
    {
        Serial.println( "no networks found" );
        WiFi.mode( WIFI_OFF );
        return;
    }

    Serial.print( n );
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
        if ( WiFi.SSID(i) == HomeWifiSSID )
        {
            DeviceIsHome = true;
        }
    }

    if ( DeviceIsHome )
    {
        DeviceIsHome = false; //reset this unless connects successfully
        Serial.println( "Device is home, trying to authenticate..." );
        //WiFi.begin( HomeWifiSSID.c_str(), HomeWifiSSID.c_str() );
        WiFi.begin( "BruceBanner", "1000Shots" );

        t = millis();
        while ( max > millis() - t )
        {
            if ( WiFi.status() == WL_CONNECTED )
                break;
            delay( 1 );
            //Serial.print( "." );
        }

        if ( WiFi.status() == WL_CONNECTED )
        {
            DeviceIsHome = true;

            Serial.println( "Connected @ " + WiFi.localIP().toString() );
            Serial.println( "Device is home, and connected to wifi!" );
        }
        else
        {
            Serial.println( "Failure to connect to Wifi" );
        }
    }

    if (!DeviceIsHome)
    {
        WiFi.disconnect();
        WiFi.mode(WIFI_OFF);
    }
}
