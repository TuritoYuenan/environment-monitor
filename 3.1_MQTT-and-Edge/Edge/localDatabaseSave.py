import mysql.connector
import paho.mqtt.client as mqtt

db_connection = mysql.connector.connect(
    host="localhost",
    user="root",
    password="pi",
    database="weather_station"
)

def on_message(client, userdata, msg):
    topic = msg.topic
    message = msg.payload.decode("utf-8")

    # Extract the values from the message
    values = message.split(",")
    temp = float(values[0])
    humidity = float(values[1])
    baroPressure = float(values[2])
    windDirect = float(values[3])
    avgWindSpd = float(values[4])
    mxWindSpd = float(values[5])
    rainPerHr = float(values[6])
    rainPerDay = float(values[7])

    # Insert the message into the database
    cursor = db_connection.cursor()
    insert_query = "INSERT INTO weather_data (temp, humidity, baroPressure, windDirect, avgWindSpd, mxWindSpd, rainPerHr, rainPerDay) VALUES (%s, %s, %s, %s, %s, %s, %s, %s)"
    insert_values = (temp, humidity, baroPressure, windDirect, avgWindSpd, mxWindSpd, rainPerHr, rainPerDay)
    cursor.execute(insert_query, insert_values)
    db_connection.commit()
    cursor.close()

    print("Message inserted into the database successfully.")

def check_and_reset_table():
    # Check if the table is empty
    cursor = db_connection.cursor()
    cursor.execute("SELECT COUNT(*) FROM weather_data")
    result = cursor.fetchone()

    if result[0] == 0:
        # Reset the recordID to 1
        cursor.execute("ALTER TABLE weather_data AUTO_INCREMENT = 1")
        db_connection.commit()
        print("Table is empty. Reset recordID to 1.")
    else:
        print("Table is not empty.")

    cursor.close()

# Check and reset the table
check_and_reset_table()

# Setup MQTT client
client = mqtt.Client()
client.on_message = on_message

client.connect("192.168.1.4", 1883)

client.subscribe("zimmerWeather")

# Keep the script running
client.loop_forever()