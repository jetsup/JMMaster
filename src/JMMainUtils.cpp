#include <JMMain.hpp>

void monitoringTask(void *pvParameters) {
  unsigned long prevLogTime = millis();
  DEBUG_PRINTF("Millis: %ld\n", prevLogTime);

  while (true) {
    if (network.isConnectedToNetwork() &&
        (network.getNetworkStatus() != NetworkStatus::CONNECTED)) {
      network.getIpAddress();
      DEBUG_PRINTLN("Connected");
      network.setNetworkStatus(NetworkStatus::CONNECTED);
    } else if (!network.isConnectedToNetwork() &&
               (network.getNetworkStatus() == NetworkStatus::DISCONNECTED)) {
      DEBUG_PRINTLN("Not connected to network");
    }

    network.reconnect(5000);
    delay(10);
  }
}

void executorTask(void *pvParameters) {
  long counter = 0;
  while (true) {
  }
}
