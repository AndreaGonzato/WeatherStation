/*
  Activity.cpp
  Created by Andrea Gonzato,  21-4-2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "MyTime.h"
#include "Mode.h"


MyTime::MyTime(){
}

void MyTime::update(Mode *mode)
{	
	unsigned long currentTime = millis(); // update current time
	//Serial.println(sec); 
	if (currentTime - previousTime >= synchronizationTimeInterval){   // if time is up (1 second has pass)
		previousTime = currentTime;   // updates the previous time: previousTime remember when the last sec was pass
		mySec += 1;                     //update sec
		validateTime();
   	 	Serial.println(mySec);          //print the actual sec on the consol, just for having a log/time rappresentation

	}
	if(mode->getSettingActivity()){
		//setting-mode
		//I need to change the var displayWhatAreYouSetting evry blinkInterval
		if(currentTime-lastBlink >= blinkInterval){
			lastBlink = currentTime;
			mode->setDisplayWhatAreYouSetting(!mode->getDisplayWhatAreYouSetting());
		}
	}
}

void MyTime::validateTime(){

	if(mySec>=60){
		myMinutes += 1;
		mySec = 0;
		if(myMinutes>=60){
			myHours += 1;
			myMinutes = 0;
			if(myHours >= 24){
				myDay += 1;
				myHours = 0;
				if(myMonth == 2 && myDay > 28){
					myMonth += 1;
				}
				if((myMonth == 4 || myMonth == 9 || myMonth == 11) && (myDay >30)){
					myMonth += 1;
				}
				if(myDay > 31){
					myMonth += 1;
				}
				if(myMonth > 12){
					myMonth = 1;
					myYear += 1;
				}

			}
		}
	}
	
}

void MyTime::validateTimeDuringSettings(){
	if(mySec>=60){
		mySec = 0;
	}
	if(mySec<0){
		mySec = 59;
	}

	if(myMinutes>=60){
		myMinutes = 0;
	}
	if(myMinutes<0){
		myMinutes = 59;
	}

	if(myHours>=24){
		myHours = 0;
	}
	if(myHours<0){
		myHours = 23;
	}

	if(myDay>31){
		myDay = 1;
	}
	if(myDay<1){
		myDay = 31;
	}

	if(myMonth>12){
		myMonth=1;
	}
	if(myMonth<1){
		myMonth = 12;
	}

	if(myYear>99){
		myYear = 0;
	}
	if(myYear<0){
		myYear = 99;
	}

}



int MyTime::getMySec(){
	return mySec;
}

int MyTime::getMyMinutes(){
	return myMinutes;
}

int MyTime::getMyHours(){
	return myHours;
}

int MyTime::getMyDay(){
	return myDay;
}

int MyTime::getMyMonth(){
	return myMonth;
}

int MyTime::getMyYear(){
	return myYear;
}


void MyTime::setMySec(int s){
	mySec = s;
}

void MyTime::setMyMinutes(int m){
	myMinutes = m;
}

void MyTime::setMyHours(int h){
	myHours = h;
}

void MyTime::setMyDay(int d){
	myDay = d;
}

void MyTime::setMyMonth(int m){
	myMonth = m;
}

void MyTime::setMyYear(int y){
	myYear = y;
}


