# ZimmerWetter 2: Electric Boogaloo

This is a university IoT project about building a simple, easy to use weather station that provides you with reliable data of your own region, removing the need for other weather services

> [!NOTE]
> Check out the [web application](https://github.com/TuritoYuenan/zimmer-wetter-webapp) for receiving weather data

> [!NOTE]
> [Legacy version using ESP32-C3, DHT22 and Blynk](./esp32-c3/)

## 8 types of Weather data

- Humidity (%)
- Temperature (ºC)
- Pressure, barometric (hPa)
- Rainfall, hourly and daily (mm)
- Wind speed, average and maximum (m/s)
- Wind direction (degree)

## Tech stack

- Devices: Arduino Uno, ESP8266
- Sensor: DFRobot SEN0186 Weather Station

## Usage

- Prepare and wire together an Arduino Uno board, an ESP8266 board, and an SEN0186 kit.
- Using either Arduino IDE or VSCode Arduino, install the board libraries for ESP8266.
- Create a secret file based on the [template](./esp8266/secrets.template.h). Change the settings to yours
- Upload [Arduino Uno codes](./arduino-uno/) and [ESP8266 codes](./esp8266/) to the respective devices.
- Weather data will be uploaded to your Xata database.
