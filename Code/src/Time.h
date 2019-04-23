/*
  Time.h
  Created by Andrea G. Italy, 21-04-2019.
  Released into the public domain.
*/
#ifndef Time_h
#define Time_h

#include "Arduino.h"

class Time
{
public:
	Time();

	void update();

	int getSec();
	int getMinutes();
	int getHours();

private:
	int sec = 0;
	int minutes = 0;
	int hours = 0;
	int day = 1;
	int month = 1;
	int year = 19;

	void validateTime();

	const double synchronizationTimeInterval = 1000;
	unsigned long previousTime = 0;

};

#endif