/**-----------------------------------------------------------------------------
 * \file    OXOCardRunner.h
 * \author  jh, tg
 * \date    xx.02.2017
 *
 * \version 1.0
 *
 * \brief   The OXOCardRunner is a set of simplified functions for
 *          programming

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
  globalOXOCard.begin();
}

/* ------------------------------------- */
void clearDisplay() {
   globalOXOCard.matrix->fillScreen(0);
}

/* ------------------------------------- */
void turnOff() {
   globalOXOCard.turnOff();
}



/* ------------------------------------- */
void turnDisplayOn() {
   globalOXOCard.matrix->fillScreen(255);
}


/* ------------------------------------- */
void fillDisplay(byte brightness=255) {
  globalOXOCard.matrix->fillScreen(brightness);
}


/* ------------------------------------- */
void drawPixel(byte x, byte y, byte brightness=255) {
  globalOXOCard.matrix->drawPixel(x,y,brightness);
}


/* ------------------------------------- */
void drawRectangle(byte x, byte y, byte l, byte h, byte b=255) {
  globalOXOCard.matrix->drawRectangle(x,y,l,h,b);
};


/* ------------------------------------- */
void drawFilledRectangle(byte x, byte y, byte l, byte h, byte b=255) {
  globalOXOCard.matrix->drawFilledRectangle(x,y,l,h,b);
};


/* ------------------------------------- */
void drawLine(byte x0, byte y0, byte x1, byte y1, byte b=255)
{
  globalOXOCard.matrix->drawLine(x0,y0,x1,y1,b);
};


/* ------------------------------------- */
void drawCircle(byte x0, byte y0, byte r, byte b=255)
{
  globalOXOCard.matrix->drawCircle(x0,y0,r,b);
};


/* ------------------------------------- */
void drawFilledCircle(byte x0, byte y0, byte r, byte b=255)
{
  globalOXOCard.matrix->drawFilledCircle(x0,y0,r,b);
};


/* ------------------------------------- */
void drawTriangle(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, byte b=255) {
  globalOXOCard.matrix->drawTriangle(x0,y0,x1,y1,x2,y2,b);
}


/* ------------------------------------- */
void drawFilledTriangle(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, byte b=255) {
  globalOXOCard.matrix->drawFilledTriangle(x0,y0,x1,y1,x2,y2,b);
}



/* ------------------------------------- */
void drawImage(byte image[8], byte brightness=255) {
  for (byte y =0;y<=7;y++) {
    byte b = image[y];
    for (byte x = 0;x<=7;x++) {
      if (b & (1 << (7-x))) {

        globalOXOCard.matrix->drawPixel(x,y,brightness);
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
  drawImage(image, brightness );
};



/* ------------------------------------- */
inline bool isLeftButtonPressed() {
  return button1Pressed;
}

/* ------------------------------------- */
inline bool isMiddleButtonPressed() {
  return button2Pressed;
}

/* ------------------------------------- */
inline bool isRightButtonPressed() {
  return button3Pressed;
}



#endif

/**
 * @}
 */
