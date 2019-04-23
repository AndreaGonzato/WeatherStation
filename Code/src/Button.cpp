/*
  Button.cpp
  Created by Andrea Gonzato,  23-4-2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Button.h"
#include "Mode.h"

Button::Button(int pin, String n){
    pinButton = pin;
    nameButton = n;
}

void Button::update(Mode *mode)
{	
    if(isPressed != digitalRead(pinButton)){
        if(digitalRead(pinButton) && isPressed == false){
            //start to press the button
            Serial.println(nameButton);
            if(nameButton.equals("PLUS"))
                mode->scrollRight();
            if(nameButton.equals("MIN"))
                mode->scrollLeft();
            if(nameButton != "SET")
                Serial.println(mode->getActiveMode());
        }
        isPressed = digitalRead(pinButton);  //update button status
    }
}

bool Button::getIsPressed(){
    return isPressed;
}

