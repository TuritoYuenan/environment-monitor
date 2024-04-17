/**
 * @file Minh Triet's Weather Station - Code for ESP32 module
 * @version 2.9.0
 * @author Nguyen Ta Minh Triet <turitoyuenan@proton.me>
 * @ref https://wiki.dfrobot.com/APRS_Weather_Station_Sensor_Kit_SEN0186
 * @ref https://pijaeducation.com/serial-print-and-printf-solved
*/

// Debug mode
#define IS_DEBUGGING false

// Library for non-blocking code
#include <BlockNot.h>

//Library for Json data fomat
#include <ArduinoJson.h>

//Library for Time NTP to get cur timeStamp
#include <NTPClient.h>
#include <WiFiUdp.h>

// Libraries for WiFi connection
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <WiFi.h>

// Internal libraries
#include "Secrets.h"
#include "WeatherData.h"
#include "Certificate.h"

/// @brief Raw data received from the weather station
char stationData[35];

/// @brief Structured weather station data
WeatherData data;

/// @brief Weather station data in JSON format
String weatherJSON;

/// @brief Timer for database sending routine
BlockNot sendTimer(10, SECONDS);

/// @brief Timer for data printing routine
BlockNot logTimer(2, SECONDS);

/// @brief Secure WiFi client
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
}

/// @brief Tasks to routinely do
void loop()
{
	// Get data from weather station. Redo if format is wrong
	Serial.readBytes(stationData, sizeof(stationData));
	if (stationData[0] != 'c') { return; }

	// Store weather station data
	data = WeatherData(stationData); // data = WeatherData();
	weatherJSON = data.toJSON();

	// Print out data.
	if (logTimer.triggered()) {
		Serial.println(weatherJSON);
	}

	// Send data to database
	if (sendTimer.triggered()) {
		// Send data to database
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
