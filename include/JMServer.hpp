#pragma once

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <JMCredentials.hpp>

extern AsyncWebServer server;

extern const char index_html[] PROGMEM;

/**
 * @brief Check the state of the output
 * @param output The output pin to check
 * @return "checked" if the output is high, "" otherwise
 */
String outputState(int output);

/**
 * @brief Replaces placeholder with button section in your web page
 * @param var The variable to replace
 * @return The replaced variable
 */
String processor(const String &var);
