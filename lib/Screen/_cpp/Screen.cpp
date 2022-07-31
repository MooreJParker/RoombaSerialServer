#include "../Screen.h"

Screen::Screen()
    : mScreen( U8G2_R0, U8X8_PIN_NONE )
{
    mScreen.begin(); // screen
}

void Screen::Clear()
{
    mScreen.clear();
    // mScreen.firstPage();
    // do { mScreen.clear(); } while( mScreen.nextPage() );
}

void Screen::Write( String str )
{
    mScreen.clear();
    do
    {
        updateScreen( str );
    } while( mScreen.nextPage() );

}

void Screen::updateScreen( String str )
{
    // uint8_t yGapDist = 20;
    // uint8_t xDataOffset = 55;
    uint8_t distPosX = 5;
    uint8_t distPosY = 15;

    mScreen.setFont( u8g_font_profont10 );
    mScreen.setCursor( distPosX, distPosY );

    mScreen.print( str );
}
