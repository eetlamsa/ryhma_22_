#include "highscore.h"
#include "display.h"
#include <EEPROM.h>

static uint8_t highScores[MAX_SCORES];

static void sortScoresDescending(void) {
  for (uint8_t i = 0; i < MAX_SCORES - 1; i++) {
    for (uint8_t j = i + 1; j < MAX_SCORES; j++) {
      if (highScores[j] > highScores[i]) {
        uint8_t temp = highScores[i];
        highScores[i] = highScores[j];
        highScores[j] = temp;
      }
    }
  }
}

static void saveScoresToEEPROM(void) {
  for (uint8_t i = 0; i < MAX_SCORES; i++) {
    EEPROM.update(i, highScores[i]);
  }
}

// Lataa olemassa olevat tulokset EEPROM:sta
void initializeHighScores(void) {
  for (uint8_t i = 0; i < MAX_SCORES; i++) {
    uint8_t value = EEPROM.read(i);
    if (value <= 99) {
      highScores[i] = value;
    } else {
      highScores[i] = 0; // mitätön tulos -> nollaa
    }
  }
  sortScoresDescending();
}

// Palauttaa pistelistan i. arvon (jos indeksi on virheellinen → palauttaa 0)
uint8_t getHighScore(uint8_t index) {
  if (index < MAX_SCORES) {
    return highScores[index];
  } else {
    return 0;
  }
}

// Tsekkaa onko tulos top 10:ssä ja lisätään, jos on
void saveHighScore(uint16_t newScore) {
  uint8_t score = (newScore > 99) ? 99 : newScore;
  bool updated = false;

  for (uint8_t i = 0; i < MAX_SCORES; i++) {
    if (score > highScores[i]) {
      // Siirrä alempana olevia tuloksia alemmas
      for (int8_t j = MAX_SCORES - 1; j > i; j--) {
        highScores[j] = highScores[j - 1];
      }
      highScores[i] = score;
      updated = true;
      break;
    }
  }

  if (updated) {
    saveScoresToEEPROM();
  }
}

// Tällä saa tyhjättyä parhaat tulokset, jos sille tarvetta testauksien yhteydessä
void resetHighScores(void) {
  for (uint8_t i = 0; i < MAX_SCORES; i++) {
    highScores[i] = 0;
    EEPROM.update(i, 0);
  }
}