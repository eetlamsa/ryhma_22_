#include "buttons.h"

extern volatile int buttonNumber;

// MUUTOS: Vaihdettu uint8_t -> unsigned long jotta millis() toimii oikein
volatile unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void initButtonsAndButtonInterrupts(void)
{
  //Alustetaan napit tuloiksi
  for (int i = 2; i < 7; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  PCICR = 0b00000100; //PCIE2 portD keskeytykset aktivoitu

  PCMSK2 = 0b01111100; //Keskeytykset sallittu pinneille 2-6

}

ISR(PCINT2_vect) {
  // MUUTOS: Käytetään täyttä millis() arvoa ilman & 0xFF maskia
  unsigned long currentTime = millis(); //debounce
  if ((currentTime - lastDebounceTime) > debounceDelay) {
  if (!(PIND & (1 << PIND2))) {
  buttonNumber = 2; //Pinni 2 nappi
  }
  else if (!(PIND &(1 << PIND3))) {
    buttonNumber = 3; //Pinni 3 nappi
  }
  else if (!(PIND &(1 << PIND4))) {
    buttonNumber = 4;//Pinni 4 nappi
  }
  else if (!(PIND &(1 << PIND5))) {
    buttonNumber = 5;//Pinni 5 nappi
  }
  else if (!(PIND &(1 << PIND6))) {
    buttonNumber = 6; //Pinni 6 nappi (aloitus)?
  }
  lastDebounceTime = currentTime; //Laitetaan lastDebounceTimeen nykyinen aika.
}
}