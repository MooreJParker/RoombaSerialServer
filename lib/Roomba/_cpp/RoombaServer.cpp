#include "../RoombaServer.h"

static const int HTTP_SUCCESS  = 200; // actuator task succeeded
static const int HTTP_ACCEPTED = 202; // actuator task started
static const int HTTP_RUNNING  = 204; // busy executing task
static const int HTTP_NOT_NOW  = 405; // task not availbe in current state


RoombaManager * RoombaServer::mRoomba = new RoombaManager();

RoombaServer::RoombaServer()
    : WemosServer()
    , mEndpoints( new std::vector<RestEndpoint>() )
{
    mEndpoints->assign
    ({
        { "/wakeup",        (EndpointHandler)RoombaServer::apiWakeUp        },
        { "/driveForward",  (EndpointHandler)RoombaServer::apiDriveForward  },
        { "/driveBackward", (EndpointHandler)RoombaServer::apiDriveBackward },
        { "/driveLeft",     (EndpointHandler)RoombaServer::apiDriveLeft     },
        { "/driveRight",    (EndpointHandler)RoombaServer::apiDriveRight    },
        { "/driveStop",     (EndpointHandler)RoombaServer::apiDriveStop     },
        { "/brush",         (EndpointHandler)RoombaServer::apiBrush         },
        { "/brushCounter",  (EndpointHandler)RoombaServer::apiBrushCounter  },
        { "/toggleVacuum",  (EndpointHandler)RoombaServer::apiToggleVacuum  },
        { "/powerDown",     (EndpointHandler)RoombaServer::apiPowerDown     },
        { "/startSerial",   (EndpointHandler)RoombaServer::apiStartSerial   },
        { "/stopSerial",    (EndpointHandler)RoombaServer::apiStopSerial    },
        { "/safeMode",      (EndpointHandler)RoombaServer::apiSafeMode      },
        { "/fullMode",      (EndpointHandler)RoombaServer::apiFullMode      }
    });
}

void RoombaServer::Begin()
{
    connect();

    // Set mServer routing and begin
    setupRouting( mEndpoints );
    mServer.onNotFound( EndpointNotFound );

    mServer.begin();
    Serial.println("HTTP server started");
}

//===========================================
//               Private
//===========================================
void RoombaServer::apiWakeUp()
{
    mRoomba->Wake();

    mServer.send( HTTP_SUCCESS, "text/plain", "Wake Up" );
}

void RoombaServer::apiDriveForward()
{
    mRoomba->Accelerate();
    mServer.send( HTTP_SUCCESS, "text/plain", "" );
}

void RoombaServer::apiDriveBackward()
{
    mRoomba->Decelerate();
    mServer.send( HTTP_SUCCESS, "text/plain", "" );
}

void RoombaServer::apiDriveLeft()
{
    mRoomba->TurnLeft();
    mServer.send( HTTP_SUCCESS, "text/plain", "" );
}

void RoombaServer::apiDriveRight()
{
    mRoomba->TurnRight();
    mServer.send( HTTP_SUCCESS, "text/plain", "" );
}

void RoombaServer::apiDriveStop()
{
    mRoomba->StopMotion();
    mServer.send( HTTP_SUCCESS, "text/plain", "Drive Stop" );
}

void RoombaServer::apiBrush()
{
    mRoomba->BrushClock();
    mServer.send( HTTP_SUCCESS, "text/plain", "Brush Clockwise" );
}

void RoombaServer::apiBrushCounter()
{
    mRoomba->BrushCounterClock();
    mServer.send( HTTP_SUCCESS, "text/plain", "Brush Counter-Clockwise" );
}

void RoombaServer::apiToggleVacuum()
{
    mRoomba->ToggleVacuum();
    mServer.send( HTTP_SUCCESS, "text/plain", "Start Vacuum" );
}

void RoombaServer::apiPowerDown()
{
    mRoomba->PowerDown();
    mServer.send( HTTP_SUCCESS, "text/plain", "Power Down" );
}

void RoombaServer::apiStartSerial()
{
    mRoomba->StartSerial();
    mServer.send( HTTP_SUCCESS, "text/plain", "Start Serial" );
}

void RoombaServer::apiStopSerial()
{
    mRoomba->StopSerial();
    mServer.send( HTTP_SUCCESS, "text/plain", "Stop Serial" );
}

void RoombaServer::apiSafeMode()
{
    mRoomba->SafeMode();
    mServer.send( HTTP_SUCCESS, "text/plain", "Safe Mode" );
}

void RoombaServer::apiFullMode()
{
    mRoomba->FullMode();
    mServer.send( HTTP_SUCCESS, "text/plain", "Full Mode" );
}


// // static
// void RoombaServer::RoombaServer::test1()
// {
//     String message = "";
//     for ( uint8_t i = 0; i < mServer.args(); i++ )
//     {
//         String argName = mServer.argName( i );
//         String argVal = mServer.arg( i );
//         message += argName + ": " + argVal;
//     }
//     Serial.println( message );
//     mServer.send( 200, "text", "Test 1!" );
// }

// static
void RoombaServer::EndpointNotFound()
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += mServer.uri();
    message += "\nMethod: ";
    message += ( mServer.method() == HTTP_GET ) ? "GET" : "POST";
    message += "\nArguments: ";
    message += mServer.args();
    message += "\n";
    for ( uint8_t i = 0; i < mServer.args(); i++ )
    {
        message += " " + mServer.argName(i) + ": " + mServer.arg(i) + "\n";
    }
    mServer.send(404, "text/plain", message);
}