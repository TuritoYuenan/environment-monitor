// Settings
#define BLYNK_PRINT Serial
#define TYPE_DHT DHT22 // DHT22 Sensor Type

// Blynk virtual pins
#define PIN_TEMP V0 // Temperature
#define PIN_HMDT V1 // Humidity
#define PIN_CRED V2 // Code Red
#define PIN_DESC V3 // Weather Description

// ESP32 pins
#define PIN_DHT 19  // DHT sensor data
#define PIN_LEDC 7  // Severe LED
#define PIN_LEDF 8  // Fahrenheit LED
#define PIN_UNIT 9  // Unit pin

// Include secrets
#include "secrets.h"

// Include libraries
#include <string>
#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Initialise Blynk timer
BlynkTimer timer;

// Initialise DHT22 sensor
DHT dht(PIN_DHT, TYPE_DHT);

// Initialise sensor humidity and temperature
float temperature, humidity;
bool useFahrenheit;

// Send temperature and humidity data to Blynk
void sendData() {
	int codeRedStatus = codeRed(temperature, useFahrenheit);
	String description = describeWeather(temperature, humidity, useFahrenheit);

	Blynk.beginGroup();
	Blynk.virtualWrite(PIN_TEMP, temperature);
	Blynk.virtualWrite(PIN_HMDT, humidity);
	Blynk.virtualWrite(PIN_CRED, codeRedStatus);
	Blynk.virtualWrite(PIN_DESC, description);
	Blynk.endGroup();
}

void setup() {
	// Debug console
	Serial.begin(9600);

	// Setup LED pins
	pinMode(PIN_LEDC, OUTPUT);
	pinMode(PIN_LEDF, OUTPUT);
	pinMode(PIN_UNIT, INPUT_PULLUP);

	// Authenticate Blynk
	Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

	// Send data every 1 second
	timer.setInterval(1000L, sendData);
}

void loop() {
	// Determine temperature unit
	useFahrenheit = digitalRead(PIN_UNIT) == 1 ? true : false;

	// Gather temperature and humidity values
	humidity = dht.readHumidity();
	temperature = dht.readTemperature(useFahrenheit);

	// Exit early to try again if any value failed to be read
	if (isnan(humidity) || isnan(temperature)) {
		Serial.println("# Unable to get value from DHT sensor!");
		return;
	}

	// Light up LED if Code Red
	int severity = codeRed(temperature, useFahrenheit) ? HIGH : LOW;
	digitalWrite(PIN_LEDC, severity);

	// Run Blynk and Blynk timer, then delay
	Blynk.run(); timer.run(); delay(1000);
}

// Activate Code Red if temperature is over 50 Celsius
bool codeRed(float temperature, bool useFahrenheit) {
	if (temperature > 50 && !useFahrenheit) return true;
	if (temperature > 122 && useFahrenheit) return true;
	return false;
}

String multiplexHumidity(float humidity, String low, String avg, String high) {
	if (humidity < 20) return low;
	else if (humidity < 60) return avg;
	else return high;
}

// Describe the current weather condition
String describeWeather(float temperature, float humidity, bool useFahrenheit) {
	// Convert to Celsius and try again if using Fahrenheit
	if (useFahrenheit) {
		float tempC = (temperature - 32) * 5 / 9;
		return describeWeather(tempC, humidity, false);
	}

	if (temperature < -15) return multiplexHumidity(humidity, "Crisp", "Freezing", "Icy");
	else if (temperature < 17) return multiplexHumidity(humidity, "Harsh", "Cold", "Snowy");
	else if (temperature < 35) return multiplexHumidity(humidity, "Droughty", "Temperate", "Humid");
	else if (temperature < 55) return multiplexHumidity(humidity, "Bone-dry",  "Hot", "Sultry");
	else return multiplexHumidity(humidity, "Desert-like", "Blistering", "Oven-like");
}
