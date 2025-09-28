#include "timer.h"
#include "leds.h"
#include "buttons.h"


void timer1_init(uint16_t compareMatch, uint16_t prescaler) {
  cli(); //keskeytykset pois
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = compareMatch;      // vertailuarvo
  TCCR1B |= (1 << WGM12);    

  // prescaler-valinta
  switch (prescaler) {
    case 1:    TCCR1B |= (1 << CS10); break;
    case 8:    TCCR1B |= (1 << CS11); break;
    case 64:   TCCR1B |= (1 << CS11) | (1 << CS10); break;
    case 256:  TCCR1B |= (1 << CS12); break;
    case 1024: TCCR1B |= (1 << CS12) | (1 << CS10); break;
    default:   TCCR1B |= (1 << CS12); // oletus 256
  }

  TIMSK1 |= (1 << OCIE1A);   
  sei(); // keskeytys päälle
}

void timer1_stop() {
  TCCR1B = 0;
  TIMSK1 &= ~(1 << OCIE1A);
}

// ISR: nappien ja ledien vertailu
ISR(TIMER1_COMPA_vect) {
  updateButtons();  // päivitä nappirekisteri
  if (ledRegister != 0 && ledRegister == buttonRegister) 
 
  
}

