#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include "WeatherData.h"

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  client.setServer(mqttServer, mqttPort);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  getBuffer(Serial);                                                                      //Begin!
  Serial.print("Wind Direction: ");
  Serial.print(WindDirection());
  Serial.println("  ");
  Serial.print("Average Wind Speed (One Minute): ");
  Serial.print(WindSpeedAverage());
  Serial.println("m/s  ");
  Serial.print("Max Wind Speed (Five Minutes): ");
  Serial.print(WindSpeedMax());
  Serial.println("m/s");
  Serial.print("Rain Fall (One Hour): ");
  Serial.print(RainfallOneHour());
  Serial.println("mm  ");
  Serial.print("Rain Fall (24 Hour): ");
  Serial.print(RainfallOneDay());
  Serial.println("mm");
  Serial.print("Temperature: ");
  Serial.print(Temperature());
  Serial.println("C  ");
  Serial.print("Humidity: ");
  Serial.print(Humidity());
  Serial.println("%  ");
  Serial.print("Barometric Pressure: ");
  Serial.print(BarPressure());
  Serial.println("hPa");
  Serial.println("");
  Serial.println("");

  String payload = String(Temperature()) + "," + String(Humidity()) + "," + String(BarPressure()) + "," +
                  String(WindDirection()) + "," + String(WindSpeedAverage()) + "," + String(WindSpeedMax()) + "," +
                  String(RainfallOneHour()) + "," + String(RainfallOneDay());

    // Publish the payload to the MQTT topic
  client.publish(mqttTopic, payload.c_str());
  
  delay(5000);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}