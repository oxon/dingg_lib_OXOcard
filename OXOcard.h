#ifndef _OXOCARD_H_
#define _OXOCARD_H_
/*******************************************************************************
* \file    OXOcard.h
********************************************************************************
* \author  Jascha Haldemann jh@oxon.ch
* \author  Thomas Garaio tg@oxon.ch
* \date    01.02.2017
* \version 1.0
*
* \brief   The OXOcard is a board to learn programming with Arduino
*
********************************************************************************
* OXOcard
*******************************************************************************/

/* ============================== Global imports ============================ */
#include <Arduino.h>
#include <avr/sleep.h>
#include <Wire.h>
#include <MMA7660FC.h>
#include <IS31FL3731.h>
#include <SoftwareSerial0.h>
#include <HM11_SoftwareSerial0.h>
#include "globals.h"
#include "pitches.h"

/* ==================== Global module constant declaration ================== */
// #define DEBUG_OXOCARD                     // define to activate Debug prints
#define DEBUG_BAUDRATE_OXOCARD    115200

#define DEFAULT_AUTO_TURN_OFF     120     // in seconds

#define BAUDRATE_BLE              9600    // in baud
#define BLE_NAME                  F("OXOcard")
#define BLE_DEFAULT_UUID          F("4F584F63617264111111111111111111")  // "OXOcard"
#define BLE_DEFAULT_MARJOR        4

/* ========================= Global macro declaration ======================= */

/* ============================ Class declaration =========================== */
class OXOcard
{
public:
  /* Public member data */
  MMA7660FC *accel;
  IS31FL3731 *matrix;
  SoftwareSerial0 *bleSerial;
  HM11_SoftwareSerial0 *ble;

  /* Constructor(s) and  Destructor */
  OXOcard() {};
  ~OXOcard() {};

  /* Public member functions */
  void begin();
  void turnOff(bool leftButton = false, bool middleButton = false, bool rightButton = false);
  void handleAutoTurnOff(uint16_t seconds = DEFAULT_AUTO_TURN_OFF, bool leftButton = false, bool middleButton = false, bool rightButton = false);
  void resetAutoTurnOffCounter();
  bool isLeftButtonPressed();
  bool isMiddleButtonPressed();
  bool isRightButtonPressed();

  void setupAsIBeacon(String beaconName, HM11::advertInterval_t interv = HM11::INTERV_550MS);
  void setupAsIBeacon(uint16_t beaconNr, HM11::advertInterval_t interv = HM11::INTERV_550MS);
  int16_t findIBeacon(String beaconName);
  int16_t findIBeacon(uint16_t beaconNr);

private:
  /* Private member functions */
  void initPins();
  void disableUnusedCpuFunctions();
  void initTimerIRQ(uint8_t timerNr, uint16_t prescaler, uint16_t divisor);
  inline bool getLEDBlue() {return !getBit(PIN_LED_BLUE, LED_BLUE);}

  /* Private class functions (static) */
  static void iBeaconNameToIBeaconUUID(String beaconName, HM11::iBeaconData_t *iBeacon);
};

#endif
