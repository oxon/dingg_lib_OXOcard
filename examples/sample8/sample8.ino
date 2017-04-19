#include "OXOcardRunner.h"

void setup() {
  clearDisplay();
}

void loop() {
  byte a = random(99);
  drawNumber(a);
  delay(500);
}
