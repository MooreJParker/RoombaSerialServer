#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID "BruceBanner"
#define WIFI_PASS "1000Shots"

void OTASetup()
{
    WiFi.begin( WIFI_SSID, WIFI_PASS );

    // Connecting to WiFi...
    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);

    // Loop continuously while WiFi is not connected
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }

    Serial.println();
    Serial.print( "Connected! Ip address: " );
    Serial.println( WiFi.localIP() );
}
