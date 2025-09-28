#include "timer.h"

// Määritellään globaalit muuttujat
volatile bool newTimerInterrupt = false;
static volatile unsigned long tickCount = 0;  // käytetään ISR:ssä

void initializeTimer(void)
{
  TCCR1A = 0; // normaali tila
  TCCR1B = 0;
  OCR1A = 15624;               // (16e6 / 1024) - 1 = 1 Hz
  TCCR1B |= (1 << WGM12);      // CTC-tila
  TIMSK1 |= (1 << OCIE1A);     // vertailu-interrupt päälle
}

void startTimer(void)
{
  TCNT1 = 0;
  TCCR1B |= (1 << CS12) | (1 << CS10);  // prescaler 1024
}

void stopTimer(void)
{
  TIMSK1 &= ~(1 << OCIE1A);              // estetään keskeytys
  TCCR1B &= ~((1 << CS12) | (1 << CS10));// prescaler pois
}

// Keskeytys: kasvatetaan tickCountia ja merkataan tapahtuma
ISR(TIMER1_COMPA_vect)
{
  tickCount++;
  newTimerInterrupt = true;
}

// Rajapinta tickCountin lukemiseen ja nollaamiseen
unsigned long getTickCount(void)
{
  return tickCount;
}

void resetTickCount(void)
{
  tickCount = 0;
}
