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

void weather() {
	// Send temperature and humidity data to Blynk
	Blynk.virtualWrite(PIN_TEMP, temp_celsius);
	Blynk.virtualWrite(PIN_HMDT, humidity);
}

void setup() {
	// Debug console
	Serial.begin(9600);

	// Setup LED pin
	pinMode(PIN_LED, OUTPUT);

	// Authenticate Blynk
	Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

	// Send data every 0.9 seconds
	timer.setInterval(900L, weather);
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
		digitalWrite(PIN_LED, HIGH);
	} else {
		digitalWrite(PIN_LED, LOW);
	}

	// Run Blynk and Blynk timer, then delay
	Blynk.run(); timer.run(); delay(100);
}
