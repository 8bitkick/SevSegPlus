/*
 Modified 2019 for 6 digit NSA1166 display

 ------------------------------------------
 Based on
 https://github.com/sparkfun/SevSeg
 http://arduino.cc/playground/Main/SevenSegmentLibrary

*/

#include "SevSegPlus.h"


SevSegPlus ledDisplay; //Create an instance of the object.

void setup()
{
  ledDisplay.begin(); // Start the display refresh in background using timer
}

void scroll(char * text)
{
  char temp[6];
  int  len = strlen(text);
  for(int i = 0; i < (len-6); i++) {
    strncpy(temp, text+i, 6);
    ledDisplay.print(temp);
    delay(200);
  }
}

void loop()
{

  ledDisplay.print("  Hi  ");  // print something to our LED
  delay(1000);

  ledDisplay.print("There ");
  delay(1000);

  scroll("      Arduino 7 SEg LED DisplaY      ");


}
