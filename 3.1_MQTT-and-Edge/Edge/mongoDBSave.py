#import mysql.connector

#db_connection = mysql.connector.connect(
#    host="localhost",
#    user="root",
#    password="pi",
#    database="weather_station"
#)

#mycursor = db_connection.cursor(dictionary=True)
#mycursor.execute("SELECT * from weather_data;")
#myresult = mycursor.fetchall()

#print(myresult)

import mysql.connector
import pymongo
import requests
import time

delete_existing_documents = True

# MySQL credentials
mysql_host = "localhost"
mysql_user = "root"
mysql_password = "pi"
mysql_database = "weather_station"

# MongoDB credentials
mongodb_host = "mongodb+srv://admin:HEX7Kx9mwHMYsh3F@zimmerweather.t8rusfg.mongodb.net/?retryWrites=true&w=majority"
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

while True:
    # Check internet connectivity
    try:
        requests.get("http://www.google.com")
        internet_connected = True
    except requests.ConnectionError:
        internet_connected = False

    if internet_connected:
        mycursor.execute("SELECT * FROM weather_data;")
        myresult = mycursor.fetchall()

        if delete_existing_documents:
            mycol.delete_many({})  # Delete existing documents in the collection

        if len(myresult) > 0:
            x = mycol.insert_many(myresult)  # Insert documents into the collection
            print(f"Successfully pushed {len(x.inserted_ids)} documents to MongoDB.")
    else:
        print("No internet connection.")

    time.sleep(60)  # Wait for 60 seconds before checking again