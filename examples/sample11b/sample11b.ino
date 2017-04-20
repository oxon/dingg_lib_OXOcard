#include "OXOcardRunner.h"

void setup() {
}

void loop() {
  if (findIBeacon(1)) {

    drawImage(  0b01100110,
                0b11111111,
                0b11111111,
                0b11111111,
                0b01111110,
                0b00111100,
                0b00011000,
                0b00001000);
    delay(1000);
  } else {
    drawImage(  0b01100110,
                0b11111111,
                0b11111111,
                0b11111111,
                0b01111110,
                0b00111100,
                0b00011000,
                0b00001000,
                20);
  }
}

