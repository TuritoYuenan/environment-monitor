/**
 * @file Minh Triet's Weather Station - Code for ESP32 module
 * @version 2.9.0
 * @author Nguyen Ta Minh Triet <turitoyuenan@proton.me>
 * @ref https://wiki.dfrobot.com/APRS_Weather_Station_Sensor_Kit_SEN0186
 * @ref https://pijaeducation.com/serial-print-and-printf-solved
*/

// Debug mode
#define IS_DEBUGGING false

// Buzzer pin
#define BUZZER D17

// MARK: Libraries
// WiFi connection
#include <WiFiClientSecure.h>

// MQTT client
#include <PubSubClient.h>

// Non-blocking code
#include <BlockNot.h>

// Internal libraries
#include "Secrets.h"
#include "WeatherData.h"
// #include "Certificate.h"

// MARK: Globals
/// @brief Raw data received from the weather station
char stationData[35];

/// @brief Structured weather station data
WeatherData data;

/// @brief Timer for database sending routine
BlockNot sendTimer(10, SECONDS);

/// @brief Timer for data printing routine
BlockNot logTimer(2, SECONDS);

/// @brief Secure WiFi client
WiFiClientSecure wifi;

/// @brief MQTT pub/sub client
PubSubClient client(wifi);

/// @brief Tasks to do once at startup
void setup() // MARK: Setup
{
	Serial.begin(9600);
	Serial.setDebugOutput(IS_DEBUGGING);

	// Connect to WiFi
	connectWiFi(WIFI_NAME, WIFI_PASS);

	// Setup MQTT client
	client.setServer(MQTT_BROKER, 1883);
	client.setCallback(mqttCallback);

	// Do time syncing stuffs
	handleTime();

	// Set root certificate
	// wifi.setCACert(cert_ISRG_Root_X1);
}

/// @brief Tasks to routinely do
void loop() // MARK: Loop
{
	// Get data from weather station. Redo if format is wrong
	// Serial.readBytes(stationData, sizeof(stationData));
	// if (stationData[0] != 'c') { return; }
	getData(stationData);

	// Store weather station data
	data = WeatherData(stationData);
	String weatherJSON = data.toJSON();

	// Print out data.
	if (logTimer.triggered()) {
		Serial.println(weatherJSON);
	}

	// Send data to database
	if (sendTimer.triggered()) {
		// Send data to database
	}
}

/// @brief Callback function when received an MQTT message
/// @param topic MQTT Topic where message is received
/// @param message Message content
/// @param length Message length
void mqttCallback(char* topic, uint8_t* message, unsigned int length) // MARK: Callback
{
	Serial.print("Message arrived on topic: ");
	Serial.print(topic);
	Serial.print(". Message: ");
	String messageTemp;

	for (int i = 0; i < length; i++) {
		Serial.print((char)message[i]);
		messageTemp += (char)message[i];
	}
}

/// @brief Connect to WiFi
/// @param ssid WiFi name / SSID
/// @param password WiFi password
void connectWiFi(const char* ssid, const char* password) // MARK: WiFi
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
void handleTime() // MARK: NTP Time
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
void getData(char* buffer) // MARK: Get Data
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
