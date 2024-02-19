#include <SoftwareSerial.h>

/// @brief ESP8266 Serial
SoftwareSerial SerialExport(8, 9);

/// @brief Tasks to do once at startup
void setup() {
	Serial.begin(9600);
	SerialExport.begin(9600);
}

/// @brief Tasks to routinely do
void loop() {
	if (Serial.available() && SerialExport.available()) {
		// Receive data from weather station
		char data = Serial.read();
		// Send data to ESP8266 board
		SerialExport.print(data);
	}
}
