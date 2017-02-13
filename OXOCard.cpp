/**-----------------------------------------------------------------------------
 * \file    OXOCard.cpp
 * \author  jh, tg
 * \date    xx.02.2017
 * @{
 -----------------------------------------------------------------------------*/

/* Includes --------------------------------------------------- */
#include "OXOCard.h"

/* Public ----------------------------------------------------- */
OXOCard::OXOCard()
{
}

OXOCard::~OXOCard()
{
  delete matrix;
}

void OXOCard::begin()
{
  // #ifdef DEBUG_OXOCARD
  //   Serial.begin(DEBUG_BAUDRATE_OXOCARD);
  // #endif

  initPins();
  disableUnusedCpuFunctions();
  setLEDRed(HIGH);

  matrix = new IS31FL3731(Wire, &P_EN_LED_DRIVER, EN_LED_DRIVER, 8, 8);

  matrix->begin();
  matrix->clear();
  //matrix->drawRectangle(0, 0, 8, 8, 255);
}


/* Private ---------------------------------------------------- */
/** ===========================================================
 * \fn      initPins
 * \brief   initializes used I/Os of the uC
 ============================================================== */
void OXOCard::initPins()
{
  DebugOXOCard_println(F("initPins"));

  /* Port B */
  DDRB =  0b00000011; // PIEZO, !RST_BLE
  PORTB = 0b00111100; // L    , L

  /* Port C */
  DDRC =  0b00000111; // EN_LED_DRIVER, !BLUE,  !RED
  PORTC = 0b00000010; // L            , H    ,  L

  /* Port D */
  //DDRD =  0b10000000; // !EN_BLE
  //PORTD = 0b10011100; // H
  DDRD = 0;           //blup: DDRD have to be 0 or Serial doesn't work any more...
  PORTD = 0b00011100;
}

/** ===========================================================
 * \fn      disableUnusedCpuFunctions
 * \brief   disables unused cpu-functions to reduce power
 *          consumption
 *
 * \note    uC: ATmega328P
 ============================================================== */
void OXOCard::disableUnusedCpuFunctions()
{
  DebugOXOCard_println(F("disableUnusedCpuFunctions"));

  setBit(ACSR, ACD);        // disable ACD
  clearBit(ADCSRA, ADEN);   // disable ADC

  /* set Power Reduction Register */
  setBit(PRR, PRADC);      // disable ADC
  //setBit(PRR, PRUSART0);    // disable USART0 -> used to debug
  setBit(PRR, PRSPI);      // disable SPI
  //setBit(PRR, PRTIM0);     // disable TIM0    -> used by the Arduino delay()-functions
  //setBit(PRR, PRTIM1);     // disable TIM1    -> used for automatic turnOff
  //setBit(PRR, PRTIM2);     // disable TIM2    -> used by the tone()-functions
  //setBit(PRR, PRTWI);      // disable TWI     -> used to control accelerometer and the LED matrix
}

/**
 * @}
 */
