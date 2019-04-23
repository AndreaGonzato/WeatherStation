/*
  Button.h
  Created by Andrea G. Italy, 23-04-2019.
  Released into the public domain.
*/
#ifndef Button_h
#define Button_h

#include "Arduino.h"
#include "Mode.h"

class Button
{
public:
	Button(int pin, String n);

    void update(Mode *mode);
    bool getIsPressed();

private:
    int pinButton = -1;
    bool isPressed = false;
    String nameButton = "";



};

#endif