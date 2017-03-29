/* Define to prevent recursive inclusion -----------------------*/
#ifndef GLOBALS_H_
#define GLOBALS_H_

/* General defines -------------------------------------------- */
#ifndef FOREVER
  #define FOREVER            ;;
#endif

/* PIN definitions -------------------------------------------- */
// PINx  -> to read input
// PORTx -> to set output
#define PB7_              7  // PB7
#define P_PB7_            PORTB
#define PIN_PB7_          PINB
#define PB6_              6  // PB6
#define P_PB6_            PORTB
#define PIN_PB6_          PINB
#define SCK               5  // PB5
#define P_SCK             PORTB
#define PIN_SCK           PINB
#define MISO              4  // PB4
#define P_MISO            PORTB
#define PIN_MISO          PINB
#define MOSI              3  // PB3
#define P_MOSI            PORTB
#define PIN_MOSI          PINB
#define INT               2  // PB2
#define P_INT             PORTB
#define PIN_INT           PINB
#define SW_TXD            1  // PB1
#define P_SW_TXD          PORTB
#define PIN_SW_TXD        PINB
#define PIN_NR_SW_TXD     9  // Arduino D9
#define SW_RXD            0  // PB0
#define P_SW_RXD          PORTB
#define PIN_SW_RXD        PINB
#define PIN_NR_SW_RXD     8  // Arduino D8

#define SCL               5  // PC5
#define P_SCL             PORTC
#define PIN_SCL           PINC
#define SDA               4  // PC4
#define P_SDA             PORTC
#define PIN_SDA           PINC
#define INTB              3  // PC3
#define P_INTB            PORTC
#define PIN_INTB          PINC
#define EN_LED_DRIVER     2  // PC2
#define P_EN_LED_DRIVER   PORTC
#define PIN_EN_LED_DRIVER PINC
#define LED_BLUE          1  // PC1
#define P_LED_BLUE        PORTC
#define PIN_LED_BLUE      PINC
#define LED_RED           0  // PC0
#define P_LED_RED         PORTC
#define PIN_LED_RED       PINC

#define PIEZO             7  // PD7
#define P_PIEZO           PORTD
#define PIN_PIEZO         PIND
#define PIN_NR_PIEZO      7  // Arduino D7
#define RST_BLE           6  // PD6
#define P_RST_BLE         PORTD
#define PIN_RST_BLE       PIND
#define EN_BLE            5  // PD5
#define P_EN_BLE          PORTD
#define PIN_EN_BLE        PIND
#define BUTTON1           4  // PD4
#define P_BUTTON1         PORTD
#define PIN_BUTTON1       PIND
#define BUTTON2           3  // PD3
#define P_BUTTON2         PORTD
#define PIN_BUTTON2       PIND
#define BUTTON3           2  // PD2
#define P_BUTTON3         PORTD
#define PIN_BUTTON3       PIND
#define TXD               1  // PD1
#define P_TXD             PORTD
#define PIN_TXD           PIND
#define RXD               0  // PD0
#define P_RXD             PORTD
#define PIN_RXD           PIND

/* Makros ----------------------------------------------------- */
/* port manipulation makros */
#ifndef clearBit
#define clearBit(reg, bit) (_SFR_BYTE(reg) &= ~_BV(bit))
#endif
#ifndef setBit
#define setBit(reg, bit) (_SFR_BYTE(reg) |= _BV(bit))
#endif
#ifndef toggleBit
#define toggleBit(reg, bit) (_SFR_BYTE(reg) ^= _BV(bit))
#endif
#ifndef getBit
#define getBit(reg, bit) ((_SFR_BYTE(reg) & _BV(bit)) != 0)
#endif

/* button makros */
#define button1Pressed (!getBit(PIN_BUTTON1, BUTTON1))
#define button2Pressed (!getBit(PIN_BUTTON2, BUTTON2))
#define button3Pressed (!getBit(PIN_BUTTON3, BUTTON3))

/* LED makros */
#define setLEDRed(on)  (bool(on) ? clearBit(P_LED_RED, LED_RED) : setBit(P_LED_RED, LED_RED))       // low active!
#define setLEDBlue(on) (bool(on) ? clearBit(P_LED_BLUE, LED_BLUE) : setBit(P_LED_BLUE, LED_BLUE))   // low active!

#endif
