//library for 7-segments display
#include "SevSeg.h"
SevSeg sevseg; 

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

/////////////////////////////////////////////////////////////////

//CONSTANTS
const long longPressTime = 1000;    // it is just a const, that indicate how many millisec is a long click for the system


// DIGITAL PIN

//DISPLAY

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

// single digit display 1 & 2
const int seg_a[] = {38, 30};
const int seg_b[] = {37, 29};
const int seg_c[] = {34, 26};
const int seg_d[] = {35, 27};
const int seg_e[] = {36, 28};
const int seg_f[] = {39, 31};
const int seg_g[] = {40, 32};
const int seg_p[] = {33, 25}; 

//BUTTONS pins
const int setButton = 2;
const int minButton = 3;
const int plusButton = 5;


// GLOBAL VARIABLES

//TIME VAR
int sec;
int minutes;
int hours;
int day = 1;
int month = 1;
int year = 19;

unsigned long blinkingTime = 500;

//BUTTON VAR
//variable for reading the Buttons status (true if Botton is press, false if is not press)
boolean setButtonState = false;
boolean minButtonState = false;
boolean plusButtonState = false;

//var that indicate if it is time to display: sec, minutes, hours
//for example when you are setting the clock minutes, evry half second displayMin change value
boolean displaySec = true;
boolean displayMin = true;
boolean displayHours = true;

//just for the right evulution of the script (I have to find a better way)
boolean avoidIfPlus = true;
boolean avoidIfMin = true;

//variable that indicate if we are setting time of the clock (it happend when the setBotton had a long click)
boolean settingTimeMode = false;

//variable that indicate what we are setting:
int setingTimeSubMenu = 0;
//Here there is a leggend for how this var work:
/*
 *  0 : we are setting nothing
 *  1 : hors
 *  2 : minutes
 *  3 : sec
 *  4 : we have finished to set evrything, now immidatly go to state 0  (4 --> 0)
 */
int menuActivity = 0;
//Here there is a leggend for how this var work:
/*
 *  -1: go to temperature
 *  0 : time
 *  1 : date
 *  2 : temperature
 *  3 : go to time
 */

long setButtonTimer = 0;            // var to calcolate how long was the clik on setBotton, it get the inizial time when setBotton was pressed

unsigned long previousTime;  // a var to control/remember when the last second started
unsigned long previousTimeBlink; // the last blink was a this time previousTimeBlink
unsigned long synchronizationTimeInterval = 1000; // 1000 millis = 1 second
boolean displayOn = true;
boolean scrollMenu = false;

void setup(){

  //START TIME
  sec = 0;
  minutes = 0;
  hours = 0;
  
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

  for(int i=0 ; i<2 ; i++){
    pinMode(seg_a[i], OUTPUT);
    pinMode(seg_b[i], OUTPUT);
    pinMode(seg_c[i], OUTPUT);
    pinMode(seg_d[i], OUTPUT);
    pinMode(seg_e[i], OUTPUT);
    pinMode(seg_f[i], OUTPUT);
    pinMode(seg_g[i], OUTPUT);
    pinMode(seg_p[i], OUTPUT);
  }
  

  //declare botton pins
  pinMode(setButton, INPUT);
  pinMode(minButton, INPUT);
  pinMode(plusButton, INPUT);

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
  
  //OLED SET UP
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  //display somthing on OLED display
  OLEDisplayText("TIME");
  display.display();
  
}

void loop(){

  unsigned long currentTime = millis(); // update current time

  if (currentTime - previousTime >= synchronizationTimeInterval){   // if time is up (1 second has pass)
    previousTime = currentTime;   // updates the previous time: previousTime remember when the last sec was pass
    sec += 1;                     //update sec
    Serial.println(sec);          //print the actual sec on the consol, just for having a log/time rappresentation
  }

  controlSetBotton();         //control what to do when the setButton receives a click/long click
  controlNavigationButton();  //control what to do when the minButton or plusButton receives a click/long click
  
  if(settingTimeMode){
    settingTime(currentTime);  //control the system during the setting process.
  }

  //controol that the data type are right (e.g. seconds > 60)
  dataValidation();


  //DISPLAY info
  switch (menuActivity)
  {
    //decide what to display
    case 0:
      displayTime();
      break;
    case 1:
      displayDate();
      break;
    case 2:
      displayTime();
      break;
  }
  
  OLEDisplay();
}


void OLEDisplay(){
    //control OLED display 
  if(scrollMenu){
    //do that only if you are changing menu
    
    switch (menuActivity)
    {
      //decide what to display
      case 0:
        OLEDisplayText("TIME");
        break;
      case 1:
        OLEDisplayText("DATE");
        break;
      case 2:
        OLEDisplayText("TEMP");
        break;
    }
    display.display();
    scrollMenu = false; 
  }
}

