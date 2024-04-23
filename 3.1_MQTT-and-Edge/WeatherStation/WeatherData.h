#ifndef WeatherData_h
#define WeatherData_h

#include <Arduino.h>
#include <Stream.h>

// Get buffer from the stream
void getBuffer(Stream& serial);

// Transform characters to integer from a specific range
int transCharToInt(char* _buffer, int _start, int _stop);

// Transform characters to integer with a specific transformation
int transCharToInt_T(char* _buffer);

// Ưind direction
int WindDirection();

// Average wind speed
float WindSpeedAverage();

// Maximum wind speed
float WindSpeedMax();

// Temperature
float Temperature();

// Rainfall for the last hour
float RainfallOneHour();

// Rainfall for the last day
float RainfallOneDay();

// Humidity
int Humidity();

// Barometric pressure
float BarPressure();

#endif