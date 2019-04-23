/*
  Date.h
  Created by Andrea G. Italy, 23-04-2019.
  Released into the public domain.
*/
#ifndef Date_h
#define Date_h

#include "Activity.h"
#include "Arduino.h"

class Date : public Activity
{
public:
	Date();

	int day = 1;
	int month = 1;
	int year = 19;

	void update();


};

#endif