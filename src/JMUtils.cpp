#include <JMUtils.hpp>
#include <string>

std::vector<String> splitStr(const String& str, const char* delimiter) {
  std::vector<String> tokens;
  String temp = str;
  int pos = 0;

  while ((pos = temp.indexOf(delimiter)) != -1) {
    tokens.push_back(temp.substring(0, pos));
    temp = temp.substring(pos + strlen(delimiter));
  }

  if (temp.length() > 0) {
    tokens.push_back(temp);
  }

  return tokens;
}
