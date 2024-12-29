import { InfluxDB } from "@influxdata/influxdb-client-browser";

const url = import.meta.env.VITE_INFLUXDB_URL || 'https://localhost:8086'
const org = import.meta.env.VITE_INFLUXDB_ORG || 'my-org'
const token = import.meta.env.VITE_INFLUXDB_TOKEN || 'my-token'

const queryApi = new InfluxDB({ url, token }).getQueryApi(org)

/**
 * Query from InfluxDB
 * @param fluxQuery Query in Flux language (the only one supported by `influxdb-client-browser`)
 * @returns InfluxDB data
 */
export default function(fluxQuery: string): Promise<{ [key: string]: any }[]> {
	return new Promise((resolve, reject) => {
		const result: Array<{ [key: string]: any; }> = []

		queryApi.queryRows(fluxQuery, {
			next(row, tableMeta) {
				const o = tableMeta.toObject(row)
				result.push(o)
			},
			error(error) {
				reject(error)
			},
			complete() {
				// Introduce a delay before resolving the promise
				setTimeout(() => { resolve(result) }, 5000);
			},
		})
	})
}

export const query = `
from(bucket: "weather_data")
|> range(start: -5s)
|> filter(fn: (r) => r._measurement == "weather")
|> drop(columns: ["_start", "_stop", "_measurement"])
`;
