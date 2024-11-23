#include <JMMain.hpp>

TaskHandle_t Task1;
TaskHandle_t Task2;
Networking network;
AsyncWebServer server(JM_PORT);

const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

void setup() {
  if (DEBUG) {
    Serial.begin(115200);
    DEBUG_PRINTLN("Serial started");
  }

  //
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(33, OUTPUT);
  digitalWrite(33, LOW);
  //

  network.connect();

  xTaskCreatePinnedToCore(monitoringTask, "L1", 10000, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore(executorTask, "L2", 10000, NULL, 1, &Task2, 1);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to
  // <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [](AsyncWebServerRequest* request) {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on
    // <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    } else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });

  // Start server
  server.begin();
}

void loop() {}
