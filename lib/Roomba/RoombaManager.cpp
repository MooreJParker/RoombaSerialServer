#include "RoombaManager.h"

#include "ByteUtils.h"

RoombaManager::RoombaManager()
    : mDriveCommand( { 0x00, 0, 0 } )
    , mSerial( RXPIN, TXPIN )
    , mWakePin( 7 )
    , mRWSpeed( 0 )
    , mLWSpeed( 0 )
{
    pinMode( mWakePin, OUTPUT );
    digitalWrite( mWakePin, HIGH );

    mSerial.begin( 19200 );
    //mSerial.begin( 115200 );
}

void RoombaManager::Accelerate()
{
    int16_t newRight = ( mDriveCommand.rightWheel + ACCEL_INC );
    int16_t newLeft = ( mDriveCommand.leftWheel + ACCEL_INC );

    mDriveCommand.id = DRIVE_PWM_COMMAND;

    if ( MAX_SPEED >= newRight )
    {
        mDriveCommand.rightWheel = newRight; 
    }

    if ( MAX_SPEED >= newLeft )
    {
        mDriveCommand.leftWheel = newLeft;
    }

    sendDriveCommand( &mDriveCommand );
}

void RoombaManager::Decelerate()
{
    int16_t newRight = ( mDriveCommand.rightWheel - ACCEL_INC );
    int16_t newLeft = ( mDriveCommand.leftWheel - ACCEL_INC );

    mDriveCommand.id = DRIVE_PWM_COMMAND;

    if ( MIN_SPEED <= newRight )
    {
        mDriveCommand.rightWheel = newRight; 
    }

    if ( MIN_SPEED <= newLeft )
    {
        mDriveCommand.leftWheel = newLeft;
    }

    sendDriveCommand( &mDriveCommand );
}

void RoombaManager::Wake()
{
    digitalWrite( mWakePin, LOW );
    delay( 10 );
    digitalWrite( mWakePin, HIGH );
    delay( 2000 );
}

//===========================================
//               Private
//===========================================
void RoombaManager::sendDriveCommand( DriveCommand * command )
{
    static uint8_t commandArr[5];
    static uint8_t sendData[5];
    memcpy( commandArr, command, sizeof( DriveCommand ) );

    sendData[0] = command->id;
    for ( int i = 1; i < 4; i += 2 )
    {
        sendData[i] = commandArr[i + 1];
        sendData[i + 1] = commandArr[i];
    }

    PrintByteArray( sendData, 5 );

    mSerial.write( sendData, 5 );
}
