#include "OXOcardRunner.h"

void setup() {
  clearDisplay();
}

void loop() {
  byte x = random(8);
  byte y = random(8);
  byte b = random(255);
  drawPixel(x,y,b);
}
