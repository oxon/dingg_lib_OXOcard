#include "OXOcardRunner.h"

void setup() {
  clearDisplay();
}

byte ship_x = 0;
byte ship_y = 7;
byte meteor_x = 0;
byte meteor_y = 0;
bool stopped = true;
byte loop_counter = 0;

void loop() {
  handleAutoTurnOff(120);

  if (stopped) {
    if (isMiddleButtonPressed()) {
      stopped = false;
      resetTimer();
    } else {
      resetTimer();
      drawIntro();
      return;
    }
  }

  clearDisplay();
  drawPixel(meteor_x, meteor_y, 80);
  drawPixel(ship_x, ship_y);
  drawPixel(ship_x + 1, ship_y);

  if ((ship_x == meteor_x || ship_x + 1 == meteor_x)
      && ship_y == meteor_y) {

    noTone();
    drawGameOver();

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

  if (loop_counter < 10) {
    loop_counter = loop_counter + 1;
  } else {
    loop_counter = 0;
    tone(1000, 50);
  }

  int seconds = getTimerSeconds();
  if (seconds < 5) {
    delay(50);
  } else if (seconds < 10) {
    delay(40);
  } else {
    delay(30);
  }

}

void drawIntro() {
  clearDisplay();
  drawImage(0b11100111,
            0b10000101,
            0b10100101,
            0b11100111,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000);
  delay(300);
  clearDisplay();
  drawImage(0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b01111110,
            0b00111100,
            0b00011000,
            80);
   delay(300);
}

void drawGameOver() {
  for (int i = 0;i<1000;i++) {
     byte x = random(8);
     byte y = random(4);
     byte b = random(255);
     drawPixel(x,4+y,b);
     tone(random(200));
  }
  noTone();
}

