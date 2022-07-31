#ifndef ROOMBA_SCREEN_WRITER_H
#define ROOMBA_SCREEN_WRITER_H

#include "U8g2lib.h"

class Screen
{
public:
    Screen();

    void Write( String str );
    void Clear();

private:
    void updateScreen( String str );

    U8G2_SH1106_128X64_NONAME_1_HW_I2C mScreen;
};

#endif // ROOMBA_SCREEN_WRITER_H
