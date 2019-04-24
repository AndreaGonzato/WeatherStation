/*
  controllSingleDigitDisplay.cpp
  Created by Andrea Gonzato,  23-4-2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "controllSingleDigitDisplay.h"

controllSingleDigitDisplay::controllSingleDigitDisplay()
{
    for(int i=0 ; i<2 ; i++){
        pinMode(seg_a[i], OUTPUT);
        pinMode(seg_b[i], OUTPUT);
        pinMode(seg_c[i], OUTPUT);
        pinMode(seg_d[i], OUTPUT);
        pinMode(seg_e[i], OUTPUT);
        pinMode(seg_f[i], OUTPUT);
        pinMode(seg_g[i], OUTPUT);
        pinMode(seg_p[i], OUTPUT);
    }
}

void controllSingleDigitDisplay::myUpdate(int num, bool on){
    if(num>=0){
        if(on){
            int n1 = num%10;
            int n2 = (num-n1)/10;
            updateDisplay(0,n2);
            updateDisplay(1,n1);
        }else{
            //close the display, set evry segments to LOW
            updateDisplay(0,10);
            updateDisplay(1,10);
        }
    }else{
        Serial.println("ERR - controllSingleDigitDisplay.update: num<0");
    }
}

void controllSingleDigitDisplay::updateDisplay(int numDisplay, int num)
{	
    
    if(numDisplay >= 2 || numDisplay < 0 || num >10 || num < 0){
        Serial.println("ERR - updateDisplay:");
    }
    switch(num){ // switch statemet to select what to display
    
    case 0: // set relevent segments HIGH and others LOW
        digitalWrite(seg_a[numDisplay],HIGH);
        digitalWrite(seg_b[numDisplay],HIGH);
        digitalWrite(seg_c[numDisplay],HIGH);
        digitalWrite(seg_d[numDisplay],HIGH);
        digitalWrite(seg_e[numDisplay],HIGH);
        digitalWrite(seg_f[numDisplay],HIGH);
        digitalWrite(seg_g[numDisplay],LOW);
        digitalWrite(seg_p[numDisplay],LOW);
        break;

    case 1:
        digitalWrite(seg_a[numDisplay],LOW);
        digitalWrite(seg_b[numDisplay],HIGH);
        digitalWrite(seg_c[numDisplay],HIGH);
        digitalWrite(seg_d[numDisplay],LOW);
        digitalWrite(seg_e[numDisplay],LOW);
        digitalWrite(seg_f[numDisplay],LOW);
        digitalWrite(seg_g[numDisplay],LOW);
        digitalWrite(seg_p[numDisplay],LOW);
        break;

    case 2:
        digitalWrite(seg_a[numDisplay],HIGH);
        digitalWrite(seg_b[numDisplay],HIGH);
        digitalWrite(seg_c[numDisplay],LOW);
        digitalWrite(seg_d[numDisplay],HIGH);
        digitalWrite(seg_e[numDisplay],HIGH);
        digitalWrite(seg_f[numDisplay],LOW);
        digitalWrite(seg_g[numDisplay],HIGH);
        digitalWrite(seg_p[numDisplay],LOW);
        break;

    case 3:
        digitalWrite(seg_a[numDisplay],HIGH);
        digitalWrite(seg_b[numDisplay],HIGH);
        digitalWrite(seg_c[numDisplay],HIGH);
        digitalWrite(seg_d[numDisplay],HIGH);
        digitalWrite(seg_e[numDisplay],LOW);
        digitalWrite(seg_f[numDisplay],LOW);
        digitalWrite(seg_g[numDisplay],HIGH);
        digitalWrite(seg_p[numDisplay],LOW);
        break;

    case 4:
        digitalWrite(seg_a[numDisplay],LOW);
        digitalWrite(seg_b[numDisplay],HIGH);
        digitalWrite(seg_c[numDisplay],HIGH);
        digitalWrite(seg_d[numDisplay],LOW);
        digitalWrite(seg_e[numDisplay],LOW);
        digitalWrite(seg_f[numDisplay],HIGH);
        digitalWrite(seg_g[numDisplay],HIGH);
        digitalWrite(seg_p[numDisplay],LOW);
        break;

    case 5:
        digitalWrite(seg_a[numDisplay],HIGH);
        digitalWrite(seg_b[numDisplay],LOW);
        digitalWrite(seg_c[numDisplay],HIGH);
        digitalWrite(seg_d[numDisplay],HIGH);
        digitalWrite(seg_e[numDisplay],LOW);
        digitalWrite(seg_f[numDisplay],HIGH);
        digitalWrite(seg_g[numDisplay],HIGH);
        digitalWrite(seg_p[numDisplay],LOW);
        break;

    case 6:
        digitalWrite(seg_a[numDisplay],HIGH);
        digitalWrite(seg_b[numDisplay],LOW);
        digitalWrite(seg_c[numDisplay],HIGH);
        digitalWrite(seg_d[numDisplay],HIGH);
        digitalWrite(seg_e[numDisplay],HIGH);
        digitalWrite(seg_f[numDisplay],HIGH);
        digitalWrite(seg_g[numDisplay],HIGH);
        digitalWrite(seg_p[numDisplay],LOW);
        break;

    case 7:
        digitalWrite(seg_a[numDisplay],HIGH);
        digitalWrite(seg_b[numDisplay],HIGH);
        digitalWrite(seg_c[numDisplay],HIGH);
        digitalWrite(seg_d[numDisplay],LOW);
        digitalWrite(seg_e[numDisplay],LOW);
        digitalWrite(seg_f[numDisplay],LOW);
        digitalWrite(seg_g[numDisplay],LOW);
        digitalWrite(seg_p[numDisplay],LOW);
        break;

    case 8:
        digitalWrite(seg_a[numDisplay],HIGH);
        digitalWrite(seg_b[numDisplay],HIGH);
        digitalWrite(seg_c[numDisplay],HIGH);
        digitalWrite(seg_d[numDisplay],HIGH);
        digitalWrite(seg_e[numDisplay],HIGH);
        digitalWrite(seg_f[numDisplay],HIGH);
        digitalWrite(seg_g[numDisplay],HIGH);
        digitalWrite(seg_p[numDisplay],LOW);
        break;

    case 9:
        digitalWrite(seg_a[numDisplay],HIGH);
        digitalWrite(seg_b[numDisplay],HIGH);
        digitalWrite(seg_c[numDisplay],HIGH);
        digitalWrite(seg_d[numDisplay],HIGH);
        digitalWrite(seg_e[numDisplay],LOW);
        digitalWrite(seg_f[numDisplay],HIGH);
        digitalWrite(seg_g[numDisplay],HIGH);
        digitalWrite(seg_p[numDisplay],LOW);
        break;
        
    case 10:
        digitalWrite(seg_a[numDisplay],LOW);
        digitalWrite(seg_b[numDisplay],LOW);
        digitalWrite(seg_c[numDisplay],LOW);
        digitalWrite(seg_d[numDisplay],LOW);
        digitalWrite(seg_e[numDisplay],LOW);
        digitalWrite(seg_f[numDisplay],LOW);
        digitalWrite(seg_g[numDisplay],LOW);
        digitalWrite(seg_p[numDisplay],LOW);
        break;
    }
}
