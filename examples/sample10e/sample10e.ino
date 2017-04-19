#include "OXOcardRunner.h"

void setup() {
}

void loop() {
  int y = getYAcceleration();

  if (y > 50) {
      drawLine(0,7,7,7);
  }
  
  if (y < -50) {
      drawLine(0,0,7,0);
  }

  delay(100);
  clearDisplay();
}
