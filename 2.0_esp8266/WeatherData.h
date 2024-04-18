/// @brief Data received from the SEN0186 Weather Station Kit
struct WeatherData {
	int windDirection; ///< @brief Wind Direction (deg)
	float windSpeedAvg; ///< @brief Average Wind Speed (m/s)
	float windSpeedMax; ///< @brief Maximum Wind Speed (m/s)
	float rainfallH; ///< @brief Rainfall in 1 hour (mm)
	float rainfallD; ///< @brief Rainfall in 1 day (mm)
	float temperature; ///< @brief Temperature (deg C)
	int humidity; ///< @brief Humidity (%)
	int pressure; ///< @brief Pressure (Pa)
};
