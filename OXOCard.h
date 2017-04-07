/**-----------------------------------------------------------------------------
 * \file    OXOCard.h
 * \author  jh, tg
 * \date    xx.03.2017
 *
 * \version 1.0
 *
 * \brief   The OXOCard is a board for kids to learn programming with Arduino
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
#include <SoftwareSerial.h>
#include <MMA7660FC.h>
#include <IS31FL3731.h>
#include <HM11_SoftwareSerial.h>
#include "globals.h"
#include "pitches.h"

/* Defines -----------------------------------------------------*/
#define DEBUG_OXOCARD  // define to activate Debug prints
#define DEBUG_BAUDRATE_OXOCARD    115200

#define DEFAULT_AUTO_TURN_OFF     120          // in seconds

#define BAUDRATE_BLE              9600//19200  // in baud
#define BLE_NAME                  "OXOCard"
#define BLE_UUID                  "9123456789123456"
#define BLE_MARJOR                20

/* Macros ----------------------------------------------------- */
#ifdef DEBUG_OXOCARD
  #define DebugOXOCard_print(...)     Serial.print(__VA_ARGS__)
  #define DebugOXOCard_println(...)   Serial.println(__VA_ARGS__)
#else
  #define DebugOXOCard_print(...)
  #define DebugOXOCard_println(...)
#endif

/* Class ------------------------------------------------------ */
class OXOCard
{
public:
  /* constructor(s) & deconstructor */
  OXOCard();
  ~OXOCard();

  /* public enumerations */
  //...

  /* public typedefs */
  //...

  /* public methods */
  void begin();
  void turnOff();

  void setupAsIBeacon(uint16_t beacon_nr, HM11_SoftwareSerial::advertInterval_t interv = HM11_SoftwareSerial::INTERV_550MS);
  int16_t findIBeacon(uint16_t beacon_nr);

  /* public members */
  MMA7660FC *accel;
  IS31FL3731 *matrix;
  SoftwareSerial *bleSerial;
  HM11_SoftwareSerial *ble;

private:
  /* attributes */
  //...

  /* private constants (static) */
  //...

  /* private variables */


  /* private methods */
  void initPins();
  void disableUnusedCpuFunctions();
  void initTimerIRQ(uint8_t timer_nr, uint16_t prescaler, uint16_t divisor);
  inline bool getLEDBlue();

};

#endif

/**
 * @}
 */
