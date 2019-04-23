/*
  Mode.h
  Created by Andrea G. Italy, 23-04-2019.
  Released into the public domain.
*/
#ifndef Mode_h
#define Mode_h

#include "Arduino.h"

class Mode
{
public:
	Mode();

    String getActiveMode();
    void scrollRight();
    void scrollLeft();

private:
    String activeMode = "";
    String modes[5] = {"TIME", "DATE", "DEGREES", "HUMIDITY", "ALLARM"};
    int index;
    int maxIndexValue = 4;
    

};

#endif