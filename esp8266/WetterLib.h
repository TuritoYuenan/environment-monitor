#define WIFI_NAME "Swinburne Students"
#define WIFI_PASS "Swinburne@a35"

/// @brief Data received from the SEN0186 Weather Station Kit
struct WeatherData {
	/// @brief Wind Direction (deg)
	int windDirection;
	/// @brief Average Wind Speed (m/s)
	float windSpeedAvg;
	/// @brief Maximum Wind Speed (m/s)
	float windSpeedMax;
	/// @brief Temperature (deg C)
	float temperature;
	/// @brief Rainfall in 1 hour (mm)
	float rainfallH;
	/// @brief Rainfall in 1 day (mm)
	float rainfallD;
	/// @brief Humidity (%)
	int humidity;
	/// @brief Pressure, barometric (hPa)
	float pressure;
};
