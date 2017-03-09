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
  DDRB =  0b00000010; // SW-TXD (must be defined as output!)
  PORTB = 0b00111000; // L

  /* Port C */
  DDRC =  0b00000111; // EN_LED_DRIVER, !BLUE,  !RED
  PORTC = 0b00000010; // L            , H    ,  L

  /* Port D */
  setBit(P_EN_BLE, EN_BLE);
  DDRD =  0b11100000; // PIEZO, !RST_BLE, !EN_BLE
  PORTD = 0b00111101; // L    , L       , H
}



/** ===========================================================
 * \fn      turnOff
 * \brief   turns off the device by putting it in a power down
 *          sleep-mode, it will wake up again if INTn occures
 *
 * \requ    <avr/interrupt.h> and <avr/sleep.h>
 ============================================================== */
void OXOCard::turnOff() {
  /* disable periphery */
  matrix->disableHW(); //Matrix.end();
//  Accel.end();
//  BLE.disable();  //BLE.end();
  clearBit(P_PIEZO, PIEZO);
  setLEDBlue(LOW);
  setLEDRed(LOW);
  delay(200);

  /* all interrupts have to be disabled during turn off configurations */
  cli();

  /* define that a low-level of INTn generates an interrupt request */
  clearBit(EICRA, ISC11); clearBit(EICRA, ISC10); // INT1
  //clearBit(EICRA, ISC01); clearBit(EICRA, ISC00); // INT0

  /* clear the interrupt flags */
  //setBit(PCIFR, PCIF2);
  setBit(EIFR, INTF1);
  //setBit(EIFR, INTF0);

  /* enable external interrupt INTn (to wake up later) */
  //setBit(PCICR, PCIE2); // BUTTON 1
  setBit(EIMSK, INT1);  // BUTTON 2
  //setBit(EIMSK, INT0);  // BUTTON 3

//  /* disable other interrupts */
//  clearBit(TIMSK2, OCIE2A);

  /* choose "Power-down" sleep mode */
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  /* enable sleep-mode */
  sleep_enable();

  /* reenable interrupts */
  sei();

  /* system actually sleeps here */
  sleep_cpu();

  /* zzzZZZzzzZZZ... */

  /* INTn occured (button click) -> wakes up! system continues here... */

//  /* reenable other interrupts */
//  setBit(TIMSK2, OCIE2A);

  /* reenable periphery */
  matrix->enableHW(); //Matrix.begin();
  //Accel.begin();
  //BLE.enable();  //BLE.begin();
  clearBit(P_PIEZO, PIEZO);
  setLEDBlue(LOW);
  setLEDRed(LOW);
  setLEDRed(HIGH);



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
