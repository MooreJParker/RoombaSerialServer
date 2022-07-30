#ifndef ROOMBA_MANAGER_H
#define ROOMBA_MANAGER_H

#include <Arduino.h>

#include "defs/RoombaDefs.h"
#include "defs/RoombaUtils.h"

#define RXPIN 5
#define TXPIN 6

class RoombaManager
{
public:
    RoombaManager();

    void Accelerate();
    void Decelerate();
    void TurnRight();
    void TurnLeft();
    void StopMotion();

    void BrushClock();
    void BrushCounterClock();

    void ToggleVacuum();

    void PowerDown();
    void StartSerial();
    void StopSerial();
    void SafeMode();
    void FullMode();
    void Wake();

private:
    static const uint16_t BRUSH_DELAY = 500;
    static const int16_t MAX_SPEED = 255;
    static const int16_t MIN_SPEED = -255;

    static const uint8_t BRUSH_CLOCKWISE         = 0x01;
    static const uint8_t BRUSH_COUNTER_CLOCKWISE = 0x09;
    static const uint8_t VACUUM_MOTORS           = 0x06;

    void sendDriveCommand( DriveCommand * command );

    static const int16_t ACCEL_INC = 20;
    static const int16_t TURN_INC = ( ACCEL_INC * 1.5 );

    DriveCommand mDriveCommand;
    DriveCommand mTurnCommand;

    uint8_t mWakePin;
    int16_t mRWSpeed;
    int16_t mLWSpeed;
    bool mVacuumState;
};

#endif // ROOMBA_MANAGER_H
