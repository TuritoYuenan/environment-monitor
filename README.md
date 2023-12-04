# Environment Monitor

![](images/preview.png)

This is an IoT project for monitoring temperature and humidity using ESP32 and Blynk.

## Usage

- Create the settings file by copying `settings.example.h` and rename the copied file as `settings.h`
- Edit the settings file to your preferences
- Load the files `sketch.ino`, `settings.h`, `libraries.txt` and `diagram.json` to a Wokwi project
- To use in-real-life, connect an ESP32 board wired to a DHT22 sensor and an LED, then run the file `sketch.ino` in Arduino IDE/CLI.

## Tech stack

- Frontend: Blynk
- Simulation: Wokwi
- Libraries: See [the library file](libraries.txt)
- Hardware:
	- ESP32 microcontroller
	- DHT22 sensor
	- LED & Wires

![Hardware](images/hardware-layout.png)
