#include "OXOcardRunner.h"

void setup() {

}

void loop() {
  clearDisplay();
  drawImage(0b00000000,
            0b00101000,
            0b00101000,
            0b00000000,
            0b01000100,
            0b00111000,
            0b00000000,
            0b00000000);
  delay(1000);

  clearDisplay();
  drawImage(0b00000000,
            0b00101100,
            0b00100000,
            0b00000000,
            0b00000100,
            0b00111000,
            0b00000000,
            0b00000000);
  delay(1000);
}

