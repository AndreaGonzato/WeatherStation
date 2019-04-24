/*
  controllSingleDigitDisplay.h
  Created by Andrea G. Italy, 23-04-2019.
  Released into the public domain.
*/
#ifndef controllSingleDigitDisplay_h
#define controllSingleDigitDisplay_h

#include "Arduino.h"

class controllSingleDigitDisplay
{
public:
	controllSingleDigitDisplay(); //constructor

    void myUpdate(int num);
    void updateDisplay(int numDisplay, int num);

private:

    // single digit display 1 & 2
    const int seg_a[2] = {38, 30};
    const int seg_b[2] = {37, 29};
    const int seg_c[2] = {34, 26};
    const int seg_d[2] = {35, 27};
    const int seg_e[2] = {36, 28};
    const int seg_f[2] = {39, 31};
    const int seg_g[2] = {40, 32};
    const int seg_p[2] = {33, 25}; 
};

#endif