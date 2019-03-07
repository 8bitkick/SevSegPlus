/*
 Modified 2019 for 6 digit NSA1166 display

 ------------------------------------------
 Based on
 https://github.com/sparkfun/SevSeg
 http://arduino.cc/playground/Main/SevenSegmentLibrary

*/

#include "SevSegPlus.h"


SevSegPlus ledDisplay; //Create an instance of the object.
void TC4_Handler() { ledDisplay.Handler(); }; // Set up the display handler

void setup()
{
  ledDisplay.begin(); // Start the display refresh in background using timer
}

void loop()
{

  ledDisplay.print("  Hi  ");  // print something to our LED
  delay(1000);

  ledDisplay.print("There ");
  delay(1000);

  char scroll[] = "      Arduino       ";
  char temp[6];

  for(int i = 0; i < 13; i++) {
    strncpy(temp, scroll+i, 6);
    ledDisplay.print(temp);
    delay(200);
  }

}
