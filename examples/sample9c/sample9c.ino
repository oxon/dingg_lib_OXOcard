#include "OXOcardRunner.h"

void setup() {

  int melody[] = { NOTE_C5, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, 0, NOTE_B4, NOTE_C5 };
  int durations[] = { 250, 125, 125, 250, 250, 250, 250, 250 };

  playMelody(melody, durations, 8);
}

void loop() {
}
