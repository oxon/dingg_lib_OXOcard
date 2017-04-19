#include "OXOCardRunner.h"

void setup() {
  clearDisplay();
}

byte a;

void loop() {
  drawPixel(3,a);
  delay(50);
  drawPixel(3,a,0);

  if (a < 7) {
    a = a + 1;
  }
  else {
    a = 0;
  }
}
