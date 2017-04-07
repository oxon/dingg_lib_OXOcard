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
  delete accel;
  delete bleSerial;
  delete ble;
}

/* System methods */
/** ===========================================================
 * \fn      begin
 * \brief   initializes the OXOCard
 ============================================================== */
void OXOCard::begin()
{
  #ifdef DEBUG_OXOCARD
    Serial.begin(DEBUG_BAUDRATE_OXOCARD);
    DebugOXOCard_println("");
  #endif

  initPins();
  disableUnusedCpuFunctions();

  initTimerIRQ(1, 1024, 7812);   // interrupt every 1 Second

  /* init LED matrix */
  DebugOXOCard_println(F("init LED matrix"));
  matrix = new IS31FL3731(Wire, &P_EN_LED_DRIVER, EN_LED_DRIVER, 8, 8);
  matrix->begin();
  matrix->clear();
  //matrix->drawRectangle(0, 0, 8, 8, 255);

  /* init accelerometer */
  DebugOXOCard_println(F("init accelerometer"));
  accel = new MMA7660FC(Wire);
  accel->begin();

  /* init BLE */
  DebugOXOCard_println(F("init BLE"));
  bleSerial = new SoftwareSerial(PIN_NR_SW_RXD, PIN_NR_SW_TXD);
  ble = new HM11_SoftwareSerial(*bleSerial, &P_SW_RXD, SW_RXD, &P_SW_TXD, SW_TXD, &P_EN_BLE, EN_BLE, &P_RST_BLE, RST_BLE);
  delay(5);  // wait some time to charge the 22uF capacitor
  ble->begin(BAUDRATE_BLE);
}

/** ===========================================================
 * \fn      turnOff
 * \brief   turns off the device by putting it in a power down
 *          sleep-mode, it will wake up again if INTn occures
 *
 * \requ    <avr/interrupt.h> and <avr/sleep.h>
 ============================================================== */
void OXOCard::turnOff() {
  DebugOXOCard_println(F("turnOff"));

  /* check periphery state */
  bool isBlueLEDEnabled = getLEDBlue();

  /* disable periphery */
  matrix->end();
  accel->end();
  ble->disable();
  clearBit(P_PIEZO, PIEZO);
  setLEDBlue(LOW);
  setLEDRed(LOW);

  /* disable HW-Serial */
  Serial.flush();
  uint8_t ucsrb = UCSR0B;
  UCSR0B = 0;
  clearBit(P_RXD, RXD);  // necessary!

  delay(100);

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

  /* reenable HW-Serial */
  UCSR0B = ucsrb;
  setBit(P_RXD, RXD);

  /* reenable periphery */
  setLEDRed(HIGH);
  matrix->begin();
  accel->begin();
  ble->enable();
  if (isBlueLEDEnabled) setLEDBlue(HIGH);
}

/* BLE methods */
/** ===========================================================
 * \fn      setupAsIBeacon
 * \brief   setup the BLE module of the OXOCard as iBeacon
 *
 * \param   (uint)   beacon number (1... 65534)
 *          (struct) advertInterval
 * \return  -
 ============================================================== */
void OXOCard::setupAsIBeacon(uint16_t beacon_nr, HM11_SoftwareSerial::advertInterval_t interv)
{
  HM11_SoftwareSerial::iBeaconData_t iBeacon;
  iBeacon.name = BLE_NAME;
  iBeacon.uuid = BLE_UUID;
  iBeacon.marjor = BLE_MARJOR;
  iBeacon.minor = beacon_nr;
  iBeacon.interv = interv;
  ble->setupAsIBeacon(&iBeacon);
  setLEDBlue(HIGH);
}

/** ===========================================================
 * \fn      findIBeacon
 * \brief   find near iBeacon with given number
 *
 * \param   (uint) beacon number (1... 65534)
 * \return  (int)  txPower
 ============================================================== */
