#include <Arduino.h>

#include <SPI.h>

#include "debug.h"

// put function declarations here:
int myFunction(int, int);
void setup_debug();

void setup()
{
  setup_debug();
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
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
