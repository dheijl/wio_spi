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
  // put your main code here, to run repeatedly:
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
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(1);
  tft_println("SPI initialised");
  delay(500);
  while (digitalRead(WIO_KEY_B) == HIGH)
  {
    delay(1);
  }
  tft_clear();
}