#pragma once
#include <Arduino.h>

#define DEBUG
// #undef DEBUG

#ifdef DEBUG
#define DPRINT(x) Serial.println(x)
#endif
