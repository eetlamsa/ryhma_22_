#include "leds.h"

byte ledSequence[200]; 
int sequenceLength = 0;
void initializeLeds() //ledien alustus
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
 
 if (ledNumber == 0) digitalWrite(A2, HIGH);
 else if (ledNumber == 1) digitalWrite(A3, HIGH);
 else if (ledNumber == 2) digitalWrite(A4, HIGH);
 else if (ledNumber == 3) digitalWrite(A5, HIGH);
}


void clearAllLeds() //kaikkien ledien sammutus
{
 digitalWrite(A2, LOW);
 digitalWrite(A3, LOW);
 digitalWrite(A4, LOW);
 digitalWrite(A5, LOW); 
}

void setAllLeds() //kaikkien ledien sytytys
{
 digitalWrite(A2, HIGH);
 digitalWrite(A3, HIGH);
 digitalWrite(A4, HIGH);
 digitalWrite(A5, HIGH);
}


void show1() //valo show 1
{
 for (int value = 0; value < 16; value++) {
  digitalWrite(A2, (value & 0x01) ? HIGH : LOW);
  digitalWrite(A3, (value & 0x02) ? HIGH : LOW);
  digitalWrite(A4, (value & 0x04) ? HIGH : LOW);
  digitalWrite(A5, (value & 0x08) ? HIGH : LOW);
   delay(300);
}
}

void show2(int rounds) // vaoshow 2
{
  int delayTime = 800;  // aloitusnopeus (ms)
  int minDelay = 100;   // pienin viive (nopein vaihe)
  int step = 30;        // kuinka paljon nopeutta lisätään/hidastetaan per kierros
  bool speedingUp = true; // tila: nopeutuuko vai hidastuuko

  sequenceLength = 0;

  for (int r = 0; r < rounds; r++) {
    for (int i = 0; i < 4; i++) {
      byte lit = i; // LED-järjestys 0,1,2,3
      ledSequence[sequenceLength++] = lit;
      
      setLed(lit);
      delay(delayTime);
      clearAllLeds();
      delay(50);
    }

    // nopeutus tai hidastus
    if (speedingUp) {
      delayTime -= step;
      if (delayTime <= minDelay) {
        delayTime = minDelay;
        speedingUp = false; // vaihdetaan hidastukseen
      }
    } else {
      delayTime += step;
      if (delayTime >= 800) { // palattu alkuperäiseen nopeuteen
        delayTime = 800;
        speedingUp = true; // aloitetaan taas nopeutus (valinnainen)
      }
    }
  }

  clearAllLeds();
}
