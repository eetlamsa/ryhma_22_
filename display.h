#ifndef DISPLAY_H
#define DISPLAY_H
#include <arduino.h>



static const uint8_t DIGIT_CC[10] = {
  0x3F, // 0
  0x06, // 1 
  0x5B, // 2 
  0x4F, // 3 
  0x66, // 4 
  0x6D, // 5 
  0x7D, // 6 
  0x07, // 7 
  0x7F, // 8 
  0x6F  // 9
};

static const uint8_t SEG_BLANK = 0x00; 

const uint8_t PIN_SER = 8;
const uint8_t PIN_OE  = 9;
const uint8_t PIN_LATCH = 10;
const uint8_t PIN_CLOCK = 11;
const uint8_t PIN_RESET = 12;

static const uint8_t SEG_A  = 0;
static const uint8_t SEG_B  = 1;
static const uint8_t SEG_C  = 2;
static const uint8_t SEG_D  = 3;
static const uint8_t SEG_E  = 4;
static const uint8_t SEG_F  = 5;
static const uint8_t SEG_G  = 6;
static const uint8_t SEG_DP = 7;

void initializeDisplay(void);

static inline void setDataBit(bool v);


static inline void pulseClock();

static inline void pulseLatch();

static void shiftOutByte(uint8_t value);

void writeByte(uint8_t number, bool last);



void writeHighAndLowNumber(uint8_t tens,uint8_t ones);


void showResult(byte result);
#endif