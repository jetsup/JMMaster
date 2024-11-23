#pragma once

#include <IPAddress.h>

// Networking
#define JM_SSID ""
#define JM_PASSWORD ""

#define JM_HOST_NAME "threading"  // access/ping it on 'threading.local'
#define JM_IP_ADDRESS IPAddress(192, 168, 10, 10)
#define JM_GATEWAY IPAddress(192, 168, 10, 1)
#define JM_SUBNET IPAddress(255, 255, 255, 0)

// WebServer
#define JM_PORT 80
