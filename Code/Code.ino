//library for humidity and temperature sensor
#include <DHT.h>
const int sensorPin = 7;
DHT dht(sensorPin, DHT11);

//library for OLED display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//library for 7-segments display
#include "SevSeg.h"
SevSeg sevseg;

//7-segments 4 digit display
const int seg_a_4_digits = 49;
const int seg_b_4_digits = 47;
const int seg_c_4_digits = 44;
const int seg_d_4_digits = 42;
const int seg_e_4_digits = 41;
const int seg_f_4_digits = 48;
const int seg_g_4_digits = 45;
const int seg_p_4_digits = 43; //point  .
const int seg_dp_4_digits = 46; //double point  :

//display digits of:
const int d1 = 53; //Digit 1
const int d2 = 52; //Digit 2
const int d3 = 51; //Digit 3
const int d4 = 50; //Digit 4

#include "src/MyTime.h"
MyTime myTime = MyTime();

#include "src/Mode.h"
Mode mode = Mode();

#include "src/Button.h"
Button setButton = Button(2, "SET");
Button minButton = Button(3, "MIN");
Button plusButton = Button(5, "PLUS");

#include "src/controllSingleDigitDisplay.h"
controllSingleDigitDisplay singleDigitDisplay = controllSingleDigitDisplay();

//sensor dht var:
float temperature;
int humidity;


unsigned long lastSamplingSensor = 0;
unsigned long samplingSensorInterval = 20000;

void setup(){
    //declare pin:
    //display (4 digits)
    pinMode(seg_a_4_digits, OUTPUT);
    pinMode(seg_b_4_digits, OUTPUT);
    pinMode(seg_c_4_digits, OUTPUT);
    pinMode(seg_d_4_digits, OUTPUT);
    pinMode(seg_e_4_digits, OUTPUT);
    pinMode(seg_f_4_digits, OUTPUT);
    pinMode(seg_g_4_digits, OUTPUT);
    pinMode(seg_p_4_digits, OUTPUT);
    pinMode(seg_dp_4_digits, OUTPUT);
    
    pinMode(d1, OUTPUT);
    pinMode(d2, OUTPUT);
    pinMode(d3, OUTPUT);
    pinMode(d4, OUTPUT);

      //SET UP SEVSEG LIBRARY
    byte numDigits = 4;
    byte digitPins[] = {d1, d2, d3, d4};
    byte segmentPins[] = {seg_a_4_digits, seg_b_4_digits, seg_c_4_digits, seg_d_4_digits, seg_e_4_digits, seg_f_4_digits, seg_g_4_digits, seg_p_4_digits};
    bool resistorsOnSegments = true; 
    bool updateWithDelaysIn = true;
    byte hardwareConfig = COMMON_CATHODE; 
    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);
    digitalWrite(seg_dp_4_digits, HIGH);  // set the two points on :
  
    Serial.begin(9600);

    //start sensor dht ativity
    dht.begin();
    
    //OLED SET UP
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
    }
    OLEDisplayText(mode.getActiveMode());
    display.display();

    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
}

