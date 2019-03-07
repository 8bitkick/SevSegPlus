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

---
Based on: https://github.com/sparkfun/SevSeg

Original Library: http://arduino.cc/playground/Main/SevenSegmentLibrary


![Alt Text](https://github.com/8bitkick/SevSegPlus/blob/master/examples/example.png?raw=true)

