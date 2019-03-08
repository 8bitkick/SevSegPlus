# SevSegPlus

Display numbers and characters on a 6 digit 7-segment display without additional controller. Tested with 1970s NSA1166 bubble LED display


![Alt Text](https://raw.githubusercontent.com/8bitkick/SevSegPlus/master/examples/led.gif)

## Improvements

- Display now refreshed in the background using timer based interrupts (no need to call in loop)
- Added 6 segment display support tested on NSA1166 bubble LED display
- Library calls made a little simpler
- Some speed optimizations

## Limitations

- For Arduino Due, Zero or MKR only
- Use of TC4_Handler may clash with other libraries (e.g. LCD matrix drivers)

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

## Hardware

These instructions are for the 6 digit NSA1166 LED 'bubble' display https://www.jameco.com/Jameco/Products/ProdDS/2210976NAT.pdf


* NSA1166 with male headers
* inserted into breadboard
* 220 ohm resistors in series with the 6x cathodes 'digit'
* hooked up to Arduino MKR 1010 with jumper wires (see table below)
Pinout from Arduino to NSA1166 display

Use a 220ohm limiting resistor in series for each of these cathode lines

|        |Arduino  | NSA1166|
| :------------- | :----------: | -----------: |
|digit1     |0     |Pin 6|
|digit2     |1     |Pin 8|
|digit3     |2     |Pin 10|
|digit4     |3     |Pin 12|
|digit5     |4     |Pin 14|
|digit6     |5     |Pin 16|

The segment pins are hooked directly to the Arduino

| |Arduino  |NSA1166|
| :------------- | :----------: | -----------: |
|segA       |6     |Pin 7|
|segB       |7     |Pin 15|
|segC       |8     |Pin 3|
|segD       |9     |Pin 11|
|segE       |10    |Pin 9|
|segF       |11    |Pin 17|
|segG       |12    |Pin 13|
|segDP      |13    |Pin 5|


## Credits

Based on: https://github.com/sparkfun/SevSeg

Original Library: http://arduino.cc/playground/Main/SevenSegmentLibrary



