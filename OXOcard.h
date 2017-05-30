/**-----------------------------------------------------------------------------
 * \file    OXOcard.h
 * \author  jh, tg
 * \date    xx.02.2017
 *
 * \version 1.0
 *
 * \brief   The OXOcard is a board for kids to learn programming with Arduino
 *
 * @{
 -----------------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -----------------------*/
#ifndef OXOCARD_H_
#define OXOCARD_H_

/* Includes --------------------------------------------------- */
#include <Arduino.h>
#include <avr/sleep.h>
#include <Wire.h>
#include <SoftwareSerial0.h>
#include <MMA7660FC.h>
#include <IS31FL3731.h>
#include <HM11_SoftwareSerial0.h>
#include "globals.h"
#include "pitches.h"

/* Defines -----------------------------------------------------*/
// #define DEBUG_OXOCARD  // define to activate Debug prints
#define DEBUG_BAUDRATE_OXOCARD    115200

#define DEFAULT_AUTO_TURN_OFF     120           // in seconds

#define BAUDRATE_BLE              9600//19200   // in baud
#define BLE_NAME                  "OXOcard"
#define BLE_DEFAULT_UUID          "4F584F63617264111111111111111111"  // "OXOcard"
#define BLE_DEFAULT_MARJOR        4

/* Macros ----------------------------------------------------- */
#ifdef DEBUG_OXOCARD
  #define DebugOXOcard_print(...)     Serial.print(__VA_ARGS__)
  #define DebugOXOcard_println(...)   Serial.println(__VA_ARGS__)
  #define DebugOXOcard_begin(...)     Serial.begin(__VA_ARGS__)
#else
  #define DebugOXOcard_print(...)
  #define DebugOXOcard_println(...)
  #define DebugOXOcard_begin(...)
#endif

/* Class ------------------------------------------------------ */
class OXOcard
{
public:
  /* constructor(s) & deconstructor */
  OXOcard() {};
  ~OXOcard() {};

  /* public enumerations */
  //...

  /* public typedefs */
  //...

  /* public methods */
  void begin();
  void turnOff(bool leftButton = false, bool middleButton = false, bool rightButton = false);
  void handleAutoTurnOff(uint16_t seconds = DEFAULT_AUTO_TURN_OFF);
  bool isLeftButtonPressed();
  bool isMiddleButtonPressed();
  bool isRightButtonPressed();

  void setupAsIBeacon(String beaconName, HM11_SoftwareSerial0::advertInterval_t interv = HM11_SoftwareSerial0::INTERV_550MS);
  void setupAsIBeacon(uint16_t beaconNr, HM11_SoftwareSerial0::advertInterval_t interv = HM11_SoftwareSerial0::INTERV_550MS);
  int16_t findIBeacon(String beaconName);
  int16_t findIBeacon(uint16_t beaconNr);

  /* public members */
  MMA7660FC *accel;
  IS31FL3731 *matrix;
  SoftwareSerial0 *bleSerial;
  HM11_SoftwareSerial0 *ble;

private:
  /* attributes */
  //...

  /* private constants (static) */
  //...

  /* private variables */
  //...

  /* private methods */
  void initPins();
  void disableUnusedCpuFunctions();
  void initTimerIRQ(uint8_t timer_nr, uint16_t prescaler, uint16_t divisor);
  inline bool getLEDBlue();
  void iBeaconNameToIBeaconUUID(String beaconName, HM11_SoftwareSerial0::iBeaconData_t *iBeacon);

};

#endif
