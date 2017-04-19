#include "OXOCardRunner.h"

void setup() {
}

void loop() {

  byte o = getOrientation();
  if (o) {
    drawNumber(o);
  }
  
}
