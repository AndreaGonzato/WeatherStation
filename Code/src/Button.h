/*
  Button.h
  Created by Andrea G. Italy, 23-04-2019.
  Released into the public domain.
*/
#ifndef Button_h
#define Button_h

#include "Arduino.h"
#include "Mode.h"
#include "MyTime.h"

class Button
{
public:
	Button(int pin, String n);

    void update(Mode *mode, MyTime *myTime);

    bool getIsPressed();
    bool getSettingMode(); //indicates if we are setting something

private:
    int pinButton = -1;
    bool isPressed = false;
    String nameButton = "";

    long setButtonTimer;                //take the initial time when you pressed the set botton
    const long longPressTime = 1000;    //indicates how many milliseconds are needed to press a button to have a long clik
    
    bool settingMode = false;  //indicates if we are setting something



};

#endif