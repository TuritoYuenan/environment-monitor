/**
 * @file Minh Triet's Weather Station - Code for ESP8266 module
 * @version 2.0
 * @author Nguyen Ta Minh Triet <turitoyuenan@proton.me>
 * @ref https://wiki.dfrobot.com/APRS_Weather_Station_Sensor_Kit_SEN0186
 * @ref https://lastminuteengineers.com/bme280-esp8266-weather-station
 * @ref https://pijaeducation.com/serial-print-and-printf-solved
*/

// Debug mode
#define IS_DEBUGGING false

// Library for non-blocking code
#include <BlockNot.h>

// Libraries for WiFi connection
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// Internal libraries
#include "Secrets.h"
#include "WeatherData.h"
#include "Certificate.h"

/// @brief Raw data received from the weather station
char stationData[35];

/// @brief Structured weather station data
WeatherData weatherData;

/// @brief Weather station data in JSON format
String weatherJSON;

/// @brief Timer for database sending routine
BlockNot sendTimer(10, SECONDS);

/// @brief Timer for data printing routine
BlockNot logTimer(2, SECONDS);

/// @brief WiFi client with BearSSl security
WiFiClientSecure client;

/// @brief HTTPS client
HTTPClient https;

/// @brief Tasks to do once at startup
void setup()
{
	Serial.begin(9600);
	Serial.setDebugOutput(IS_DEBUGGING);

	// Connect to WiFi
	connectWiFi(WIFI_NAME, WIFI_PASS);

	// Do time syncing stuffs
	handleTime();

	// Connect to database
	client.setCACert(cert_ISRG_Root_X1);
	client.connect(XATA_host, XATA_port);
}

/// @brief Tasks to routinely do
void loop()
{
	// Get data from weather station. Redo if format is wrong
	// Serial.readBytes(stationData, sizeof(stationData));
	// if (stationData[0] != 'c') { return; }
	getData(stationData);

	// Store weather station data
	weatherData = WeatherData(stationData);
	weatherJSON = weatherData.toJSON();

	// Print out data.
	if (logTimer.triggered()) {
		Serial.println(weatherJSON);
	}

	// Send data to database
	if (sendTimer.triggered()) {
		sendData(weatherJSON);
	}
}

/// @brief Connect to WiFi
/// @param ssid WiFi name / SSID
/// @param password WiFi password
void connectWiFi(const char* ssid, const char* password)
{
	Serial.printf("\nWiFi is %s. Connecting.", ssid);
	WiFi.hostname(F("ZimmerWetter"));
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print(".");
	}

	if (WiFi.status() == WL_CONNECTED) {
		Serial.print("\nConnected! View your weather at: ");
		Serial.println(WiFi.localIP());
	}
}

/// @brief Sync with with NTP servers to get current time
void handleTime()
{
	configTime(7 * 3600, 0, "asia.pool.ntp.org", "pool.ntp.org", "time.nist.gov");

	Serial.print("Waiting for NTP time sync");
	time_t now = time(nullptr);
	while (now < 8 * 3600 * 2) {
		delay(500);
		Serial.print(".");
		now = time(nullptr);
	}
	Serial.println("");
	struct tm timeinfo;
	gmtime_r(&now, &timeinfo);
	Serial.print("Current time: ");
	Serial.print(asctime(&timeinfo));
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

/// @brief Send weather station data to an Astra database
/// @param data Structured weather station data
void sendData(String json)
{
	// Create a HTTP request with headers
	https.begin(client, XATA_host, XATA_port, DB_ENDPOINT, true);
	https.addHeader("Content-Type", "application/json");
	https.addHeader("Authorization", "Bearer " API_KEY);

	// Send request to POST weather data
	int responseCode = https.POST(json);

	// Handle response
	if (responseCode > 0) {
		Serial.print("Request sent! Code: ");
		Serial.println(responseCode);

		if (IS_DEBUGGING) {
			String payload = https.getString();
			Serial.println(payload);
		}
	} else {
		Serial.print("Request failed! Code: ");
		Serial.println(responseCode);
	}

	// Free resources
	https.end();
}
