#define WIFI_NAME "Swinburne Students"
#define WIFI_PASS "Swinburne@a35"

/// @brief Data received from the SEN0186 Weather Station Kit
struct WeatherData {
	int windDirection; // Wind Direction (deg)
	float windSpeedAvg; // Average Wind Speed (m/s)
	float windSpeedMax; // Maximum Wind Speed (m/s)
	float temperature; // Temperature (deg C)
	float rainfallH; // Rainfall in 1 hour (mm)
	float rainfallD; // Rainfall in 1 day (mm)
	int humidity; // Humidity (%)
	float pressure; // Pressure, barometric (hPa)
};
