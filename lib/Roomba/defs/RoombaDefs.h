#ifndef ROOMBA_DEFS_H
#define ROOMBA_DEFS_H

#include <Arduino.h>

typedef uint8_t Command; enum
{
    RESET_COMMAND = 7,
    START_SCI_COMMAND = 128,
    STOP_SCI_COMMAND = 173,
    SAFE_MODE_COMMAND = 131,
    FULL_MODE_COMMAND = 132,
    POWER_DOWN_COMMAND = 133,
    DRIVE_DIRECT_COMMAND = 137,
    DRIVE_PWM_COMMAND = 146,
    MOTORS_COMMAND = 138,

    COUNT_COMMANDS = 9
};

struct RoombaCommandInfo
{
    char i; // input
    Command command;
    String name;
};

typedef struct __attribute__((packed)) Drive_t
{
    uint8_t id;
    int16_t rightWheel;
    int16_t leftWheel;
} DriveCommand;

#endif // ROOMBA_DEFS_H
