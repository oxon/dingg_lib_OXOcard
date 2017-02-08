/**-----------------------------------------------------------------------------
 * \file    OXOCardRunner.h
 * \author  jh, tg
 * \date    xx.02.2017
 *
 * \version 1.0
 *
 * \brief   The OXOCardRunner is a ...
 *
 * @{
 -----------------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -----------------------*/
#ifndef OXOCARD_RUNNER_H_
#define OXOCARD_RUNNER_H_

/* Includes --------------------------------------------------- */
#include "OXOCard.h"

/* Defines -----------------------------------------------------*/
#define DEBUG_OXOCARD_RUNNER  //blup: define to activate Debug prints

/* Macros ----------------------------------------------------- */
#ifdef DEBUG_OXOCARD_RUNNER
  #define DebugOXOCardRunner_print(...)     Serial.print(__VA_ARGS__)
  #define DebugOXOCardRunner_println(...)   Serial.println(__VA_ARGS__)
#else
  #define DebugOXOCardRunner_print(...)
  #define DebugOXOCardRunner_println(...)
#endif

/* Object instantiations -------------------------------------- */
OXOCard globalOXOCard;

/* Functions -------------------------------------------------- */
void initOXOCard() {
  // #ifdef DEBUG_OXOCARD_RUNNER
  //   Serial.begin(DEBUG_BAUDRATE_OXOCARD_RUNNER);
  // #endif
  DebugOXOCardRunner_println(F("initOXOCard"));

  globalOXOCard.begin();

}

void displayImage(byte b1,
                  byte b2,
                  byte b3,
                  byte b4,
                  byte b5,
                  byte b6,
                  byte b7,
                  byte b8) {
  // TO DO
};

/*
byte image[8] {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000
};
*/

void displayImage(byte image[8]) {
  DebugOXOCardRunner_println(F("displayImage"));
  for (byte i =0;i<7;i++) {
    DebugOXOCardRunner_println(image[i]);
  }

  // TO DO
}

void setBrightness(byte value) {
  DebugOXOCardRunner_println(F("setBrightness"));
  // TO DO
}

void clearDisplay() {
  DebugOXOCardRunner_println(F("clearDisplay"));
  // TO DO
}

void turnDisplayOn() {
  DebugOXOCardRunner_println(F("turnDisplayOn"));
  // TO DO
}

inline bool isLeftButtonPressed() {
  return button1Pressed;
}

inline bool isMiddleButtonPressed() {
  return button2Pressed;
}

inline bool isRightButtonPressed() {
  return button3Pressed;
}

#endif

/**
 * @}
 */
