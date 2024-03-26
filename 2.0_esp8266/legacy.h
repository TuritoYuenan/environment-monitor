#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "wetter-lib.h"

/// @brief Server for web dashboard
ESP8266WebServer server(80);

/// @brief Web server HTML template
String htmlTemplate = R"(<!DOCTYPE html><html lang='en'><head>
	<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>
	<title>Zimmer Wetter</title><link rel='icon' href='data:,'><style>
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
		<div><img src='https://raw.githubusercontent.com/TuritoYuenan/zimmer-wetter/init/web-server/swinburne.svg' alt='Swinburne University Logo'></div>
		<div id='title'><h1>Minh Triet's Weather Station</h1><h2>Made with Arduino Uno, ESP8266, SEN0186, and passion🔥</h2></div>
	</header><main class='grid'>
		<section style='grid-area: tp'><h2>Temperature</h2><p>{TEMP} &deg;C</p></section>
		<section style='grid-area: ht'><h2>Humidity</h2><p>{HMDT} %</p></section>
		<section style='grid-area: ps'><h2>Barometric Pressure</h2><p>{PRSR} Pa</p></section>
		<section style='grid-area: rn'><h2>Rainfall (1 Hour)</h2><p>{RNFH} mm</p><h2>Rainfall (1 Day)</h2><p>{RNFD} mm</p></section>
		<section style='grid-area: wd'><h2>Wind Direction</h2><p>{WDRT} degrees</p>
			<h2>Average Wind Speed</h2><p>{WSAG} m/s</p><h2>Maximum Wind Speed</h2><p>{WSMX} m/s</p></section>
	</main><footer>&COPY; 2024 Nguyen Ta Minh Triet @
		<a target='_blank' href='https://turitoyuenan.pages.dev'>turitoyuenan.pages.dev</a></footer>
</body></html>)";

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
	server.on("/", []() {server.send(200, "text/html", hydrateHTML(htmlTemplate, {/*weatherData*/}));});
	server.onNotFound([]() {server.send(404, "text/plain", "there's only 1 page bro");});
	server.begin();

	Serial.println("Started web server!");
}

void loop() {
	// Serve webpage if requested
	server.handleClient();
}
