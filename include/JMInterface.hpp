#pragma once

/**
 * Parse data from the serial port(server) and execute it or send it to the
 * other nodes
 */
#include <Arduino.h>

class Interface {
 private:
  HardwareSerial *iSerial;

  //   delete default constructor
  Interface() = delete;

 public:
  /**
   * Construct a new Interface object
   */
  Interface(HardwareSerial *serial);

  /**
   * Destroy the Interface object
   */
  ~Interface();
};
