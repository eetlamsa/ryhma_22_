#include "buttons.h" 
#include "leds.h"
#include "SpedenSpelit.h"
#include "timer.h"

// -------- Declarations --------
void initializeGame(void);
void checkGame(byte lastButtonPress);
void startTheGame(void);

// -------- Global Variables --------

// Button pressed in ISR (-1 = none)
volatile int8_t buttonNumber = -1;       

// Set true in timer ISR, cleared in loop()
extern volatile bool newTimerInterrupt;  

// Game state
uint16_t score = 0;        // player score (0–65,535)
uint8_t expectedIndex = 0; // current position in sequence (0–200 max)


void setup()
{
  initializeLeds();
  initButtonsAndButtonInterrupts();
  // initializeDisplay();
  initializeTimer();
  interrupts();

void loop()
{
  // --- Handle button press ---
  if (buttonNumber >= 0) {
    int8_t pressed = buttonNumber;
    buttonNumber = -1; // reset for next press

    if (pressed == 6) { // start button
      startTheGame();
    } else if (pressed >= 2 && pressed <= 5) {
      // map pins 2..5 → led numbers 0..3
      byte btn = static_cast<byte>(pressed - 2);
      checkGame(btn);
    }
  }
  
  // --- Handle timer tick ---
  if (newTimerInterrupt) {
    newTimerInterrupt = false;

    // Pick new LED, store to sequence, light it
    byte rnd = random(0, 4);
    ledSequence[sequenceLength++] = rnd;
    setLed(rnd);

    expectedIndex = 0; // restart remembering from beginning
  }
}

// --- Check if player's button is correct ---
void checkGame(byte btn)
{
  if (btn == ledSequence[expectedIndex]) {
    expectedIndex++;
    score++;
    // showResult(score);

    // Finished current sequence, wait for timer to extend it
    if (expectedIndex >= sequenceLength) {
      expectedIndex = 0;
    }
  } else {
    // Wrong button → game over
    setAllLeds();
    delay(1000);
    clearAllLeds();
    stopTimer();  // use timer module instead of clearing registers
  }
}

void initializeGame()
{
  sequenceLength = 0;
  score = 0;
  expectedIndex = 0;
  clearAllLeds();
  // showResult(0);
}

void startTheGame()
{
  initializeGame();
  resetTickCount();  // reset ticks for fairness
  startTimer();      // start timer using module
}