void OLEDisplayText(String text) {
  display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner

  display.println(text);              // Display the text 

}


void controlSetBotton(){
  // this method check if the setButton is pressed/long click and performs actions based also on its previous history
  
  if(digitalRead(setButton) == HIGH){
    //the set_button is pressed
    
    if (setButtonState == false) {
      //at the first moment when the setBotton is press do this:
      setButtonTimer = millis();  //take the initial time when you pressed the set botton
      setButtonState = true;      //update setButtonState

      // if you are already in the settingTimeMenu and you have pressed another time set
      if(setingTimeSubMenu > 0){
        setingTimeSubMenu += 1;
        
        switch (setingTimeSubMenu)
        {
          case 2:
            displayHours = true;//if you are setting minutes, now you can fully display hours
          case 3:
            displayMin = true;  //if you are setting sec, now you can fully display minutes
            break;
          case 4:
            displaySec = true;  //if you finisched to set, now you can fully display secondi
            break;
        }
        
      }
      printSubMenu(setingTimeSubMenu);
    }

    // check if the setting menu is over
    if(setingTimeSubMenu >= 4){
      //this means the setting menu is over, you have set your clock
      setingTimeSubMenu = 0;
      settingTimeMode = false;
      displayOn = true;
      
    }

    //check if the setButton had a long click
    if ((millis() - setButtonTimer > longPressTime) && (settingTimeMode == false)) {
      //setButton had a long click
      settingTimeMode = true;  // now we are in the setting time mode
      setingTimeSubMenu = 1;
      Serial.println("LONG CLICK");
      printSubMenu(setingTimeSubMenu);
    }
  }else{
    setButtonState = false;     // setButton in not press
  }
}

void controlNavigationButton(){
  // this method check if the plusButton/minButton are pressed/long click and performs actions based also on its previous history
  
  if(!plusButtonState && !settingTimeMode && digitalRead(plusButton) == HIGH){
    //the plusButton is pressed and I'm not setting things
    
    plusButtonState = true;
    Serial.println("change feature");
    scrollMenu = true;
    menuActivity = menuActivity + 1;
    if(menuActivity >= 3){
      menuActivity = 0;
    }
    setPoints();
  }

  if(digitalRead(plusButton) == LOW){
    plusButtonState = false;
  }
  
  if(!minButtonState && !settingTimeMode && digitalRead(minButton) == HIGH){
    //the minButton is pressed and I'm not setting things
    
    minButtonState = true;
    Serial.println("change feature");
    scrollMenu = true;
    menuActivity = menuActivity - 1;
    if(menuActivity <= -1){
      menuActivity = 2;
    }
    setPoints();
  }
  if(digitalRead(minButton) == LOW){
    minButtonState = false;
  }
}


void setPoints(){
    if(menuActivity == 0){
      digitalWrite(seg_dp_4_digits, HIGH);  // set the two points on :
    }
    if(menuActivity == 1){
      digitalWrite(seg_dp_4_digits, LOW);  // set the two points off
      digitalWrite(seg_p_4_digits, HIGH); // set the single point on
    }
    if(menuActivity == 2){
      digitalWrite(seg_p_4_digits, LOW); // set the single point off
    }
}


void settingTime(long currentTime){
  /*this method is executed only when settingTimeMode is on
    this method has 3 main parts:
    1 - CONTROL PLUS BUTTON
    2 - CONTROL MIN BOTTON
    3 - BLINK what we are settings
  */
  
    
    //CONTROL PLUS BUTTON
    if((digitalRead(plusButton) == HIGH) && (avoidIfPlus)){
      // plus button is press
      Serial.println("+ PLUS");//TEST
      avoidIfPlus = false;
      //currentNum = (currentNum+1)%10;
      switch (setingTimeSubMenu)
      {
        case 1:
          //add hours
          hours += 1;
          hours = hours % 24 ;
          break;
          
        case 2:
          //add minutes
          minutes += 1;
          minutes = minutes % 60;
          break;

        case 3:
          //add sec
          sec += 1;
          sec = sec % 60;
          break;
      }
    }
    else{
       if(digitalRead(plusButton) == LOW){
         avoidIfPlus = true;
       }    
    }


    //CONTROL MIN BUTTON
    if((digitalRead(minButton) == HIGH) && (avoidIfMin)){
      //min button is press in the menù mode
      Serial.println("- MIN");//TEST
      avoidIfMin = false;
      switch (setingTimeSubMenu)
      {
        case 1:
          //decrease hours
          hours -= 1;
          if(hours < 0)
             hours = 23;
          break;
          
        case 2:
          //decrease minutes
          minutes -= 1;
          if(minutes < 0)
            minutes = 59;
          break;

        case 3:
          //decrease sec
          sec -= 1;
          if(sec < 0)
            sec = 59;
          break;
      }
    }
    else{
       if(digitalRead(minButton) == LOW){
         avoidIfMin = true;
       }    
    }


    
    // I'm in the menù mode, so blink what are you settings...
    switch (setingTimeSubMenu)
      {
        case 1:
          //blink hours
          if(currentTime - previousTimeBlink >= blinkingTime){
            displayHours = !displayHours;
            previousTimeBlink = currentTime;
          }
          break;
        case 2:
          //blink minutes
          displayHours = true;  // now you can display hours
          if(currentTime - previousTimeBlink >= blinkingTime){
            displayMin = !displayMin;
            previousTimeBlink = currentTime;
          }
          break;

        case 3:
          //blink sec
          displayMin = true;
          if(currentTime - previousTimeBlink >= blinkingTime){
            displaySec = !displaySec;
            previousTimeBlink = currentTime;
          }
          
          break;

        case 4:
          displaySec = true;
      }
  
}


