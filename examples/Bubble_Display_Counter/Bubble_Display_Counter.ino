/*
Modified 2019 for 6 digit NSA1166 display

------------------------------------------
Based on
https://github.com/sparkfun/SevSeg
http://arduino.cc/playground/Main/SevenSegmentLibrary

*/

#include "SevSegPlus.h"

//Create an instance of the object.
SevSegPlus ledDisplay;


void setup()
{
  ledDisplay.begin();
}

void loop()
{
  ledDisplay.print(millis());
}
