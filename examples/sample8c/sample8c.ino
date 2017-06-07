#include "OXOcardRunner.h"

void setup() {

}

void loop() {
  byte x = random(8);
  byte y = random(8);
  byte b = random(255);
  drawPixel(x,y,b);
}

