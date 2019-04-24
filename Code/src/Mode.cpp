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
    if(index == 0){
        //"TIME" sub menu
        indexSubMenu += 1;
        settingActivity = true;
        Serial.println(getActualSubMenu());
        if(indexSubMenu>3){
            indexSubMenu = 0;
            settingActivity = false;
            displayWhatAreYouSetting = true;
        }
    }
    if(index == 1){
        //"DATE" sub menu
        indexSubMenu += 1;
        settingActivity = true;
        Serial.println(getActualSubMenu());
        if(indexSubMenu>3){
            indexSubMenu = 0;
            settingActivity = false;
            displayWhatAreYouSetting = true;
        }
    }
    
}


int Mode::getIndexSubMenu(){
    return indexSubMenu;
}


bool Mode::getDisplayWhatAreYouSetting(){
    return displayWhatAreYouSetting;
}

void Mode::setDisplayWhatAreYouSetting(bool d){
    displayWhatAreYouSetting = d;
}