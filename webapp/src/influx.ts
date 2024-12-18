import { InfluxDB } from "@influxdata/influxdb-client-browser";

const url = import.meta.env.VITE_INFLUXDB_URL || 'https://localhost:8086'
const token = import.meta.env.VITE_INFLUXDB_TOKEN || 'my-token'
const org = import.meta.env.VITE_INFLUXDB_ORG || 'my-org'

const queryApi = new InfluxDB({ url, token }).getQueryApi(org)

export function queryExample(fluxQuery: string): Promise<{ [key: string]: any }[]> {
	return new Promise((resolve, reject) => {
		const result: { [key: string]: any; }[] = []
		queryApi.queryRows(fluxQuery, {
			next(row, tableMeta) {
				const o = tableMeta.toObject(row)
				result.push(o)
			},
			error(error) {
				console.log('QUERY FAILED', error)
				reject(error)
			},
			complete() {
				console.log('QUERY FINISHED')
				// Introduce a delay before resolving the promise
				setTimeout(() => { resolve(result) }, 4000);
			},
		})
	})
}

export const fields: { [key: string]: { unit: string, label: string, icon: string, sanitise: (value: number) => string } } = {
	"humidity": { unit: "%", label: "Air Humidity", icon: "humidity_percentage", sanitise: (value) => value.toFixed(0) },
	"pressure": { unit: "hPa", label: "Air Pressure", icon: "airwave", sanitise: (value) => (value / 1000).toFixed(3) },
	"temperature": { unit: "C", label: "Temperature", icon: "", sanitise: (value) => value.toFixed(2) },
	"wind_direction": { unit: "deg", label: "Wind Direction", icon: "explore", sanitise: (value) => value.toFixed(0) },
	"wind_speed_max": { unit: "m/s", label: "Max. Wind Speed", icon: "air", sanitise: (value) => value.toFixed(2) },
	"wind_speed_avg": { unit: "m/s", label: "Avg. Wind Speed", icon: "air", sanitise: (value) => value.toFixed(2) },
	"rainfall_hour": { unit: "mm", label: "Hourly Rainfall", icon: "rainy", sanitise: (value) => value.toFixed(2) },
	"rainfall_day": { unit: "mm", label: "Daily Rainfall", icon: "rainy", sanitise: (value) => value.toFixed(2) },
}
