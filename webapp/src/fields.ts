export function toDirection(angle: number): string {
	let label: string = ""

	if (292.5 < angle || angle < 67.5) label += "N"
	if (112.5 < angle && angle < 247.5) label += "S"
	if (22.5 < angle && angle < 157.5) label += "E"
	if (202.5 < angle && angle < 337.5) label += "W"

	return label
}

const fields: Record<string, {
	label: string,
	icon: string,
	format: (value: number) => string
}> = {
	"humidity": {
		label: "Air Humidity",
		icon: "humidity_percentage",
		format: (value) => value.toFixed(0) + '%'
	},
	"pressure": {
		label: "Air Pressure",
		icon: "airwave",
		format: (value) => value.toString() + ' Pa'
	},
	"temperature": {
		label: "Temperature",
		icon: "",
		format: (value) => value.toFixed(0) + '°C'
	},
	"wind_direction": {
		label: "Wind Direction",
		icon: "explore",
		format: (value) => toDirection(value) + ' ' + value.toFixed(0) + '°'
	},
	"wind_speed_max": {
		label: "Max. Wind Speed",
		icon: "air",
		format: (value) => value.toFixed(2) + ' m/s'
	},
	"wind_speed_avg": {
		label: "Avg. Wind Speed",
		icon: "air",
		format: (value) => value.toFixed(2) + ' m/s'
	},
	"rainfall_hour": {
		label: "Hourly Rainfall",
		icon: "rainy",
		format: (value) => value.toFixed(2) + ' mm'
	},
	"rainfall_day": {
		label: "Daily Rainfall",
		icon: "rainy",
		format: (value) => value.toFixed(2) + ' mm'
	},
}

export default fields
