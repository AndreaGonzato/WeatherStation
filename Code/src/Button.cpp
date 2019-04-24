/*
  Button.cpp
  Created by Andrea Gonzato,  23-4-2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Button.h"
#include "Mode.h"
#include "MyTime.h"

Button::Button(int pin, String n){
    pinButton = pin;
    nameButton = n;
    settingMode = false;
}

void Button::update(Mode *mode, MyTime *myTime)
{	
    if(isPressed != digitalRead(pinButton)){
        if(digitalRead(pinButton) && isPressed == false){
            //one button is press

            Serial.println(nameButton); //print what button is pressed
            Serial.println(mode->getSettingActivity());

            if(mode->getSettingActivity()){
                //setting

                if(nameButton.equals("SET")){
                    mode->scrollSubMenu();
                
                    if(!mode->getSettingActivity()){
                        settingMode = false;
                        setButtonTimer = millis();
                    }
                }

                switch(mode->getIndexSubMenu())
                {
                    case 1:
                        if(nameButton.equals("PLUS")){
                            myTime->setMyHours(myTime->getMyHours()+1);
                        }
                        if(nameButton.equals("MIN")){
                            myTime->setMyHours(myTime->getMyHours()-1);
                        }
                        break;
                    case 2:
                        if(nameButton.equals("PLUS")){
                            myTime->setMyMinutes(myTime->getMyMinutes()+1);
                        }
                        if(nameButton.equals("MIN")){
                            myTime->setMyMinutes(myTime->getMyMinutes() -1);
                        }
                        break;
                    case 3:
                        if(nameButton.equals("PLUS")){
                            myTime->setMySec(myTime->getMySec()+1);
                        }
                        if(nameButton.equals("MIN")){
                            myTime->setMySec(myTime->getMySec() -1);
                        }
                        break;
                }
                
            }else{
                //when you start to press one button
                if(nameButton.equals("PLUS"))
                    mode->scrollRight();
                if(nameButton.equals("MIN"))
                    mode->scrollLeft();
                if(nameButton != "SET")
                    Serial.println(mode->getActiveMode());
                if(nameButton == "SET"){
                    Serial.println("TEST");
                    setButtonTimer = millis();  //take the initial time when you pressed the set botton
                }
            }
                
        }
        isPressed = digitalRead(pinButton);  //update button status
    }

    if(nameButton == "SET" && isPressed){
        if ((millis() - setButtonTimer > longPressTime) && (settingMode == false)) {
            //setButton had a long click
            settingMode = true;  // now we are in the setting mode
            Serial.println("LONG CLICK");
            mode->scrollSubMenu();
        }
    }
}

bool Button::getIsPressed(){
    return isPressed;
}

bool Button::getSettingMode(){
    return settingMode;
}

