#ifndef ROOMBA_SERVER_H
#define ROOMBA_SERVER_H

#include <vector>

// base class
#include "WemosWifi/defs/WServerDefs.h"

#include "RoombaManager.h"
#include "WemosWifi/WemosServer.h"

class RoombaServer: public WemosServer
{
public:
    RoombaServer();

    void Begin();

private:
    std::vector<RestEndpoint> * mEndpoints;
    static RoombaManager * mRoomba;

    // api endpoints
    static void apiWakeUp();

    static void apiDriveForward();
    static void apiDriveBackward();
    static void apiDriveLeft();
    static void apiDriveRight();
    static void apiDriveStop();
    static void apiBrush();
    static void apiBrushCounter();
    static void apiToggleVacuum();

    static void apiPowerDown();
    static void apiStartSerial();
    static void apiStopSerial();
    static void apiSafeMode();
    static void apiFullMode();

    static void EndpointNotFound();
};

#endif // ROOMBA_SERVER_H
