/**-----------------------------------------------------------------------------
 * \file    OXOcardRunner.h
 * \author  jh, tg
 * \date    xx.02.2017
 *
 * \version 1.0
 *
 * \brief   The OXOcardRunner is a set of simplified functions for
 *          programming the OXOcard
 *
 * @{
 -----------------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -----------------------*/
#ifndef OXOCARD_RUNNER_H_
#define OXOCARD_RUNNER_H_

/* Includes --------------------------------------------------- */
#include "OXOcard.h"

/* global variables ------------------------------------------- */
uint16_t autoTurnOffAfter = -1;
volatile uint16_t autoTurnOffCnt = 0;
volatile bool goingToTurnOff = false;
volatile bool serialOn = false;
volatile int secondsSinceLastReset = 0;

enum orientation : byte {UNKNOWN = 0, UP = 1, DOWN = 2, HORIZONTALLY = 3, VERTICALLY = 4};

/* Object instantiations -------------------------------------- */
OXOcard globalOXOcard;

/* System functions ------------------------------------------- */
void initVariant() {      // hook function from Arduino to allow 3rd party variant-specific initialization
  globalOXOcard.begin();
}

/* ------------------------------------- */
void turnOff() {
   globalOXOcard.turnOff();
}

/* ------------------------------------- */
void handleAutoTurnOff(uint16_t seconds = DEFAULT_AUTO_TURN_OFF)
{
  if (seconds < autoTurnOffAfter)
  {
    /* counter has been changed -> reset the interrupt counter */
    autoTurnOffCnt = 0;
  }
  autoTurnOffAfter = seconds;

  if (goingToTurnOff)
  {
    goingToTurnOff = false;
    globalOXOcard.turnOff();
  }
}

/* ------------------------------------- */
bool isLeftButtonPressed() {
  bool pressed = false;
  if (button1Pressed)
  {
    autoTurnOffCnt = 0; // prevent autoturnoff after an action
    pressed = true;
  }
  return pressed;
}

/* ------------------------------------- */
bool isMiddleButtonPressed() {
  bool pressed = false;
  if (button2Pressed)
  {
    autoTurnOffCnt = 0; // prevent autoturnoff after an action
    pressed = true;
  }
  return pressed;
}

/* ------------------------------------- */
bool isRightButtonPressed() {
  bool pressed = false;
  if (button3Pressed)
  {
    autoTurnOffCnt = 0; // prevent autoturnoff after an action
    pressed = true;
  }
  return pressed;
}

/* LED-Matrix functions --------------------------------------- */
void clearDisplay() {
   globalOXOcard.matrix->fillScreen(0);
}

/* ------------------------------------- */
void turnDisplayOn() {
  globalOXOcard.matrix->fillScreen(255);
}

/* ------------------------------------- */
void fillDisplay(byte brightness=255) {
  globalOXOcard.matrix->fillScreen(brightness);
}

/* ------------------------------------- */
void drawPixel(byte x, byte y, byte brightness=255) {
  globalOXOcard.matrix->drawPixel(x,y,brightness);
}

/* ------------------------------------- */
void drawRectangle(byte x, byte y, byte l, byte h, byte b=255) {
  globalOXOcard.matrix->drawRectangle(x,y,l,h,b);
};

/* ------------------------------------- */
void drawFilledRectangle(byte x, byte y, byte l, byte h, byte b=255) {
  globalOXOcard.matrix->drawFilledRectangle(x,y,l,h,b);
};

/* ------------------------------------- */
void drawLine(byte x0, byte y0, byte x1, byte y1, byte b=255)
{
  globalOXOcard.matrix->drawLine(x0,y0,x1,y1,b);
};

/* ------------------------------------- */
void drawCircle(byte x0, byte y0, byte r, byte b=255)
{
  globalOXOcard.matrix->drawCircle(x0,y0,r,b);
};

/* ------------------------------------- */
void drawFilledCircle(byte x0, byte y0, byte r, byte b=255)
{
  globalOXOcard.matrix->drawFilledCircle(x0,y0,r,b);
};

/* ------------------------------------- */
void drawTriangle(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, byte b=255) {
  globalOXOcard.matrix->drawTriangle(x0,y0,x1,y1,x2,y2,b);
}

/* ------------------------------------- */
void drawFilledTriangle(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, byte b=255) {
  globalOXOcard.matrix->drawFilledTriangle(x0,y0,x1,y1,x2,y2,b);
}

/* ------------------------------------- */
void drawImage(byte image[8], byte brightness=255) {
  for (byte y =0;y<=7;y++) {
    byte b = image[y];
    for (byte x = 0;x<=7;x++) {
      if (b & (1 << (7-x))) {

        globalOXOcard.matrix->drawPixel(x,y,brightness);
      }
    }
  }
}

/* ------------------------------------- */
void drawImage(byte b0,
               byte b1,
               byte b2,
               byte b3,
               byte b4,
               byte b5,
               byte b6,
               byte b7,
               byte brightness=255) {

  byte image[8] = {b0,b1,b2,b3,b4,b5,b6,b7};
  drawImage(image, brightness);
};

/* ------------------------------------- */
void drawChar(byte x, byte y, char c, byte brightness=255) {
  globalOXOcard.matrix->drawChar(x, y,  c, brightness);
}

/* ------------------------------------- */
void drawDigit(byte x, byte y, byte digit, byte brightness=255) {
  drawChar(x,y,48 + (digit%10), brightness);
}

/* ------------------------------------- */
void drawNumber(byte number, byte brightness=255) {
  if (number > 99) {
    drawChar(0,1,'?');
    drawChar(5,1,'?');
  }
  else
  {
    drawChar(0,1,48 + (number/10));
    drawChar(5,1,48 + (number%10));
  }
}

