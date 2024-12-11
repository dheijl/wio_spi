#include <Arduino.h>

#include <SPI.h>

#include "debug.h"
#include <tft_functions.h>
#include <battery.h>
#include "buttons.h"

// put function declarations here:
int myFunction(int, int);
void setup_debug();
void setup_spi();

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

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}

void setup_debug()
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

void setup_spi()
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
  }
  tft_clear();
}