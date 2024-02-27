/**
 * @file Minh Triet's Weather Station - Code for ESP8266 module
 * @version 0.7.0
 * @author Nguyen Ta Minh Triet <turitoyuenan@proton.me>
 * @ref https://wiki.dfrobot.com/APRS_Weather_Station_Sensor_Kit_SEN0186
 * @ref https://lastminuteengineers.com/bme280-esp8266-weather-station
 * @ref https://pijaeducation.com/serial-print-and-printf-solved
*/

#include <BlockNot.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include "certs.h"
#include "secrets.h"
#include "wetter-lib.h"

/// @brief Raw data received from the weather station
char stationData[35];

/// @brief Structured weather station data
WeatherData weatherData;

/// @brief Timer for database sending routine
BlockNot sendTimer(5000);

/// @brief Timer for data printing routine
BlockNot logTimer(1000);

/// @brief Tasks to do once at startup
void setup()
{
	Serial.begin(9600);
	Serial.setDebugOutput(true);

	// Connect to WiFi
	connectWiFi(WIFI_NAME, WIFI_PASS);
}

/// @brief Tasks to routinely do
void loop()
{
	// Get data from weather station. Redo if format is wrong
	Serial.readBytes(stationData, sizeof(stationData));
	if (stationData[0] != 'c') { return; }

	// Store weather station data
	weatherData = storeData(stationData);
	String JSON = createJSON(weatherData);

	// Print out data.
	// printData(weatherData);
	Serial.println(JSON);

	// Send data to Astra DB
	if (sendTimer.TRIGGERED) { sendData(JSON); }
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

/// @brief Convert characters to integers
/// @param buffer Raw weather station data
/// @param start First character to include
/// @param stop Last character to include
/// @return An integer, negative if there's a minus sign
int charToInt(char* buffer, int start, int stop)
{
	int result = 0;
	int temp[stop - start + 1];

	// Negative number (contains a minus sign)
	if (buffer[start] == '-') {
		for (int i = start + 1; i <= stop; i++) {
			temp[i - start] = buffer[i] - '0';
			result = 10 * result + temp[i - start];
		}
		return 0 - result;
	}

	// Non-negative number
	for (int i = start; i <= stop; i++) {
		temp[i - start] = buffer[i] - '0';
		result = 10 * result + temp[i - start];
	}
	return result;
}

/// @brief Convert raw data from the weather station to structured data
/// @param buffer Raw weather station data
/// @return data Structured weather station data
WeatherData storeData(char* buffer)
{
	WeatherData data;

	data.windDirection = charToInt(buffer, 1, 3);
	data.windSpeedAvg = charToInt(buffer, 5, 7) * 0.44704;
	data.windSpeedMax = charToInt(buffer, 9, 11) * 0.44704;
	data.temperature = (charToInt(buffer, 13, 15) - 32.00) * 5.00 / 9.00;
	data.rainfallH = charToInt(buffer, 17, 19) * 25.40 * 0.01;
	data.rainfallD = charToInt(buffer, 21, 23) * 25.40 * 0.01;
	data.humidity = charToInt(buffer, 25, 26);
	data.pressure = charToInt(buffer, 28, 32) * 10.00;

	return data;
}

/// @brief Send weather station data to an Astra database
/// @param data Structured weather station data
void sendData(String json)
{
	std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
	HTTPClient https;

	client->setFingerprint(fingerprint_astra_datastax_com);

	// Create a HTTP request with headers
	https.begin(*client, astradb_host, astradb_port);
	https.addHeader("content-type", "application/json");
	https.addHeader("x-cassandra-token", ASTRA_TOKEN);

	// Send HTTP POST request
	int responseCode = https.POST(json);

	if (responseCode > 0) {
		Serial.print("Request sent! Code: "); Serial.println(responseCode);
		String payload = https.getString(); Serial.println(payload);
	} else {
		Serial.print("Request failed! Code: "); Serial.println(responseCode);
	}

	// Free resources
	https.end();
}

/// @brief Create a JSON document from weather station data
/// @param data Structured weather station data
/// @return A JSON document containing a timestamp field and data fields
String createJSON(WeatherData data)
{
	String JSONTemplate = R"({
		"date": "2024-02-26T14:14:14.000Z",
		humidity: {HMDT},
		pressure: {PRSR},
		temperature: {TEMP},
		rainfalld: {RNFD}, rainfallh: {RNFH},
		windspeedavg: {WSAG}, windspeedmax: {WSMX},
		winddirection: {EDRT}
	})";

	JSONTemplate.replace("{PRSR}", String(data.pressure));
	JSONTemplate.replace("{HMDT}", String(data.humidity));
	JSONTemplate.replace("{TEMP}", String(data.temperature));
	JSONTemplate.replace("{RNFH}", String(data.rainfallH));
	JSONTemplate.replace("{RNFD}", String(data.rainfallD));
	JSONTemplate.replace("{WSAG}", String(data.windSpeedAvg));
	JSONTemplate.replace("{WSMX}", String(data.windSpeedMax));
	JSONTemplate.replace("{WDRT}", String(data.windDirection));
	return JSONTemplate;
}
