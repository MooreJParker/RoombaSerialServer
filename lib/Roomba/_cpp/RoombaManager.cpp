#include "../RoombaManager.h"

#include "Utils/ByteUtils.h"
#include "defs/RoombaDefs.h"

RoombaManager::RoombaManager()
    : mDriveCommand( { 0x00, 0, 0 } )
    , mTurnCommand( { 0x00, 0, 0 } )
    //, mWakePin( GPIO_NUM_19 )
    , mWakePin( 3 )
    , mRWSpeed( 0 )
    , mLWSpeed( 0 )
    , mVacuumState( false )
{
    pinMode( mWakePin, OUTPUT );
    digitalWrite( mWakePin, HIGH );
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

void RoombaManager::TurnRight()
{
    int16_t newRight = ( mDriveCommand.rightWheel - TURN_INC );
    int16_t newLeft = mDriveCommand.leftWheel;

    // driving backwards
    if ( 0 > mDriveCommand.leftWheel )
    {
        // switch inc val
        newRight = ( mDriveCommand.rightWheel + TURN_INC );
    }

    // check bounds
    if ( ( MIN_SPEED > newRight ) || ( MAX_SPEED < newRight ) )
    {
        // set back to previous
        newRight = mDriveCommand.rightWheel;
    }

    // mTurnCommand.id = DRIVE_PWM_COMMAND;
    // mTurnCommand.rightWheel = newRight;
    // mTurnCommand.leftWheel = newLeft;
    // sendDriveCommand( &mTurnCommand );

    mDriveCommand.id = DRIVE_PWM_COMMAND;
    mDriveCommand.rightWheel = newRight;
    mDriveCommand.leftWheel = newLeft;
    sendDriveCommand( &mDriveCommand );
}

void RoombaManager::TurnLeft()
{
    int16_t newLeft= ( mDriveCommand.leftWheel - TURN_INC );
    int16_t newRight = mDriveCommand.rightWheel;

    // driving backwards
    if ( 0 > mDriveCommand.rightWheel )
    {
        // switch inc val
        newLeft = ( mDriveCommand.leftWheel + TURN_INC );
    }

    // check bounds
    if ( ( MIN_SPEED > newLeft ) || ( MAX_SPEED < newLeft ) )
    {
        // set back to previous
        newLeft = mDriveCommand.leftWheel;
    }

    // mTurnCommand.id = DRIVE_PWM_COMMAND;
    // mTurnCommand.rightWheel = newRight;
    // mTurnCommand.leftWheel = newLeft;
    // sendDriveCommand( &mTurnCommand );

    mDriveCommand.id = DRIVE_PWM_COMMAND;
    mDriveCommand.rightWheel = newRight;
    mDriveCommand.leftWheel = newLeft;
    sendDriveCommand( &mDriveCommand );

}

void RoombaManager::StopMotion()
{
    mDriveCommand.rightWheel = 0;
    mDriveCommand.leftWheel = 0;
    sendDriveCommand( &mDriveCommand );
}


void RoombaManager::BrushClock()
{
    static const uint8_t motorData[2] = { MOTORS_COMMAND, BRUSH_CLOCKWISE };
    static const uint8_t stopData[2] =  { MOTORS_COMMAND, 0x00 };

    //Serial2.write( motorData, 2 );
    delay( BRUSH_DELAY );
    //Serial2.write( stopData, 2 );
}

void RoombaManager::BrushCounterClock()
{
    static const uint8_t motorData[2] = { MOTORS_COMMAND, BRUSH_COUNTER_CLOCKWISE };
    static const uint8_t stopData[2] =  { MOTORS_COMMAND, 0x00 };

    //Serial2.write( motorData, 2 );
    delay( BRUSH_DELAY );
    //Serial2.write( stopData, 2 );
}

void RoombaManager::ToggleVacuum()
{
    static const uint8_t startData[2] =  { MOTORS_COMMAND, VACUUM_MOTORS };
    static const uint8_t stopData[2] =  { MOTORS_COMMAND, 0x00 };

    if ( mVacuumState )
    {
        //Serial2.write( stopData, 2 );
    }
    else
    {
        //Serial2.write( startData, 2 );
    }
    mVacuumState = !mVacuumState;
}

void RoombaManager::PowerDown()
{
    //Serial2.write( POWER_DOWN_COMMAND );
}

void RoombaManager::StartSerial()
{
    //Serial2.write( START_SCI_COMMAND );
    delay( 500 );
    //Serial2.write( FULL_MODE_COMMAND );
}

void RoombaManager::StopSerial()
{
    //Serial2.write( STOP_SCI_COMMAND );
}

void RoombaManager::SafeMode()
{
    //Serial2.write( SAFE_MODE_COMMAND );
}

void RoombaManager::FullMode()
{
    //Serial2.write( FULL_MODE_COMMAND );
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

    //Serial2.write( sendData, 5 );
}
