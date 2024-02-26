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

/// @brief Data received from the SEN0186 Weather Station Kit
struct WeatherData {
	/// @brief Wind Direction (deg)
	int windDirection;
	/// @brief Average Wind Speed (m/s)
	float windSpeedAvg;
	/// @brief Maximum Wind Speed (m/s)
	float windSpeedMax;
	/// @brief Rainfall in 1 hour (mm)
	float rainfallH;
	/// @brief Rainfall in 1 day (mm)
	float rainfallD;
	/// @brief Temperature (deg C)
	float temperature;
	/// @brief Humidity (%)
	int humidity;
	/// @brief Pressure (Pa)
	int pressure;
};
