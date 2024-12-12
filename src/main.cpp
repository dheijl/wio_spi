#include <Arduino.h>

#include <SPI.h>

#include "debug.h"
#include <tft_functions.h>
#include <battery.h>
#include "buttons.h"

// for documentation
const auto spi_ss = PIN_SPI_SS;     // (50ul) = BCM24 = pin 18 on wio breakout
const auto spi_mosi = PIN_SPI_MOSI; // (48ul) = BCM10 = pin 19 on wio breakout
const auto spi_miso = PIN_SPI_MISO; // (47ul) = BCM9  = pin 21 on wio breakout
const auto spi_sck = PIN_SPI_SCK;   // (49ul) = BCM11 = pin 23 on wio breakout

// local function declarations here:
static void setup_debug();
static void setup_spi();
static void print_hex(uint8_t x);

void setup()
{
  setup_debug();
  // buttons
  init_buttons();
  // initialize tft
  init_tft();
  tft_clear();
  // initialize battery
  init_battery();
  printBatteryStats();
  // initialize spi
  setup_spi();
}

void loop()
{

  unsigned char txbuf[64];
  memset(txbuf, 0xff, sizeof(txbuf));
  unsigned char rxbuf[64];
  memset(rxbuf, 0xff, sizeof(rxbuf));
  txbuf[0] = '?';
  txbuf[1] = 0;
  size_t count = 2;

  tft_println("Start SPI");
  digitalWrite(PIN_SPI_SS, LOW);
  SPI.beginTransaction(SPISettings((int)12000000, MSBFIRST, (uint8_t)SPI_MODE0));

  // TXBUF != NULL => write and read simultaneously
  // TXBUF == NULL => read only
  SPI.transfer(txbuf, NULL, count, false);
  SPI.waitForTransfer();
  SPI.endTransaction();
  digitalWrite(PIN_SPI_SS, HIGH);
  tft_println("SPI complete");
#ifdef DEBUG
  for (size_t i = 0; i < sizeof(rxbuf); i++)
  {
    print_hex(rxbuf[i]);
  }
  Serial.println();
  for (size_t i = 0; i < sizeof(txbuf); i++)
  {
    print_hex(txbuf[i]);
  }
  Serial.println();
#endif
}

static void print_hex(uint8_t x)
{
  if (x < 16)
  {
    Serial.print('0');
  }
  Serial.print(x, HEX);
}

static void setup_debug()
{
#ifdef DEBUG
  Serial.begin(115200);
  int n = 250;
  while (!Serial && n-- > 0)
  {
    delay(1);
  }
  delay(100);
#endif
}

static void setup_spi()
{
  tft_println("SPI setup");
  SPI.begin();
  /*
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(1);
  */
  tft_println("SPI initialised");
  delay(500);
  while (digitalRead(WIO_KEY_B) == HIGH)
  {
    delay(1);
  }
  tft_clear();
}