#include "WeatherData.h"

char                 databuffer[35]; // Buffer to store data
double               temp; // Temporary variable for calculations

// Get buffer from the stream
void getBuffer(Stream& serial) {
  int index;
  for (index = 0; index < 35; index++) {
    if (Serial.available()) {
      databuffer[index] = Serial.read();
      // If the first character is not 'c', reset the index
      if (databuffer[0] != 'c') {
        index = -1;
      }
    } else {
      index--;
    }
  }
}

// Transform characters to integer from a specific range
int transCharToInt(char* _buffer, int _start, int _stop) {
  int _index;
  int result = 0;
  int num = _stop - _start + 1;
  int _temp[num];
  for (_index = _start; _index <= _stop; _index++) {
    _temp[_index - _start] = _buffer[_index] - '0';
    result = 10 * result + _temp[_index - _start];
  }
  return result;
}

// Transform characters to integer with a specific transformation
int transCharToInt_T(char* _buffer) {
  int result = 0;
  if (_buffer[13] == '-') {
    result = 0 - (((_buffer[14] - '0') * 10) + (_buffer[15] - '0'));
  } else {
    result = ((_buffer[13] - '0') * 100) + ((_buffer[14] - '0') * 10) + (_buffer[15] - '0');
  }
  return result;
}

// Wind direction
int WindDirection() {
  return transCharToInt(databuffer, 1, 3);
}

// Average wind speed
float WindSpeedAverage() {
  temp = 0.44704 * transCharToInt(databuffer, 5, 7);
  return temp;
}

// Maximum wind speed
float WindSpeedMax() {
  temp = 0.44704 * transCharToInt(databuffer, 9, 11);
  return temp;
}

// Temperature
float Temperature() {
  temp = (transCharToInt_T(databuffer) - 32.00) * 5.00 / 9.00;
  return temp;
}

// Rainfall for the last hour
float RainfallOneHour() {
  temp = transCharToInt(databuffer, 17, 19) * 25.40 * 0.01;
  return temp;
}

// Rainfall for the last day
float RainfallOneDay() {
  temp = transCharToInt(databuffer, 21, 23) * 25.40 * 0.01;
  return temp;
}

// Humidity
int Humidity() 
{
  return transCharToInt(databuffer, 25, 26);
}

// Barometric pressure
float BarPressure() 
{
  temp = transCharToInt(databuffer, 28, 32);
  return temp / 10.00;
}