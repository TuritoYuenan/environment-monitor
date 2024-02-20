#include <SoftwareSerial.h>

/// @brief ESP8266 Serial
SoftwareSerial SerialExport(8, 9);

/// @brief Raw weather station data
char buffer[35];

/// @brief Tasks to do once at startup
void setup() {
	Serial.begin(9600);
	SerialExport.begin(9600);
}

/// @brief Tasks to routinely do
void loop() {
	if (Serial.available()) {
		// Receive data from weather station
		getData(buffer);
		// Send data to ESP8266 board
		SerialExport.print(buffer);
	}
}

/// @brief Get raw weather station data
/// @param buffer Variable to save data into
void getData(char* buffer)
{
	for (int i = 0; i < 35; i++) {
		if (Serial.available()) {
			buffer[i] = Serial.read();
		} else {
			i--;
		}
		if (buffer[0] != 'c') { i = -1; }
	}
}
