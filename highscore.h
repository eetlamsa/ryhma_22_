#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <Arduino.h>
#include <EEPROM.h>

// Number of scores to keep
#define MAX_SCORES 10

// Initialize the high score system (loads from EEPROM)
void initializeHighScores(void);

// Returns the i-th high score (0 = best, 9 = worst)
uint8_t getHighScore(uint8_t index);

// Attempts to save a new high score
void saveHighScore(uint16_t newScore);

// For debugging or clearing EEPROM
void resetHighScores(void);

#endif