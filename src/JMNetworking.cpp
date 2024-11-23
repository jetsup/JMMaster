#include <JMNetworking.hpp>

Networking::Networking(String ssid, String password) {
  this->ssid = ssid;
  this->password = password;

  this->networkStatus = NetworkStatus::DISCONNECTED;
}

Networking::~Networking() {}

// network methods
void Networking::connect() {
  WiFi.begin(ssid.c_str(), password.c_str());

  mdns_init();
  mdns_hostname_set(hostname.c_str());
  mdns_instance_name_set(hostname.c_str());

  networkStatus = NetworkStatus::CONNECTING;
  DEBUG_PRINTF("Connecting to '%s'['%s']\n", ssid.c_str(), password.c_str());
}

void Networking::disconnect() {
  WiFi.disconnect();
  networkStatus = NetworkStatus::DISCONNECTED;
  DEBUG_PRINTLN("Disconnected from network");
}

bool Networking::isConnectedToNetwork() {
  bool status = WiFi.status() == WL_CONNECTED;
  if (status && networkStatus != NetworkStatus::CONNECTED) {
    networkStatus = NetworkStatus::CONNECTED;
    ipAddress = WiFi.localIP();
    gateway = WiFi.gatewayIP();
    subnet = WiFi.subnetMask();
  } else if (!status && networkStatus == NetworkStatus::CONNECTED) {
    networkStatus = NetworkStatus::DISCONNECTED;
  }
  return status;
}

//   setters
void Networking::setSsid(String ssid) {
  this->ssid = ssid;
  DEBUG_PRINTF("SSID: '%s'\n", ssid.c_str());
}

void Networking::setPassword(String password) {
  this->password = password;
  DEBUG_PRINTF("Password: '%s'\n", password.c_str());
}

//   getters
String Networking::getSSID() {
  DEBUG_PRINTF("SSID: '%s'\n", ssid.c_str());
  return ssid;
}

String Networking::getPassword() {
  DEBUG_PRINTF("Password: '%s'\n", password.c_str());
  return password;
}

IPAddress Networking::getIpAddress() {
  if (networkStatus == NetworkStatus::DISCONNECTED) {
    return INADDR_NONE;
  }

  DEBUG_PRINTF("IP: '%s' Gateway: '%s' Subnet: '%s'\n",
               ipAddress.toString().c_str(), gateway.toString().c_str(),
               subnet.toString().c_str());
  return ipAddress;
}

NetworkStatus Networking::getNetworkStatus() { return networkStatus; }

void Networking::setNetworkStatus(NetworkStatus status) {
  this->networkStatus = status;
  DEBUG_PRINTF(
      "Network Status: '%s'\n",
      networkStatus == NetworkStatus::CONNECTED ? "Connected" : "Disconnected");
}
