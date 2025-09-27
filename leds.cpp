#include "leds.h"

volatile byte ledRegister = 0;
byte ldeSequence[200];
int sequenceLength = 0:

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

 ledRegister = (1 << ledNumber);
 
 if (ledNumber == 0) digitalWrite(A2, HIGH);
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
 ledRegister = 0;
}

void setAllLeds()
{
 digitalWrite(A2, HIGH);
 digitalWrite(A3, HIGH);
 digitalWrite(A4, HIGH);
 digitalWrite(A5, HIGH);
 ledRegister = 0b1111;
}


void show1()
{
 for (int value = 0; value < 16; value++) {
  digitalWrite(A2, (value & 0x01) ? HIGH : LOW);
  digitalWrite(A3, (value & 0x02) ? HIGH : LOW);
  digitalWrite(A4, (value & 0x04) ? HIGH : LOW);
  digitalWrite(A5, (value & 0x08) ? HIGH : LOW);

  ledRegister = value & 0x0F;
   delay(300);
}
}

void show2(int rounds)
{

int delayTime = 800; //aloitus nopeus
 int maxDelay = 100; // suurin nopeus
 int lvlup = 20; // nopeuden lisääminen per kierros

 sequenceLength = 0; 
 // edellisen pelin nollaus?
 
 
 for (int r = 0; r < rounds; r++) {
  byte leds[4] = {0, 1, 2, 3}; //taulukko 

  //ledien random järjestyksen syöttäminen
  for (int i = 3; i > 0; i--) {
   int j = random(i+ 1);
   byte temp = leds[i];
   leds[i] = leds[j];
   leds[j] = temp;
}
  //ledien sytytys ja järjestyksen tallennus
 for (int i = 0; i < 4; i++) {
  byte lit = leds[i];
  ledSequence[sequenceLength++] = lit;
  
      setLed(lit);
      delay(delayTime);
      clearAllLeds();
      delay(50);
 }
  //nopeutus
 if (delayTime > maxDelay) {
      delayTime -= lvlup; 
 }
 }
clearAllLeds();
}
