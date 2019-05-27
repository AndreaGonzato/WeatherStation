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

            if(mode->getSettingActivity()){
                //setting

                if(nameButton.equals("SET")){
                    mode->scrollSubMenu();
                    
                    if(!mode->getSettingActivity()){
                        //end setting
                        settingMode = false;
                        setButtonTimer = millis();
                    }
                    
                }

                switch(mode->getIndexSubMenu())
                {
                    case 1:
                        if(mode->getIndex() == 0){
                            //TIME
                            if(nameButton.equals("PLUS")){
                                myTime->setMyHours(myTime->getMyHours()+1);
                            }
                            if(nameButton.equals("MIN")){
                                myTime->setMyHours(myTime->getMyHours()-1);
                            }
                        }
                        if(mode->getIndex() == 1){
                            //DATE
                            if(nameButton.equals("PLUS")){
                                myTime->setMyDay(myTime->getMyDay()+1);
                            }
                            if(nameButton.equals("MIN")){
                                myTime->setMyDay(myTime->getMyDay()-1);
                            }
                        }
                        if(mode->getIndex() == 4){
                            //ALLARM
                            if(nameButton.equals("PLUS")){
                                myTime->setMyHoursAllarm(myTime->getMyHoursAllarm()+1);
                            }
                            if(nameButton.equals("MIN")){
                                myTime->setMyHoursAllarm(myTime->getMyHoursAllarm()-1);
                            }
                        }
	                    myTime->validateTimeDuringSettings();
                        
                        break;
                    case 2:
                        if(mode->getIndex() == 0){
                            //TIME
                            if(nameButton.equals("PLUS")){
                                myTime->setMyMinutes(myTime->getMyMinutes()+1);
                            }
                            if(nameButton.equals("MIN")){
                                myTime->setMyMinutes(myTime->getMyMinutes() -1);
                            }
                        }
                        if(mode->getIndex() == 1){
                            //DATE
                            if(nameButton.equals("PLUS")){
                                myTime->setMyMonth(myTime->getMyMonth()+1);
                            }
                            if(nameButton.equals("MIN")){
                                myTime->setMyMonth(myTime->getMyMonth()-1);
                            }
                        }
                        if(mode->getIndex() == 4){
                            //ALLARM
                            if(nameButton.equals("PLUS")){
                                myTime->setMyMinutesAllarm(myTime->getMyMinutesAllarm()+1);
                            }
                            if(nameButton.equals("MIN")){
                                myTime->setMyMinutesAllarm(myTime->getMyMinutesAllarm() -1);
                            }
                        }
                        myTime->validateTimeDuringSettings();

                        break;
                    case 3:
                        if(mode->getIndex() == 0){
                            if(nameButton.equals("PLUS")){
                                myTime->setMySec(myTime->getMySec()+1);
                            }
                            if(nameButton.equals("MIN")){
                                myTime->setMySec(myTime->getMySec() -1);
                            }
                        }
                        if(mode->getIndex() == 1){
                            //DATE
                            if(nameButton.equals("PLUS")){
                                myTime->setMyYear(myTime->getMyYear()+1);
                            }
                            if(nameButton.equals("MIN")){
                                myTime->setMyYear(myTime->getMyYear()-1);
                            }
                        }
                        if(mode->getIndex() == 4){
                            //ALLARM
                            if(nameButton.equals("PLUS")){
                                myTime->setMySecAllarm(myTime->getMySecAllarm()+1);
                            }
                            if(nameButton.equals("MIN")){
                                myTime->setMySecAllarm(myTime->getMySecAllarm() -1);
                            }
                        }
                        myTime->validateTimeDuringSettings();

                        break;
                }
                
            }else{
                //no setting
                //when you start to press one button, navigate menu to menu
                if(nameButton.equals("PLUS"))
                    mode->scrollRight();
                if(nameButton.equals("MIN"))
                    mode->scrollLeft();
                if(nameButton != "SET")
                    Serial.println(mode->getActiveMode());
                if(nameButton == "SET"){
                    if(mode->getActiveMode() == "ALLARM OFF" || mode->getActiveMode() == "ALLARM ON" ){
                        mode->switchAlarmStatus();
                    }
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

