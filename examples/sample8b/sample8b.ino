#include "OXOcardRunner.h"

void setup() {

}

void loop() {
  byte r = random(4);

  drawCircle(4,4,r);
  delay(100);
  drawCircle(4,4,r,0);
}

