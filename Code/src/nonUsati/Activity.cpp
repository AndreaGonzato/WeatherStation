/*
  Activity.cpp
  Created by Andrea Gonzato,  21-4-2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Activity.h"


Activity::Activity()
{
	//Serial.println("new Activity created");
}

void Activity::update()
{
	Serial.println("update Activity");
}

void Activity::display()
{
	Serial.println("display Activity");
}
