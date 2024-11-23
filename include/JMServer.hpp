#pragma once

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <ArduinoJson.hpp>
#include <JMConfig.hpp>
#include <JMCredentials.hpp>
#include <JMUtils.hpp>

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

/**
 * @brief Control more than one appliances using a single POST request
 * @param request The request object
 * @param data The data to send
 * @param len The length of the data
 * @param index The index of the data
 * @param total The total length of the data
 * @note This function accepts data in the format `{"appliances":
 * "A1,A2,...An","value": "V1,V2,...Vn","is_digital": "D1,D2,...D3"}`
 */
void apiControlAppliances(AsyncWebServerRequest *request, uint8_t *data,
                          size_t len, size_t index, size_t total);

/**
 * @brief Control the appliance by sending a POST request
 * @param request The request object
 * @param data The data to send
 * @param len The length of the data
 * @param index The index of the data
 * @param total The total length of the data
 * @note This function accepts data in the format `{"appliance":
 * "PIN_NUMBER","value": "VALUE","is_digital": "1/0"}`
 */
void apiControlAppliance(AsyncWebServerRequest *request, uint8_t *data,
                         size_t len, size_t index, size_t total);

void sendSystemStats(AsyncWebServerRequest *request);
