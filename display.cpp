#include "display.h"

void initializeDisplay(void) {
pinMode(PIN_SER, OUTPUT);
pinMode(PIN_OE, OUTPUT);
pinMode(PIN_LATCH, OUTPUT);
pinMode(PIN_CLOCK, OUTPUT);
pinMode(PIN_RESET, OUTPUT);
digitalWrite(PIN_SER, LOW);
digitalWrite(PIN_OE, LOW);
digitalWrite(PIN_LATCH, LOW);
digitalWrite(PIN_CLOCK, LOW);
digitalWrite(PIN_RESET, HIGH);
}

static inline void setDataBit(bool v) {
  digitalWrite(PIN_SER, v ? HIGH : LOW);
}

static inline void pulseClock() {            // SH_CP / SRCLK
  digitalWrite(PIN_CLOCK, HIGH);
  digitalWrite(PIN_CLOCK, LOW);
}

static inline void pulseLatch() {            // ST_CP / RCLK
  digitalWrite(PIN_LATCH, HIGH);
  digitalWrite(PIN_LATCH, LOW);
}

//  MSB → LSB
static void shiftOutByte(uint8_t value) {
  for (int i = 7; i >= 0; --i) {             // MSB eka
    setDataBit((value >> i) & 0x01);
    pulseClock();
  }
}

void writeHighAndLowNumber(uint8_t tens, uint8_t ones) {
  writeByte(tens, false);   // eka bitti
  writeByte(ones,  true);   // toinen bitti
}
  

/*
  showResuts(byte result) This function separates tens and ones
  from a result number and calls writeHighAndLowNumber subroutine
  to actually write the number to 7-segment display.
  
  Parameters:
  byte result: A number between 0,1,..,99. This function
*/
void showResult(byte result) {
uint8_t tens = result / 10;
uint8_t ones = result % 10;
writeHighAndLowNumber(tens, ones);
}

void writeByte(uint8_t number, bool last)
{
  
  uint8_t pattern = (number < 10) ? DIGIT_CC[number] : SEG_BLANK;


  shiftOutByte(pattern);

 
  if (last) {
    pulseLatch();
  }
}
