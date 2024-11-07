/**
 * @file Minh Triet's Weather Station - Code for ESP32 module
 * @version 2.9.0
 * @author Nguyen Ta Minh Triet <turitoyuenan@proton.me>
 * @ref https://wiki.dfrobot.com/APRS_Weather_Station_Sensor_Kit_SEN0186
 * @ref https://pijaeducation.com/serial-print-and-printf-solved
*/

// Debug mode
#define IS_DEBUGGING true

// MARK: Libraries
// ESP32 libraries
#include <NetworkClientSecure.h>
#include <WiFi.h>

// Third party libraries
#include <PubSubClient.h>
#include <BlockNot.h>

// Internal libraries
#include "secrets.h"
#include "weather_data.h"

// MARK: Globals
/// @brief Raw data received from the weather station
char stationData[35];

/// @brief Structured weather station data
WeatherData data;

/// @brief WiFi client
NetworkClient wifi;

/// @brief MQTT client
PubSubClient client;

/// @brief Timer to log data
BlockNot logTimer(5, SECONDS);

/// @brief Tasks to do at startup
void setup() // MARK: Setup
{
	// Start Serial communication
	Serial.begin(115200);
	Serial.setDebugOutput(IS_DEBUGGING);

	// Connect to WiFi
	connectWiFi(WIFI_NAME, WIFI_PASS);

	// Setup MQTT client
	client
		.setClient(wifi)
		.setServer(IPAddress(MQTT_BROKER), 1883)
		.setCallback(handleMessage);

	// Do time syncing stuffs
	handleTime();
}

/// @brief Tasks to do routinely
void loop() // MARK: Loop
{
	while (!client.connected()) { connectBroker(); }

	// Get data from weather station. Redo if format is wrong
	// getData(stationData);
	// if (stationData[0] != 'c') { return; }

	// Store weather station data
	data = WeatherData();
	String weatherJSON = data.toJSON();

	// Log data
	if (logTimer.triggered()) {
		if (IS_DEBUGGING) { Serial.println(stationData); }

		Serial.println(weatherJSON);
		client.publish(MQTT_TOPIC, weatherJSON.c_str());
	}
}

/// @brief Callback function when received an MQTT message
/// @param topic MQTT Topic where message is received
/// @param message Message content
/// @param length Message length
void handleMessage(char* topic, uint8_t* message, unsigned int length) // MARK: Callback
{
	Serial.print("Message arrived on topic: ");
	Serial.print(topic);
	Serial.print(". Message: ");

	for (int i = 0; i < length; i++) {
		Serial.print((char)message[i]);
	}
}

/// @brief Connect to WiFi
/// @param ssid WiFi name / SSID
/// @param password WiFi password
void connectWiFi(const char* ssid, const char* password) // MARK: WiFi
{
	Serial.printf("\nWiFi is %s. Connecting.", ssid);
	WiFi.hostname("ZimmerWetter");
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print(".");
	}

	if (WiFi.status() == WL_CONNECTED) {
		Serial.print("\nConnected to WiFi as: ");
		Serial.println(WiFi.localIP());
	}
}

/// @brief Connect to MQTT Broker
/// @author Kallen Houston
void connectBroker() // MARK: MQTT
{
	Serial.println("Connecting to MQTT Broker...");

	if (client.connect(BROKER_CLIENT_ID)) {
		Serial.println("Connected to MQTT Broker");
	} else {
		Serial.print("Failed connecting to MQTT Broker: ");
		Serial.println(client.state());
		Serial.println("Retrying in 5 seconds...\n");
		delay(5000);
	}
}

/// @brief Sync with with NTP servers to get current time
void handleTime() // MARK: NTP
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
