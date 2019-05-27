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
	MyTime(int allarmPinIO, int allarmPin5V, int alarmFrequency);

	void update(Mode *mode);

	void validateTimeDuringSettings();

	int getMySec();
	int getMyMinutes();
	int getMyHours();

	int getMySecAllarm();
	int getMyMinutesAllarm();
	int getMyHoursAllarm();

	int getMyDay();
	int getMyMonth();
	int getMyYear();

	void setMySec(int s);
	void setMyMinutes(int m);
	void setMyHours(int h);

	void setMySecAllarm(int s);
	void setMyMinutesAllarm(int m);
	void setMyHoursAllarm(int h);

	void setMyDay(int d);
	void setMyMonth(int m);
	void setMyYear(int y);

private:
	int mySec = 0;
	int myMinutes = 0;
	int myHours = 9;

	int mySecAllarm = 10;
	int myMinutesAllarm = 0;
	int myHoursAllarm = 9;

	int myDay = 1;
	int myMonth = 1;
	int myYear = 19;

	bool isTimeToPlayAllarm(); //indicate if we need to start play the allrm

	void startAllarm();
	void endAllarm();

	const int blinkInterval = 500;
	unsigned long lastBlink = 0;

	void validateTime(); 		  //check that the date format is correct

	bool isInSettingMode = false; //indicates if you are setting something

	const double synchronizationTimeInterval = 1000;  //indicates how many milliseconds to increase the system by one second
	unsigned long previousTime = 0;  				  //previous second past when the system was active from this var milliseconds

	int allarmPinIO;
	int allarmPin5V;
	int alarmFrequency;

	const int alarmInterval = 5000;
	unsigned long timeToEndAllarm = 0; 

};

#endif