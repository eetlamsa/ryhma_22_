#include "leds.h"


void initializeLeds()
{
 pinMode(A2, OUTPUT);
 pinMode(A3, OUTPUT);
 pinMode(A4, OUTPUT);
 pinMode(A5, OUTPUT);

 digitalWrite(A2, LOW);
 digitalWrite(A3, LOW);
 digitalWrite(A4, LOW);
 digitalWrite(A5, LOW);
}

void setLed(byte ledNumber)
{
clearAllLeds();
 
 if (ledeNumber == 0) digitalWrite(A2, HIGH);
 else if (ledNumber == 1) digitalWrite(A3, HIGH);
 else if (ledNumber == 2) digitalWrite(A4, HIGH);
 else if (ledNumber == 3) digitalWrite(A5, HIGH);
}


void clearAllLeds()
{
 digitalWrite(A2, LOW);
 digitalWrite(A3, LOW);
 digitalWrite(A4, LOW);
 digitalWrite(A5, LOW); 
}

void setAllLeds()
{
 digitalWrite(A2, HIGH);
 digitalWrite(A3, HIGH);
 digitalWrite(A4, HIGH);
 digitalWrite(A5, HIGH);
}


void show1()
{
 for (int value = 0; value < 16; value++) {
  digitalWrite(A2, (value & 0x01) ? HIGH : LOW);
  digitalWrite(A3, (value & 0x02) ? HIGH : LOW);
  digitalWrite(A4, (value & 0x04) ? HIGH : LOW);
  digitalWrite(A5, (value & 0x08) ? HIGH : LOW);
   delay(300);
}

void show2(int rounds)
{
int delayTime = 300;
  int minDelay = 50;
  int step = 10;

  for (int r = 0; r < rounds; r++) {
    clearAllLeds(); digitalWrite(A2, HIGH); delay(delayTime);
    clearAllLeds(); digitalWrite(A3, HIGH); delay(delayTime);
    clearAllLeds(); digitalWrite(A4, HIGH); delay(delayTime);
    clearAllLeds(); digitalWrite(A5, HIGH); delay(delayTime);

    if (delayTime > minDelay) delayTime -= step; // increase speed
  }
  clearAllLeds();
}