void dataValidation(){

  //data type is correct ?
  if(sec >= 60){
    minutes += 1;
    sec = sec % 60;
    
    if(minutes >= 60){
      hours += 1;
      minutes = minutes % 60;
      
      if(hours >= 24){
        day += 1;
        hours = 0;
      }
    }
  }
}


void displayTime(){
//this method display actual time on the 7 segments display

  if(displaySec){
    int s2 = sec % 10;
    updateDisplaySec(1, s2);
    
    int s1 = (sec - s2 )/10;
    updateDisplaySec(0, s1);
    
  }else{
    updateDisplaySec(0,10);
    updateDisplaySec(1,10);
  }
  

  if(displayMin && displayHours){
    int myTime = hours * 100 + minutes ;
    sevseg.setNumber(myTime, 4);
    sevseg.refreshDisplay();
  }else{
    
      if(!displayHours){
        int m2 = minutes % 10;
        int m1 = (minutes - m2) / 10;
        char c1 = (char)m1;
        char c2 = (char)m2;
        char str[4] = {' ', ' ', ' ', ' '};
        str[2] = c1+'0';
        str[3] = c2+'0';
        sevseg.setChars(str);
        sevseg.refreshDisplay();
      }
      if(!displayMin){
        int m1 = hours % 10;
        int m2 = (hours - m1) / 10;
        char c1 = (char)m1;
        char c2 = (char)m2;
        char str[4] = {' ', ' ', ' ', ' '};
        str[0] = c2+'0';
        str[1] = c1+'0';
        
        sevseg.setChars(str);
        sevseg.refreshDisplay();
      }
  }
}


void displayDate(){
  //this method display actual date on the 7 segments display

  //determinate and display digits of the current year
  int a2 = year % 10;
  updateDisplaySec(1, a2);
  
  int a1 = (year - a2 )/10;
  updateDisplaySec(0, a1);

  //determinate and display digits of the current day & month
  int myDate = day * 100 + month ;
  sevseg.setNumber(myDate, 2);
  sevseg.refreshDisplay();

}


void printSubMenu(int setSubMenu){
 //this is a test method
 //this method just writes on console live info
  switch (setSubMenu)
  {
    case 0:
      Serial.println("SET");
      break;
    case 1:
      Serial.println("SET-ORE");
      break;
    case 2:
      Serial.println("SET-MINUTI");
      break;
    case 3:
      Serial.println("SET-SECONDI");
      break;
    case 4:
      Serial.println("SETTINGS COMPLETED");
      break;
  }
  
}


