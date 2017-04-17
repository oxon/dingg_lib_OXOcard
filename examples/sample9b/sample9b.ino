#include "OXOCardRunner.h"

void setup() {

  for (int i = 0; i<4000;i++) {
    tone(i);  
  }
  for (int i = 4000; i>0;i--) {
    tone(i);  
  }
  noTone();
}

void loop() {
}
