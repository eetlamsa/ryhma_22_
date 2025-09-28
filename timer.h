#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

extern volatile bool newTimerInterrupt;

void initializeTimer(void);

void startTimer(void);

void stopTimer(void);

#endif
