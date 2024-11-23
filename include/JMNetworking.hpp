#pragma once

#include <Arduino.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <strings.h>

#include <JMConfig.hpp>
#include <JMCredentials.hpp>
#include <JMEnums.hpp>

class Networking {
 private:
  String ssid = JM_SSID;
  String password = JM_PASSWORD;

  String hostname = JM_HOST_NAME;
  IPAddress ipAddress = JM_IP_ADDRESS;
  IPAddress gateway = JM_GATEWAY;
  IPAddress subnet = JM_SUBNET;

  bool isConnected = false;
  NetworkStatus networkStatus = NetworkStatus::DISCONNECTED;

  int previousRetryTime = 0;

 public:
  /**
   * Construct a new Networking object
   * @param ssid The ssid of the network to connect to
   * @param password The password of the network to connect to
   * @param ipAddress The IP address of the device
   * @param gateway The gateway of the network
   * @param subnet The subnet of the network
   */
  Networking(String ssid = JM_SSID, String password = JM_PASSWORD);

  /**
   * Destroy the Networking object
   */
  ~Networking();

  /**
   * Connect to the network using the already set ssid and password
   */
  void connect();

  /**
   * Try to reconnect to the network
   * @param retryTimeout Time before trying to connect to the network [in ms]
   */
  void reconnect(int retryTimeout = WIFI_RECONNECTION_TIMEOUT);

  /**
   * Disconnect from the network
   */
  void disconnect();

  /**
   * Check if the device is connected to the network
   * @return true if connected, false otherwise
   */
  bool isConnectedToNetwork();

  /*setters*/
  /**
   * Set the ssid of the network to connect to
   * @param ssid The ssid of the network
   */
  void setSsid(String ssid);

  /**
   * Set the password of the network to connect to
   * @param password The password of the network
   */
  void setPassword(String password);

  /**
   * Set the network status
   * @param status The new network status
   */
  void setNetworkStatus(NetworkStatus status);

  /*getters*/
  /**
   * Get the ssid of the connected network
   * @return The ssid of the network
   */
  String getSSID();

  /**
   * Get the password of the connected network
   * @return The password of the network
   */
  String getPassword();

  /**
   * Get the IP address of the device
   * @return The IP address of the device
   */
  IPAddress getIpAddress();

  /**
   * Get the network status
   * @return The network status
   */
  NetworkStatus getNetworkStatus();
};
