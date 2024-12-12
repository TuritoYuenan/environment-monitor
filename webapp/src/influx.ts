import { InfluxDBClient } from '@influxdata/influxdb3-client'

const host = process.env.INFLUXDB_URL || 'http://localhost:8086'
const token = process.env.INFLUXDB_TOKEN || 'my-token'
const org = process.env.INFLUXDB_ORG || 'my-org'
const bucket = 'weather_data'

export const client = new InfluxDBClient({ host, token, database: bucket })
