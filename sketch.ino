// Include settings
#include "settings.h"

// Include libraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Initialise Blynk timer
BlynkTimer timer;

// Initialise DHT22 sensor
DHT dht(PIN_DHT, DHTTYPE);

// Initialise sensor humidity and temperature
float humidity, temp_celsius, temp_frnheit;

// Send temperature and humidity data to Blynk
void sendData() {
	Blynk.beginGroup();
	Blynk.virtualWrite(PIN_TEMP, temp_celsius);
	Blynk.virtualWrite(PIN_HMDT, humidity);

	Blynk.endGroup();
}

void setup() {
	// Debug console
	Serial.begin(9600);

	// Setup LED pins
	pinMode(PIN_LEDC, OUTPUT);
	pinMode(PIN_LEDF, OUTPUT);

	// Authenticate Blynk
	Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

	// Send data every 0.9 seconds
	timer.setInterval(900L, sendData);
}

void loop() {
	// Gather temperature and humidity values
	humidity = dht.readHumidity();
	temp_celsius = dht.readTemperature();
	temp_frnheit = dht.readTemperature(true);

	// Exit early to try again if any value failed to be read
	if (isnan(humidity) || isnan(temp_celsius) || isnan(temp_frnheit)) {
		Serial.println(F("Failed to read from DHT sensor!"));
		return;
	}

	// Light up if temperature is at critical level
	if (temp_celsius > 40) {
		digitalWrite(PIN_LEDC, HIGH);
	} else {
		digitalWrite(PIN_LEDC, LOW);
	}

	// Run Blynk and Blynk timer, then delay
	Blynk.run(); timer.run(); delay(100);
}

BLYNK_CONNECTED() {
	Blynk.syncAll();
}
