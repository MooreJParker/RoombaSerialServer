#include "../RoombaUtils.h"

#include "ByteUtils.h"

void SendDriveCommand( DriveCommand * command )
{
    // static uint8_t commandArr[5];
    // static uint8_t sendData[5];
    // memcpy( commandArr, command, sizeof( DriveCommand ) );

    // sendData[0] = command->id;
    // for ( int i = 1; i < 4; i += 2 )
    // {
    //     sendData[i] = commandArr[i + 1];
    //     sendData[i + 1] = commandArr[i];
    // }

    // PrintByteArray( sendData, 5 );

    // Serial2.write( sendData, 5 );
}
