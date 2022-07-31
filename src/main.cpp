#include <Arduino.h>

#include "RoombaServer.h"
#include "Screen.h"

Screen * screen;
RoombaServer * roombaServer;

#define BUTTON_1 D5
#define BUTTON_2 D6
#define BUTTON_3 D7

void checkButtons();

void setup()
{
    pinMode( BUTTON_1, INPUT_PULLUP );
    pinMode( BUTTON_2, INPUT_PULLUP );
    pinMode( BUTTON_3, INPUT_PULLUP );

    //Serial.begin( 19200 );
    Serial.begin( 115200 );

    screen = new Screen();

    roombaServer = new RoombaServer();
    roombaServer->Begin();
}

void loop()
{
    // roombaServer->Run();
    checkButtons();
}


void checkButtons()
{
    static const unsigned long debounce = 500;
    static unsigned long prevInputMillis = 0;
    unsigned long currMillis = millis();

    if ( debounce <= ( currMillis - prevInputMillis ) )
    {
        if ( LOW == digitalRead( BUTTON_1 ) )
        {
            screen->Write( "Button 1" );
            prevInputMillis = currMillis;
        }
        else if ( LOW == digitalRead( BUTTON_2 ) )
        {
            screen->Write( "Button 2" );
            prevInputMillis = currMillis;
        }
        else if ( LOW == digitalRead( BUTTON_3 ) )
        {
            screen->Write( "Button 3" );
            prevInputMillis = currMillis;
        }
    }
}
