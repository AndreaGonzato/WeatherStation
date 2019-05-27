# WeatherStation
Weather Station is an Arduino project.

## Main Components
 * clock
 * date keeper
 * digital thermometer
 * digital humidity sensor
 * alarm clock
 
## Usage
Install these library in your Arduino environment:
* SevSeg  			https://github.com/DeanIsMe/SevSeg
* Adafruit_GFX  	https://github.com/adafruit/Adafruit-GFX-Library
* Adafruit_SSD1306	https://github.com/adafruit/Adafruit_SSD1306
* DHT				https://github.com/adafruit/DHT-sensor-library
* Adafruit_Sensor  	https://github.com/adafruit/Adafruit_Sensor

Open the file Code/Code.ino using Arduino IDE
Compile & upload on your Arduino.
Connect all the components like the following schema.

## Electronic Components
This is what I used for this project:
* [1] Arduino Mega 2560
* [1] breadboard (63x10) 
* [1] DHT11 humidity and temperature sensor
* [1] OLED display
* [1] 7-segments display (4 digits)
* [2] 7-segments display (1 digit)
* [1] cicalino passivo
* [3] buttons
* [7] resistors 220 Ohm
* [3] resistors 1k Ohm
* [50/55] Jumper Wires M/M
* [8] Jumper Wires M/F

## Schema
This is one possible schema for this project:
![Scema](Schema.png?raw=true "schema")

## Precision
I estimate that the clock loses approximately one second per day.

## Remark
The date format is: dd/mm/yy

## Warnings
The system is not fully tested.

The system after 4,294,967,295 milliseconds ≃ 49 days could crash due to overflow (not yet tested).

# Credits
All the software is open source and developed by Andrea Gonzato

