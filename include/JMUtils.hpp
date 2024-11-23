#pragma once

#include <Arduino.h>

#include <vector>

/**
 * @brief Split a string into a vector of strings
 * @param str The string to split
 * @param delimiter The delimiter to split the string
 * @return A vector of strings
 */
std::vector<String> splitStr(const String& str, const char* delimiter);
