#include "OXOCardRunner.h"

void setup() {
  clearDisplay();
}

byte ship_x = 0;
byte ship_y = 7;
byte meteor_x = 0;
byte meteor_y = 0;
bool stopped = false;

void loop() {
  handleAutoTurnOff(120);

  if (stopped) {
    if (isMiddleButtonPressed()) {
      stopped = false;
    } else {
      
      return;
    }
  }

  clearDisplay();
  drawPixel(meteor_x, meteor_y, 80);
  drawPixel(ship_x, ship_y);
  drawPixel(ship_x + 1, ship_y);

  if ((ship_x == meteor_x || ship_x + 1 == meteor_x) 
      && ship_y == meteor_y) {

    drawRectangle(0, 0, 8, 8, 255);
    tone(100, 1000);
    ship_x = 0;
    ship_y = 7;
    stopped = true;
  }

  if (isLeftButtonPressed()) {
    if (ship_x > 0) {
      ship_x = ship_x - 1;
    } else {
      ship_x = 0 ;
    }
  }

  if (isRightButtonPressed()) {
    if (ship_x < 6) {
      ship_x = ship_x + 1;
    } else {
      ship_x = 6;
    }
  }
  meteor_y = meteor_y + 1;

  if (meteor_y > 7) {
    meteor_x = random(8);
    meteor_y = 0;
  }

  
  delay(50);
}
