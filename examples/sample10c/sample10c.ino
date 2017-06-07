#include "OXOcardRunner.h"

void setup() {

}

void loop() {
  int x = getXAcceleration();

  print("x = ");
  println(x);

  delay(200);  
}

