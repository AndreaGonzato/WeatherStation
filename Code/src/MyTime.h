/*
  Time.h
  Created by Andrea G. Italy, 21-04-2019.
  Released into the public domain.
*/
#ifndef MyTime_h
#define MyTime_h

#include "Arduino.h"
#include "Mode.h"

class MyTime
{
public:
	MyTime();

	void update(Mode *mode);

	void validateTimeDuringSettings();

	int getMySec();
	int getMyMinutes();
	int getMyHours();
	int getMyDay();
	int getMyMonth();
	int getMyYear();

	void setMySec(int s);
	void setMyMinutes(int m);
	void setMyHours(int h);
	void setMyDay(int d);
	void setMyMonth(int m);
	void setMyYear(int y);



private:
	int mySec = 0;
	int myMinutes = 0;
	int myHours = 0;
	int myDay = 1;
	int myMonth = 1;
	int myYear = 19;

	const int blinkInterval = 500;
	unsigned long lastBlink = 0;

	void validateTime();
	bool isInSettingMode = false;

	const double synchronizationTimeInterval = 1000;
	unsigned long previousTime = 0;

};

#endif