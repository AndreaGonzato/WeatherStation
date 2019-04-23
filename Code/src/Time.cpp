/*
  Activity.cpp
  Created by Andrea Gonzato,  21-4-2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Time.h"


Time::Time(){
}

void Time::update()
{	
	unsigned long currentTime = millis(); // update current time
	//Serial.println(sec); 
	if (currentTime - previousTime >= synchronizationTimeInterval){   // if time is up (1 second has pass)
		previousTime = currentTime;   // updates the previous time: previousTime remember when the last sec was pass
		sec += 1;                     //update sec
		validateTime();
   	 	Serial.println(sec);          //print the actual sec on the consol, just for having a log/time rappresentation
  	}
}

void Time::validateTime(){
	if(sec>=60){
		minutes += 1;
		sec = 0;
		if(minutes>=60){
			hours += 1;
			minutes = 0;
			if(hours >= 24){
				day += 1;
				hours = 0;
				if(month == 2 && day > 28){
					month += 1;
				}
				if((month == 4 || month == 9 || month == 11) && (day >30)){
					month += 1;
				}
				if(day > 31){
					month += 1;
				}
				if(month > 12){
					month = 1;
					year += 1;
				}

			}
		}
	}
}


int Time::getSec(){
	return sec;
}

int Time::getMinutes(){
	return minutes;
}

int Time::getHours(){
	return hours;
}

