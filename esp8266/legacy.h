#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "wetter-lib.h"

/// @brief Server for web dashboard
ESP8266WebServer server(80);

/// @brief Print out weather station data
/// @param data Structured weather station data
void printData(WeatherData data)
{
	Serial.println("");
	Serial.printf("Temperature: %f deg C\n", data.temperature);
	Serial.printf("Humidity: %d percents\n", data.humidity);
	Serial.printf("Pressure: %d Pa\n", data.pressure);
	Serial.printf("Rainfall: (1h) %f mm, (1d) %f mm\n", data.rainfallH, data.rainfallD);
	Serial.printf("Wind Speed: avg %f m/s, max %f m/s\n", data.windSpeedAvg, data.windSpeedMax);
	Serial.printf("Wind Direction: %d deg\n", data.windDirection);
}

/// @brief Fill weather station data into a HTML file for web server
/// @param html A HTML template with placeholders to fill in data
/// @param data Structured weather station data
/// @return A HTML webpage with the numbers plugged in
String hydrateHTML(String html, WeatherData data)
{
	html.replace("{PRSR}", String(data.pressure));
	html.replace("{HMDT}", String(data.humidity));
	html.replace("{TEMP}", String(data.temperature));
	html.replace("{RNFH}", String(data.rainfallH));
	html.replace("{RNFD}", String(data.rainfallD));
	html.replace("{WSAG}", String(data.windSpeedAvg));
	html.replace("{WSMX}", String(data.windSpeedMax));
	html.replace("{WDRT}", String(data.windDirection));
	return html;
}

void setup() {
	// Setup web server
	server.on("/", []() {server.send(200, "text/html", hydrateHTML(htmlTemplate, weatherData));});
	server.onNotFound([]() {server.send(404, "text/plain", "there's only 1 page bro");});
	server.begin();

	Serial.println("Started web server!");
}

void loop() {
	// Serve webpage if requested
	server.handleClient();
}
