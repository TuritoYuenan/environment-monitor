import json
from influxdb_client import InfluxDBClient, Point
from influxdb_client.client.write_api import SYNCHRONOUS
from influxdb_client.rest import ApiException
from paho.mqtt.client import Client, MQTTMessage
from paho.mqtt.enums import CallbackAPIVersion


# MARK: Constants
DEBUG_MODE = True
CLIENT_ID = 'Weather Data Edge Function'
BROKER_HOST = 'broker' # name of Mosquitto service in compose.yml
BROKER_PORT = 1883
USERNAME = 'swinuser'
PASSWORD = 'swinpass'
TOPIC = 'swinburne/hcmc_a35'


# MARK: Connection callback
def on_connect(client: Client, userdata, flags, reason_code, properties):
	"""Routine to do when connected to the MQTT broker

	Args:
		client (Client): MQTT Client
		userdata (InfluxDBClient): Client to save data
		flags (unknown): Program flags
		reason_code (_type_): _description_
		properties (_type_): _description_
	"""
	print('Connected to broker')

	client.subscribe(TOPIC)
	print(f'Subscribed to {TOPIC} topic')


# MARK: Message callback
def on_message(client: Client, userdata: InfluxDBClient, message: MQTTMessage):
	"""Routine to do when received an MQTT message

	Args:
		client (Client): MQTT Client
		user_data (InfluxDBClient): Client to save data
		message (MQTTMessage): The received message. Needs to be decoded
	"""
	write_api = userdata.write_api(SYNCHRONOUS)
	if DEBUG_MODE: print('Begin message processing')

	payload = message.payload.decode('utf-8')
	extract = json.loads(payload)
	if DEBUG_MODE: print('Decoded and extracted data')

	point = (
		Point('weather').tag('city', 'HCMC').tag('campus', 'A35')
		.field('humidity', extract['humidity'])
		.field('pressure', extract['pressure'])
		.field('temperature', extract['temperature'])
		.field('rainfall_day', extract['rainfall_day'])
		.field('rainfall_hour', extract['rainfall_hour'])
		.field('wind_speed_avg', extract['wind_speed_avg'])
		.field('wind_speed_max', extract['wind_speed_max'])
		.field('wind_direction', extract['wind_direction'])
	)

	try:
		write_api.write('weather_data', record = point)
		if DEBUG_MODE: print('Uploaded data')
	except ApiException:
		print('Connection to InfluxDB is unauthorised')
	except:
		print('Something wrong happened')


# MARK: Main procedure
def main():
	"""Main procedure
	"""
	write_client = InfluxDBClient.from_env_properties()

	print("Entering credentials")
	mqtt_client = Client(CallbackAPIVersion.VERSION2, CLIENT_ID)
	mqtt_client.username_pw_set(USERNAME, PASSWORD)
	mqtt_client.user_data_set(write_client)

	print("Setting up callback functionality")
	mqtt_client.on_connect = on_connect
	mqtt_client.on_message = on_message

	print("Connecting to broker")
	mqtt_client.connect(BROKER_HOST, BROKER_PORT)

	print("Connected! Start processing incoming data")
	mqtt_client.loop_forever()

	return 0


# MARK: Main execution
if __name__ == '__main__': main()
