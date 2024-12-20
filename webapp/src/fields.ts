const fields: Record<string, {
	label: string,
	icon: string,
	unit: string,
	sanitise: (value: number) => string
}> = {
	"humidity": {
		label: "Air Humidity",
		icon: "humidity_percentage",
		unit: "%",
		sanitise: (value) => value.toFixed(0)
	},
	"pressure": {
		label: "Air Pressure",
		icon: "airwave",
		unit: "hPa",
		sanitise: (value) => (value / 1000).toFixed(3)
	},
	"temperature": {
		label: "Temperature",
		icon: "",
		unit: "&deg;C",
		sanitise: (value) => value.toFixed(0)
	},
	"wind_direction": {
		label: "Wind Direction",
		icon: "explore",
		unit: "degrees",
		sanitise: (value) => value.toFixed(0)
	},
	"wind_speed_max": {
		label: "Max. Wind Speed",
		icon: "air",
		unit: "m/s",
		sanitise: (value) => value.toFixed(2)
	},
	"wind_speed_avg": {
		label: "Avg. Wind Speed",
		icon: "air",
		unit: "m/s",
		sanitise: (value) => value.toFixed(2)
	},
	"rainfall_hour": {
		label: "Hourly Rainfall",
		icon: "rainy",
		unit: "mm",
		sanitise: (value) => value.toFixed(2)
	},
	"rainfall_day": {
		label: "Daily Rainfall",
		icon: "rainy",
		unit: "mm",
		sanitise: (value) => value.toFixed(2)
	},
}

export default fields
