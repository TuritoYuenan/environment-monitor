import { InfluxDB } from "@influxdata/influxdb-client-browser";

const url = import.meta.env.VITE_INFLUXDB_URL || 'https://localhost:8086'
const org = import.meta.env.VITE_INFLUXDB_ORG || 'my-org'
const token = import.meta.env.VITE_INFLUXDB_TOKEN || 'my-token'

const queryApi = new InfluxDB({ url, token }).getQueryApi(org)

export function fluxQuery(fluxQuery: string): Promise<{ [key: string]: any }[]> {
	return new Promise((resolve, reject) => {
		const result: Array<{ [key: string]: any; }> = []

		queryApi.queryRows(fluxQuery, {
			next(row, tableMeta) {
				const o = tableMeta.toObject(row)
				result.push(o)
			},
			error(error) {
				console.error(error)
				reject(error)
			},
			complete() {
				console.table(result)
				// Introduce a delay before resolving the promise
				setTimeout(() => { resolve(result) }, 4000);
			},
		})
	})
}
