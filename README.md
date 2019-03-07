# SevSegPlus

Display numbers and characters on a 6 digit 7-segment display without additional controller. Tested with NSA1166 bubble LED display

## Improvements

- Display now refreshed using timer based interrupts (no need to call in loop)
- Added 6 segment display support tested on NSA1166 bubble LED display
- Library calls made a little simpler
- Some speed optimizations

## Limitations

- For Arduino Due, Zero or MKR only
- Use of TC4_Handler may clash with other libraries (e.g. LCD matrix drivers)

## Hardware

Instancing with `ledDisplay.begin();` defaults to the NSA1166 setup with the following pin assignments:

* Arduino pins 0-5 to LED digits 1-6 (NSA1166 c3 - c8) with 220 ohm resistors in series
* Arduino pins 6-13 to LED segments A-G (NSA1166 Aa - Ga)

## Example use
~~~~
#include "SevSegPlus.h"

SevSegPlus ledDisplay; 

void setup()
{
  ledDisplay.begin(); 
}

void loop()
{
  ledDisplay.print("  Hi  "); 
  delay(1000);

  ledDisplay.print("There ");
  delay(1000);
}
~~~~

## Credits

Based on: https://github.com/sparkfun/SevSeg

Original Library: http://arduino.cc/playground/Main/SevenSegmentLibrary

![Alt Text](https://github.com/8bitkick/SevSegPlus/blob/master/examples/example.png?raw=true)


