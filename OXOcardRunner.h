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
volatile bool serialOn = false;
volatile unsigned long millisSinceLastReset = 0;

/* Object instantiations -------------------------------------- */
OXOcard globalOXOcard;

/* hook function from Arduino to allow 3rd party variant-specific initialization */
void initVariant() {
  globalOXOcard.begin();
}

/* System functions ------------------------------------------- */
void turnOff(bool leftButton = false, bool middleButton = false, bool rightButton = false) {
   globalOXOcard.turnOff(leftButton, middleButton, rightButton);
}

/* ------------------------------------- */
void handleAutoTurnOff(unsigned int seconds = DEFAULT_AUTO_TURN_OFF) {
  globalOXOcard.handleAutoTurnOff(seconds);
}

void resetOXOcard() {
  ((void (*)())0x0)();  // jumpt to address 0x0
}

/* ------------------------------------- */
bool isLeftButtonPressed() {
  return globalOXOcard.isLeftButtonPressed();
}

/* ------------------------------------- */
bool isMiddleButtonPressed() {
  return globalOXOcard.isMiddleButtonPressed();
}

/* ------------------------------------- */
bool isRightButtonPressed() {
  return globalOXOcard.isRightButtonPressed();
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
void drawLine(byte x0, byte y0, byte x1, byte y1, byte b=255) {
  globalOXOcard.matrix->drawLine(x0,y0,x1,y1,b);
};

/* ------------------------------------- */
void drawCircle(byte x0, byte y0, byte r, byte b=255) {
  globalOXOcard.matrix->drawCircle(x0,y0,r,b);
};

/* ------------------------------------- */
void drawFilledCircle(byte x0, byte y0, byte r, byte b=255) {
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
  for (byte y = 0; y <= 7; y++) {
    byte b = image[y];
    for (byte x = 0; x <= 7; x++) {
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
  drawImage(image,brightness);
}

/* ------------------------------------- */
void drawChar(byte x, byte y, char c, byte brightness=255) {
  globalOXOcard.matrix->drawChar(x,y,c,brightness);
}

/* ------------------------------------- */
void drawDigit(byte x, byte y, byte digit, byte brightness=255) {
  drawChar(x,y,48+(digit%10),brightness);
}

/* ------------------------------------- */
void drawNumber(byte number, byte brightness=255) {
  if (number > 99) {
    drawChar(0,1,'?',brightness);
    drawChar(5,1,'?',brightness);
  } else {
    drawChar(0,1,48+(number/10),brightness);
    drawChar(5,1,48+(number%10),brightness);
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

/* ------------------------------------- */
bool isOrientationUp() {
  return byte(globalOXOcard.accel->getOrientation()) == MMA7660FC::UP;
}

bool isOrientationDown() {
  return byte(globalOXOcard.accel->getOrientation()) == MMA7660FC::DOWN;
}

bool isOrientationHorizontally() {
  return byte(globalOXOcard.accel->getOrientation()) == MMA7660FC::HORIZONTALLY;
}

bool isOrientationVertically() {
  return byte(globalOXOcard.accel->getOrientation()) == MMA7660FC::VERTICALLY;
}

/* BLE functions ---------------------------------------------- */
void setupAsIBeacon(String beaconName, HM11::advertInterval_t interv = HM11::INTERV_550MS) {      // max. 20 characters
  globalOXOcard.setupAsIBeacon(beaconName, interv);
}

void setupAsIBeacon(unsigned int beaconNr, HM11::advertInterval_t interv = HM11::INTERV_550MS) {  // 1... 65'534 (0xFFFE)
  globalOXOcard.setupAsIBeacon(beaconNr, interv);
}

/* ------------------------------------- */
int findIBeacon(String beaconName) {
  return globalOXOcard.findIBeacon(beaconName);
}

int findIBeacon(unsigned int beaconNr) {
  return globalOXOcard.findIBeacon(beaconNr);
}

/* ------------------------------------- */
void setBluetoothTxPower(byte txPower) {    // 0 = -23dbm, 1 = -6dbm, 2 = 0dbm, 3 = 6dbm
  globalOXOcard.ble->setTxPower(HM11::txPower_t(txPower));
}

byte getBluetoothTxPower() {                // 0 = -23dbm, 1 = -6dbm, 2 = 0dbm, 3 = 6dbm
  return byte(globalOXOcard.ble->getTxPower());
}

/* ------------------------------------- */
String getBluetoothMacAddress() {
  return globalOXOcard.ble->getMacAddress();
}

void connectToBluetoothMacAddress(String macAddr, bool master) {
  globalOXOcard.ble->connectToMacAddress(macAddr, master);
  setLEDBlue(HIGH);
}

void bluetoothWrite(byte b) {
  globalOXOcard.bleSerial->write(b);
}

void bluetoothPrint(char c) {
  globalOXOcard.bleSerial->print(c);
}

void bluetoothPrintln(char c) {
  globalOXOcard.bleSerial->println(c);
}

void bluetoothPrint(String str) {
  for (byte i = 0; i < str.length(); i++) {
    globalOXOcard.bleSerial->print(str[i]);
  }
}

void bluetoothPrintln(String str) {
  for (byte i = 0; i < str.length()-1; i++) {
    globalOXOcard.bleSerial->print(str[i]);
  }
  globalOXOcard.bleSerial->println(str[str.length()-1]);
}

byte bluetoothRead() {
  return globalOXOcard.bleSerial->read();
}

char bluetoothReadChar() {
  return globalOXOcard.ble->readChar();
}

byte bluetoothAvailable() {
  return globalOXOcard.bleSerial->available();
}

void bluetoothHandshaking(bool master) {
  if (!(globalOXOcard.ble->handshaking(master))) resetOXOcard();
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
    tone(tones[i]);
    delay(lengths[i]);
    noTone();
    delay(pause);
  }
}

void resetTimer() {
  millisSinceLastReset = millis();
}

int getTimerSeconds() {
  return (millis() - millisSinceLastReset) / 1000;
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
void print(unsigned char c, int x = DEC) {
  checkIfSerialOn();
  Serial.print(c,x);
}
void print(int i, int x = DEC) {
  checkIfSerialOn();
  Serial.print(i,x);
}
void print(unsigned int i, int x = DEC) {
  checkIfSerialOn();
  Serial.print(i,x);
}
void print(long l, int x = DEC) {
  checkIfSerialOn();
  Serial.print(l,x);
}
void print(unsigned long l, int x = DEC) {
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
void println(unsigned char c, int x = DEC) {
  checkIfSerialOn();
  Serial.println(c,x);
}
void println(int i, int x = DEC) {
  checkIfSerialOn();
  Serial.println(i,x);
}
void println(unsigned int i, int x = DEC) {
  checkIfSerialOn();
  Serial.println(i,x);
}
void println(long l, int x = DEC) {
  checkIfSerialOn();
  Serial.println(l,x);
}
void println(unsigned long l, int x = DEC) {
  checkIfSerialOn();
  Serial.println(l,x);
}

#endif
