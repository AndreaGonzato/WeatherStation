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
    index += 1;
    if(index > maxIndexValue){
        index = 0;
    }
}

void Mode::scrollLeft(){
    index -= 1;
    if(index < 0){
        index = maxIndexValue;
    }
}

