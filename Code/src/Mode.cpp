/*
  Mode.cpp
  Created by Andrea Gonzato,  23-4-2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Mode.h"

Mode::Mode(){
    index = 0;
    activeMode = modes[index];
}

String Mode::getActiveMode(){
    return modes[index];
}

void Mode::scrollRight(){
    updateOLED = true;
    index += 1;
    if(index > maxIndexValue){
        index = 0;
    }
}

void Mode::scrollLeft(){
    updateOLED = true;
    index -= 1;
    if(index < 0){
        index = maxIndexValue;
    }
}

void Mode::setUpdateOLED(bool u){
    updateOLED = u;
}

bool Mode::getUpdateOLED(){
    return updateOLED;
}

bool Mode::getSettingActivity(){
    return settingActivity;
}

void Mode::setSettingActivity(bool s){
    if(index != 2 && index != 3) //you can not set DEGREES & HUMIDITY
        settingActivity = s;
}

String Mode::getActualSubMenu(){
    return subMenu[index][indexSubMenu];
}

int Mode::getIndex(){
    return index;
}
void Mode::scrollSubMenu(){
    if(index == 0 || index == 1 || index == 4){
        String toPrint = "";

        switch (index)
        {
            case 0: //"TIME" sub menu                
                indexSubMenu += 1;
                settingActivity = true;
                toPrint = getActualSubMenu();
                if(indexSubMenu>3){
                    indexSubMenu = 0;
                    settingActivity = false;
                    displayWhatAreYouSetting = true;
                }
                break;

            case 1: //"DATE" sub menu
                indexSubMenu += 1;
                settingActivity = true;
                toPrint = getActualSubMenu();
                if(indexSubMenu>3){
                    indexSubMenu = 0;
                    settingActivity = false;
                    displayWhatAreYouSetting = true;
                }
                break;
            
            case 4: //"ALLARM sub menu"
                //"ALLARM" sub menu
                indexSubMenu += 1;
                settingActivity = true;
                toPrint = getActualSubMenu();
                if(indexSubMenu>3){
                    indexSubMenu = 0;
                    settingActivity = false;
                    displayWhatAreYouSetting = true;
                }
                break;

        }
        Serial.println(toPrint);

    }
    
    
}


int Mode::getIndexSubMenu(){
    return indexSubMenu;
}


bool Mode::getDisplayWhatAreYouSetting(){
    return displayWhatAreYouSetting;
}

String Mode::getModes(int i){
    return modes[i];
}

void Mode::setDisplayWhatAreYouSetting(bool d){
    displayWhatAreYouSetting = d;
}
 void Mode::switchAlarmStatus(){
    if(modes[4] == "ALARM OFF"){
        modes[4] = "ALARM ON";
        Serial.println("ALARM ON");
    }else{
        if(modes[4] == "ALARM ON"){
            modes[4] = "ALARM OFF";
            Serial.println("ALARM OFF");
        }
    }
    updateOLED = true;
 }