void loop(){
    myTime.update(&mode);
    setButton.update(&mode, &myTime);
    minButton.update(&mode, &myTime);
    plusButton.update(&mode, &myTime);

    unsigned long currentTime = millis(); // update current time

    if(currentTime - lastSamplingSensor > samplingSensorInterval){
      lastSamplingSensor = currentTime;
      temperature = dht.readTemperature();
      humidity = dht.readHumidity();
      Serial.println(temperature);
    }
    
    //display on 7-segments
    displayOn7Segments();

    //display on OLED
    if(mode.getUpdateOLED()){
        String myString = mode.getActiveMode();
        OLEDisplayText(myString);
        display.display();
    }
    mode.setUpdateOLED(false);

}
void displayOn7Segments(){
    int numToDisplayOnSingleDigit = -1;
    // if at the end thi var will be negative, then will not display nothing
    
    if(mode.getActiveMode() == "TIME"){
        digitalWrite(seg_dp_4_digits, HIGH);  // set the two points on :
        
        if(!mode.getSettingActivity() || mode.getDisplayWhatAreYouSetting()){
            int myTimeToDisplay = myTime.getMyHours() * 100 + myTime.getMyMinutes() ;
            sevseg.setNumber(myTimeToDisplay, 4);
            sevseg.refreshDisplay();
            numToDisplayOnSingleDigit = myTime.getMySec();
        }else{
            switch (mode.getIndexSubMenu()){
                case 1: //do not show hours    
                    update7SegDiplayTime(-1, myTime.getMyMinutes());           
                    numToDisplayOnSingleDigit = myTime.getMySec();
                    break;
                case 2: //do not show minutes    
                    update7SegDiplayTime(myTime.getMyHours(), -1);           
                    numToDisplayOnSingleDigit = myTime.getMySec();
                    break;
                case 3: //do not show seconds    
                    update7SegDiplayTime(myTime.getMyHours(), myTime.getMyMinutes());           
                    numToDisplayOnSingleDigit = -1;
                    break;
                
            }
            
            
            
        }
        
        
    }
    if(mode.getActiveMode() == "DATE"){
        Serial.println(mode.getDisplayWhatAreYouSetting());
        digitalWrite(seg_dp_4_digits, LOW);  // set the two points off :
        if(!mode.getSettingActivity() || mode.getDisplayWhatAreYouSetting()){
            //display all
            update7SegDiplayDate(myTime.getMyDay(), myTime.getMyMonth());
            numToDisplayOnSingleDigit = myTime.getMyYear();
        }else{
            switch (mode.getIndexSubMenu()){
                case 1: //do not show day
                    update7SegDiplayDate(myTime.getMyDay()*-1, myTime.getMyMonth());
                    numToDisplayOnSingleDigit = myTime.getMyYear();
                    break;
                case 2: //do not show month
                    update7SegDiplayDate(myTime.getMyDay(), myTime.getMyMonth()*-1);
                    numToDisplayOnSingleDigit = myTime.getMyYear();
                    break;
               case 3: //do not show month
                    update7SegDiplayDate(myTime.getMyDay(), myTime.getMyMonth());
                    numToDisplayOnSingleDigit = myTime.getMyYear()*-1;
                    break;
            }
        }
        
    }
    if(mode.getActiveMode() == "DEGREES"){
        digitalWrite(seg_dp_4_digits, LOW);  // set the two points off :
        int myTemperatureToDisplay = (int)(temperature) ;
        sevseg.setNumber(myTemperatureToDisplay, 0);
        sevseg.refreshDisplay();
        int myDecimalTemperature = (int)((temperature*100) - (myTemperatureToDisplay*100));
        numToDisplayOnSingleDigit = abs(myDecimalTemperature);
    }
    if(mode.getActiveMode() == "HUMIDITY"){
        digitalWrite(seg_dp_4_digits, LOW);  // set the two points off :
        sevseg.setNumber(humidity);
        sevseg.refreshDisplay();
    }
    
    singleDigitDisplay.myUpdate(numToDisplayOnSingleDigit);
    
}

void OLEDisplayText(String text) {
    display.clearDisplay();
    
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    
    display.println(text);              // Display the text 

}

void update7SegDiplayDate(int day, int month){
    int d1 = day % 10;
    int d2 = (day - d1) / 10;
    char c2 = (char)d1;
    char c1 = (char)d2;
    int m1 = month % 10;
    int m2 = (month - m1) / 10;
    char c4 = (char)m1;
    char c3 = (char)m2;
    
    char str[5] = {' ', ' ','.',' ', ' '};
    if(day>= 0){
        str[0] = c1+'0';
        str[1] = c2+'0';
    }
    if(month>= 0){
        str[3] = c3+'0';
        str[4] = c4+'0';
    }
    sevseg.setChars(str);
    sevseg.refreshDisplay();
}


void update7SegDiplayTime(int hour, int minutes){
    int d1 = hour % 10;
    int d2 = (hour - d1) / 10;
    char c2 = (char)d1;
    char c1 = (char)d2;
    int m1 = minutes % 10;
    int m2 = (minutes - m1) / 10;
    char c4 = (char)m1;
    char c3 = (char)m2;
    
    char str[4] = {' ', ' ',' ', ' '};
    if(hour>= 0){
        str[0] = c1+'0';
        str[1] = c2+'0';
    }
    if(minutes>= 0){
        str[2] = c3+'0';
        str[3] = c4+'0';
    }
    
    sevseg.setChars(str);
    sevseg.refreshDisplay();
}
