# WeatherStation
Weather Station is an Arduino project where i bult a small Weather Station composed by a clock, a date keeper and a temperature sensor.

## Main Components
 * clock
 * date keeper
 * digital thermometer (not yet implemented)
 
## Usage
Install this library:
* SevSeg  			https://github.com/DeanIsMe/SevSeg
* Adafruit_GFX  	https://github.com/adafruit/Adafruit-GFX-Library
* Adafruit_SSD1306	https://github.com/adafruit/Adafruit_SSD1306

## Precision
I estimate that clock loses approximately one second per day.

## Electronic Components
* [1] Arduino Mega 2560
* [1] breadboard (63x10) 
* [1] OLED display
* [1] 7-segments display (4 digits)
* [2] 7-segments display (1 digit)
* [3] buttons
* [7] resistors 220 Ohm
* [3] resistors 1k Ohm
* [45/55] Jumper Wires M/M
* [4] Jumper Wires M/F

## Schema
This is one possible schema for this project:
![Scema](Schema.png?raw=true "schema")

## Warnings
The system is not fully tested.

The system after 49 days could crash due to overflow (not yet tested).

# Credits
All the software is open source and developed by Andrea Gonzato

