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
void TC4_Handler() { ledDisplay.Handler(); };

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
    char tempString[12]; //Used for sprintf
    timer = millis();
    deciSecond++;
    sprintf(tempString, "%6d", deciSecond);
    ledDisplay.print(tempString);
  }

  // Otherwise we can do something else
  delay(5);
}
