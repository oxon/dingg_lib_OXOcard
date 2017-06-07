#include "OXOcardRunner.h"

byte ship_x = 0;
byte ship_y = 7;
byte meteor_x = 0;
byte meteor_y = 0;
bool stopped = true;
byte loop_counter = 0;
byte level = 1;
byte old_level = 0;

void setup() {
  clearDisplay();
}

// *************************************

byte accel_value = 50;

byte levels[] = {  5, 100,
                   10, 80,
                   15, 60,
                   20, 40
                };

void backgroundTicker() {
  tone(1000, 50);
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
 for (int i = 0; i < 1000; i++) {
    byte x = random(8);
    byte y = random(4);
    byte b = random(255);
    drawPixel(x, 4 + y, b);
    tone(random(200));
  }
  noTone();

  clearDisplay();
  drawNumber(level);
  delay(1000);
}

void drawLevel() {
  clearDisplay();
  drawNumber(level);

  tone(NOTE_A5, 100);
  delay(200);
  tone(NOTE_B5, 100);
  delay(200);
  tone(NOTE_C6, 100);

  delay(1000);
}

void onMoveUp() {
  if (ship_y >0) ship_y--;
}

void onMoveDown() {
  if (ship_y <7) ship_y++;
}

void onMoveLeft() {
  if (ship_x >0) ship_x--;
}

void onMoveRight() {
  if (ship_x <6) ship_x++;
}

void drawScene() {
  clearDisplay();
  drawPixel(meteor_x, meteor_y, 80);
  drawPixel(ship_x, ship_y);
  drawPixel(ship_x + 1, ship_y);
}

// *************************************

void newMeteor() {
  meteor_x = random(8);
  meteor_y = 0;
}

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

  drawScene();

  int ay = getYAcceleration(); 
  if (ay < -accel_value) onMoveUp();
  if (ay > accel_value) onMoveDown();

  int ax = getXAcceleration();  
  if (ax > accel_value) onMoveLeft();
  if (ax < -accel_value) onMoveRight();

  if ((ship_x == meteor_x || ship_x + 1 == meteor_x)
      && ship_y == meteor_y) {

    noTone();
    drawGameOver();

    ship_x = 0;
    ship_y = 7;
    stopped = true;
    level = 1;
    old_level = 0;
    newMeteor();
    return;
  }

  if (old_level != level) {
    drawLevel();
    newMeteor();
    old_level = level;
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
    newMeteor();
  }

  if (loop_counter < 10) {
    loop_counter = loop_counter + 1;
  } else {
    loop_counter = 0;
    backgroundTicker();
  }

  int seconds = getTimerSeconds();
  int i = 0;
  bool delayed = false;
  for (int i = 0; i < sizeof(levels) / 2; i++) {
    if (!delayed && seconds <= levels[i * 2]) {
      delay(levels[(i * 2) + 1]);
      delayed = true;
      level = i + 1;
    }
  }
  if (!delayed) {
    delay(levels[sizeof(levels) - 1]);
  }
}

