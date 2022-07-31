#include <Arduino.h>

#include "RoombaServer.h"

RoombaServer * roombaServer;

// #define BUTTON_1 D5
// #define BUTTON_2 D6
// #define BUTTON_3 D7

// void checkButtons();

void setup()
{
    // pinMode( BUTTON_1, INPUT_PULLUP );
    // pinMode( BUTTON_2, INPUT_PULLUP );
    // pinMode( BUTTON_3, INPUT_PULLUP );

    //Serial.begin( 19200 );
    Serial.begin( 115200 );

    roombaServer = new RoombaServer();
    roombaServer->Begin();
}

void loop()
{
    roombaServer->Run();
}


// void checkButtons()
// {
//     static const unsigned long debounce = 500;
//     static unsigned long prevInputMillis = 0;
//     unsigned long currMillis = millis();

//     if ( debounce <= ( currMillis - prevInputMillis ) )
//     {
//         if ( LOW == digitalRead( BUTTON_1 ) )
//         {
//             prevInputMillis = currMillis;
//         }
//         else if ( LOW == digitalRead( BUTTON_2 ) )
//         {
//             prevInputMillis = currMillis;
//         }
//         else if ( LOW == digitalRead( BUTTON_3 ) )
//         {
//             prevInputMillis = currMillis;
//         }
//     }
// }
