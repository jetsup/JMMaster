#include <JMServer.hpp>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

String outputState(int output) {
  if (digitalRead(output)) {
    return "checked";
  } else {
    return "";
  }
}

// Replaces placeholder with button section in your web page
String processor(const String &var) {
  // Serial.println(var);
  if (var == "BUTTONPLACEHOLDER") {
    String buttons = "";
    buttons +=
        "<h4>Output - GPIO 2</h4><label class=\"switch\"><input "
        "type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " +
        outputState(2) + "><span class=\"slider\"></span></label>";
    buttons +=
        "<h4>Output - GPIO 4</h4><label class=\"switch\"><input "
        "type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"4\" " +
        outputState(4) + "><span class=\"slider\"></span></label>";
    buttons +=
        "<h4>Output - GPIO 33</h4><label class=\"switch\"><input "
        "type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"33\" " +
        outputState(33) + "><span class=\"slider\"></span></label>";
    return buttons;
  }
  return String();
}

//
void apiControlAppliances(AsyncWebServerRequest *request, uint8_t *data,
                          size_t len, size_t index, size_t total) {
  ArduinoJson::JsonDocument doc;
  ArduinoJson::DeserializationError error = deserializeJson(doc, data, len);

  DEBUG_PRINTF("Data: %s\n", data);

  if (error) {
    request->send(400, "text/plain", "Invalid JSON body");
    return;
  }

  String rawAppliances = doc["appliances"];  // eg. "1,2,3"
  String rawValues = doc["values"];          // eg. "1,0,1"
  String rawIsDigital = doc["signals"];      // eg. "1,0,1"

  std::vector<String> applianceControlPins = splitStr(rawAppliances, ",");
  std::vector<String> applianceValues = splitStr(rawValues, ",");
  std::vector<String> applianceSignals = splitStr(rawIsDigital, ",");

  int boardPins[applianceControlPins.size()];
  int writeValues[applianceValues.size()];
  int isDigital[applianceSignals.size()];

  for (int i = 0; i < applianceControlPins.size(); i++) {
    // Validate pin and state
    if (applianceControlPins.at(i).toInt() != 2 &&
        applianceControlPins.at(i).toInt() != 4 &&
        applianceControlPins.at(i).toInt() != 33) {
      DEBUG_PRINTF("Invalid pin number: %d\n",
                   applianceControlPins.at(i).toInt());

      request->send(400, "text/plain",
                    "Invalid pin number: '" + applianceControlPins.at(i) + "'");
      return;
    }
    if (applianceValues.at(i).toInt() != 0 &&
        applianceValues.at(i).toInt() != 1) {
      DEBUG_PRINTF("Invalid state value: %d\n", applianceValues.at(i).toInt());
      request->send(400, "text/plain",
                    "Invalid state value: '" + applianceValues.at(i) + "'");
      return;
    }

    boardPins[i] = applianceControlPins.at(i).toInt();
    writeValues[i] = applianceValues.at(i).toInt();
    isDigital[i] = applianceSignals.at(i).toInt();
  }

  for (int i = 0; i < applianceControlPins.size(); i++) {
    // Update appliance values
    if (isDigital[i] == 1) {
      digitalWrite(boardPins[i], writeValues[i]);
    } else if (isDigital[i] == 0) {
      analogWrite(boardPins[i], writeValues[i]);
    }
  }

  request->send(200, "text/plain", "OK");
}

void apiControlAppliance(AsyncWebServerRequest *request, uint8_t *data,
                         size_t len, size_t index, size_t total) {
  ArduinoJson::JsonDocument doc;
  ArduinoJson::DeserializationError error = deserializeJson(doc, data, len);

  DEBUG_PRINTF("Len: '%d' Data: '%s'\n", len, data);

  if (error) {
    request->send(400, "text/plain", "Invalid JSON body");
    return;
  }

  String strAppliance = doc["appliance"];
  String strValue = doc["value"];
  String strIsDigital = doc["signal"];

  int appliance = strAppliance.toInt();
  int value = strValue.toInt();
  int isDigital = strIsDigital.toInt();

  DEBUG_PRINTF("A: '%d' V: '%d' D: '%d'\n", appliance, value, isDigital);

  if (isDigital == 1) {
    digitalWrite(appliance, value);
  } else if (isDigital == 0) {
    analogWrite(appliance, value);
  }

  DEBUG_PRINTLN("Sending response");
  request->send(200, "text/plain", "OK");
}

void sendSystemStats(AsyncWebServerRequest *request) {
  // Update logic
  ArduinoJson::JsonDocument doc;

  doc["led2"] = digitalRead(2);
  doc["led4"] = digitalRead(4);
  doc["led33"] = digitalRead(33);

  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}
