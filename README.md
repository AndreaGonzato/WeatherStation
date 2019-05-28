# WeatherStation
Weather Station is an Arduino project.

## Main Components
 * clock
 * date keeper
 * digital thermometer
 * digital humidity sensor
 * alarm clock
 
## Electronic Components
This is the complete list of all the electronic components that I used for this project:
* [1] Arduino Mega 2560  (you can't use the Arduino Uno because you don't have too many digital pins)
* [1] breadboard (63x10) 
* [1] DHT11 humidity and temperature (digital sensor) 																
	https://www.amazon.it/gp/product/B00L11IISS/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1
* [1] OLED display (128 * 32)  
	https://www.amazon.it/gp/product/B07D9H83R4/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1
* [1] 7-segments display (4 digits, common cathode)
* [2] 7-segments display (1 digit, common cathode)
* [1] passive buzzer  	
	https://www.amazon.it/gp/product/B071DFX4W2/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1
* [3] buttons
* [7] resistors 220 Ohm
* [3] resistors 1k Ohm
* [50/55] Jumper Wires M/M
* [8] Jumper Wires M/F


## Usage
Install these library on your Arduino environment:
* SevSeg  			https://github.com/DeanIsMe/SevSeg
* Adafruit_GFX  	https://github.com/adafruit/Adafruit-GFX-Library
* Adafruit_SSD1306	https://github.com/adafruit/Adafruit_SSD1306
* DHT				https://github.com/adafruit/DHT-sensor-library
* Adafruit_Sensor  	https://github.com/adafruit/Adafruit_Sensor

Open the file Code/Code.ino using Arduino IDE, compile and upload on your Arduino and then connect all the components like the following schema.

Then to controll the weather station/clock you have three buttons and they work like almost every watch.
In this schema the leftmost one is the SET button, in the middle there is the MINUS one and further to the right there is the PLUS one.
To scroll through the menus you can press both of them PLUS or MINUS.
For setting a particular activity you need to press a long on the SET button; to deactivate the alarm just press the SET button in the alarm menu.

## Schema
This is one possible schema for this project:
![Scema](Schema.png?raw=true "schema")

Note that in this schema there isn't the connection of: passive buzzer and OLED display.
But this two connections are very easy and depends a lot on the components you held.

## Image
This is a photo of my project
![Image](projectPhoto.png?raw=true "project photo")

## Project Files
**Code** and **Code_No_OOP** folders are two realization of the same project.
If you want all the latest features I recommend to use **Code**.

Last final commit of **Code_No_OOP** was on Apr 18, 2019 and at that time this folder name was "ArduinoCode".

## For Programmers
All the code in **Code_No_OOP** is in only one file: so it is perfect if you want to understand the whole structure of the project but it doesn't have all the latest features.

If you wanna understand only some part of the code or you want to develop and update some new feature I recommend to use **Code**, which used a OOP structure.
In the **Code** project all the objects are created in the file Code.ino and most of objects have a method call "update", which is the main method.

### Hardware & Arduino
The connection protocol used between the display and the Arduino is the I2C.

In Arduino loop function you can't add some delay, because otherwise libraries doesn't work correctly.

The dht11 sensor reads by default the data (temperature and humidity) every 20 seconds. This is to avoid excessive slowdowns to the system.


## Precision
I estimate that the clock loses approximately one second per day.

## Remark
The date format is: dd/mm/yy

## Future developments
The project is not fully completed yet.
Next features to develop:
* new alarm clock melodies
* new timer mode
* new stopwatch mode
* introduction of a barometer sensor and a new mode to read his status 
* introduction of some beep sound during setting mode
* new storage system of weather data on micro sd and a software for having a complete report on PC


## Warnings
The system is not fully tested.

The system after 4,294,967,295 milliseconds ≃ 49 days could crash due to overflow (not tested yet).

## Credits
All the software is open source and developed by Andrea Gonzato

