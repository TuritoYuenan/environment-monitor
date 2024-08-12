#ifndef WEATHER_DATA
#define WEATHER_DATA

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

/// @brief Data received from the SEN0186 Weather Station Kit
struct WeatherData {
	uint8_t humidity; ///< @brief Humidity (%)
	uint32_t pressure; ///< @brief Pressure (Pa)
	uint16_t windDirection; ///< @brief Wind Direction (deg)
	float windSpeedAvg; ///< @brief Average Wind Speed (m/s)
	float windSpeedMax; ///< @brief Maximum Wind Speed (m/s)
	float rainfallH; ///< @brief Rainfall in 1 hour (mm)
	float rainfallD; ///< @brief Rainfall in 1 day (mm)
	float temperature; ///< @brief Temperature (deg C)

	/// @brief Generate weather station data
	WeatherData()
	{
		windDirection = random(360);
		windSpeedAvg = random(100);
		windSpeedMax = random(100);
		temperature = random(-30, 70);
		rainfallH = random(100);
		rainfallD = random(100);
		humidity = random(100);
		pressure = random(100000, 105000);
	}

	/// @brief Extract raw weather station data
	/// @param buffer SEN0186 data buffer
	WeatherData(char* buffer)
	{
		windDirection = charToInt(buffer, 1, 3);
		windSpeedAvg = charToInt(buffer, 5, 7) * 0.44704;
		windSpeedMax = charToInt(buffer, 9, 11) * 0.44704;
		temperature = (charToInt(buffer, 13, 15) - 32.00) * 5.00 / 9.00;
		rainfallH = charToInt(buffer, 17, 19) * 25.40 * 0.01;
		rainfallD = charToInt(buffer, 21, 23) * 25.40 * 0.01;
		humidity = charToInt(buffer, 25, 26);
		pressure = charToInt(buffer, 28, 32) * 10.00;
	}

	/// @brief Convert weather station data to JSON format
	/// @return Weather station data formatted in a JSON document
	String toJSON()
	{
		String JSONTemplate = R"({"humidity": {HMDT}, "pressure": {PRSR}, "temperature": {TEMP}, "rainfall_D": {RNFD}, "rainfall_H": {RNFH}, "windSpeedAvg": {WSAG}, "windSpeedMax": {WSMX}, "windDirection": {WDRT}})";

		JSONTemplate.replace("{PRSR}", String(pressure));
		JSONTemplate.replace("{HMDT}", String(humidity));
		JSONTemplate.replace("{TEMP}", String(temperature));
		JSONTemplate.replace("{RNFH}", String(rainfallH));
		JSONTemplate.replace("{RNFD}", String(rainfallD));
		JSONTemplate.replace("{WSAG}", String(windSpeedAvg));
		JSONTemplate.replace("{WSMX}", String(windSpeedMax));
		JSONTemplate.replace("{WDRT}", String(windDirection));
		return JSONTemplate;
	}
};

#endif // MARK: WEATHER_DATA
