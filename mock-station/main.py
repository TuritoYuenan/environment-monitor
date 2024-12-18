import json, random, time
from paho.mqtt import client, enums


# MARK: Constants
DEBUG_MODE = True
CLIENT_ID = 'Mock Weather Station'
BROKER_HOST = 'broker' # name of Mosquitto service in compose.yml
BROKER_PORT = 1883
TOPIC = 'swinburne/hcmc_a35'


# MARK: Connection callback
def on_connect(client: client.Client, userdata, flags, reason_code, properties):
	"""Routine to do when connected to the MQTT broker

	Args:
		client (Client): MQTT Client
		userdata (InfluxDBClient): Client to save data
		flags (unknown): Program flags
		reason_code (_type_): _description_
		properties (_type_): _description_
	"""
	print('Connected to broker')


# MARK: Generate data
def generate_data(client: client.Client):
	mock_data: dict[str, int | float] = {
		'humidity': random.randint(0, 100),
		'pressure': random.randint(100000, 102000),
		'temperature': random.uniform(10, 40),
		'rainfall_day': random.uniform(0, 10),
		'rainfall_hour': random.uniform(0, 10),
		'wind_speed_avg': random.uniform(0, 60),
		'wind_speed_max': random.uniform(0, 60),
		'wind_direction': random.randint(0, 360)
	}

	if DEBUG_MODE: print(mock_data)
	client.publish(TOPIC, json.dumps(mock_data))


# MARK: Main procedure
def main():
	"""Main procedure
	"""
	mqtt_client = client.Client(enums.CallbackAPIVersion.VERSION2, CLIENT_ID)

	print("Setting up callback functionality")
	mqtt_client.on_connect = on_connect

	print("Connecting to broker")
	mqtt_client.connect(BROKER_HOST, BROKER_PORT)

	print("Connected! Start generating weather data")
	while True:
		generate_data(mqtt_client)
		time.sleep(5)


# MARK: Main execution
if __name__ == '__main__': main()
