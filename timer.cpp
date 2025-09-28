#include "timer.h"

// Tämän muuttujan tarvitsee olla määritelty täällä
volatile bool newTimerInterrupt = false;

// Timerin alustus, mutta EI vielä käynnistystä
void initializeTimer(void)
{
  TCCR1A = 0; // normaali tila
  TCCR1B = 0;
  OCR1A = 15624;               // (16e6 / 1024) - 1 = 1 Hz
  TCCR1B |= (1 << WGM12);      // CTC-tila
  TIMSK1 |= (1 << OCIE1A);     // vertailu-interrupt päälle
  // ei prescaleria vielä
}

// Timerin käynnistys (prescaler 1024)
void startTimer(void)
{
  TCNT1 = 0;
  TCCR1B |= (1 << CS12) | (1 << CS10);
}

// Timerin pysäytys
void stopTimer(void)
{
  TIMSK1 &= ~(1 << OCIE1A);  // estetään keskeytys
  TCCR1B &= ~((1 << CS12) | (1 << CS10)); // prescalerit pois → pysähtyy
}

// ISR itse .cpp:ssä
ISR(TIMER1_COMPA_vect)
{
  newTimerInterrupt = true;
}

