#ifndef ROOMBA_BYTE_UTILS_H
#define ROOMBA_BYTE_UTILS_H

#include <Arduino.h>

void ArrayToString( const uint8_t * inArray, char * outStr, uint8_t arrSize );

void ClearByteArray( uint8_t * arr, uint8_t sz );
void ClearFrameArray( uint8_t * arr );

void CopyByteArray( uint8_t * into_arr, const uint8_t * from_arr, uint8_t sz );
void CopyFrameArray( uint8_t * into_arr, const uint8_t * from_arr );

void PrintByteArray( const uint8_t * arr, size_t sz );
void PrintFrameArray( const uint8_t * arr );

void StringToArray( const char * data, uint8_t * outData, uint8_t dataLen );
int CanIdToInt( const char * data );

#endif // ROOMBA_BYTE_UTILS_H
