#include "buttons.h" 
#include "leds.h"
#include "SpedenSpelit.h"
#include "timer.h"
#include "display.h"

// -------- Alustukset --------
void initializeGame(void);
void checkGame(byte lastButtonPress);
void startTheGame(void);
void adjustTimerSpeed(void); // LISÄTTY: Nopeuden säätöfunktio

// -------- Globaalit muuttujat --------

// Nappi painettu keskeytyksessä (-1 = ei painallusta)
volatile int buttonNumber = -1;       

// Asetetaan true ajastimen keskeytyksessä, poistetaan loop():ssa
extern volatile bool newTimerInterrupt;  

// Pelin tila
uint16_t score = 0;        // pelaajan pisteet (0–65,535)
uint8_t expectedIndex = 0; // tämän hetkinen kohta sekvenssissä (0–200 max)

// LISÄTTY: Muuttujat nopeuden kasvattamista varten
uint8_t correctPresses = 0;  // Oikeiden painalluksien laskuri
uint8_t speedLevel = 0;      // Nopeustaso


void setup()
{
  randomSeed(analogRead(0)); // LISÄTTY: Satunnaislukugeneraattorin alustus
  initializeLeds();
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeTimer();
  interrupts();
  showResult(0); // LISÄTTY: Näytetään alkutulos
}

void loop()
{
  // --- Käsittelee napin painallukset ---
  if (buttonNumber >= 0) {
    int8_t pressed = buttonNumber;
    buttonNumber = -1; // Nollaa seuraavaa varten

    if (pressed == 6) { // aloitus nappi
      startTheGame();
    } else if (pressed >= 2 && pressed <= 5) {
      // muunnetaan pinnit 2..5 → LED -numeroiksi 0..3
      byte btn = static_cast<byte>(pressed - 2);
      checkGame(btn);
    }
  }
  
  // --- Käsittelee ajastimen pulssin ---
  if (newTimerInterrupt) {
    newTimerInterrupt = false;

    // MUUTETTU: Lisätään aina uusi ledi sekvenssiin
    byte rnd = random(0, 4);
    ledSequence[sequenceLength++] = rnd;
    
    // Näytetään ledi
    setLed(rnd);
    delay(300); // Ledi näkyy 300ms
    clearAllLeds();
  }
}

// --- Tarkistaa, onko pelaajan painallus oikein  ---
void checkGame(byte btn)
{
  // Estetään painallukset ennen kuin ledi on näytetty
  if (expectedIndex >= sequenceLength) {
    return; // ohitetaan painallukset ennen sekvenssiä
  }

  // Tarkistetaan onko nappi oikea
  if (btn == ledSequence[expectedIndex]) {
    // OIKEA NAPPI!
    expectedIndex++;
    score++;
    correctPresses++; // LISÄTTY: Kasvatetaan oikeiden painalluksien laskuria
    showResult(score);
    
    // LISÄTTY: Nopeutetaan peliä joka 10. oikean painalluksen jälkeen
    if (correctPresses >= 10) {
      correctPresses = 0;
      speedLevel++;
      adjustTimerSpeed();
    }
    
  } else {
    // VÄÄRÄ NAPPI → peli päättyy
    stopTimer();
    setAllLeds();
    delay(2000);
    clearAllLeds();
    
    // Nollataan pelin tila mutta pidetään lopputulos näytössä
    sequenceLength = 0;
    expectedIndex = 0;
    correctPresses = 0;  // LISÄTTY
    speedLevel = 0;      // LISÄTTY
  }
}

// LISÄTTY: Funktio joka kasvattaa pelin nopeutta 10%
void adjustTimerSpeed(void)
{
  // Lasketaan uusi OCR1A arvo
  // Alkuarvo: 15624 = 1 Hz (yksi ledi sekunnissa)
  // Jokainen taso: 10% nopeampi → kerrotaan 0.9:llä
  
  uint16_t newOCR = 15624;
  for (uint8_t i = 0; i < speedLevel; i++) {
    newOCR = (newOCR * 9) / 10;  // kerrotaan 0.9:llä
  }
  
  // Maksimi nopeus (noin 5 Hz)
  if (newOCR < 3124) {
    newOCR = 3124;
  }
  
  // Päivitetään timer
  cli();         // Estetään keskeytykset hetkeksi
  OCR1A = newOCR;  // Asetetaan uusi vertailuarvo
  TCNT1 = 0;     // Nollataan laskuri välttääksemme viiveen
  sei();         // Sallitaan keskeytykset
}

void initializeGame()
{
  sequenceLength = 0;
  score = 0;
  expectedIndex = 0;
  correctPresses = 0;  // LISÄTTY
  speedLevel = 0;      // LISÄTTY
  clearAllLeds();
  showResult(0);
  
  // LISÄTTY: Palautetaan timer alkuperäiseen 1 Hz nopeuteen
  OCR1A = 15624;
}

void startTheGame()
{
  initializeGame();
  resetTickCount();
  startTimer();
}