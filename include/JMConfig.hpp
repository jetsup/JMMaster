#pragma once

#include <Arduino.h>

#define DEBUG true

#define DEBUG_PRINT(x) if (DEBUG) Serial.print(x)

#define DEBUG_PRINTLN(x) if (DEBUG) Serial.println(x)

#define DEBUG_PRINTF(format, ...) if (DEBUG) Serial.printf(format, __VA_ARGS__)
