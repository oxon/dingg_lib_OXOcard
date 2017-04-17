#include "OXOCardRunner.h"

void setup() {
  clearDisplay();
}

byte a;
byte b;

void loop() {
  a = 5;
  b = 10;

  drawNumber(5+a*b/2);
}
