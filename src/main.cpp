#include <Arduino.h>

#include "RoombaServer.h"


//*** ESP32
// #define RXD2 GPIO_NUM_16
// #define TXD2 GPIO_NUM_17

RoombaServer * roombaServer;

void setup()
{
    //Serial.begin( 19200 );
    Serial.begin( 115200 );

    //*** ESP32
    ////Serial2.begin( 19200, SERIAL_8N1, RXD2, TXD2 );
    ////Serial2.begin( 115200, SERIAL_8N1, RXD2, TXD2 );

    roombaServer = new RoombaServer();
    roombaServer->Begin();
}

void loop()
{
    roombaServer->Run();

    // if ( //Serial2.available() )
    // {
    //     Serial.write( //Serial2.read() );
    // }
}
