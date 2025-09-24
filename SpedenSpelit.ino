#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler

// game state variables
int score = 0;
int expectedIndex = 0;  // where we are in ledSequence


void setup()
{
  initializeLeds();
  initButtonsAndButtonInterrupts();
  //initializeDisplay();
  initializeTimer();
  sei(); // enable interrupts
}

void loop()
{
  // button pressed?
  if (buttonNumber >= 0) {
    int pressed = buttonNumber;
    buttonNumber = -1;

    if (pressed == 6) { // start button
      startTheGame();
    } else if (pressed >= 2 && pressed <= 5) {
      // map pins 2..5 -> led numbers 0..3
      byte btn = pressed - 2;
      checkGame(btn);
    }
  }
  
  // timer ticked?
  if (newTimerInterrupt) {
    newTimerInterrupt = false;

    // pick new led, store to sequence, light it
    byte rnd = random(0, 4);
    ledSequence[sequenceLength++] = rnd;
    setLed(rnd);

    expectedIndex = 0; // restart remembering from beginning
  }
}

// initialize Timer1 to 1 Hz but disabled at start
void initializeTimer(void)
{
  TCCR1A = 0; // normal mode
  TCCR1B = 0;
  OCR1A = 15624;  // (16e6 / 1024) - 1 = 1 Hz
  TCCR1B |= (1 << WGM12);  // CTC mode
  TIMSK1 |= (1 << OCIE1A); // enable compare interrupt
  // no prescaler yet, will start in startTheGame()
}

ISR(TIMER1_COMPA_vect)
{
  static int tickCount = 0;
  tickCount++;
  newTimerInterrupt = true;
}

// check if player's button is correct
void checkGame(byte btn)
{
  if (btn == ledSequence[expectedIndex]) {
    expectedIndex++;
    score++;
    // showResult(score);

    // finished current sequence, wait for timer to add new one
    if (expectedIndex >= sequenceLength) {
      expectedIndex = 0;
    }
  } else {
    // wrong button → game over
    setAllLeds();
    delay(1000);
    clearAllLeds();
    TIMSK1 &= ~(1 << OCIE1A); // disable timer
  }
}

void initializeGame()
{
  sequenceLength = 0;
  score = 0;
  expectedIndex = 0;
  clearAllLeds();
  //showResult(0);
}

void startTheGame()
{
  initializeGame();
  TCNT1 = 0;
  TCCR1B |= (1 << CS12) | (1 << CS10); // start timer with 1024 prescaler
}

