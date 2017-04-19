#include "OXOcardRunner.h"

void setup() {
}

void loop() {
  int x = getXAcceleration();

  if (x > 50) {
    drawLine(0, 0, 0, 7);
  }

  if (x < -50) {
    drawLine(7, 0, 7, 7);
  }

  delay(100);
  clearDisplay();
}
