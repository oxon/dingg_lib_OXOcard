#include "OXOcardRunner.h"

void setup() {

}

void loop() {
  byte o = getOrientation();
  if (o == 1) {
    drawImage(0b00000000,
              0b01101100,
              0b00000000,
              0b00000000,
              0b01000100,
              0b00111000,
              0b00000000,
              0b00000000);
  }
  else if (o == 4) {
    drawImage(0b00000000,
              0b11101110,
              0b10101010,
              0b00000000,
              0b01000100,
              0b00111000,
              0b00000000,
              0b00000000);
  }
  else {
    clearDisplay();
  }
}

