#include "ByteUtils.h"

void ArrayToString( const uint8_t * inArray, char * outStr, uint8_t arrSize )
{
    uint8_t responseIdx = 0;
    for ( int i = 0; i < arrSize; i++ )
    {
        uint8_t leftNibble = ( inArray[i] >> 4 ) & 0xF;
        uint8_t rightNibble = inArray[i] & 0xF;

        itoa( leftNibble, &outStr[2 * responseIdx], HEX );
        itoa( rightNibble, &outStr[( 2 * responseIdx ) + 1], HEX );
        responseIdx++;
    }
}

void ClearByteArray( uint8_t * arr, uint8_t sz )
{
    for ( int i = 0; i < sz; i++ )
    {
        arr[i] = 0;
    }
}

void CopyByteArray( uint8_t * into_arr, const uint8_t * from_arr, uint8_t sz )
{
    for ( int i = 0; i < sz; i++ )
    {
        into_arr[i] = from_arr[i];
    }
}

void PrintByteArray( const uint8_t * arr, size_t sz )
{
    for ( int i = 0; i < ( sz - 1 ); i++ )
    {
        if ( 0x0F >= arr[i] ) Serial.print( "0" );

        if ( 0 == i )
            Serial.print( arr[i] );
        else
            Serial.print( arr[i], HEX );
        Serial.print( ", ");
    }
    if ( 0x0F >= arr[( sz - 1 )] ) Serial.print( "0" );
    Serial.println( arr[( sz - 1 )], HEX );
}

void StringToArray( const char * data, uint8_t * outData, uint8_t dataLen )
{
    // Convert the request data from string to uint8_t *
    for ( int i = 0; i < dataLen; i++ )
    {
        char first = data[( 2 * i )];
        char second = data[( 2 * i ) + 1];
        char combine[2] = { first, second };

        outData[i] = (uint8_t)( strtoul( &combine[0], NULL, 16 ) );
    }
}

int CanIdToInt( const char * data )
{
    // Convert the request data from string to uint8_t *
    char first = data[0];
    char second = data[1];
    char third = data[2];
    char combine[3] = { first, second, third };

    int result = (int)( strtoul( &combine[0], NULL, 16 ) );
    return result;
}
