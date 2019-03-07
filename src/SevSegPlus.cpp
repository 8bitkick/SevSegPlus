/*

SevSegPlus

Allows an Arduino to easily display numbers and characters on a 6 digit 7-segment display without additional controller

- Display now refreshed using timer based interrupts (no need to call in loop)
- Added 6 segment display support tested on NSA1166 bubble LED display
- Library calls made a little simpler
- Some speed optimizations

For Arduino Due, Zero or MKR only.

---
Based on: https://github.com/sparkfun/SevSegPlus
Original Library by Dean Reading (deanreading@hotmail.com: http://arduino.cc/playground/Main/SevenSegmentLibrary), 2012

*/

#include "SevSegPlus.h"

SevSegPlus::SevSegPlus()
{
  //Initial values
  digit = 1;
  strcpy(display_string, "Hello ");

}
void SevSegPlus::begin(boolean mode_in, byte numOfDigits,
  byte dig1, byte dig2, byte dig3, byte dig4, byte dig5, byte dig6,
  byte segA, byte segB, byte segC, byte segD, byte segE, byte segF, byte segG,
  byte segDP)
  {
    //Bring all the variables in from the caller
    numberOfDigits = numOfDigits;
    digit1 = dig1;
    digit2 = dig2;
    digit3 = dig3;
    digit4 = dig4;
    digit5 = dig5;
    digit6 = dig6;

    segmentA = segA;
    segmentB = segB;
    segmentC = segC;
    segmentD = segD;
    segmentE = segE;
    segmentF = segF;
    segmentG = segG;
    segmentDP = segDP;

    //Assign input values to variables
    //mode is what the digit pins must be set at for it to be turned on. 0 for common cathode, 1 for common anode
    mode = mode_in;
    if(mode == COMMON_ANODE)
    {
      DigitOn = HIGH;
      DigitOff = LOW;
      SegOn = LOW;
      SegOff = HIGH;
    }
    else
    {
      DigitOn = LOW;
      DigitOff = HIGH;
      SegOn = HIGH;
      SegOff = LOW;
    }

    DigitPins[0] = digit1;
    DigitPins[1] = digit2;
    DigitPins[2] = digit3;
    DigitPins[3] = digit4;
    DigitPins[4] = digit5;
    DigitPins[5] = digit6;
    SegmentPins[0] = segmentA;
    SegmentPins[1] = segmentB;
    SegmentPins[2] = segmentC;
    SegmentPins[3] = segmentD;
    SegmentPins[4] = segmentE;
    SegmentPins[5] = segmentF;
    SegmentPins[6] = segmentG;
    SegmentPins[7] = segmentDP;

    //Turn everything Off before setting pin as output
    //Set all digit pins off. Low for common anode, high for common cathode
    for (byte digit = 0 ; digit < numberOfDigits ; digit++)
    {
      digitalWrite(DigitPins[digit], DigitOff);
      pinMode(DigitPins[digit], OUTPUT);
    }
    //Set all segment pins off. High for common anode, low for common cathode
    for (byte seg = 0 ; seg < 8 ; seg++)
    {
      digitalWrite(SegmentPins[seg], SegOff);
      pinMode(SegmentPins[seg], OUTPUT);
    }

    Timer();
  }

  // Let's set up some default to reduce lines in the sketch.
  void SevSegPlus::begin()
  {
    begin(COMMON_CATHODE,6,0,1,2,3,4,5,6,7,8,9,10,11,12,13);
  }

  void SevSegPlus::print(char * myString)
  {
    int len = strlen(myString);
    if (len>6) {len=6;};
    strncpy(display_string, myString,6);
  }

  // Refresh Display - turn the previous digit off, and the next digit on
  // To be called by timer every 3ms
  /*******************************************************************************************/

  void SevSegPlus::refresh()
  {

    unsigned char characterToDisplay = display_string[digit-1];
    uint8_t chr = pgm_read_byte(&characterArray[characterToDisplay]);

    //Turn off previous digit
    if (chr & (1<<6)) digitalWrite_fast(segmentA, SegOff);
    if (chr & (1<<5)) digitalWrite_fast(segmentB, SegOff);
    if (chr & (1<<4)) digitalWrite_fast(segmentC, SegOff);
    if (chr & (1<<3)) digitalWrite_fast(segmentD, SegOff);
    if (chr & (1<<2)) digitalWrite_fast(segmentE, SegOff);
    if (chr & (1<<1)) digitalWrite_fast(segmentF, SegOff);
    if (chr & (1<<0)) digitalWrite_fast(segmentG, SegOff);

    //Turn off this digit
    switch(digit)
    {
      case 1:
      digitalWrite_fast(digit1, DigitOff);
      break;
      case 2:
      digitalWrite_fast(digit2, DigitOff);
      break;
      case 3:
      digitalWrite_fast(digit3, DigitOff);
      break;
      case 4:
      digitalWrite_fast(digit4, DigitOff);
      break;
      case 5:
      digitalWrite_fast(digit5, DigitOff);
      break;
      case 6:
      digitalWrite_fast(digit6, DigitOff);
      break;
    }

    // Turn on next digit
    if (digit < (numberOfDigits+1)) {digit++;} else {digit=1;};

    characterToDisplay = display_string[digit-1];
    chr = pgm_read_byte(&characterArray[characterToDisplay]);

    if (chr==0){return;}

    switch(digit)
    {
      case 1:
      digitalWrite_fast(digit1, DigitOn);
      break;
      case 2:
      digitalWrite_fast(digit2, DigitOn);
      break;
      case 3:
      digitalWrite_fast(digit3, DigitOn);
      break;
      case 4:
      digitalWrite_fast(digit4, DigitOn);
      break;
      case 5:
      digitalWrite_fast(digit5, DigitOn);
      break;
      case 6:
      digitalWrite_fast(digit6, DigitOn);
      break;
    }

    if (chr & (1<<6)) digitalWrite_fast(segmentA, SegOn);
    if (chr & (1<<5)) digitalWrite_fast(segmentB, SegOn);
    if (chr & (1<<4)) digitalWrite_fast(segmentC, SegOn);
    if (chr & (1<<3)) digitalWrite_fast(segmentD, SegOn);
    if (chr & (1<<2)) digitalWrite_fast(segmentE, SegOn);
    if (chr & (1<<1)) digitalWrite_fast(segmentF, SegOn);
    if (chr & (1<<0)) digitalWrite_fast(segmentG, SegOn);

  }


  // Fast digital write as we are in an interrupt handler
  void SevSegPlus::digitalWrite_fast(int pin, bool val) { if (val)
    PORT->Group[g_APinDescription[pin].ulPort].OUTSET.reg = (1ul << g_APinDescription[pin].ulPin);
    else
    PORT->Group[g_APinDescription[pin].ulPort].OUTCLR.reg = (1ul << g_APinDescription[pin].ulPin);
  }

  // Interrupt Service Routine (ISR) for timer TC4
  void SevSegPlus::Handler()
  {
    // Check for overflow (OVF) interrupt
    if (TC4->COUNT8.INTFLAG.bit.OVF && TC4->COUNT8.INTENSET.bit.OVF)
    {
      refresh();
      REG_TC4_INTFLAG = TC_INTFLAG_OVF;         // Clear the OVF interrupt flag
    }
    // Check for match counter 0 (MC0) interrupt
    if (TC4->COUNT8.INTFLAG.bit.MC0 && TC4->COUNT8.INTENSET.bit.MC0)
    {
      REG_TC4_INTFLAG = TC_INTFLAG_MC0;         // Clear the MC0 interrupt flag
    }

    // Check for match counter 1 (MC1) interrupt
    if (TC4->COUNT8.INTFLAG.bit.MC1 && TC4->COUNT8.INTENSET.bit.MC1)
    {
      REG_TC4_INTFLAG = TC_INTFLAG_MC1;        // Clear the MC1 interrupt flag
    }
  }

  // Set up timer to call handler every 3ms
  // http://forum.arduino.cc/index.php?topic=396201.msg2727162#msg2727162
  // (48MHz/10= 4.8MHz, 4.8MHz/64=75kHz, 256kHz/(255 + 1) ~ 300 Hz ~ 50Hz refresh per digit).
  void SevSegPlus::Timer()
  {
    REG_GCLK_GENDIV = GCLK_GENDIV_DIV(10) |          // Divide the 48MHz clock source by divisor 10: 48MHz/10= 4.8 MHz


    GCLK_GENDIV_ID(4);            // Select Generic Clock (GCLK) 4
    while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

    REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |           // Set the duty cycle to 50/50 HIGH/LOW
    GCLK_GENCTRL_GENEN |         // Enable GCLK4
    GCLK_GENCTRL_SRC_DFLL48M |   // Set the 48MHz clock source
    GCLK_GENCTRL_ID(4);          // Select GCLK4
    while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

    // Feed GCLK4 to TC4 and TC5
    REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |         // Enable GCLK4 to TC4 and TC5
    GCLK_CLKCTRL_GEN_GCLK4 |     // Select GCLK4
    GCLK_CLKCTRL_ID_TC4_TC5;     // Feed the GCLK4 to TC4 and TC5
    while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

    REG_TC4_CTRLA |= TC_CTRLA_MODE_COUNT8;           // Set the counter to 8-bit mode
    while (TC4->COUNT8.STATUS.bit.SYNCBUSY);        // Wait for synchronization

    REG_TC4_COUNT8_CC0 = 0x55;                      // Set the TC4 CC0 register to some arbitary value
    while (TC4->COUNT8.STATUS.bit.SYNCBUSY);        // Wait for synchronization
    REG_TC4_COUNT8_CC1 = 0xAA;                      // Set the TC4 CC1 register to some arbitary value
    while (TC4->COUNT8.STATUS.bit.SYNCBUSY);        // Wait for synchronization
    REG_TC4_COUNT8_PER = 0xFF;                      // Set the PER (period) register to its maximum value
    while (TC4->COUNT8.STATUS.bit.SYNCBUSY);        // Wait for synchronization

    //NVIC_DisableIRQ(TC4_IRQn);
    //NVIC_ClearPendingIRQ(TC4_IRQn);
    NVIC_SetPriority(TC4_IRQn, 192);    // Set the Nested Vector Interrupt Controller (NVIC) priority for TC4 to 192 (lowest)
    NVIC_EnableIRQ(TC4_IRQn);         // Connect TC4 to Nested Vector Interrupt Controller (NVIC)

    REG_TC4_INTFLAG |= TC_INTFLAG_MC1 | TC_INTFLAG_MC0 | TC_INTFLAG_OVF;        // Clear the interrupt flags
    REG_TC4_INTENSET = TC_INTENSET_MC1 | TC_INTENSET_MC0 | TC_INTENSET_OVF;     // Enable TC4 interrupts
    // REG_TC4_INTENCLR = TC_INTENCLR_MC1 | TC_INTENCLR_MC0 | TC_INTENCLR_OVF;     // Disable TC4 interrupts

    REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV64 |     // Set prescaler to 64
    TC_CTRLA_ENABLE;               // Enable TC4
    while (TC4->COUNT8.STATUS.bit.SYNCBUSY);        // Wait for synchronization
  }
