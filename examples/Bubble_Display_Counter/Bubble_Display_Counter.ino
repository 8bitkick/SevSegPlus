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

//Create global variables
unsigned long timer;
int deciSecond = 0;

void setup()
{
  ledDisplay.begin();
  timer = millis();
}

void loop()
{

  // Every 10ms we update the display
  if (millis() - timer >= 100)
  {
    timer = millis();
    deciSecond++;

    ledDisplay.print(deciSecond);
  }

  // Otherwise we can do something else
  delay(5);
}
