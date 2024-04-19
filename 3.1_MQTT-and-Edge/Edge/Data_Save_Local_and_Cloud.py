import mysql.connector
import pymongo
import time
import paho.mqtt.client as mqtt

# MySQL credentials
mysql_host = "localhost"
mysql_user = "root"
mysql_password = "pi"
mysql_database = "weather_station"

# MongoDB credentials
mongodb_host = "mongodb_host"
mongodb_dbname = "WeatherStation"

# MySQL connection
db_connection = mysql.connector.connect(
    host=mysql_host,
    user=mysql_user,
    password=mysql_password,
    database=mysql_database
)

mycursor = db_connection.cursor(dictionary=True)

# MongoDB connection
myclient = pymongo.MongoClient(mongodb_host)
mydb = myclient[mongodb_dbname]
mycol = mydb["WeatherStation"]

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

def is_internet_connected():
    # Check if the internet is connected
    # Return True if connected, False otherwise
    return True

def is_duplicate_document(document):
    # Check if a document with the same recordTime already exists in MongoDB
    existing_doc = mycol.find_one({"recordTime": document["recordTime"]})
    return existing_doc is not None

def push_table_to_mongodb():
    # Select all rows from the MySQL table
    mycursor.execute("SELECT * FROM weather_data")
    rows = mycursor.fetchall()

    # Push each non-duplicate row to MongoDB
    for row in rows:
        document = {
            "RecordID": row["recordID"],  
            "temp": row["temp"],
            "humidity": row["humidity"],
            "baroPressure": row["baroPressure"],
            "windDirect": row["windDirect"],
            "avgWindSpd": row["avgWindSpd"],
            "mxWindSpd": row["mxWindSpd"],
            "rainPerHr": row["rainPerHr"],
            "rainPerDay": row["rainPerDay"],
            "recordTime": row["recordTime"].strftime('%Y-%m-%d %H:%M:%S')
        }

        if not is_duplicate_document(document):
            mycol.insert_one(document)
            print("Document inserted into MongoDB.")
        else:
            print("Duplicate document. Skipped insertion.")

    print("Table pushed to MongoDB.")

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

    # Insert the message into MySQL local 
    insert_query = "INSERT INTO weather_data (temp, humidity, baroPressure, windDirect, avgWindSpd, mxWindSpd, rainPerHr, rainPerDay) VALUES (%s, %s, %s, %s, %s, %s, %s, %s)"
    insert_values = (temp, humidity, baroPressure, windDirect, avgWindSpd, mxWindSpd, rainPerHr, rainPerDay)
    mycursor.execute(insert_query, insert_values)
    db_connection.commit()

    # Insert the message into MongoDB if notduplicate
    document = {
        "recordID": mycursor.lastrowid,
        "temp": temp,
        "humidity": humidity,
        "baroPressure": baroPressure,
        "windDirect": windDirect,
        "avgWindSpd": avgWindSpd,
        "mxWindSpd": mxWindSpd,
        "rainPerHr": rainPerHr,
        "rainPerDay": rainPerDay,
        "recordTime": time.strftime('%Y-%m-%d %H:%M:%S')
    }

    if not is_duplicate_document(document):
        mycol.insert_one(document)
        print("Message inserted into MySQL and MongoDB.")
    else:
        print("Duplicate document. Skipped insertion.")

# Setup MQTT client
client = mqtt.Client()
client.on_message = on_message

client.connect("192.168.1.4", 1883)

client.subscribe("zimmerWeather")

# Check internet connection
if is_internet_connected():
    push_table_to_mongodb()

# Loop the Script
while True:
    client.loop()

    time.sleep(5)  # Wait for 5 seconds