void updateDisplaySec(int numDisplay, int num){
  
  if(numDisplay >= 2 || numDisplay < 0 || num >10 || num < 0)
    Serial.println("ERR - updateDisplay ");
  
  switch(num){ // switch statemet to select what to display
  
  case 0: // set relevent segments HIGH and others LOW
    digitalWrite(seg_a[numDisplay],HIGH);
    digitalWrite(seg_b[numDisplay],HIGH);
    digitalWrite(seg_c[numDisplay],HIGH);
    digitalWrite(seg_d[numDisplay],HIGH);
    digitalWrite(seg_e[numDisplay],HIGH);
    digitalWrite(seg_f[numDisplay],HIGH);
    digitalWrite(seg_g[numDisplay],LOW);
    digitalWrite(seg_p[numDisplay],LOW);
    break;

  case 1:
    digitalWrite(seg_a[numDisplay],LOW);
    digitalWrite(seg_b[numDisplay],HIGH);
    digitalWrite(seg_c[numDisplay],HIGH);
    digitalWrite(seg_d[numDisplay],LOW);
    digitalWrite(seg_e[numDisplay],LOW);
    digitalWrite(seg_f[numDisplay],LOW);
    digitalWrite(seg_g[numDisplay],LOW);
    digitalWrite(seg_p[numDisplay],LOW);
    break;

  case 2:
    digitalWrite(seg_a[numDisplay],HIGH);
    digitalWrite(seg_b[numDisplay],HIGH);
    digitalWrite(seg_c[numDisplay],LOW);
    digitalWrite(seg_d[numDisplay],HIGH);
    digitalWrite(seg_e[numDisplay],HIGH);
    digitalWrite(seg_f[numDisplay],LOW);
    digitalWrite(seg_g[numDisplay],HIGH);
    digitalWrite(seg_p[numDisplay],LOW);
    break;

  case 3:
    digitalWrite(seg_a[numDisplay],HIGH);
    digitalWrite(seg_b[numDisplay],HIGH);
    digitalWrite(seg_c[numDisplay],HIGH);
    digitalWrite(seg_d[numDisplay],HIGH);
    digitalWrite(seg_e[numDisplay],LOW);
    digitalWrite(seg_f[numDisplay],LOW);
    digitalWrite(seg_g[numDisplay],HIGH);
    digitalWrite(seg_p[numDisplay],LOW);
    break;

  case 4:
    digitalWrite(seg_a[numDisplay],LOW);
    digitalWrite(seg_b[numDisplay],HIGH);
    digitalWrite(seg_c[numDisplay],HIGH);
    digitalWrite(seg_d[numDisplay],LOW);
    digitalWrite(seg_e[numDisplay],LOW);
    digitalWrite(seg_f[numDisplay],HIGH);
    digitalWrite(seg_g[numDisplay],HIGH);
    digitalWrite(seg_p[numDisplay],LOW);
    break;

  case 5:
    digitalWrite(seg_a[numDisplay],HIGH);
    digitalWrite(seg_b[numDisplay],LOW);
    digitalWrite(seg_c[numDisplay],HIGH);
    digitalWrite(seg_d[numDisplay],HIGH);
    digitalWrite(seg_e[numDisplay],LOW);
    digitalWrite(seg_f[numDisplay],HIGH);
    digitalWrite(seg_g[numDisplay],HIGH);
    digitalWrite(seg_p[numDisplay],LOW);
    break;

  case 6:
    digitalWrite(seg_a[numDisplay],HIGH);
    digitalWrite(seg_b[numDisplay],LOW);
    digitalWrite(seg_c[numDisplay],HIGH);
    digitalWrite(seg_d[numDisplay],HIGH);
    digitalWrite(seg_e[numDisplay],HIGH);
    digitalWrite(seg_f[numDisplay],HIGH);
    digitalWrite(seg_g[numDisplay],HIGH);
    digitalWrite(seg_p[numDisplay],LOW);
    break;

  case 7:
    digitalWrite(seg_a[numDisplay],HIGH);
    digitalWrite(seg_b[numDisplay],HIGH);
    digitalWrite(seg_c[numDisplay],HIGH);
    digitalWrite(seg_d[numDisplay],LOW);
    digitalWrite(seg_e[numDisplay],LOW);
    digitalWrite(seg_f[numDisplay],LOW);
    digitalWrite(seg_g[numDisplay],LOW);
    digitalWrite(seg_p[numDisplay],LOW);
    break;

  case 8:
    digitalWrite(seg_a[numDisplay],HIGH);
    digitalWrite(seg_b[numDisplay],HIGH);
    digitalWrite(seg_c[numDisplay],HIGH);
    digitalWrite(seg_d[numDisplay],HIGH);
    digitalWrite(seg_e[numDisplay],HIGH);
    digitalWrite(seg_f[numDisplay],HIGH);
    digitalWrite(seg_g[numDisplay],HIGH);
    digitalWrite(seg_p[numDisplay],LOW);
    break;

  case 9:
    digitalWrite(seg_a[numDisplay],HIGH);
    digitalWrite(seg_b[numDisplay],HIGH);
    digitalWrite(seg_c[numDisplay],HIGH);
    digitalWrite(seg_d[numDisplay],HIGH);
    digitalWrite(seg_e[numDisplay],LOW);
    digitalWrite(seg_f[numDisplay],HIGH);
    digitalWrite(seg_g[numDisplay],HIGH);
    digitalWrite(seg_p[numDisplay],LOW);
    break;
    
   case 10: // set relevent segments HIGH and others LOW
    digitalWrite(seg_a[numDisplay],LOW);
    digitalWrite(seg_b[numDisplay],LOW);
    digitalWrite(seg_c[numDisplay],LOW);
    digitalWrite(seg_d[numDisplay],LOW);
    digitalWrite(seg_e[numDisplay],LOW);
    digitalWrite(seg_f[numDisplay],LOW);
    digitalWrite(seg_g[numDisplay],LOW);
    digitalWrite(seg_p[numDisplay],LOW);
    break;
  }
  
}
