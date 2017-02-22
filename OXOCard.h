/**-----------------------------------------------------------------------------
 * \file    OXOCard.h
 * \author  jh, tg
 * \date    xx.02.2017
 *
 * \version 1.0
 *
 * \brief   The OXOCard is a ...
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
#include <MMA7660FC.h>
#include <SoftwareSerial.h>
#include <IS31FL3731.h>
#include <BLE_HM11.h>
#include "globals.h"

/* Defines -----------------------------------------------------*/
#define DEBUG_OXOCARD  //blup: define to activate Debug prints
#define DEBUG_BAUDRATE_OXOCARD  115200

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

  /* public members */
  IS31FL3731 *matrix;

private:
  /* attributes */
  //...

  /* private constants (static) */
  //...

  /* private variables */


  /* private methods */
  void initPins();
  void disableUnusedCpuFunctions();

};

#endif

/**
 * @}
 */
