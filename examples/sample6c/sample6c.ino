#include "OXOcardRunner.h"

void setup() {
  clearDisplay();
}

void loop() {

  drawCircle(1,1,1,20);
  drawRectangle(4,0,3,3,50);
  drawPixel(1,5,255);
  drawTriangle(7,3,7,7,2,7,100);

  delay(1000);

  drawRectangle(4,0,3,3,0);
  drawPixel(1,5,0);

  delay(1000);

}
