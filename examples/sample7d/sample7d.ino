#include "OXOcardRunner.h"

void setup() {

}

byte a;

void loop() {
  drawPixel(3,a);
  delay(50);
  clearPixel(3,a);

  if (a < 7) {
    a = a + 1;
  }
  else {
    a = 0;
  }
}

