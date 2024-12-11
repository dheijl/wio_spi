#include <Arduino.h>

#include <SPI.h>

#include "debug.h"
#include <tft_functions.h>
#include <battery.h>

// put function declarations here:
int myFunction(int, int);
void setup_debug();

void setup()
{
  setup_debug();

  Serial.println("SPI setup");
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(1);
  Serial.println("SPI initialised");

  // initialize tft
  init_tft();
  tft_clear();
  // initialize battery
  init_battery();
  printBatteryStats();
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
