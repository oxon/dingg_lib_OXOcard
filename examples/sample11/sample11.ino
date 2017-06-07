#include "OXOcardRunner.h"

void setup() {
  setupAsIBeacon(1);
  clearDisplay();
  drawNumber(1);
}

void loop() {
  handleAutoTurnOff(30);
}