/* Accelerometer functions ------------------------------------ */
int getXAcceleration() {
  float vector[3];
  globalOXOcard.accel->getAccelerationVector(vector);
  return vector[0]*255;
}

/* ------------------------------------- */
int getYAcceleration() {
  float vector[3];
  globalOXOcard.accel->getAccelerationVector(vector);
  return vector[1]*255;
}

/* ------------------------------------- */
int getZAcceleration() {
  float vector[3];
  globalOXOcard.accel->getAccelerationVector(vector);
  return vector[2]*255;
}

/* ------------------------------------- */
byte getOrientation() {
  return byte(globalOXOcard.accel->getOrientation());    // 1 = UP, 2 = DOWN, 3 = HORIZONTALLY, 4 = VERTICALLY
}

// String getOrientation() {
//   String orientation;
//   switch(byte(globalOXOcard.accel->getOrientation()))
//   {
//     case UP:           orientation = "UP";           break;
//     case DOWN:         orientation = "DOWN";         break;
//     case HORIZONTALLY: orientation = "HORIZONTALLY"; break;
//     case VERTICALLY:   orientation = "VERTICALLY";   break;
//     default:           orientation = "UNKNOWN";      break;
//   };
//   return orientation;
// }

/* ------------------------------------- */
bool isOrientationUp() {
  return byte(globalOXOcard.accel->getOrientation()) == UP;
}

bool isOrientationDown() {
  return byte(globalOXOcard.accel->getOrientation()) == DOWN;
}

bool isOrientationHorizontally() {
  return byte(globalOXOcard.accel->getOrientation()) == HORIZONTALLY;
}

bool isOrientationVertically() {
  return byte(globalOXOcard.accel->getOrientation()) == VERTICALLY;
}

/* BLE functions ---------------------------------------------- */
void setupAsIBeacon(String beaconName) {    // max. 20 characters
  globalOXOcard.setupAsIBeacon(beaconName);
}
void setupAsIBeacon(uint16_t beaconNr) {    // 1... 65'534 (0xFFFE)
  globalOXOcard.setupAsIBeacon(beaconNr);
}

/* ------------------------------------- */
int findIBeacon(String beaconName) {
  return globalOXOcard.findIBeacon(beaconName);
}

int findIBeacon(uint16_t beaconNr) {
  return globalOXOcard.findIBeacon(beaconNr);
}

/* Tone functions --------------------------------------------- */
void tone(int frequency, int duration = 0) {
  if (frequency < 0) return;
  tone(PIN_NR_PIEZO, (unsigned int)(frequency), (unsigned long)(duration));
}

void noTone() {
  noTone(PIN_NR_PIEZO);
}

void playMelody(int tones[], int lengths[], int size, int pause = 100) {
  for (int i = 0;i<size;i++) {
    tone(tones[i],lengths);
    delay(lengths[i]);
    noTone();
    delay(pause);
  }
}

void resetTimer() {
  secondsSinceLastReset = millis();
}

int getTimerSeconds() {
  return (millis() - secondsSinceLastReset) / 1000;
}

void checkIfSerialOn() {
  if (!serialOn) {
    Serial.begin(DEBUG_BAUDRATE_OXOCARD);
    serialOn = true;
  }
}

void print(const String &s) {
  checkIfSerialOn();
  Serial.print(s);
}
void print(const char chrs[] ) {
  checkIfSerialOn();
  Serial.print(chrs);
}
void print(char c) {
  checkIfSerialOn();
  Serial.print(c);
}
void print(unsigned char c, int x = DEC){
  checkIfSerialOn();
  Serial.print(c,x);
}
void print(int i, int x = DEC){
  checkIfSerialOn();
  Serial.print(i,x);
}
void print(unsigned int i, int x = DEC){
  checkIfSerialOn();
  Serial.print(i,x);
}
void print(long l, int x = DEC){
  checkIfSerialOn();
  Serial.print(l,x);
}
void print(unsigned long l, int x = DEC){
  checkIfSerialOn();
  Serial.print(l,x);
}

void println(const String &s) {
  checkIfSerialOn();
  Serial.println(s);
}
void println(const char chrs[] ) {
  checkIfSerialOn();
  Serial.println(chrs);
}
void println(char c) {
  checkIfSerialOn();
  Serial.println(c);
}
void println(unsigned char c, int x = DEC){
  checkIfSerialOn();
  Serial.println(c,x);
}
void println(int i, int x = DEC){
  checkIfSerialOn();
  Serial.println(i,x);
}
void println(unsigned int i, int x = DEC){
  checkIfSerialOn();
  Serial.println(i,x);
}
void println(long l, int x = DEC){
  checkIfSerialOn();
  Serial.println(l,x);
}
void println(unsigned long l, int x = DEC){
  checkIfSerialOn();
  Serial.println(l,x);
}

/* Interrupts ------------------------------------------------- */
/** ===========================================================
 * \fn      ISR (timer1 OCIE1A interrupt TIMER1_COMPA)
 * \brief   interrupt service routine (handler) which will be
 *          called from time to time
 *          (f_isr = fcpu / (prescaler * frequency_divisor))
 *
 * \param   'TIMER1_COMPA vector'
 * \return  -
 ============================================================== */
ISR (TIMER1_COMPA_vect)
{
  autoTurnOffCnt++;
  if (autoTurnOffCnt >= autoTurnOffAfter)
  {
    autoTurnOffCnt = 0;
    goingToTurnOff = true;
  }
}

#endif
