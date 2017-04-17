#include "OXOCardRunner.h"

void setup() {
  clearDisplay();
}

void loop() {
  byte r = random(4);

  drawCircle(4,4,r);
  delay(100);
  drawCircle(4,4,r,0);
}
