#include "OXOCardRunner.h"

void setup() {
  clearDisplay();
}

void loop() {

  drawCircle(1,1,1,20);
  drawRectangle(4,0,3,3,50);
  drawPixel(1,5,255);
  drawTriangle(7,3,7,7,2,7,100);

  delay(1000);

  clearDisplay();

  delay(1000);
}