int16_t OXOCard::findIBeacon(uint16_t beacon_nr)
{
  static bool firstTime = true;
  int16_t txPower = 0;

  static HM11_SoftwareSerial::iBeaconData_t iBeacon;
  iBeacon.minor = beacon_nr;      // minor you wish to search for

  if (firstTime)
  {
    iBeacon.uuid = BLE_UUID;      // UUID you wish to search for
    iBeacon.marjor = BLE_MARJOR;  // marjor you wish to search for
    ble->setupAsIBeaconDetector();
    firstTime = false;
  }

  DebugOXOCard_println("detectIBeacon...");
  if (ble->detectIBeacon(&iBeacon))
  {
    setLEDBlue(HIGH);
    DebugOXOCard_print(F("iBeacon.accessAddress = ")); DebugOXOCard_println(iBeacon.accessAddress);
    DebugOXOCard_print(F("iBeacon.deviceAddress = ")); DebugOXOCard_println(iBeacon.deviceAddress);
    DebugOXOCard_print(F("iBeacon.marjor = ")); DebugOXOCard_println(iBeacon.marjor);
    DebugOXOCard_print(F("iBeacon.minor = ")); DebugOXOCard_println(iBeacon.minor);
    DebugOXOCard_print(F("iBeacon.txPower = ")); DebugOXOCard_println(iBeacon.txPower);
    txPower = iBeacon.txPower;
  }
  else
  {
    DebugOXOCard_println(F("I-Beacon not found"));
    setLEDBlue(LOW);
  }
  DebugOXOCard_println();

  return txPower;
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

/** ===========================================================
 * \fn      initTimerIRQ
 * \brief   initialize a timer in the Clear Timer on Compare
 *          Match (CTC) mode and enables its interrupt OCIEnA.
 *
 * \note    uC: ATtiny85, ATmega328P or ATmeag32U4
 *          implement: ISR (TIMERn_COMPA_vect)
 *          f_isr = ((fckl / prescaler) / (divisor + 1))
 *
 * \param   (byte) timer number (0, 1, 2, 3)
 *          (uint) prescaler value (1, 8, 64, 256, 1024)
 *          (uint) divisor value (0... 255 or 65535)
 * \return  -
 ============================================================== */
void OXOCard::initTimerIRQ(uint8_t timer_nr, uint16_t prescaler, uint16_t divisor)
{
  Serial.println(F("initTimerIRQ"));

  cli();
  switch (prescaler)
  {
    case 1:    prescaler = uint8_t(0x01); break;
    case 8:    prescaler = uint8_t(0x02); break;
    case 64:   prescaler = uint8_t(0x03); break;
    case 256:  prescaler = uint8_t(0x04); break;
    case 1024: prescaler = uint8_t(0x05); break;
    default:
      DebugOXOCard_println(F("invalid TIM prescaler!"));
      for(;;);
  }
  switch (timer_nr)
  {
    case 0: // 8bit Timer/Counter
      TCCR0A = 0x02;            // enable CTC (Clear Timer on Compare match) mode
      TCCR0B = prescaler;       // select prescaler mode
      clearBit(TCCR0B, WGM02);  // enable CTC (Clear Timer on Compare match) mode
      #ifdef TIMSK0
        setBit(TIMSK0, OCIE0A);   // enable interrupt (register A)
      #else
        setBit(TIMSK, OCIE0A);    // enable interrupt (register A)
      #endif
      OCR0A = uint8_t(divisor); // set output compare register A
      TCNT0 = 0;                // reset counter register
      break;
    case 1: // 16bit Timer/Counter
      #ifdef TCCR1B
        TCCR1A = 0x00;
        TCCR1B = (TCCR1B & ~0x07) | prescaler;
        setBit(TCCR1B, WGM12);
      #else
        TCCR1 = (TCCR1 & ~0x0F) | prescaler;
      #endif
      #ifdef TIMSK1
        setBit(TIMSK1, OCIE1A);   // enable interrupt (register A)
      #else
        setBit(TIMSK, OCIE1A);    // enable interrupt (register A)
      #endif
      #ifdef OCR1AH
        OCR1AH = (divisor & 0xFF00) >> 8;
        OCR1AL = divisor & 0xFF;
      #else
        OCR1A = uint8_t(divisor);
      #endif
      TCNT1 = 0;
      break;
    #ifdef TCCR2A
    case 2: // 8bit Timer/Counter
      TCCR2A = 0x02;
      TCCR2B = prescaler;
      clearBit(TCCR2B, WGM22);
      setBit(TIMSK2, OCIE2A);
      OCR2A = uint8_t(divisor);
      TCNT2 = 0;
      break;
    #endif
    #ifdef TCCR3A
    case 3: // 16bit Timer/Counter
      TCCR3A = 0x00;
      TCCR3B = prescaler;
      setBit(TCCR3B, WGM32);
      setBit(TIMSK3, OCIE3A);
      OCR3AH = (divisor & 0xFF00) >> 8;
      OCR3AL = divisor & 0xFF;
      TCNT3 = 0;
      break;
    #endif
    default:
      DebugOXOCard_println(F("invalid timer_nr!"));
      for(;;);
  }
  sei();
}

/** ===========================================================
 * \fn      getLEDBlue
 * \brief   returns current pin state
 *
 * \param   -
 * \return  (bool) pin state
 ============================================================== */
inline bool OXOCard::getLEDBlue()
{
  return !getBit(PIN_LED_BLUE, LED_BLUE);
}

/** ===========================================================
 * \fn      ISR (external interrupt INT1)
 * \brief   interrupt service routine (handler) for the wake-up-
 *          interrupt (INT1)
 *
 * \requ    <avr/sleep.h>
 *
 * \param   'INT1 vector'
 * \return  -
 ============================================================== */
ISR(INT1_vect)
{
  /* disable wake up interrupt INTn */
  clearBit(PCICR, PCIE2); // BUTTON 1
  clearBit(EIMSK, INT1);  // BUTTON 2
  clearBit(EIMSK, INT0);  // BUTTON 3

  sleep_disable();

  DebugOXOCard_println(F("wkUpInt2 occured, waking up..."));
}

/** ===========================================================
 * \fn      ISR (external interrupt INT0)
 * \brief   interrupt service routine (handler) for the wake-up-
 *          interrupt (INT0)
 *
 * \requ    <avr/sleep.h>
 *
 * \param   'INT0 vector'
 * \return  -
 ============================================================== */
ISR(INT0_vect)
{
  /* disable wake up interrupt INTn */
  clearBit(PCICR, PCIE2); // BUTTON 1
  clearBit(EIMSK, INT1);  // BUTTON 2
  clearBit(EIMSK, INT0);  // BUTTON 3

  /* disable sleep-mode */
  sleep_disable();

  DebugOXOCard_println("wkUpInt3 occured, waking up...");
}

/**
 * @}
 */
