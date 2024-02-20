/**
 * @file Minh Triet's Weather Station - Code for ESP8266 module
 * @version 0.7.0
 * @author Nguyen Ta Minh Triet <turitoyuenan@proton.me>
 * @ref https://wiki.dfrobot.com/APRS_Weather_Station_Sensor_Kit_SEN0186
 * @ref https://lastminuteengineers.com/bme280-esp8266-weather-station
 * @ref https://pijaeducation.com/serial-print-and-printf-solved
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WetterLib.h"

/// @brief Raw data received from the weather station
char stationData[35];

/// @brief Structured weather station data
WeatherData weatherData;

/// @brief Web server
ESP8266WebServer server(80);

/// @brief Web server HTML template
String htmlTemplate = R"(<!DOCTYPE html><html lang='en'><head>
	<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>
	<title>Zweiten Wetter</title><link rel='icon' href='data:,'><style>
		#title {display: grid; align-content: center; text-align: center;} #title > * {margin-block: 0.5rem;}
		.grid {display: grid; gap: 1rem;} @media (width <= 900px) {.grid {display: flex; flex-direction: column;}}
		body {max-width: 1280px; margin: auto; padding: 1rem; background: #ED1C2E; font-family: system-ui, sans-serif;}
		body > * {margin-bottom: 1rem;} header {grid-template-columns: auto 1fr;} * {box-sizing: border-box;}
		main {grid-template-columns: 1fr 1fr 1fr; grid-template-areas: 'tp ht ps' 'wd wd rn';}
		h1, h2, p {margin-block: 0.8rem;} h1 {font-size: 3rem;} p {font-size: 3rem; text-align: end;}
		div, section, footer {padding: 1rem 2rem; border-radius: 1rem; background: white;}
		img {margin: auto; padding-inline: 1rem; display: block;}
	</style><script>setInterval(() => {var x = new XMLHttpRequest(); x.onreadystatechange = function () {
		if (this.readyState == 4 && this.status == 200) {document.body.innerHTML = this.responseText}
	}; x.open('GET', '/', true); x.send(); }, 1000);</script>
</head><body><header class='grid'>
		<div><img src='./assets/swinburne.svg' alt='Swinburne University Logo'></div>
		<div id='title'><h1>Minh Triet's Weather Station</h1><h2>Made with Arduino Uno, ESP8266, SEN0186, and passion🔥</h2></div>
	</header><main class='grid'>
		<section style='grid-area: tp'><h2>Temperature</h2><p>{TEMP} &deg;C</p></section>
		<section style='grid-area: ht'><h2>Humidity</h2><p>{HMDT} %</p></section>
		<section style='grid-area: ps'><h2>Barometric Pressure</h2><p>{PRSR} hPa</p></section>
		<section style='grid-area: rn'><h2>Rainfall (1 Hour)</h2><p>{RNFH} mm</p><h2>Rainfall (1 Day)</h2><p>{RNFD} mm</p></section>
		<section style='grid-area: wd'><h2>Wind Direction</h2><p>{WDRT} degrees</p>
			<h2>Average Wind Speed</h2><p>{WSAG} m/s</p><h2>Maximum Wind Speed</h2><p>{WSMX} m/s</p></section>
	</main><footer>&COPY; 2024 Nguyen Ta Minh Triet @
		<a target='_blank' href='https://turitoyuenan.pages.dev'>turitoyuenan.pages.dev</a></footer>
</body></html>)";

/// @brief Tasks to do once at startup
void setup()
{
	Serial.begin(9600);

	// Connect to WiFi
	connectWiFi(WIFI_NAME, WIFI_PASS);

	// Setup web server
	server.on("/", []() {server.send(200, "text/html", hydrateHTML(htmlTemplate, weatherData));});
	server.onNotFound([]() {server.send(404, "text/plain", "there's only 1 page bro");});
	server.begin();

	Serial.println("Started web server!");
}

/// @brief Tasks to routinely do
void loop()
{
	// Get data from weather station. Redo if format is wrong
	Serial.readBytes(stationData, sizeof(stationData));
	if (stationData[0] != 'c') { return; }

	// Convert and store weather station data
	storeData(weatherData, stationData);

	// Print out data. Might be removed in favor of web server
	printData(weatherData);

	// Serve webpage if requested
	server.handleClient();
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

/// @brief Organise raw data received from the weather station to structured data
/// @param data Structured weather station data
/// @param buffer Raw weather station data
void storeData(WeatherData data, char* buffer)
{
	data.windDirection = charToInt(buffer, 1, 3);
	data.windSpeedAvg = charToInt(buffer, 5, 7) * 0.44704;
	data.windSpeedMax = charToInt(buffer, 9, 11) * 0.44704;
	data.temperature = (charToInt(buffer, 13, 15) - 32.00) * 5.00 / 9.00;
	data.rainfallH = charToInt(buffer, 17, 19) * 25.40 * 0.01;
	data.rainfallD = charToInt(buffer, 21, 23) * 25.40 * 0.01;
	data.humidity = charToInt(buffer, 25, 26);
	data.pressure = charToInt(buffer, 28, 32) / 10.00;
}

/// @brief Print out weather station data
/// @param data Structured weather station data
void printData(WeatherData data)
{
	Serial.printf("Wind Direction: %d deg\n", data.windDirection);
	Serial.printf("Avg Wind Speed: %f m/s\n", data.windSpeedAvg);
	Serial.printf("Max Wind Speed: %f m/s\n", data.windSpeedMax);
	Serial.printf("Rainfall in 1h: %f mm\n", data.rainfallH);
	Serial.printf("Rainfall in 1d: %f mm\n", data.rainfallD);
	Serial.printf("Temperature: %f deg C\n", data.temperature);
	Serial.printf("Humidity: %d %\n", data.humidity);
	Serial.printf("Pressure: %f hPa\n", data.pressure);
	Serial.println("");
}

/// @brief Connect to WiFi
/// @param ssid WiFi name / SSID
/// @param password WiFi password
void connectWiFi(const char* ssid, const char* password)
{
	Serial.printf("Connecting to WiFi %s", ssid);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print(".");
	}

	Serial.printf("\nConnected! IP is %s\n", WiFi.localIP());
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
