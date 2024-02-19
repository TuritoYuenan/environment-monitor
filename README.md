# ZimmerWetter 2: Electric Boogaloo

> This is a university IoT project

This is an IoT project about building a simple, easy to use weather station that provides you with reliable data of your own region, removing the need for other weather services

> [Legacy version using ESP32-C3, DHT22 and Blynk](./esp32-c3/)

## Weather data

- Humidity (%)
- Temperature (ºC)
- Pressure, barometric (hPa)
- Rainfall, in 1 hour and 1 day (mm)
- Wind speed, average and maximum (m/s)
- Wind direction (degree)

## Tech stack

- Devices: Arduino Uno, ESP8266
- Sensor: DFRobot SEN0186 Weather Station
- Web UI: Pure HTML, CSS & JavaScript

## Usage

- Prepare and assemble hardware components
- Using either Arduino IDE or VSCode Arduino, install the board libraries for ESP8266
- Change the WiFi settings in the [WetterLib.h](./esp8266/WetterLib.h) file to yours
- Upload Arduino Uno and ESP8266 codes to the respective devices
- On your browser (connected to the same WiFi), enter the IP address announced in the Serial Monitor to access your web dashboard.
