DROP TABLE weather_data.sen0186;

CREATE TABLE IF NOT EXISTS weather_data.sen0186 (
	date TIMESTAMP,
	temperature DECIMAL,
	humidity INT,
	pressure INT,
	rainfallH DECIMAL,
	rainfallD DECIMAL,
	windDirection INT,
	windSpeedAvg DECIMAL,
	windSpeedMax DECIMAL,
	PRIMARY KEY (date)
);
