# WeatherStation
Weather Station is an Arduino project.

## Main Components
 * clock
 * date keeper
 * digital thermometer
 * digital humidity sensor
 * alarm clock
 
## Electronic Components
This is the complete list of all the electronic components that I used for this project
* [1] Arduino Mega 2560  (you can't use the Arduino Uno because you don't have too much digital pins)
* [1] breadboard (63x10) 
* [1] DHT11 humidity and temperature (digital sensor) 																
	https://www.amazon.it/gp/product/B00L11IISS/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1
* [1] OLED display (128 * 32)  
	https://www.amazon.it/gp/product/B07D9H83R4/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1
* [1] 7-segments display (4 digits)
* [2] 7-segments display (1 digit)
* [1] passive buzzer  	
	https://www.amazon.it/gp/product/B071DFX4W2/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1
* [3] buttons
* [7] resistors 220 Ohm
* [3] resistors 1k Ohm
* [50/55] Jumper Wires M/M
* [8] Jumper Wires M/F


## Usage
Install these library in your Arduino environment:
* SevSeg  			https://github.com/DeanIsMe/SevSeg
* Adafruit_GFX  	https://github.com/adafruit/Adafruit-GFX-Library
* Adafruit_SSD1306	https://github.com/adafruit/Adafruit_SSD1306
* DHT				https://github.com/adafruit/DHT-sensor-library
* Adafruit_Sensor  	https://github.com/adafruit/Adafruit_Sensor

Open the file Code/Code.ino using Arduino IDE
Compile and upload on your Arduino.
Connect all the components like the following schema.

## Schema
This is one possible schema for this project:
![Scema](Schema.png?raw=true "schema")

Note that in this schema there are not the connection of: passive buzzer and OLED display.
But this two connections are very easy and it depends on what components you have.

## Project files
**Code** and **Code_No_OOP** folders are two realization of the same project.
If you want all the features I recommend you to use **Code**, because I will not update **Code_No_OOP**

If you try to read my code:
**Code_No_OOP** has all the code in one file, so is perfet if you want to understand all the code.
If you wanna understand only some part of the code or you want to develop and update with new feature I recommend you to use **Code**.

## Precision
I estimate that the clock loses approximately one second per day.

## Remark
The date format is: dd/mm/yy

## Future developments
The project is not yet fully completed.
Next features to develop:
* new alarm clock melodies
* new timer mode
* new stopwatch mode
* introduction of a barometer sensor and a new mode to read it status 
* introduction of some beep sound during setting mode
* new storage system of weather data on micro and a software for having a complete report on PC


## Warnings
The system is not fully tested.

The system after 4,294,967,295 milliseconds ≃ 49 days could crash due to overflow (not yet tested).

# Credits
All the software is open source and developed by Andrea Gonzato

